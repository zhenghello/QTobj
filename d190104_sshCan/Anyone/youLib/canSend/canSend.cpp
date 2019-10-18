#include "canSend.h"
#include "ui_canSend.h"

#include "canpack.h"


canSend::canSend(QWidget *parent, QString titleName) :QWidget(parent),ui(new Ui::canSend)
{
    ui->setupUi(this);
    setWindowTitle(titleName);
    dat_config_load();

    // Tree�����ݿ�
    treeOredr = new FtreeDabeBase(this,"canOrder");
    treeOredr->setMinimumHeight(300);
    ui->tab_tree->layout()->addWidget(treeOredr);
    ui->label_ssh->deleteLater();

    // SSH�Ķ˿�
    sshPort = new FsshGui(this,"canSendSSH");
    sshPort->setMinimumHeight(300);
    ui->tab_ssh->layout()->addWidget(sshPort);
    ui->label_order->deleteLater();

    connect(treeOredr,&FtreeDabeBase::sendMsgTree                           ,this, &canSend::msgTreeAnalyze);           // ����tree���һ��¼�ת�����ش���
    connect(sshPort,SIGNAL(connectSuccess())                                ,this, SLOT(showSshOpenMsg()));                               // ���ӳɹ��ź�
    connect(sshPort,SIGNAL(connectFailure())                                ,this, SLOT(showSshCloseMsg()));                              // ����ʧ���ź�
    connect(sshPort,SIGNAL(sFtpFinished(QSsh::SftpJobId, const QString))    ,this, SIGNAL(sFtpFinished(QSsh::SftpJobId, const QString))); // FTP�ļ����������ź�

    // �ļ����ؿ�
    treeFile = new FtreeDabeBase(this,"sshFile");
    treeFile->setWhatsThis("�����Դ��ַ�������ص�����\n�����������ַ�����ϴ���������");
    ui->tab_fileDownload->layout()->addWidget(treeFile);
    ui->label_file->deleteLater();
    connect(treeFile,SIGNAL(sendMsgTree(QTreeWidgetItem*,int)),this,SLOT(fileTreeOperate(QTreeWidgetItem*,int)));   // ����tree���һ��¼�ת�����ش���

    // ѡ�� ->����ʾ��
    ui->tabWidget->setCurrentWidget(ui->tab_tree);
   // ui->tabWidget->setCurrentWidget(ui->tab_base);
    //������
    canPack *cp;
    cp = new canPack(this,12);
    ui->tab_base->layout()->addWidget(cp);

    // ����

    //QTimer::singleShot(10000, this, SLOT(on_button_upgrade_modular_clicked()));

}
canSend::~canSend()
{
    dat_config_save();
    delete ui;
}
// ����������������
void canSend::on_button_reboot_clicked()
{
    if(sshPort->isConnected())
    {
        sshPort->sendSshCmd("sh /dymind/appStart.sh");  // ����SSH����
        ui->button_reboot->setEnabled(false);           //

        ui->tabWidget->setCurrentIndex(2);                                     // ֱ����ȥSSH��ʾ��
        QTimer::singleShot(62000, this, SLOT(button_reboot_setEnableTrue()));  // �����ٰ�����
        QTimer::singleShot(60000, sshPort, SLOT(closeSsh()));  // 1���Ӻ�ر�ssh
        QTimer::singleShot(62000, sshPort, SLOT(openSsh()));   // ��62����ssh
//        QMessageBox msg(QMessageBox::NoIcon, QString("Please Wait"), QString("Please Wait reboot"));
//        QTimer::singleShot(11000, &msg, SLOT(close()));     // ����һ��ʱ��󴥷�,������ʱһ���ȴ���
//        msg.exec();
    }
    else
    {
        QMessageBox msg(QMessageBox::NoIcon, QString("NO Open SSH"), QString("NO Open SSH"));
        QTimer::singleShot(1000, &msg, SLOT(close()));  // ����һ��ʱ��󴥷�,������ʱһ���ȴ���
        msg.exec();
    }
}

// button_reboot()
void canSend::button_reboot_setEnableTrue(void)
{
    ui->button_reboot->setEnabled(true);
    ui->tabWidget->setCurrentIndex(1);                                     // ֱ������������ʾ��

}

// �ļ���ص��������ͳ���������
void canSend::fileTreeOperate(QTreeWidgetItem *tree,int column)
{

    if(isConnected() == false)
    {
        QMessageBox::warning(NULL, QString("No Open SSH9"),QString("No Open SSH"));
        return;
    }

    if(column==1)// ���ص�����
    {
        if(tree->text(0)=="F")// �����ļ�
        {
            if(tree->text(1).isNull()||tree->text(1).isEmpty())return;// �հ���Ч
            if(tree->text(2).isNull()||tree->text(2).isEmpty())return;// �հ���Ч
            sshPort->SSH_downloadFile(tree->text(1),tree->text(2));
            return;
        }
        else if(tree->text(0)=="D")// �����ļ���
        {
            if(tree->text(1).isNull()||tree->text(1).isEmpty())return;// �հ���Ч
            if(tree->text(2).isNull()||tree->text(2).isEmpty())return;// �հ���Ч
            sshPort->SSH_downloadDir(tree->text(1),tree->text(2));
            return;
        }
    }
    else if(column==2)// �ϴ���������
    {
        if(tree->text(0)=="F")// �ϴ��ļ�
        {
            if(tree->text(1).isNull()||tree->text(1).isEmpty())return;// �հ���Ч
            if(tree->text(2).isNull()||tree->text(2).isEmpty())return;// �հ���Ч
            QFileInfo file(tree->text(2));//�ж��ļ�����
            if(file.isFile()==false)
            {
                QMessageBox::warning(NULL, QString("No File"),QString("No File : ")+tree->text(2));
                return;
            }
            // �ϴ�
            sshPort->SSH_uploadFile(tree->text(2),tree->text(1));
            QMessageBox msg(QMessageBox::NoIcon, QString("upload File"), QString("upload File : ")+tree->text(2)+QString(" -> ")+tree->text(1) );
            QTimer::singleShot(1000, &msg, SLOT(close()));  // ����һ��ʱ��󴥷�,������ʱһ���ȴ���
            msg.exec();
            sshPort->sendSshCmd("sync");// ����ͬ������
            return;
        }
        else if(tree->text(0)=="D")// �ϴ��ļ���
        {
            if(tree->text(1).isNull()||tree->text(1).isEmpty())return;// �հ���Ч
            if(tree->text(2).isNull()||tree->text(2).isEmpty())return;// �հ���Ч
            QFileInfo file(tree->text(2));//�ж��ļ�����
            if(file.isDir()==false)
            {
                QMessageBox::warning(NULL, QString("No Dir"),QString("No Dir : ")+tree->text(2));
                return;
            }
            sshPort->SSH_uploadDir(tree->text(2),tree->text(1));
            QMessageBox msg(QMessageBox::NoIcon, QString("upload Dir"), QString("upload Dir : ")+tree->text(2)+QString(" -> ")+tree->text(1) );
            QTimer::singleShot(1000, &msg, SLOT(close()));  // ����һ��ʱ��󴥷�
            msg.exec();                                     // ������ʱһ���ȴ���
            sshPort->sendSshCmd("sync");// ����ͬ������
            return;
        }
    }
}

// ���Ҫ���͵�����
void canSend::msgTreeAnalyze(QTreeWidgetItem *tree,int column)
{
    if(column==1)
    {
        sendCanMsg(tree->text(column));
    }
}
// ����Ҫ���͵�����
void canSend::sendCanMsg(QString str)
{
    QStringList strlist = str.simplified().split(' ');
    // ����̫��
    if(strlist.size()<8) return ;

    uint        canDestID    ; // Ŀ��ID
    uint        canSrcID     ; // ԴID
    uint        segnum       ; //
    uint        idCode       ; // ID��
    QString     canStr       ; //
    // �Դ���ַ�����->û����ַ�ӿ���ȡ
    if((strlist.at(0).at(0)=='0')&&((strlist.at(0).at(1)=='x')||(strlist.at(0).at(1)=='X'))&&(strlist.at(1).at(0)=='0')&&((strlist.at(1).at(1)=='x')||(strlist.at(1).at(1)=='X')))
    {
        canSrcID  = strlist.at(0).toInt(NULL,16);
        canDestID = strlist.at(1).toInt(NULL,16);
        strlist.removeFirst();// �õ����ݺ�ȥ��
        strlist.removeFirst();
    }
    else
    {
        canDestID = ui->spinBox_destID->value();
        canSrcID  = ui->spinBox_srcID->value();
    }

    idCode = (canDestID<<16)+(canSrcID<<22); // ��ID�ı���
    // �ֽ����
    // ֻ��һ֡�����
    if(strlist.size()<=8)
    {
        canStr = QString("cansend can0 -i 0x%1").arg(idCode,0,16);
        for(int i=0;i<8;i++)
        {
            canStr += QString(" 0x%1").arg(strlist.first().toInt(NULL,16),0,16);
            strlist.removeFirst();
        }
        canStr += " -e";
        sshPort->sendSshCmd(canStr);
    }
    // �ж�֡�����
    else
    {
        // ͷ��
        idCode = (canDestID<<16)+(canSrcID<<22)+0x4000; // ��ID�ı���+��ͷ����
        segnum = 0;
        canStr = QString("cansend can0 -i 0x%1").arg(idCode+(segnum<<8),0,16);
        for(int i=0;i<8;i++)
        {
            canStr += QString(" 0x%1").arg(strlist.first().toInt(NULL,16),0,16);
            strlist.removeFirst();
        }
        canStr += " -e && ";
        // �м��
        idCode = (canDestID<<16)+(canSrcID<<22)+0x8000; // ��ID�ı���+�м�α���
        if(strlist.size()>8)
        {
            segnum ++;
            canStr += QString("cansend can0 -i 0x%1").arg(idCode+(segnum<<8),0,16);
            for(int i=0;i<8;i++)
            {
                canStr += QString(" 0x%1").arg(strlist.first().toInt(NULL,16),0,16);
                strlist.removeFirst();
            }
            canStr += " -e && ";
        }
        // β�Ͷ�
        idCode = (canDestID<<16)+(canSrcID<<22)+0xc000; // ��ID�ı���+��β����
        segnum ++;
        canStr += QString("cansend can0 -i 0x%1").arg(idCode+(segnum<<8),0,16);
        while (strlist.size())
        {
            canStr += QString(" 0x%1").arg(strlist.first().toInt(NULL,16),0,16);
            strlist.removeFirst();
        }
        canStr += " -e";
        sshPort->sendSshCmd(canStr);
    }
}
// �����������Ͳ��� ------------------------------------------------ begin
void canSend::on_pushButton_bathcOrder_clicked()
{
    if(sshPort->isConnected()==false)
    {
        QMessageBox::warning(NULL, QString("No Open SSH5"),QString("No Open SSH"));
        return;
    }
    strList_batch = ui->plainTextEdit_BatchOrder->toPlainText().split("\n");
    QString bstr;
    // ������Ч��Ϣ
    for(int i=0; i<strList_batch.size(); i++)
    {
        QString str = strList_batch.at(i);
        if(str.indexOf("0x00") == 9)
        {
            bstr += str.mid(9)+"\n";
        }
        qDebug()<<"u="<<str.indexOf("0x00");
    }
    ui->plainTextEdit_BatchOrder->setPlainText(bstr);
    strList_batch = ui->plainTextEdit_BatchOrder->toPlainText().split("\n");
    qDebug()<<strList_batch.size();

    connect(&timer_batch, SIGNAL(timeout()), this, SLOT(bathcOrder_timeout()) );
    timer_batch.start(20);
}
void canSend::bathcOrder_timeout()
{
    QString str = strList_batch.takeFirst();
    sshPort->sendSshCmd(str);
    if(strList_batch.size() == 0)
    {
        timer_batch.stop();
        disconnect(&timer_batch, SIGNAL(timeout()), this, SLOT(bathcOrder_timeout()) );
    }
}
// �����������Ͳ��� ------------------------------------------------ end

// ******************************************** �ⲿ���� ******************************************** begin

// ******************************************** �ⲿ���� ******************************************** end

// ******************************************** ���ݱ��� ******************************************** begin
//�������ܣ���������
//���������
//���������
//��ע��
void canSend::dat_config_save(void)
{
    QString path = ".\\config\\AllConfig.dat";  // ͳһ���õ�ַ
    QSettings save_config(path,QSettings::IniFormat);
    save_config.setIniCodec("GB2312");          //֧������
    save_config.remove(windowTitle());          // ɾ����
    save_config.beginGroup(windowTitle());      // �����------------------------------------------begin
    save_config.setValue ("have_config"        ,true);
    save_config.setValue ("plainTextEdit_BatchOrder"        ,ui->plainTextEdit_BatchOrder->toPlainText());
    // ------------------------ ���õı��� ------------------------


    save_config.endGroup();                    // �����------------------------------------------end

}
//�������ܣ���������
//���������
//���������
//��ע��
void canSend::dat_config_load(void)
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
    ui->plainTextEdit_BatchOrder->setPlainText(load_config.value("plainTextEdit_BatchOrder").toString());

    load_config.endGroup();                            // �����------------------------------------------end
}



// ���µ����¶Ȱ���
void canSend::on_button_temp_clicked()
{
    if(pTmpCfg == NULL)
    {
        pTmpCfg = new canTmpConfig(this);
        pTmpCfg->setWindowFlags(pTmpCfg->windowFlags()|Qt::Window);//����Ϊ���
        pTmpCfg->show();
        connect(pTmpCfg,SIGNAL(send_can_pack(QString)),this,SLOT(sendCanMsg(QString)));
    }
    else
    {
        disconnect(pTmpCfg,SIGNAL(send_can_pack(QString)),this,SLOT(sendCanMsg(QString)));
        pTmpCfg->deleteLater();
        pTmpCfg = NULL;
    }
//      cp->setCanPack_ArgNum(20);
//      cp->table_init(20);
}

// �������ģ��
void canSend::on_button_motor_clicked()
{
    if(pMotor == NULL)
    {
        pMotor = new FOptMotor(this);
        pMotor->setWindowFlags(pMotor->windowFlags()|Qt::Window);//����Ϊ���
        pMotor->show();
        connect(pMotor,SIGNAL(send_can_pack(QString)),this,SLOT(sendCanMsg(QString)));
    }
    else
    {
        disconnect(pMotor,SIGNAL(send_can_pack(QString)),this,SLOT(sendCanMsg(QString)));
        pMotor->deleteLater();
        pMotor = NULL;
    }
}
// ѡ����������
void canSend::on_button_upgrade_modular_clicked()
{
    // ����������Ҫ�õ�ssh�ķ����ļ�������ܣ�Ҫ��ssh�Ľӿڴ��ݽ�ȥ
    if(pupgrade == NULL)
    {
        if(sshPort->isConnected()==false)
        {
            QMessageBox::warning(NULL, QString("No Open SSH4"),QString("No Open SSH"));
            return;
        }
        // ֱ����ȥSSH��ʾ��
        ui->tabWidget->setCurrentIndex(2);
        pupgrade = new UpgradeModel(this,sshPort);
        pupgrade->setWindowFlags(pupgrade->windowFlags()|Qt::Window);//����Ϊ���
        pupgrade->show();
        pupgrade->move(100,100);
    }
    else
    {
        pupgrade->deleteLater();
        pupgrade = NULL;
    }
}




void canSend::on_pushButton_debug_clicked()
{

}




void canSend::on_button_text_clicked()
{

}

