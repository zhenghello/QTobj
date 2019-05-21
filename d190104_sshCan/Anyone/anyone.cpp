#include "anyone.h"
#include "ui_anyone.h"
#include<QSplitter>
#include<QSettings>
#include<QTimer>

#include "excel2treeWidget.h"

#include "canSend.h"
#include "canRecv.h"
canSend   *canFrameSend;
canRecv   *canFrameRecv;

Fdebug *myShow;
Fdebug *myDebug;

AnyOne::AnyOne(QWidget *parent):QMainWindow(parent),ui(new Ui::AnyOne)
{
    ui->setupUi(this);
    dat_config_load();  // �ļ�����

    // ��ʼ���ⲿ���� ----------------------------------------------------------------------------------
    myDebug = Fdebug::myDebug(this);
    myDebug->setWindowFlags(myDebug->windowFlags()|Qt::Window);//����Ϊ����
//    myDebug->show();

// ��Ҫ��ʾ����
    myShow = Fdebug::myShow(this);
    ui->verticalLayout_main->insertWidget(0,myShow);
    ui->label_nothing->deleteLater();
    move(0, 0);

// Can��Ϣ����
    canFrameSend = new canSend(this,"canFrameSend");
    canFrameSend->setWindowFlags(myShow->windowFlags()|Qt::Window);//����Ϊ����
    canFrameSend->show();
    canFrameSend->move(width(),10);
    connect(canFrameSend,SIGNAL(sFtpFinished(QSsh::SftpJobId, const QString)),this,SLOT(OnSftpFinished(QSsh::SftpJobId , const QString)));
// Can��Ϣ����
    canFrameRecv = new canRecv(this,"canFrameRecv");
    canFrameRecv->setWindowFlags(myShow->windowFlags()|Qt::Window);//����Ϊ����
    canFrameRecv->show();
    canFrameRecv->move(width()+200,100);
    on_checkBox_recvFrame_clicked();    // can���ڵĶ�Ӧ����
    on_checkBox_sendFrame_clicked();

// ��ע��Ϣ��
    messageBoard* youMessage = new messageBoard(this,"ZhengKaiPengMessage");
    ui->verticalLayout_msg->addWidget(youMessage);
    ui->label_msg->deleteLater();

}
AnyOne::~AnyOne()
{
    dat_config_save();
    delete ui;
}
// �رմ���
void AnyOne::on_pushButton_end_clicked()
{
    close();
}
// ������������ļ��С�
void AnyOne::on_pushButton_openConfig_clicked()
{
    // �򿪶�Ӧ���ļ���
    QProcess process;
    QString filePath = ui->lineEdit_configPath->text();
    filePath.replace("/", "\\"); // ֻ��ʶ�� ".\\config"
    QString cmd = QString("explorer.exe %1").arg(filePath);
    process.startDetached(cmd);



}
// �����һ���Լ족
void AnyOne::on_pushButton_check_clicked()
{
    if(canFrameRecv->isConnected() == false)
    {
        myShow->setTextStyle(QString::fromLocal8Bit("����SSHû�д�"),Qt::red,Qt::white,16);   // ����
        return;
    }
    if(canFrameSend->isConnected() == false)
    {
        myShow->setTextStyle(QString::fromLocal8Bit("����SSHû�д�"),Qt::red,Qt::white,16);   // ����
        return;
    }
    canFrameSend->sendCanMsg("0x00 0x01 aa 00 03 01 00 01 05 55");
    canFrameSend->sendCanMsg("0x00 0x02 aa 00 03 01 00 01 05 55");
    canFrameSend->sendCanMsg("0x00 0x03 aa 00 03 01 00 01 05 55");
    canFrameSend->sendCanMsg("0x00 0x04 aa 00 03 01 00 01 05 55");
    canFrameSend->sendCanMsg("0x00 0x05 aa 00 03 01 00 01 05 55");
}

// �����b4��-���Է�������
void AnyOne::on_pushButton_testExplain_clicked()
{
    QStringList strList;
    strList = ui->plainTextEdit_in->toPlainText().trimmed().split("\n");
    for(int i=0;i<strList.size();i++)
    {
        canFrameRecv->explain(strList.at(i).simplified()); // ��������
    }
}
// �����b5��,һ����SSH
void AnyOne::on_pushButton_openSSH_clicked()
{
    canFrameSend->setSshIP(ui->lineEdit_IP->text());    // ���÷��Ͷ�IP
    canFrameRecv->setSshIP(ui->lineEdit_IP->text());    // ���ý��ն�IP
    canFrameSend->openSsh();    // �򿪷��Ͷ˵� ssh
    canFrameRecv->openSsh();    // �򿪽��ն˵� ssh
}

// ����򿪷��Ϳ�
void AnyOne::on_checkBox_sendFrame_clicked()
{
    if(ui->checkBox_sendFrame->isChecked())
        canFrameSend->show();
    else
        canFrameSend->hide();
}
// ����򿪽��տ�
void AnyOne::on_checkBox_recvFrame_clicked()
{
    if(ui->checkBox_recvFrame->isChecked())
        canFrameRecv->show();
    else
        canFrameRecv->hide();
}
// �����b6��-����
void AnyOne::on_pushButton_clear_clicked()
{
    myShow->clear();
    canFrameRecv->clear();
    canFrameSend->clear();

}
// ftp���������ʾ
void AnyOne::OnSftpFinished(QSsh::SftpJobId job, const QString &error)
{
    if(error.isEmpty())
    {
        myShow->setTextStyle(QString("SftpJobId = %1,Operate success").arg(job),Qt::white,Qt::gray,12);
    }
    else
    {
        myShow->setTextStyle(QString("SftpJobId = %1,error=%2").arg(job).arg(error),Qt::white,Qt::gray,12);
    }
}
// ******************************************** ���ݱ��� ******************************************** begin
//�������ܣ���������
//���������
//���������
//��ע��
void AnyOne::dat_config_save(void)
{
    QString path = ".\\config\\AllConfig.dat";  // ͳһ���õ�ַ
    QSettings save_config(path,QSettings::IniFormat);
    save_config.setIniCodec("GB2312");          //֧������
    save_config.remove(windowTitle());          // ɾ����
    save_config.beginGroup(windowTitle());      // �����------------------------------------------begin
    save_config.setValue ("have_config"        ,true);

    // ------------------------ ���õı��� ------------------------
    save_config.setValue ("plainTextEdit_in"   ,ui->plainTextEdit_in->toPlainText());//
    save_config.setValue("checkBox_recvFrame",ui->checkBox_recvFrame->isChecked());
    save_config.setValue("checkBox_sendFrame",ui->checkBox_sendFrame->isChecked());
    save_config.setValue("lineEdit_IP",ui->lineEdit_IP->text());

    save_config.endGroup();                    // �����------------------------------------------end

}
//�������ܣ���������
//���������
//���������
//��ע��
void AnyOne::dat_config_load(void)
{
    // ��ʱ���¼
    QSettings recordOpen(".\\config\\openRecord.dat" , QSettings::IniFormat);
    recordOpen.setValue(QDateTime::currentDateTime().toString("yyyy-MM-dd--hh-mm-ss"),"");//ʱ�䴮

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
    ui->plainTextEdit_in->setPlainText(load_config.value("plainTextEdit_in").toString());//
    ui->checkBox_recvFrame->setChecked(load_config.value("checkBox_recvFrame").toBool());
    ui->checkBox_sendFrame->setChecked(load_config.value("checkBox_sendFrame").toBool());
    ui->lineEdit_IP->setText(load_config.value("lineEdit_IP").toString());

    load_config.endGroup();                            // �����------------------------------------------end
}













