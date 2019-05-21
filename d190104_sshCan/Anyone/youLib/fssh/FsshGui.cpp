#include "FsshGui.h"
#include "ui_FsshGui.h"


FsshGui::FsshGui(QWidget *parent, QString name) :QWidget(parent),ui(new Ui::FsshGui)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);     // Ĭ�����
    setWindowTitle(name);           // �����ļ���
    // ��ʾ��
    sshOut = new Fdebug(this,"ssh Show message",true);
    sshOut->show();
    // �滻 label_sshOut ��λ��
    ui->mainLayout->insertWidget(0,sshOut);
    ui->label_sshOut->deleteLater();

    // �ļ�����
    dat_config_load();  // ���õ���

    // ssh �źŹ������ -- begin
    connect(&myssh,SIGNAL(sshIsConnected(void))          ,this, SLOT(mysshIsConnect(void))      );
    connect(&myssh,SIGNAL(sshIsDisconnected(void))       ,this, SLOT(mysshIsDisConnect(void))   );
    connect(&myssh,SIGNAL(receiveSshDate(QString))       ,this, SLOT(mysshCommandBack(QString)) );
    connect(&myssh,SIGNAL(sshConnectErr(QString))        ,this, SLOT(mysshIsError(QString)) );
    connect(&myssh,SIGNAL(sFtpFinished(QSsh::SftpJobId,QString)),this,SLOT(OnSftpFinished(QSsh::SftpJobId,QString)));
    // ssh �źŹ������ -- end    

    // ������Ϣ�򴴽�
    msgBox = new QMessageBox(QMessageBox::Information,QString("Please Wait!"), "Connecting SSH, IP = "+ui->lineEdit_IP->text(),QMessageBox::Ok);
    msgBox->button(QMessageBox::Ok)->hide();
    ftpBox = new QMessageBox(QMessageBox::Information,QString("Please Wait!"), QString("NULL"),QMessageBox::Ok);
    ftpBox->button(QMessageBox::Ok)->hide();
    //
    timerAutoConnect = new QTimer();
    timerAutoConnect->setInterval(5000);    // ÿ�������Զ�����
    connect(timerAutoConnect,SIGNAL(timeout()),this,SLOT(autoConnect()));

    // �Զ������Զ�Ӧ���
    ui->label_autoAck->deleteLater();
    ui->groupBox_autoAck->setMaximumHeight(ui->spinBox_autoAckNum->value()*25+50); // ��������
    for(int i=0;i<ui->spinBox_autoAckNum->value();i++)
    {
        FsshGuiAutoAck *autoAckOne = new FsshGuiAutoAck(this,windowTitle()+QString("-FsshGuiAutoAck-Num%1").arg(i));
        ui->autoAckLayout->addWidget(autoAckOne);
        autoAck.append(autoAckOne);
        connect(this,SIGNAL(revMsg(QString))                ,autoAckOne ,   SLOT(dealRecMsg(QString)) );// �����ź�:FsshGui�����Զ�Ӧ��ģ��
        connect(autoAckOne,SIGNAL(autoAckSting(QString))    ,this       ,   SLOT(sendSshCmd(QString)) );          // �����ź�:�Զ�Ӧ��ģ�鷢��FsshGui
    }
}
FsshGui::~FsshGui()
{
    dat_config_save();  // ��������

    closeSsh();                 // �ر�ssh
    delete sshOut;
    delete ui;
}
// �����Զ�����
void FsshGui::autoConnect()
{
    if(ui->checkBox_autoConnect->isChecked())
    {
        if(ui->button_open->text() == "open_ssh")
            on_button_open_clicked();
    }
}
// ��״�ı��¼����ض��庯��
void FsshGui::resizeEvent(QResizeEvent *event)
{
    // ������ʾ��չ
    if(ui->checkBox_SrceenAutoExpand->isChecked())
        sshOut->setMinimumHeight(height()-5);
    else
        sshOut->setMinimumHeight(100);
    if(event==NULL)return;
}
// �������Ļ��չ��
void FsshGui::on_checkBox_SrceenAutoExpand_clicked()
{
    resizeEvent(NULL);
}

// ���"open_ssh" - ��������
void FsshGui::on_button_open_clicked()
{
    if(ui->button_open->text() == "open_ssh")
    {
        myssh.SSH_connectToHost(ui->lineEdit_IP->text(),ui->spinBox_port->value(),ui->lineEdit_name->text(),ui->lineEdit_password->text(),50);
        ui->button_open->setText("connecting_ssh");
        msgBox->setText("Connecting SSH, IP = "+ui->lineEdit_IP->text());
        msgBox->show(); // ��Ӱ���̨����
    }
    else if(ui->button_open->text() == "close_ssh")
    {
        myssh.SSH_disconnectFromHost();
        ui->button_open->setText("disconnecting_ssh");
    }
}
// ssh ���ӳɹ�����
void FsshGui::mysshIsConnect()
{
    sshOut->setTextStyle("mysshIsConnect",Qt::white,Qt::green,12);
    ui->button_open->setText("close_ssh");
    emit connectSuccess();      // �������ӳɹ��ź�
    msgBox->hide(); // �ر���ʾ����
}
// ssh �Ͽ�
void FsshGui::mysshIsDisConnect()
{
    sshOut->setTextStyle("mysshIsDisConnect",Qt::white,Qt::red,12);
    ui->button_open->setText("open_ssh");
    emit connectFailure();      // ��������ʧ���ź�
    msgBox->hide(); // �ر���ʾ����
}
// ssh ���ӳ���
void FsshGui::mysshIsError(QString str)
{
    sshOut->setTextStyle("mysshIsError = "+str,Qt::white,Qt::red,12);
    ui->button_open->setText("open_ssh");
    emit connectFailure();      // ��������ʧ���ź�
    msgBox->hide(); // �ر���ʾ����
    QMessageBox msg(QMessageBox::Warning,QString("SSH CONNECT ERROR"), "MSG:"+str,QMessageBox::Ok);
    msg.exec();
}
// ssh ��������,���������ݲ�ֳɵ��з��ͳ�ȥ
void FsshGui::mysshCommandBack(QString str)
{
    str = str.trimmed();// ȥ����Ч�ַ�
    if(str.isEmpty()||str.isNull())return;  // ���Կհ��ַ�
    sshOut->setTextStyle(str);                      // �����ַ�����������ʾ
    QStringList strList;
    strList = str.trimmed().split("\n");            // ͬʱ���յ����о�Ҫ�ֽ�
    for(int i=0;i<strList.size();i++)
    {
        QString str = strList.at(i).simplified();
        if(str.isEmpty()||str.isNull())continue;    // �հ����ݲ�Ҫ
        emit revMsg(str);                           // ת�����յ���ssh���ݳ�ȥ
    }
}
// ���ftp��������
void FsshGui::OnSftpFinished(QSsh::SftpJobId job, const QString &error)
{
    //    qDebug()<<"SftpJobId= "<<job<<"error="<<error;
    if(error.isEmpty())
    {
        sshOut->setTextStyle(QString("SftpJobId = %1,Operate success").arg(job),Qt::white,Qt::gray,12);
    }
    else
    {
        sshOut->setTextStyle(QString("SftpJobId = %1,error=%2").arg(job).arg(error),Qt::white,Qt::gray,12);
    }
    ftpBox->hide();                 //  �Զ��ر���ʾ��
    emit sFtpFinished(job, error);  //  ת������FTP���������ĺ���
}
// ����
void FsshGui::clear(void)
{
    sshOut->clear();
}


// ��� �շ��ļ� ��
void FsshGui::on_groupBox_file_clicked()
{
    ui->frame_file->setVisible(ui->groupBox_file->isChecked());
}
// ��� �������� ��
void FsshGui::on_groupBox_order_clicked()
{
    ui->frame_order->setVisible(ui->groupBox_order->isChecked());
}
// ��� ��¼ ��
void FsshGui::on_groupBox_land_clicked()
{
    ui->frame_land->setVisible(ui->groupBox_land->isChecked());
}
// ��� Ӧ�� ��
void FsshGui::on_groupBox_autoAck_clicked()
{
    ui->frame_autoAck->setVisible(ui->groupBox_autoAck->isChecked());
}

// ��� ���������
void FsshGui::on_button_send_clicked()
{
    // û�д�SSH������
    if(myssh.isConnected() == false)
    {
        sshOut->setTextStyle("No Open SSH6",Qt::white,Qt::red,12);
        QMessageBox::warning(NULL, QString("No Open SSH6"),QString("No Open SSH"));
        return;
    }
     myssh.SSH_sendCommand(ui->plainTextEdit_in->toPlainText());
}
// �б༭����
void FsshGui::on_lineEdit_sendSingle_editingFinished()
{
    // û�д�SSH������
    if(myssh.isConnected() == false)
    {
        sshOut->setTextStyle("No Open SSH5",Qt::white,Qt::red,12);
        QMessageBox::warning(NULL, QString("No Open SSH5"),QString("No Open SSH"));
        return;
    }
     myssh.SSH_sendCommand(ui->lineEdit_sendSingle->text());
}


// �ļ��������------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ⲿ����->ִ��ftp�ļ�����
void FsshGui::SSH_downloadFile(const QString &remotePath,   const QString &localPath)
{
    if(myssh.isConnected() == false)// û�д�SSH������
    {
        sshOut->setTextStyle("No Open SSH1",Qt::white,Qt::red,12);
        QMessageBox::warning(NULL, QString("No Open SSH1"),QString("No Open SSH"));
        return;
    }
    QSsh::SftpJobId job = myssh.SSH_downloadFile(remotePath,localPath);// ftp�ļ���������
    ftpBox->setText(QString("SSH_downloadFile : ")+remotePath+QString(" -> ")+localPath);
    ftpBox->show();
    sshOut->setTextStyle(QString("SSH_downloadFile -> SftpJobId = %1").arg(job),Qt::white,Qt::gray,12);
}
// �ⲿ����->ִ��ftp�ļ��ϴ�
void FsshGui::SSH_uploadFile(const QString &localPath,      const QString &remotePath)
{
    if(myssh.isConnected() == false)// û�д�SSH������
    {
        sshOut->setTextStyle("No Open SSH2",Qt::white,Qt::red,12);
        QMessageBox::warning(NULL, QString("No Open SSH2"),QString("No Open SSH"));
        return;
    }
    QSsh::SftpJobId job = myssh.SSH_uploadFile(localPath,remotePath);// �����ļ�����
    ftpBox->setText(QString("SSH_uploadFile : ")+localPath+QString(" -> ")+remotePath);
    ftpBox->show();
    sshOut->setTextStyle(QString("SSH_uploadFile -> SftpJobId = %1").arg(job),Qt::white,Qt::gray,12);
}
// �ⲿ����->ִ��ftp�ļ��ϴ��ļ���
void FsshGui::SSH_uploadDir(const QString &localDirPath,    const QString &remoteDirPath)
{
    if(myssh.isConnected() == false)// û�д�SSH������
    {
        sshOut->setTextStyle("No Open SSH3",Qt::white,Qt::red,12);
        QMessageBox::warning(NULL, QString("No Open SSH3"),QString("No Open SSH"));
        return;
    }
    QSsh::SftpJobId job = myssh.SSH_uploadDir(localDirPath,remoteDirPath);// �����ļ�������
    ftpBox->setText(QString("SSH_uploadDir : ")+localDirPath+QString(" -> ")+remoteDirPath);
    ftpBox->show();
    sshOut->setTextStyle(QString("SSH_uploadDir -> SftpJobId = %1").arg(job),Qt::white,Qt::gray,12);
}
// �ⲿ����->ִ��ftp�ļ������ļ���
void FsshGui::SSH_downloadDir(const QString &remoteDirPath, const QString &localDirPath)
{
    if(myssh.isConnected() == false)// û�д�SSH������
    {
        sshOut->setTextStyle("No Open SSH4",Qt::white,Qt::red,12);
        QMessageBox::warning(NULL, QString("No Open SSH4"),QString("No Open SSH"));
        return;
    }
    QSsh::SftpJobId job = myssh.SSH_downloadDir(remoteDirPath,localDirPath);// �����ļ�������
    ftpBox->setText(QString("SSH_downloadDir : ")+remoteDirPath+QString(" -> ")+localDirPath);
    ftpBox->show();
    sshOut->setTextStyle(QString("SSH_downloadDir -> SftpJobId = %1").arg(job),Qt::white,Qt::gray,12);
}



// ��� �������ļ���
void FsshGui::on_button_uploadFile_clicked()
{
    SSH_uploadFile(ui->lineEdit_local_addr->text(),     ui->lineEdit_obj_addr->text());
}
// ��� �������ļ���
void FsshGui::on_button_recvFile_clicked()
{
    SSH_downloadFile(ui->lineEdit_obj_addr->text(),     ui->lineEdit_local_addr->text());
}
// ��� �������ļ��С�
void FsshGui::on_button_downloadDir_clicked()
{
    SSH_downloadDir(ui->lineEdit_objDir_addr->text(), ui->lineEdit_localDir_addr->text());
}
// ��� ���ϴ��ļ��С�
void FsshGui::on_button_uploadDir_clicked()
{
    SSH_uploadDir( ui->lineEdit_localDir_addr->text(), ui->lineEdit_objDir_addr->text());
}
// ��� �������ļ���
void FsshGui::on_button_openLocalFile_clicked()
{
    // �򿪶�Ӧ���ļ���
    QProcess process;
    QString filePath = ui->lineEdit_local_addr->text();
    filePath.replace("/", "\\"); // ֻ��ʶ�� "\"
    QString cmd = QString("explorer.exe /select,\"%1\"").arg(filePath);
    process.startDetached(cmd);
}

// ��� �������ļ��С�
void FsshGui::on_button_openLocalDir_clicked()
{
    // �򿪶�Ӧ���ļ���
    QProcess process;
    QString filePath = ui->lineEdit_localDir_addr->text();
    filePath.replace("/", "\\"); // ֻ��ʶ�� "\"
    QString cmd = QString("explorer.exe %1").arg(filePath);
    process.startDetached(cmd);
}
// ��� ��������
void FsshGui::on_pushButton_clicked()
{
    sshOut->clear();
}
// ******************************************** �ⲿ�ӿ����� ******************************************** begin
// ����IP
void FsshGui::setSshIP(QString str)
{
    // IP��ַ����3��С����
    if( str.count('.') !=3)return;
    ui->lineEdit_IP->setText(str);
}
// ��SSH
void FsshGui::openSsh()
{
    // ԭ��û�򿪣���ִ�д򿪲���
    if(ui->button_open->text() == "open_ssh")
    {
        on_button_open_clicked();
    }
}
// �ر�SSH
void FsshGui::closeSsh()
{
    // ԭ���رգ���ִ�йرղ���
    if(ui->button_open->text() == "close_ssh")
    {
        on_button_open_clicked();
    }
}
// ����SSH����,���޸�����������
bool FsshGui::sendSshCmd(QString str)
{
//    ui->plainTextEdit_in->setPlainText(str); // ���淢�Ͳ���
    // û�д�SSH������
    if(myssh.isConnected() == false)
    {
        sshOut->setTextStyle("No Open SSH8",Qt::white,Qt::red,12);
        QMessageBox::warning(NULL, QString("No Open SSH8"),QString("No Open SSH"));
        return false;
    }
    else
    {
        myssh.SSH_sendCommand(str);
        return true;
    }
}
// ******************************************** �ⲿ�ӿ����� ******************************************** end

// ******************************************** ���ݱ��� ******************************************** begin
#include<QSettings>
//�������ܣ� ��������
//��������� �������õ�Qsetting��ָ��
//���������
//��ע��
void FsshGui::dat_config_save(void)
{
    QString path = ".\\config\\AllConfig.dat";  // ͳһ���õ�ַ
    QSettings save_config(path,QSettings::IniFormat);
    save_config.setIniCodec("GB2312");//֧������
    save_config.remove(windowTitle());  // ɾ����
    save_config.beginGroup(windowTitle());     // �����------------------------------------------begin
    save_config.setValue ("have_config"        ,true);

    // ------------------------ ���õı��� ------------------------
    save_config.setValue ("lineEdit_IP"        ,ui->lineEdit_IP->text());             // ��������
    save_config.setValue ("lineEdit_name"      ,ui->lineEdit_name->text());           //
    save_config.setValue ("lineEdit_password"  ,ui->lineEdit_password->text());       //
    save_config.setValue ("spinBox_port"  ,ui->spinBox_port->value());                //
    save_config.setValue ("plainTextEdit_in"   ,ui->plainTextEdit_in->toPlainText()); // ��������
    save_config.setValue ("lineEdit_sendSingle"   ,ui->lineEdit_sendSingle->text()); // ��������

    save_config.setValue("lineEdit_obj_addr"    ,ui->lineEdit_obj_addr->text());
    save_config.setValue("lineEdit_local_addr"    ,ui->lineEdit_local_addr->text());
    save_config.setValue("lineEdit_objDir_addr"    ,ui->lineEdit_objDir_addr->text());
    save_config.setValue("lineEdit_localDir_addr"    ,ui->lineEdit_localDir_addr->text());

    save_config.setValue("groupBox_order"       ,ui->groupBox_order->isChecked());//
    save_config.setValue("groupBox_land"        ,ui->groupBox_land->isChecked()); //
    save_config.setValue("groupBox_file"        ,ui->groupBox_file->isChecked()); //
    save_config.setValue("groupBox_autoAck"     ,ui->groupBox_autoAck->isChecked()); //

    save_config.setValue("spinBox_autoAckNum"   ,ui->spinBox_autoAckNum->value());

    save_config.endGroup();                    // �����------------------------------------------end
}
//�������ܣ���������
//����������������õ�Qsetting��ָ��
//���������
//��ע��
void FsshGui::dat_config_load(void)
{
    QString path = ".\\config\\AllConfig.dat";  // ͳһ���õ�ַ
    QSettings load_config(path,QSettings::IniFormat);
    load_config.setIniCodec("GB2312");  // ֧������

    load_config.beginGroup(windowTitle());     // �����------------------------------------------begin
    //�ж��ļ�����
    if(load_config.contains("have_config")==false)
    {
        qDebug()<< QString("FsshGui:dat_config_load error")+windowTitle() + " no file!";
        return;
    }
    // ------------------------ ���õĶ�ȡ ------------------------
    ui->lineEdit_IP->setText(load_config.value("lineEdit_IP").toString());
    ui->lineEdit_name->setText(load_config.value("lineEdit_name").toString());
    ui->lineEdit_password->setText(load_config.value("lineEdit_password").toString());
    ui->spinBox_port->setValue(load_config.value("spinBox_port").toInt());
    ui->plainTextEdit_in->setPlainText(load_config.value("plainTextEdit_in").toString());       // ��������
    ui->lineEdit_sendSingle->setText(load_config.value("lineEdit_sendSingle").toString());

    ui->lineEdit_local_addr->setText(load_config.value("lineEdit_local_addr").toString());      // �ļ���ַ
    ui->lineEdit_obj_addr->setText(load_config.value("lineEdit_obj_addr").toString());
    ui->lineEdit_localDir_addr->setText(load_config.value("lineEdit_localDir_addr").toString());
    ui->lineEdit_objDir_addr->setText(load_config.value("lineEdit_objDir_addr").toString());

    ui->groupBox_order->setChecked(load_config.value("groupBox_order").toBool()); //
    ui->groupBox_land->setChecked(load_config.value("groupBox_land").toBool());   //
    ui->groupBox_file->setChecked(load_config.value("groupBox_file").toBool());     //
    ui->groupBox_autoAck->setChecked(load_config.value("groupBox_autoAck").toBool());     //

    on_groupBox_file_clicked();
    on_groupBox_order_clicked();
    on_groupBox_land_clicked();
    on_groupBox_autoAck_clicked();

    ui->spinBox_autoAckNum->setValue(load_config.value("spinBox_autoAckNum").toInt()); // �����Զ�Ӧ�����

    load_config.endGroup();                    // �����------------------------------------------end
}






// ******************************************** �Զ�Ӧ�𴴽� ******************************************** begin















