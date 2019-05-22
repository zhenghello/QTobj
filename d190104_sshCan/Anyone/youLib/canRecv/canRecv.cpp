#include "canRecv.h"
#include "ui_canRecv.h"

canRecv::canRecv(QWidget *parent, QString titleName) :QWidget(parent),ui(new Ui::canRecv)
{
    ui->setupUi(this);
    setWindowTitle(titleName);
    dat_config_load();

    // Tree�����ݿ�
    treeOredr = new FtreeDabeBase(this,"canResolverLib");
    treeOredr->setMinimumHeight(300);
    ui->tab_tree->layout()->addWidget(treeOredr);
    ui->label_order->deleteLater();
    // SSH�Ķ˿�
    sshPort = new FsshGui(this,"canRecvSSH");
    sshPort->setMinimumHeight(300);
    ui->tab_ssh->layout()->addWidget(sshPort);
    ui->label_ssh->deleteLater();
    // ��ʼ������
    initTreeDate();
    connect(treeOredr,SIGNAL(reloadExcelFinish()),this,SLOT(initTreeDate()));
    // ��������,��SSH���ź� תȥ ���ͺ���������������ʾ������
    connect(sshPort,SIGNAL(revMsg(QString))          ,this, SLOT(explain(QString)));
    connect(sshPort,SIGNAL(connectSuccess())         ,this, SLOT(showSshOpenMsg()));        // ���ӳɹ��ź�
    connect(sshPort,SIGNAL(connectFailure())         ,this, SLOT(showSshCloseMsg()));       // ����ʧ���ź�

    // CAN����������
    canFilter = new FcanShow(this);
    QVBoxLayout *vbl = qobject_cast<QVBoxLayout*>(ui->tab_base->layout());  // �ŵ�����Χ
    vbl->addWidget(canFilter);
    connect(canFilter,SIGNAL(clearMyShow())             ,myShow,SLOT(clear()));                 // �����ʾ
    connect(canFilter,SIGNAL(needTranslate(QStringList)),this,SLOT(translate(QStringList)));    // ��������
    canFilter->hide();

    //����ʾ��
    ui->tab_base->show();

}

canRecv::~canRecv()
{
    dat_config_save();
    delete ui;
}

// ****************************************************** can֡�Ľ��� **************************************************************** begin
void canRecv::initTreeDate(void)
{
    // 0.��ȡcan����������ַ
    mTree = treeOredr->mainTree();

    // 1.У�顰ID���󡱴���
    idAddr = findKeyTopTree(mTree,0,QString::fromLocal8Bit("ID����"));
    if(idAddr == NULL)
    {
        QMessageBox::warning(NULL, QString::fromLocal8Bit("����"),QString::fromLocal8Bit("ID���� ����"));
    }
    // 2.У�顰�������ࡱ����
    ctrCodeAddr = findKeyTopTree(mTree,0,QString::fromLocal8Bit("��������"));
    if(ctrCodeAddr == NULL)
    {
        QMessageBox::warning(NULL, QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�������� ����"));
    }
    // 3.У�顰�������ࡱ����
    orderCodeAddr = findKeyTopTree(mTree,0,QString::fromLocal8Bit("��������"));
    if(orderCodeAddr == NULL)
    {
        QMessageBox::warning(NULL, QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�������� ����"));
    }
    // 4.У�顰�������ࡱ����
    errCodeAddr = findKeyTopTree(mTree,0,QString::fromLocal8Bit("��������"));
    if(errCodeAddr == NULL)
    {
        QMessageBox::warning(NULL, QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�������� ����"));
    }
    // ��ʼ����־λ
    canSign = 0;
    reQuestNum = 0;
}


// ����һ��can֡���ݣ��磺<0x00800000> [8] aa d4 03 01 00 00 d8 55
// ת��������ɲ���У��õ����ݣ�ǰ��λ��Դ��Ŀ�� ��ID
bool canRecv::explain(QString str)
{
  // �ط��жϷ��� �յ� read: Network is down ��Ҫ�ط�,����Ϣ�ط���ȥ
  if(str.trimmed() == "read: Network is down")
  {
    //emit candumpIsDown();
    myShow->setTextStyle(QString("candump is close"),Qt::red,Qt::white,16);   // can����
    return true;
  }
  //myShow->setText(str); // ������
  //1.�ж�������Ч�ԣ���0���ǡ�<��,��11���ǡ�>��,��13�ǡ�[������15���ǡ�]��
  if(str.size()<16)  return false;
  if(str.at(0)!='<') return false;
  if(str.at(11)!='>')return false;
  if(str.at(13)!='[')return false;
  if(str.at(15)!=']')return false;
  //2.������ݣ����ո񻮷�
  QStringList list=str.simplified().split(' ');
  uint  id      ;   // * ID��
  int  len     ;    // * �������ݳ���
  QStringList da ;  // * ����
  QString id_str = list.at(0);
  QString len_qby = list.at(1);

  id_str.remove(11,1);  // ȥ����>��
  id_str.remove(0,3);   // ȥ����<0x��
  len_qby.remove(2,1);   // ȥ����]��
  len_qby.remove(0,1);   // ȥ����[��
  id = id_str.toUInt(NULL,16);  // id��
  len = len_qby.toUInt();       // һ��can֡�����ݳ���
  if(len != (list.size()-2))return false;//�ж����ݳ�����ȷ
  for(int i=0;i<len;i++)
  {
    da.append(list.at(i+2));
  }
  //3.��������
//  qDebug("%x",id);            // ����
//  qDebug()<<len;              // ����
//  qDebug()<<da;               // ����
  // 3.0.����Ϊ0�Ĵ���������֡
  if(len == 0)
  {
      //myShow->setText("Request Frame!");
      ui->label_requestNum->setText(QString("%1").arg(++reQuestNum,5,10,(QChar)'0'));
      return true;
  }
  // 3.1.֮ǰû�н�������
  if(canSign == 0)
  {
    // ͷ����
    if(da.at(0).toLower() != "aa")
    {
      emit canRevErr(1);
      myShow->setTextStyle(QString::fromLocal8Bit("ͷ����"),Qt::red,Qt::white,16);   // ����
      return false;
    }

    canDate.clear();
    canDate.append(da);
    canCurLen   = len;
    canDestID   = (id >> 16) & 0x1f;
    canSrcID    = (id >> 22) & 0x1f;
    canSign     = 1;  //�������״̬

    canNeedLen  = da.at(2).toUInt(NULL,16)+5;// can����Ҫ�ĳ���
    if(da.at(1)=="c4")  // �Լ���հ忨�����ϴ������ݣ��������ռ��������λ
    {
        canNeedLen  = da.at(2).toUInt(NULL,16)*256+da.at(3).toUInt(NULL,16)+6;// ����������Լ���հ忨���б䶯
    }
  }
  // 3.2.�Ѿ��ڽ���������
  else
  {
    // 3.2.1.Ŀ��ID��һ��
    if(canDestID != (char)((id >> 16) & 0x1f))
    {
      emit canRevErr(1);
      myShow->setTextStyle(QString::fromLocal8Bit("Ŀ��ID��һ��"),Qt::red,Qt::white,16);   // ����
      myShow->setText(str);
      qDebug()<<"err: "<<canDate;

      canSign = 0;//�������
      return false;
    }
    // 3.2.2.ԴID��һ��
    if(canSrcID  != (char)((id >> 22) & 0x1f))
    {
      emit canRevErr(2);
      myShow->setTextStyle(QString::fromLocal8Bit("ԴID��һ��"),Qt::red,Qt::white,16);   // ����
      canSign = 0;//�������
      return false;
    }
    canDate.append(da);
    canCurLen += len;
  }
  // 3.3.1���ճ��ȳ���
  if(canNeedLen < canCurLen)
  {
    qDebug()<<"canNeedLen="<<canNeedLen<<"canCurLen="<<canCurLen;
    emit canRevErr(3);
    myShow->setTextStyle(QString::fromLocal8Bit("���ճ��ȳ���-"),Qt::red,Qt::white,16);   // ����
    canSign = 0;//�������
    return false;
  }
  // 3.3.2.���ճ�����ȷ->У������
  if(canNeedLen == canCurLen)
  {
    // ͷ����
    if(canDate.at(0).toLower() != "aa")
    {
      emit canRevErr(1);
      myShow->setTextStyle(QString::fromLocal8Bit("ͷ����2"),Qt::red,Qt::white,16);   // ����
      return false;
    }
    // β����
    if(canDate.at(canDate.size()-1).toLower() != "55")
    {
      emit canRevErr(1);
      myShow->setTextStyle(QString::fromLocal8Bit("β����"),Qt::red,Qt::white,16);   // ����
      return false;
    }
    uchar c = 0;
    uint  i ;
    for(i=1;i<(canCurLen-2);i++)
    {
        c += canDate.at(i).toUInt(NULL,16);
    }
    // 3.3.3.У�����
    if(c != canDate.at(i).toUInt(NULL,16))
    {
      emit canRevErr(4);
      myShow->setTextStyle(QString::fromLocal8Bit("У�����"),Qt::red,Qt::white,16);   // ����
      canSign = 0;//�������
      return false;
    }
    // 3.3.4.������ȷ,����ת����ȥ
//    qDebug()<<"canSrcID="<<(uchar)canSrcID;        // ����
//    qDebug()<<"canDestID="<<(uchar)canDestID;      // ����
//    qDebug()<<"canDate="<<canDate;     // ����
    canSign = 0;//�������

    canDate.prepend(QString("0x%1").arg(canDestID,2,16,(QChar)'0'));
    canDate.prepend(QString("0x%1").arg(canSrcID,2,16,(QChar)'0'));
    // ��������+����can����
    canFilter->append(canDate);
    translate(canDate);

    return true;
  }
  return true;
}
// ��can���ݽ��в��ת��,����ת��������ݷ��ͳ�ȥ
// �����ʽ 0x00 0x01 aa....55,ǰ������ID�ţ�
void canRecv::translate(const QStringList strList)
{
    // �����������ʾ���Ͳ�����
    if(canFilter->filter_show(strList)==false)return;

    QTreeWidgetItem* treeW;
    QString strResult;
    QColor  strColor=Qt::red;
    // 1.���롰Դ��ַ��
    treeW = findKeyTopTree(idAddr, 0, strList.at(0));
    if(treeW == NULL)
    {
        strResult += "NULL";
    }
    else
    {
        strResult += treeW->text(1);
    }
    strResult += "->";
    // 2.���롰Ŀ���ַ��
    treeW = findKeyTopTree(idAddr, 0, strList.at(1));
    if(treeW == NULL)
    {
        strResult += "NULL";
    }
    else
    {
        strResult += treeW->text(1);
    }
    strResult += " (";
    // 3.���롰�������͡�
    treeW = findKeyTopTree(ctrCodeAddr, 0, QString("0x")+strList.at(3));
    if(treeW == NULL)
    {
        strResult += "NULL";
    }
    else
    {
        strResult += treeW->text(1);
        strColor = QColor(treeW->text(2).toInt(NULL,16));// ������ɫ
    }
    strResult += ") ";
    // 4.���롰�����롱
    QTreeWidgetItem* treeCtlCode= NULL;
    treeCtlCode = findKeyTopTree(orderCodeAddr, 0, QString("0x")+strList.at(5));
    if(strList.at(3)=="c4")  // --����--�Լ���հ忨�����ϴ������ݣ��������ռ��������λ
    {
        treeCtlCode = findKeyTopTree(orderCodeAddr, 0, QString("0x")+strList.at(6));
    }

    if(treeCtlCode == NULL)
    {
        strResult += "NULL";
    }
    else
    {
        strResult += treeCtlCode->text(1);
    }
    strResult += "->";
    // 5.���롰����
    strResult += "OBJ:";
    if(strList.at(3)=="c4")  // --����--�Լ���հ忨�����ϴ������ݣ��������ռ��������λ
    {
        strResult += strList.at(7);
    }
    else
    {
        strResult += strList.at(6);

    }
    strResult += "->";
    // 6.���롰������� - �������ҵ��������롱�Ļ�������ɵġ�
    QTreeWidgetItem* treeCtlOrder = NULL;
    treeCtlOrder = findKeyTopTree(treeCtlCode, 0, QString("0x")+strList.at(7));
    if(strList.at(3)=="c4")  // --����--�Լ���հ忨�����ϴ������ݣ��������ռ��������λ
    {
        treeCtlOrder = findKeyTopTree(treeCtlCode, 0, QString("0x")+strList.at(8));
    }
    if(treeCtlOrder == NULL)
    {
        strResult += "NULL";
    }
    else
    {
        strResult += treeCtlOrder->text(1);
    }
    strResult += " # ";

    // 7.���롰������
    // 7.1.���롰�����롱
    if(strList.at(3).toLower() == "f8")
    {
        strResult += "Err:: ";
        QString strErrCode = "0x"+strList.at(8)+strList.at(9);
        treeW = findKeyTopTree(errCodeAddr, 0, strErrCode);
        if(treeW!=NULL)
        {
            strResult += treeW->text(1);
        }
        else
        {
            strResult += "NULL";
        }
    }
    // 7.3.���롰�����ϴ�֡ע�͡�
    if((strList.at(3).toLower() == "d8")&&(strList.at(5).toLower() == "f0")&&(strList.at(7).toLower() == "00"))
    {
        strResult += "Dbg:: ";
        QByteArray strExplain;
        strExplain.clear();
        for(int i=8;i<strList.size()-2;i++)
        {
            strExplain.append(strList.at(i).toUInt(NULL,16));
        }
        strResult += QString::fromLocal8Bit(strExplain.trimmed());
    }
    // 7.2.���롰�����������
    QTreeWidgetItem* treeOrdArg = NULL;    // REP����������Tree��ַ
    if((strList.at(3).toLower()=="00")||(strList.at(3).toLower()=="40")||(strList.at(3).toLower()=="41")||(strList.at(3).toLower()=="42")||(strList.at(3).toLower()=="43"))
    {
        strResult += "Arg::";
        // û�и��������Ļ�����excel�ļ��е��������¾�û��"ord"������Ŀ
        treeOrdArg = findKeyTopTree(treeCtlOrder, 0, "ord");
        if(treeOrdArg != NULL)
        {   // Ҫ�������Ӷ��󶼱���һ��
            int curArgIndex = 7;    // ��ǰ���Ӳ�����ƫ�Ƹ���
            for(int i=0;i<treeOrdArg->childCount();i++)
            {
                // ��ȡ��Ҫ�Ĳ�������
                int argSize = treeOrdArg->child(i)->text(0).toInt();
                // ��ȡ�ò�����ע��
                strResult += (treeOrdArg->child(i)->text(1) + "=");
                // ��ֹ�������
                if((curArgIndex+argSize) >= (strList.size()-2))
                {
                    strResult += " ARG IS TOO MANY!";
                    break;
                }
                // �ϲ������ַ���
                QString argStr;
                argStr.clear();
                for(int i2=0;i2<argSize;i2++)
                {
                    curArgIndex++;
                    argStr += strList.at(curArgIndex);
                }
                // ��ȡ��������
                QString argType=treeOrdArg->child(i)->text(2);
                // 1."10"����ת��,�ȴ�16���Ƶ��ַ���ת��10���Ƶ����֣���ת��10���Ƶ��ַ����������ݸ���
                if(argType.toLower()=="10")
                {
                    // ��ȡ����
                    strResult += QString::number(argStr.toULongLong(NULL,16));
                }
                // 2."10+-"����ת��,�ȴ�16���Ƶ��ַ���ת��10���Ƶ����֣���ת��10���Ƶ��ַ��������ݸ���
                else if(argType.toLower()=="10+-")
                {
                    // ��ȡ����
                    long num = argStr.toLongLong(NULL,16);
                    // ȡ�����λ��4��λ�������ݴ���8 ���Ǹ�����
                    // ��ΪtoUInt ���ǰ�����תΪ����
                    char a = argStr.toLatin1().back();
                    if(QString(a).toUInt() >= 8)
                    {
                      num = ~num;
                      num++;
                    }
                    strResult += QString::number(num);
                }
                // 3."16"����ת��,ԭ������16����
                else if(argType.toLower()=="16")
                {
                    strResult += ("0x" + argStr);
                }
                // 4."100" �Ӷ���ƥ��
                else if(argType.toLower()=="100")
                {
                    treeW = findKeyTopTree(treeOrdArg->child(i), 0, argStr);
                    if(treeW!=NULL)
                    {
                        strResult += treeW->text(1);
                    }
                    else
                    {
                        strResult += "NULL";
                    }
                }
                strResult += " ";
            }
        }
        else
        {   // û�в��������
            strResult += "NULL";
        }
    }
    // 7.3.���롰�ظ��������
    QTreeWidgetItem* treeRepArg;    // REP����������Tree��ַ
    if((strList.at(3).toLower() == "c0")||(strList.at(3).toLower() == "c4"))
    {
        strResult += "Arg::";
        // û�и��������Ļ�����excel�ļ��е��������¾�û��"rep"������Ŀ
        treeRepArg = findKeyTopTree(treeCtlOrder, 0, "rep");
        if(treeRepArg != NULL)
        {   // Ҫ�������Ӷ��󶼱���һ��
            int curArgIndex = 7;    // ��ǰ���Ӳ�����ƫ�Ƹ���
            if(strList.at(3)=="c4")  // --����--�Լ���հ忨�����ϴ������ݣ��������ռ��������λ
            {
                curArgIndex = 8;
            }
            for(int i=0;i<treeRepArg->childCount();i++)
            {
                // ��ȡ��Ҫ�Ĳ�������
                int argSize = treeRepArg->child(i)->text(0).toInt();
                // ��ȡ�ò�����ע��
                strResult += (treeRepArg->child(i)->text(1) + "=");
                // ��ֹ�������
                if((curArgIndex+argSize) >= (strList.size()-2))
                {
                    strResult += " ARG IS TOO MANY!";
                    break;
                }
                // �ϲ������ַ���
                QString argStr;
                argStr.clear();
                for(int i2=0;i2<argSize;i2++)
                {
                    curArgIndex++;
                    argStr += strList.at(curArgIndex);
                }
                // ��ȡ��������
                QString argType=treeRepArg->child(i)->text(2);
                // 1."10"����ת��,�ȴ�16���Ƶ��ַ���ת��10���Ƶ����֣���ת��10���Ƶ��ַ����������ݸ���
                if(argType.toLower()=="10")
                {
                    // ��ȡ����
                    strResult += QString::number(argStr.toULongLong(NULL,16));
                }
                // 2."10+-"����ת��,�ȴ�16���Ƶ��ַ���ת��10���Ƶ����֣���ת��10���Ƶ��ַ��������ݸ���
                else if(argType.toLower()=="10+-")
                {
                    // ��ȡ����
                    long num = argStr.toLongLong(NULL,16);
                    // ȡ�����λ��4��λ�������ݴ���8 ���Ǹ�����
                    // ��ΪtoUInt ���ǰ�����תΪ����
                    char a = argStr.toLatin1().back();
                    if(QString(a).toUInt() >= 8)
                    {
                      num = ~num;
                      num++;
                    }
                    strResult += QString::number(num);
                }
                // 3."16"����ת��,ԭ������16����
                else if(argType.toLower()=="16")
                {
                    strResult += ("0x" + argStr);
                }
                // 4."100" �Ӷ���ƥ��
                else if(argType.toLower()=="100")
                {
                    treeW = findKeyTopTree(treeRepArg->child(i), 0, argStr);
                    if(treeW!=NULL)
                    {
                        strResult += treeW->text(1);
                    }
                    else
                    {
                        strResult += "NULL";
                    }
                }
                strResult += " ";
            }
        }
        else
        {   // û�в��������
            strResult += "NULL";
        }
    }

    // 10.��ʾ����
    QDateTime curTime = QDateTime::currentDateTime();   //
    QString   str = curTime.toString("hh:mm:ss ");      //��ʾʱ��
    for(int i=0;i<strList.size();i++)
    {
        str += strList.at(i)+" ";
    }
    str = str.simplified();
    // ��ʾԴ������
    myShow->setTextStyle(str      ,Qt::white,strColor,8);
    // ��ʾע������
    myShow->setTextStyle(strResult,Qt::white,strColor,8);

}
// ****************************************************** can֡�Ľ��� **************************************************************** end

// ���� ���˿�
void canRecv::on_checkBox_filter_clicked()
{
    canFilter->setHidden(ui->checkBox_filter->isChecked());
}
QTimer openTimer;   // �����ӳٷ���candump
// ��� ������candump���ӡ�
void canRecv::on_button_open_clicked()
{
    // 0.�ȹر��ٴ�
    sshPort->closeSsh();
    // 1.��
    sshPort->openSsh();
    openTimer.setInterval(500);
    openTimer.setSingleShot(true);  // ���δ������Լ��رյĹ���
    connect(sshPort,SIGNAL(connectSuccess())         ,&openTimer, SLOT(start())         ,Qt::UniqueConnection);
    connect(&openTimer,SIGNAL(timeout())              ,this     , SLOT(sendCanDumpMsg()),Qt::UniqueConnection);

}
// �ӳٷ���CanDump ����
void canRecv::sendCanDumpMsg()
{
    openTimer.stop();
    disconnect(sshPort,SIGNAL(connectSuccess())         ,&openTimer, SLOT(start()));
    disconnect(&openTimer,SIGNAL(timeout())             ,this     , SLOT(sendCanDumpMsg()));
    sshPort->sendSshCmd(QString("candump"));
}
// ******************************************** ���ݱ��� ******************************************** begin
//�������ܣ���������
//���������
//���������
//��ע��
void canRecv::dat_config_save(void)
{
    QString path = ".\\config\\AllConfig.dat";  // ͳһ���õ�ַ
    QSettings save_config(path,QSettings::IniFormat);
    save_config.setIniCodec("GB2312");          //֧������
    save_config.remove(windowTitle());          // ɾ����
    save_config.beginGroup(windowTitle());      // �����------------------------------------------begin
    save_config.setValue ("have_config"        ,true);

    // ------------------------ ���õı��� ------------------------


    save_config.endGroup();                    // �����------------------------------------------end

}
//�������ܣ���������
//���������
//���������
//��ע��
void canRecv::dat_config_load(void)
{
    QString path = ".\\config\\AllConfig.dat";          // ͳһ���õ�ַ
    QSettings load_config(path,QSettings::IniFormat);
    load_config.setIniCodec("GB2312");  // ֧������
    load_config.beginGroup(windowTitle());              // �����------------------------------------------begin
    //�ж��ļ�����
    if(load_config.contains("have_config")==false)
    {
        QMessageBox::warning(NULL, QString("Loading Error"),windowTitle() + " no file!");
        return;
    }
    // ------------------------ ���õĶ�ȡ ------------------------


    load_config.endGroup();                            // �����------------------------------------------end
}








