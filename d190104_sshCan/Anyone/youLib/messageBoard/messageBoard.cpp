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
// �����ı�ʱ���ı�߿�
void messageBoard::on_spinBox_valueChanged(int arg1)
{
//    ui->textEdit_msg->setMinimumHeight(arg1);
//    ui->textEdit_msg->setMaximumHeight(arg1);
    setMinimumHeight(arg1);
    setMaximumHeight(arg1);
}



// ******************************************** ���ݱ��� ******************************************** begin
#include<QSettings>
//�������ܣ���������
//���������
//���������
//��ע��
void messageBoard::dat_config_save(void)
{
    QString path = ".\\config\\AllConfig.dat";  // ͳһ���õ�ַ
    QSettings save_config(path,QSettings::IniFormat);
    save_config.setIniCodec("GB2312");          //֧������
    save_config.remove(windowTitle());          // ɾ����
    save_config.beginGroup(windowTitle());      // �����------------------------------------------begin
    save_config.setValue ("have_config"        ,true);

    // ------------------------ ���õı��� ------------------------
    {
        save_config.setValue("textEdit_msg",ui->textEdit_msg->toPlainText());
        save_config.setValue("spinBox",ui->spinBox->value());
    }

    save_config.endGroup();                    // �����------------------------------------------end

}
//�������ܣ���������
//���������
//���������
//��ע��
void messageBoard::dat_config_load(void)
{
    QString path = ".\\config\\AllConfig.dat";          // ͳһ���õ�ַ
    QSettings load_config(path,QSettings::IniFormat);
    load_config.setIniCodec("GB2312");  // ֧������
    load_config.beginGroup(windowTitle());              // �����------------------------------------------begin
    //�ж��ļ�����
    if(load_config.contains("have_config")==false)
    {
        qDebug()<<"no dat_config_load";
        return;
    }

    // ------------------------ ���õĶ�ȡ ------------------------
    {
        ui->textEdit_msg->setPlainText(load_config.value("textEdit_msg").toString());
        ui->spinBox->setValue(load_config.value("spinBox").toInt());
    }


    load_config.endGroup();                            // �����------------------------------------------end
}
