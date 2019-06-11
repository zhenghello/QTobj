/*
    ����ļ��������� �¶ȵ��Խ���
*/
#include "cantmpconfig.h"
#include "ui_cantmpconfig.h"

canTmpConfig::canTmpConfig(QWidget *parent) :QWidget(parent),ui(new Ui::canTmpConfig)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()|Qt::Window);//����Ϊ���

    // ����CAN��
    configPID = new canPack(this,12);// ��ʼ��һ�� can ����ʽ
    //configPID->hide();
    configTmp = new canPack(this,2);
    //configTmp->hide();
    openTmp = new canPack(this,1);
    //openTmp->hide();
    readTmp = new canPack(this,0);
    //readTmp->hide();
    // ����canPack
    ui->gridLayout_cp->addWidget(configPID,0,1);
    ui->gridLayout_cp->addWidget(configTmp,1,1);
    ui->gridLayout_cp->addWidget(openTmp,2,1);
    ui->gridLayout_cp->addWidget(readTmp,3,1);
    // �����ź�
    connect(configPID,  SIGNAL(send_can_pack(QString)),this,SIGNAL(send_can_pack(QString)));
    connect(configTmp,  SIGNAL(send_can_pack(QString)),this,SIGNAL(send_can_pack(QString)));
    connect(openTmp,    SIGNAL(send_can_pack(QString)),this,SIGNAL(send_can_pack(QString)));
    connect(readTmp,    SIGNAL(send_can_pack(QString)),this,SIGNAL(send_can_pack(QString)));

}
canTmpConfig::~canTmpConfig()
{
    delete ui;
}
//����PID
void canTmpConfig::on_b_setPID_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("62");
    t = ui->box_num->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append("40");
    t = ui->box_P->value() * 10000;
    qsl.append(QString("%1").arg((t>>24)&0xFF,2,16,QChar('0')));
    qsl.append(QString("%1").arg((t>>16)&0xFF,2,16,QChar('0')));
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->box_I->value() * 10000;
    qsl.append(QString("%1").arg((t>>24)&0xFF,2,16,QChar('0')));
    qsl.append(QString("%1").arg((t>>16)&0xFF,2,16,QChar('0')));
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->box_D->value() * 10000;
    qsl.append(QString("%1").arg((t>>24)&0xFF,2,16,QChar('0')));
    qsl.append(QString("%1").arg((t>>16)&0xFF,2,16,QChar('0')));
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    configPID->setCanPack_OrderArg(qsl);
    configPID->sendCanPack();
}
// ��ȡPID
void canTmpConfig::on_b_getPID_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("62");       // ������
    t = ui->box_num->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append("41");       // PID��ѯ����
    readTmp->setCanPack_OrderArg(qsl);
    readTmp->sendCanPack();
}
// �����¶�
void canTmpConfig::on_b_setTmp_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("62");
    t = ui->box_num->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append("20");
    t = ui->box_tmp->value()*100;
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    configTmp->setCanPack_OrderArg(qsl);
    configTmp->sendCanPack();
}
// ��ȡ�¶�ֵ
void canTmpConfig::on_b_readTmp_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("62");       // ������
    t = ui->box_num->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append("10");       // �¶Ȳ�ѯ����
    readTmp->setCanPack_OrderArg(qsl);
    readTmp->sendCanPack();
}

// ���¶ȿ���
void canTmpConfig::on_b_openTmp_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("62");
    t = ui->box_num->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append("01");
    qsl.append("01");//��
    openTmp->setCanPack_OrderArg(qsl);
    openTmp->sendCanPack();
}
// �ر��¶ȿ���
void canTmpConfig::on_b_closeTmp_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("62");
    t = ui->box_num->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append("01");
    qsl.append("00");//�ر�
    openTmp->setCanPack_OrderArg(qsl);
    openTmp->sendCanPack();
}
// ��������PID ����
void canTmpConfig::on_checkBox_setPidEnable_clicked(bool checked)
{
    ui->frame_PID->setEnabled(checked);
}
