#include "FsshGuiAutoAck.h"
#include "ui_FsshGuiAutoAck.h"

FsshGuiAutoAck::FsshGuiAutoAck(QWidget *parent, QString title) :QWidget(parent),ui(new Ui::FsshGuiAutoAck)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);     // 默认外框
    setWindowTitle(title);           // 设置文件名
    dat_config_load();
//    connect(&delayTimer,SIGNAL(timeout()),this,SLOT(sendAckMsg()));    // 定时器关联
}
FsshGuiAutoAck::~FsshGuiAutoAck()
{
    dat_config_save();
    delete ui;
}
#include <QDebug>
// 接收信息，如果匹配就延时回复
void FsshGuiAutoAck::dealRecMsg(QString str)
{
    // 只有打钩的才生效
    if(ui->checkBox_enable->isChecked())
    {
//        qDebug()<< "auto Ack" <<str;
        // 需要完全匹配才生效
        if(str == ui->lineEdit_recv->text())
        {
            qDebug()<< "compear auto Ack" <<str;
            delayTimer.singleShot(ui->spinBox_delay->value(),this,SLOT(sendAckMsg()));// 单次触发该函数
        }
    }
}
// 延时到后就发送这条命令
void FsshGuiAutoAck::sendAckMsg(void)
{
//    qDebug()<< "sendAckMsg auto Ack" <<ui->lineEdit_ack->text();
    emit autoAckSting(ui->lineEdit_ack->text());
}

// ******************************************** 数据保存 ******************************************** begin
#include<QSettings>
//函数功能： 导出配置
//输入参数： 导出配置的Qsetting的指针
//输出参数：
//备注：
void FsshGuiAutoAck::dat_config_save(void)
{
    QString path = ".\\config\\AllConfig.dat";  // 统一配置地址
    QSettings save_config(path,QSettings::IniFormat);
    save_config.setIniCodec("GB2312");//支持中文
    save_config.remove(windowTitle());  // 删除组
    save_config.beginGroup(windowTitle());     // 组操作------------------------------------------begin
    // ------------------------ 配置的保存 ------------------------
    save_config.setValue("checkBox_enable",ui->checkBox_enable->isChecked());
    save_config.setValue("lineEdit_ack",ui->lineEdit_ack->text());
    save_config.setValue("lineEdit_recv",ui->lineEdit_recv->text());
    save_config.setValue("spinBox_delay",ui->spinBox_delay->value());

    save_config.endGroup();                    // 组操作------------------------------------------end
}
//函数功能：导入配置
//输入参数：导入配置的Qsetting的指针
//输出参数：
//备注：
void FsshGuiAutoAck::dat_config_load(void)
{
    QString path = ".\\config\\AllConfig.dat";  // 统一配置地址
    QSettings load_config(path,QSettings::IniFormat);
    load_config.setIniCodec("GB2312");  // 支持中文
    load_config.beginGroup(windowTitle());     // 组操作------------------------------------------begin
    // ------------------------ 配置的读取 ------------------------
    ui->checkBox_enable->setChecked(load_config.value("checkBox_enable").toBool());
    ui->lineEdit_ack->setText(load_config.value("lineEdit_ack").toString());
    ui->lineEdit_recv->setText(load_config.value("lineEdit_recv").toString());
    ui->spinBox_delay->setValue(load_config.value("spinBox_delay").toInt());

    load_config.endGroup();                    // 组操作------------------------------------------end
}
