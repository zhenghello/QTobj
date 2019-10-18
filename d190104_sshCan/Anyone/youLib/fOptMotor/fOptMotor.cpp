#include "fOptMotor.h"
#include "ui_fOptMotor.h"




FOptMotor::FOptMotor(QWidget *parent) :QWidget(parent),ui(new Ui::FOptMotor)
{
    ui->setupUi(this);

    ui->label_msg->deleteLater();
    layout()->addWidget(new messageBoard(this,"FOptMotor_msg"));

    // �����Ͳ���
    cp = new canPack(this,12);
    layout()->addWidget(cp);

    // �����ź�
    connect(cp,  SIGNAL(send_can_pack(QString)),this,SIGNAL(send_can_pack(QString)));
}

FOptMotor::~FOptMotor()
{
    delete ui;
}



// ��ʼ��
void FOptMotor::on_pushButton_init_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("23");
    t = ui->spinBox_mototNum->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append("10");
    t = ui->spinBox_speed->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// ����
    t = ui->spinBox_overTime->value();
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));// ʱ��
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->checkBox_lock->checkState();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// ����
    qsl.append("00"); // ����

    cp->setCanPack_IdCode(QString("0x%1").arg(0,2,16,QChar('0')),QString("0x%1").arg(ui->spinBox_ID->value(),2,16,QChar('0')));  // ����ID
    cp->setCanPack_OrderArg(qsl);
    cp->sendCanPack();
}
// ��λ��1
void FOptMotor::on_pushButton_p1_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("23");
    t = ui->spinBox_mototNum->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append("11");
    t = ui->spinBox_p1->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// λ��
    t = ui->spinBox_speed->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// ����
    t = ui->spinBox_overTime->value();
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));// ʱ��
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->checkBox_lock->checkState();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// ����

    cp->setCanPack_IdCode(QString("0x%1").arg(0,2,16,QChar('0')),QString("0x%1").arg(ui->spinBox_ID->value(),2,16,QChar('0')));  // ����ID
    cp->setCanPack_OrderArg(qsl);
    cp->sendCanPack();
}
// ��λ��2
void FOptMotor::on_pushButton_p2_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("23");
    t = ui->spinBox_mototNum->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append("11");
    t = ui->spinBox_p2->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// λ��
    t = ui->spinBox_speed->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// ����
    t = ui->spinBox_overTime->value();
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));// ʱ��
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->checkBox_lock->checkState();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// ����

    cp->setCanPack_IdCode(QString("0x%1").arg(0,2,16,QChar('0')),QString("0x%1").arg(ui->spinBox_ID->value(),2,16,QChar('0')));  // ����ID
    cp->setCanPack_OrderArg(qsl);
    cp->sendCanPack();
}
// �߲���1
void FOptMotor::on_pushButton_s1_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("23");
    t = ui->spinBox_mototNum->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append("12");
    t = ui->spinBox_s1->value();
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));// ����
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->spinBox_speed->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// ����
    t = ui->spinBox_overTime->value();
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));// ʱ��
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->checkBox_lock->checkState();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// ����

    cp->setCanPack_IdCode(QString("0x%1").arg(0,2,16,QChar('0')),QString("0x%1").arg(ui->spinBox_ID->value(),2,16,QChar('0')));  // ����ID
    cp->setCanPack_OrderArg(qsl);
    cp->sendCanPack();
}
// �߲���2
void FOptMotor::on_pushButton_s2_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("23");
    t = ui->spinBox_mototNum->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append("12");
    t = ui->spinBox_s2->value();
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));// ����
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->spinBox_speed->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// ����
    t = ui->spinBox_overTime->value();
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));// ʱ��
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->checkBox_lock->checkState();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// ����

    cp->setCanPack_IdCode(QString("0x%1").arg(0,2,16,QChar('0')),QString("0x%1").arg(ui->spinBox_ID->value(),2,16,QChar('0')));  // ����ID
    cp->setCanPack_OrderArg(qsl);
    cp->sendCanPack();
}
// �߲���3
void FOptMotor::on_pushButtons3_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("23");
    t = ui->spinBox_mototNum->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append("12");
    t = ui->spinBox_s3->value();
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));// ����
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->spinBox_speed->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// ����
    t = ui->spinBox_overTime->value();
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));// ʱ��
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->checkBox_lock->checkState();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// ����

    cp->setCanPack_IdCode(QString("0x%1").arg(0,2,16,QChar('0')),QString("0x%1").arg(ui->spinBox_ID->value(),2,16,QChar('0')));  // ����ID
    cp->setCanPack_OrderArg(qsl);
    cp->sendCanPack();
}
// �߲���4
void FOptMotor::on_pushButton_s4_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("23");
    t = ui->spinBox_mototNum->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append("12");
    t = ui->spinBox_s4->value();
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));// ����
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->spinBox_speed->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// ����
    t = ui->spinBox_overTime->value();
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));// ʱ��
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->checkBox_lock->checkState();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));// ����

    cp->setCanPack_IdCode(QString("0x%1").arg(0,2,16,QChar('0')),QString("0x%1").arg(ui->spinBox_ID->value(),2,16,QChar('0')));  // ����ID
    cp->setCanPack_OrderArg(qsl);
    cp->sendCanPack();
}
// �������-��ֱ��ʼ��
void FOptMotor::on_pushButton_sample_vinit_clicked()
{
    QStringList qsl;
    uint t;

    qsl.append(QString("%1").arg(CMD_TYPE_SAMPLE,2,16,QChar('0')));
    t = ui->spinBox_mototNum->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append(QString("%1").arg(CMD_V_INIT_SAMPLE,2,16,QChar('0')));

    t = ui->spinBox_speed->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));           // ����
    t = ui->spinBox_overTime->value();
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));// ʱ��
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->checkBox_lock->checkState();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));           // ����

    cp->setCanPack_IdCode(QString("0x%1").arg(0,2,16,QChar('0')),QString("0x%1").arg(ui->spinBox_ID->value(),2,16,QChar('0')));  // ����ID
    cp->setCanPack_OrderArg(qsl);
    cp->sendCanPack();
}

void FOptMotor::on_pushButton_sample_hinit_clicked()
{
    QStringList qsl;
    uint t;

    qsl.append(QString("%1").arg(CMD_TYPE_SAMPLE,2,16,QChar('0')));
    t = ui->spinBox_mototNum->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append(QString("%1").arg(CMD_H_INIT_SAMPLE,2,16,QChar('0')));

    t = ui->spinBox_speed->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));           // ����
    t = ui->spinBox_overTime->value();
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));// ʱ��
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->checkBox_lock->checkState();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));           // ����

    cp->setCanPack_IdCode(QString("0x%1").arg(0,2,16,QChar('0')),QString("0x%1").arg(ui->spinBox_ID->value(),2,16,QChar('0')));  // ����ID
    cp->setCanPack_OrderArg(qsl);
    cp->sendCanPack();
}

void FOptMotor::on_pushButton_sample_vpos_clicked()
{
    QStringList qsl;
    uint t;

    qsl.append(QString("%1").arg(CMD_TYPE_SAMPLE,2,16,QChar('0')));
    t = ui->spinBox_mototNum->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append(QString("%1").arg(CMD_SAMPLE_V_MOVE_POS,2,16,QChar('0')));

    t = ui->spinBox_sample_vpos->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));           // λ��
    t = ui->spinBox_speed->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));           // ����
    t = ui->spinBox_overTime->value();
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));// ʱ��
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->checkBox_lock->checkState();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));           // ����

    cp->setCanPack_IdCode(QString("0x%1").arg(0,2,16,QChar('0')),QString("0x%1").arg(ui->spinBox_ID->value(),2,16,QChar('0')));  // ����ID
    cp->setCanPack_OrderArg(qsl);
    cp->sendCanPack();
}

void FOptMotor::on_pushButton_sample_hpos_clicked()
{
    QStringList qsl;
    uint t;

    qsl.append(QString("%1").arg(CMD_TYPE_SAMPLE,2,16,QChar('0')));
    t = ui->spinBox_mototNum->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//���ö���
    qsl.append(QString("%1").arg(CMD_SAMPLE_H_MOVE_POS,2,16,QChar('0')));

    t = ui->spinBox_sample_hpos->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));           // λ��
    t = ui->spinBox_speed->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));           // ����
    t = ui->spinBox_overTime->value();
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));// ʱ��
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    t = ui->checkBox_lock->checkState();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));           // ����

    cp->setCanPack_IdCode(QString("0x%1").arg(0,2,16,QChar('0')),QString("0x%1").arg(ui->spinBox_ID->value(),2,16,QChar('0')));  // ����ID
    cp->setCanPack_OrderArg(qsl);
    cp->sendCanPack();
}
