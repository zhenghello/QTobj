#include "messageBoard.h"
#include "ui_messageBoard.h"
#include"QDebug"

messageBoard::messageBoard(QWidget *parent,QString titleName) :QWidget(parent),ui(new Ui::messageBoard)
{
    ui->setupUi(this);
    setWindowTitle(titleName);
    dat_config_load();
}

messageBoard::~messageBoard()
{
    dat_config_save();
    delete ui;
}
// 参数改变时，改变边框
void messageBoard::on_spinBox_valueChanged(int arg1)
{
//    ui->textEdit_msg->setMinimumHeight(arg1);
//    ui->textEdit_msg->setMaximumHeight(arg1);
    setMinimumHeight(arg1);
    setMaximumHeight(arg1);
}



// ******************************************** 数据保存 ******************************************** begin
#include<QSettings>
//函数功能：保存配置
//输入参数：
//输出参数：
//备注：
void messageBoard::dat_config_save(void)
{
    QString path = ".\\config\\AllConfig.dat";  // 统一配置地址
    QSettings save_config(path,QSettings::IniFormat);
    save_config.setIniCodec("GB2312");          //支持中文
    save_config.remove(windowTitle());          // 删除组
    save_config.beginGroup(windowTitle());      // 组操作------------------------------------------begin
    save_config.setValue ("have_config"        ,true);

    // ------------------------ 配置的保存 ------------------------
    {
        save_config.setValue("textEdit_msg",ui->textEdit_msg->toPlainText());
        save_config.setValue("spinBox",ui->spinBox->value());
    }

    save_config.endGroup();                    // 组操作------------------------------------------end

}
//函数功能：导入配置
//输入参数：
//输出参数：
//备注：
void messageBoard::dat_config_load(void)
{
    QString path = ".\\config\\AllConfig.dat";          // 统一配置地址
    QSettings load_config(path,QSettings::IniFormat);
    load_config.setIniCodec("GB2312");  // 支持中文
    load_config.beginGroup(windowTitle());              // 组操作------------------------------------------begin
    //判断文件存在
    if(load_config.contains("have_config")==false)
    {
        qDebug()<<"no dat_config_load";
        return;
    }

    // ------------------------ 配置的读取 ------------------------
    {
        ui->textEdit_msg->setPlainText(load_config.value("textEdit_msg").toString());
        ui->spinBox->setValue(load_config.value("spinBox").toInt());
    }


    load_config.endGroup();                            // 组操作------------------------------------------end
}
