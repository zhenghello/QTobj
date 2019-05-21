/* ����ļ����ڽ���can����Ĺ���
 * can����Ľ��������� canExplain.xlsx ���Ѿ��༭��
 * canЭ��������Ź���
 * 1�ࣺ�����
 * 2�ࣺ�������͵ı���
 * 3�ࣺ��������ı���
 * 4�ࣺ���͵Ĳ����ͽ��յĲ���
 * 5�ࣺ������������
 *
*/
#include "canExplain.h"
#include "QMessageBox"
#include "QDebug"
#include "fdebug.h"
int htoi(char s[]);


// ����ʱ��ʼ��������
canExplain::canExplain(QWidget *parent):FtreeDabeBase(parent)
{
    // 0.��ȡcan����������ַ
    mTree = mainTree();
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
}
canExplain::~canExplain()
{

}
// ��can���ݽ��в��ת��,����ת��������ݷ��ͳ�ȥ
void canExplain::translate(char destID,char srcID,QStringList strList)
{
    QTreeWidgetItem* treeW;
    QString strResult;
    QColor  strColor=Qt::red;

    strList.prepend(QString("0x%1").arg(destID,2,16,(QChar)'0'));
    strList.prepend(QString("0x%1").arg(srcID,2,16,(QChar)'0'));

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
    QTreeWidgetItem* treeCtlCode;
    treeCtlCode = findKeyTopTree(orderCodeAddr, 0, QString("0x")+strList.at(5));
    if(treeCtlCode == NULL)
    {
        strResult += "NULL";
        return;
    }
    else
    {
        strResult += treeCtlCode->text(1);
    }
    strResult += "->";
    // 5.���롰����
    strResult += "OBJ:";
    strResult += strList.at(6);
    strResult += "->";
    // 6.���롰������� - �������ҵ��������롱�Ļ�������ɵġ�
    QTreeWidgetItem* treeCtlOrder;
    treeCtlOrder = findKeyTopTree(treeCtlCode, 0, QString("0x")+strList.at(7));
    if(treeCtlOrder == NULL)
    {
        strResult += "NULL";
        return;
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
        strResult += treeW->text(1);
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
        strResult += strExplain.trimmed();
    }

    // 7.2.���롰�����������
    QTreeWidgetItem* treeOrdArg;    // REP����������Tree��ַ
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
    if(strList.at(3).toLower() == "c0")
    {
        strResult += "Arg::";
        // û�и��������Ļ�����excel�ļ��е��������¾�û��"rep"������Ŀ
        treeRepArg = findKeyTopTree(treeCtlOrder, 0, "rep");

        if(treeRepArg != NULL)
        {   // Ҫ�������Ӷ��󶼱���һ��
            int curArgIndex = 7;    // ��ǰ���Ӳ�����ƫ�Ƹ���
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

// ����һ��can֡���ݣ��磺<0x00800000> [8] aa d4 03 01 00 00 d8 55
// ת��������ɲ���У��õ����ݣ�ǰ��λ��Դ��Ŀ�� ��ID
bool canExplain::explain(QString str)
{
  // �ط��жϷ��� �յ� read: Network is down ��Ҫ�ط�,����Ϣ�ط���ȥ
  if(str.trimmed() == "read: Network is down")
  {
    emit candumpIsDown();
    myShow->setTextStyle(QString::fromLocal8Bit("candump is close"),Qt::red,Qt::white,16);   // can����
    return true;
  }

  //myShow->setText(str);
  //1.�ж�������Ч�ԣ���0���ǡ�<��,��11���ǡ�>��,��13�ǡ�[������15���ǡ�]��
  if(str.size()<16)  return false;
  if(str.at(0)!='<') return false;
  if(str.at(11)!='>')return false;
  if(str.at(13)!='[')return false;
  if(str.at(15)!=']')return false;
  //2.������ݣ����ո񻮷�
  QStringList list=str.simplified().split(' ');
  uint  id      ;   // * ID��
  uint  len     ;    // * �������ݳ���
  QStringList da ;  // * ����
  QString id_str = list.at(0);
  QString len_qby = list.at(1);

  id_str.remove(11,1);  // ȥ����>��
  id_str.remove(0,3);   // ȥ����<0x��
  len_qby.remove(2,1);   // ȥ����]��
  len_qby.remove(0,1);   // ȥ����[��
  id = id_str.toUInt(NULL,16);  // id��
  len = len_qby.toUInt(); // ���ݳ���
  if(len != (list.size()-2))return false;//�ж����ݳ�����ȷ
  for(uint i=0;i<len;i++)
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
      myShow->setText("Request Frame!");
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
    canNeedLen  = da.at(2).toUInt()+5;// ����������Լ���հ忨���б䶯

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
    emit canRevErr(3);
    myShow->setTextStyle(QString::fromLocal8Bit("���ճ��ȳ���"),Qt::red,Qt::white,16);   // ����
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
    // ��������
    translate(canDestID, canSrcID, canDate);




    return true;
  }

  return true;
}

// ���������µ�


//��ʮ�����Ƶ��ַ���ת��������
int htoi(char s[])
{
  int i;
  int n = 0;
  if (s[0] == '0' && (s[1]=='x' || s[1]=='X'))
  {
      i = 2;
  }
  else
  {
    i = 0;
  }
  for (; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >='A' && s[i] <= 'Z');++i)
  {
    if (tolower(s[i]) > '9')
    {
      n = 16 * n + (10 + tolower(s[i]) - 'a');
    }
    else
    {
      n = 16 * n + (tolower(s[i]) - '0');
    }
  }
  return n;
}

