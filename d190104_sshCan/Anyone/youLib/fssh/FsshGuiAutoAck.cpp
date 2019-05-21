#include "FsshGuiAutoAck.h"
#include "ui_FsshGuiAutoAck.h"

FsshGuiAutoAck::FsshGuiAutoAck(QWidget *parent, QString title) :QWidget(parent),ui(new Ui::FsshGuiAutoAck)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);     // Ĭ�����
    setWindowTitle(title);           // �����ļ���
    dat_config_load();
//    connect(&delayTimer,SIGNAL(timeout()),this,SLOT(sendAckMsg()));    // ��ʱ������
}
FsshGuiAutoAck::~FsshGuiAutoAck()
{
    dat_config_save();
    delete ui;
}
#include <QDebug>
// ������Ϣ�����ƥ�����ʱ�ظ�
void FsshGuiAutoAck::dealRecMsg(QString str)
{
    // ֻ�д򹳵Ĳ���Ч
    if(ui->checkBox_enable->isChecked())
    {
//        qDebug()<< "auto Ack" <<str;
        // ��Ҫ��ȫƥ�����Ч
        if(str == ui->lineEdit_recv->text())
        {
            qDebug()<< "compear auto Ack" <<str;
            delayTimer.singleShot(ui->spinBox_delay->value(),this,SLOT(sendAckMsg()));// ���δ����ú���
        }
    }
}
// ��ʱ����ͷ�����������
void FsshGuiAutoAck::sendAckMsg(void)
{
//    qDebug()<< "sendAckMsg auto Ack" <<ui->lineEdit_ack->text();
    emit autoAckSting(ui->lineEdit_ack->text());
}

// ******************************************** ���ݱ��� ******************************************** begin
#include<QSettings>
//�������ܣ� ��������
//��������� �������õ�Qsetting��ָ��
//���������
//��ע��
void FsshGuiAutoAck::dat_config_save(void)
{
    QString path = ".\\config\\AllConfig.dat";  // ͳһ���õ�ַ
    QSettings save_config(path,QSettings::IniFormat);
    save_config.setIniCodec("GB2312");//֧������
    save_config.remove(windowTitle());  // ɾ����
    save_config.beginGroup(windowTitle());     // �����------------------------------------------begin
    // ------------------------ ���õı��� ------------------------
    save_config.setValue("checkBox_enable",ui->checkBox_enable->isChecked());
    save_config.setValue("lineEdit_ack",ui->lineEdit_ack->text());
    save_config.setValue("lineEdit_recv",ui->lineEdit_recv->text());
    save_config.setValue("spinBox_delay",ui->spinBox_delay->value());

    save_config.endGroup();                    // �����------------------------------------------end
}
//�������ܣ���������
//����������������õ�Qsetting��ָ��
//���������
//��ע��
void FsshGuiAutoAck::dat_config_load(void)
{
    QString path = ".\\config\\AllConfig.dat";  // ͳһ���õ�ַ
    QSettings load_config(path,QSettings::IniFormat);
    load_config.setIniCodec("GB2312");  // ֧������
    load_config.beginGroup(windowTitle());     // �����------------------------------------------begin
    // ------------------------ ���õĶ�ȡ ------------------------
    ui->checkBox_enable->setChecked(load_config.value("checkBox_enable").toBool());
    ui->lineEdit_ack->setText(load_config.value("lineEdit_ack").toString());
    ui->lineEdit_recv->setText(load_config.value("lineEdit_recv").toString());
    ui->spinBox_delay->setValue(load_config.value("spinBox_delay").toInt());

    load_config.endGroup();                    // �����------------------------------------------end
}
