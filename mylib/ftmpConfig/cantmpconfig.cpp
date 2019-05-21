#include "cantmpconfig.h"
#include "ui_cantmpconfig.h"

canTmpConfig::canTmpConfig(QWidget *parent) :QWidget(parent),ui(new Ui::canTmpConfig)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()|Qt::Window);//设置为外框

    configPID = new canPack(12);// 初始化一个 can 包格式
    configPID->hide();

    configTmp = new canPack(2);
    configTmp->hide();
    openTmp = new canPack(1);
    openTmp->hide();
    readTmp = new canPack(0);
    readTmp->hide();

}
canTmpConfig::~canTmpConfig()
{
    delete ui;
}
//设置PID
void canTmpConfig::on_b_setPID_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("62");
    t = ui->box_num->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//设置对象
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
// 读取PID
void canTmpConfig::on_b_getPID_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("62");       // 命令码
    t = ui->box_num->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//设置对象
    qsl.append("41");       // PID查询命令
    readTmp->setCanPack_OrderArg(qsl);
    readTmp->sendCanPack();
}
// 设置温度
void canTmpConfig::on_b_setTmp_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("62");
    t = ui->box_num->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//设置对象
    qsl.append("20");
    t = ui->box_tmp->value()*100;
    qsl.append(QString("%1").arg((t>> 8)&0xFF,2,16,QChar('0')));
    qsl.append(QString("%1").arg((t>> 0)&0xFF,2,16,QChar('0')));
    configTmp->setCanPack_OrderArg(qsl);
    configTmp->sendCanPack();
}
// 读取温度值
void canTmpConfig::on_b_readTmp_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("62");       // 命令码
    t = ui->box_num->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//设置对象
    qsl.append("10");       // 温度查询命令
    readTmp->setCanPack_OrderArg(qsl);
    readTmp->sendCanPack();
}

// 打开温度控制
void canTmpConfig::on_b_openTmp_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("62");
    t = ui->box_num->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//设置对象
    qsl.append("01");
    qsl.append("01");//打开
    openTmp->setCanPack_OrderArg(qsl);
    openTmp->sendCanPack();
}
// 关闭温度控制
void canTmpConfig::on_b_closeTmp_clicked()
{
    QStringList qsl;
    uint t;
    qsl.append("62");
    t = ui->box_num->value();
    qsl.append(QString("%1").arg(t,2,16,QChar('0')));//设置对象
    qsl.append("01");
    qsl.append("00");//关闭
    openTmp->setCanPack_OrderArg(qsl);
    openTmp->sendCanPack();
}
// 允许设置PID 参数
void canTmpConfig::on_checkBox_setPidEnable_clicked(bool checked)
{
    ui->frame_PID->setEnabled(checked);
}
