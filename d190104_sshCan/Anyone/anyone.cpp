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
    dat_config_load();  // 文件导入

    // 初始化外部器件 ----------------------------------------------------------------------------------
    myDebug = Fdebug::myDebug(this);
    myDebug->setWindowFlags(myDebug->windowFlags()|Qt::Window);//设置为从类
//    myDebug->show();

// 主要显示窗口
    myShow = Fdebug::myShow(this);
    ui->verticalLayout_main->insertWidget(0,myShow);
    ui->label_nothing->deleteLater();
    move(0, 0);

// Can消息发送
    canFrameSend = new canSend(this,"canFrameSend");
    canFrameSend->setWindowFlags(myShow->windowFlags()|Qt::Window);//设置为从类
    canFrameSend->show();
    canFrameSend->move(width(),10);
    connect(canFrameSend,SIGNAL(sFtpFinished(QSsh::SftpJobId, const QString)),this,SLOT(OnSftpFinished(QSsh::SftpJobId , const QString)));
// Can消息接收
    canFrameRecv = new canRecv(this,"canFrameRecv");
    canFrameRecv->setWindowFlags(myShow->windowFlags()|Qt::Window);//设置为从类
    canFrameRecv->show();
    canFrameRecv->move(width()+200,100);
    on_checkBox_recvFrame_clicked();    // can窗口的对应操作
    on_checkBox_sendFrame_clicked();

// 备注信息框
    messageBoard* youMessage = new messageBoard(this,"ZhengKaiPengMessage");
    ui->verticalLayout_msg->addWidget(youMessage);
    ui->label_msg->deleteLater();

}
AnyOne::~AnyOne()
{
    dat_config_save();
    delete ui;
}
// 关闭窗体
void AnyOne::on_pushButton_end_clicked()
{
    close();
}
// 点击“打开配置文件夹”
void AnyOne::on_pushButton_openConfig_clicked()
{
    // 打开对应的文件夹
    QProcess process;
    QString filePath = ui->lineEdit_configPath->text();
    filePath.replace("/", "\\"); // 只能识别 ".\\config"
    QString cmd = QString("explorer.exe %1").arg(filePath);
    process.startDetached(cmd);



}
// 点击“一键自检”
void AnyOne::on_pushButton_check_clicked()
{
    if(canFrameRecv->isConnected() == false)
    {
        myShow->setTextStyle(QString::fromLocal8Bit("接收SSH没有打开"),Qt::red,Qt::white,16);   // 出错
        return;
    }
    if(canFrameSend->isConnected() == false)
    {
        myShow->setTextStyle(QString::fromLocal8Bit("发送SSH没有打开"),Qt::red,Qt::white,16);   // 出错
        return;
    }
    canFrameSend->sendCanMsg("0x00 0x01 aa 00 03 01 00 01 05 55");
    canFrameSend->sendCanMsg("0x00 0x02 aa 00 03 01 00 01 05 55");
    canFrameSend->sendCanMsg("0x00 0x03 aa 00 03 01 00 01 05 55");
    canFrameSend->sendCanMsg("0x00 0x04 aa 00 03 01 00 01 05 55");
    canFrameSend->sendCanMsg("0x00 0x05 aa 00 03 01 00 01 05 55");
}

// 点击“b4”-测试翻译命令
void AnyOne::on_pushButton_testExplain_clicked()
{
    QStringList strList;
    strList = ui->plainTextEdit_in->toPlainText().trimmed().split("\n");
    for(int i=0;i<strList.size();i++)
    {
        canFrameRecv->explain(strList.at(i).simplified()); // 解析命令
    }
}
// 点击“b5”,一键打开SSH
void AnyOne::on_pushButton_openSSH_clicked()
{
    canFrameSend->setSshIP(ui->lineEdit_IP->text());    // 设置发送端IP
    canFrameRecv->setSshIP(ui->lineEdit_IP->text());    // 设置接收端IP
    canFrameSend->openSsh();    // 打开发送端的 ssh
    canFrameRecv->openSsh();    // 打开接收端的 ssh
}

// 点击打开发送框
void AnyOne::on_checkBox_sendFrame_clicked()
{
    if(ui->checkBox_sendFrame->isChecked())
        canFrameSend->show();
    else
        canFrameSend->hide();
}
// 点击打开接收框
void AnyOne::on_checkBox_recvFrame_clicked()
{
    if(ui->checkBox_recvFrame->isChecked())
        canFrameRecv->show();
    else
        canFrameRecv->hide();
}
// 点击“b6”-清屏
void AnyOne::on_pushButton_clear_clicked()
{
    myShow->clear();
    canFrameRecv->clear();
    canFrameSend->clear();

}
// ftp操作完成提示
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
// ******************************************** 数据保存 ******************************************** begin
//函数功能：保存配置
//输入参数：
//输出参数：
//备注：
void AnyOne::dat_config_save(void)
{
    QString path = ".\\config\\AllConfig.dat";  // 统一配置地址
    QSettings save_config(path,QSettings::IniFormat);
    save_config.setIniCodec("GB2312");          //支持中文
    save_config.remove(windowTitle());          // 删除组
    save_config.beginGroup(windowTitle());      // 组操作------------------------------------------begin
    save_config.setValue ("have_config"        ,true);

    // ------------------------ 配置的保存 ------------------------
    save_config.setValue ("plainTextEdit_in"   ,ui->plainTextEdit_in->toPlainText());//
    save_config.setValue("checkBox_recvFrame",ui->checkBox_recvFrame->isChecked());
    save_config.setValue("checkBox_sendFrame",ui->checkBox_sendFrame->isChecked());
    save_config.setValue("lineEdit_IP",ui->lineEdit_IP->text());

    save_config.endGroup();                    // 组操作------------------------------------------end

}
//函数功能：导入配置
//输入参数：
//输出参数：
//备注：
void AnyOne::dat_config_load(void)
{
    // 打开时间记录
    QSettings recordOpen(".\\config\\openRecord.dat" , QSettings::IniFormat);
    recordOpen.setValue(QDateTime::currentDateTime().toString("yyyy-MM-dd--hh-mm-ss"),"");//时间串

    QString path = ".\\config\\AllConfig.dat";          // 统一配置地址
    QSettings load_config(path,QSettings::IniFormat);
    load_config.setIniCodec("GB2312");  // 支持中文
    load_config.beginGroup(windowTitle());              // 组操作------------------------------------------begin
    //判断文件存在
    if(load_config.contains("have_config")==false)
    {
        QMessageBox::warning(NULL, QString("Loading Error"),windowTitle() + " no file!");
        return;
    }

    // ------------------------ 配置的读取 ------------------------
    ui->plainTextEdit_in->setPlainText(load_config.value("plainTextEdit_in").toString());//
    ui->checkBox_recvFrame->setChecked(load_config.value("checkBox_recvFrame").toBool());
    ui->checkBox_sendFrame->setChecked(load_config.value("checkBox_sendFrame").toBool());
    ui->lineEdit_IP->setText(load_config.value("lineEdit_IP").toString());

    load_config.endGroup();                            // 组操作------------------------------------------end
}













