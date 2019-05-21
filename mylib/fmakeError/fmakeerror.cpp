#include "fmakeerror.h"
#include "ui_fmakeerror.h"
#include <QDebug>
FmakeError::FmakeError(QWidget *parent) :QWidget(parent),ui(new Ui::FmakeError)
{
    ui->setupUi(this);
    // 设置为外框
    setWindowFlags(windowFlags()|Qt::Window);
    // 添加CAN包协议
    idPack = new canPack(2);
    ui->verticalLayout_table->addWidget(idPack);

    errPack = new canPack(2);
    ui->verticalLayout_table->addWidget(errPack);
    errPack->setCanPack_ctlCode("D8");  // 设置控制码为EVT帧

    // 修改生效一次
    errCodeChange();
    idCodeChange();
    // 添加关联
    connect(ui->lineEdit_errCode,SIGNAL(textChanged(QString)),this,SLOT(errCodeChange()));
    connect(ui->spinBox_ID,SIGNAL(editingFinished()),this,SLOT(idCodeChange()));
}
FmakeError::~FmakeError()
{
    delete ui;
}
// 发送故障
void FmakeError::on_pushButton_send_clicked()
{
    // 发送
    idPack->sendCanPack();
    errPack->sendCanPack();
}
// 修改故障码
void FmakeError::errCodeChange(void)
{
    QStringList qsl;
    qlonglong num;
    bool ok=false;
    num = ui->lineEdit_errCode->text().toLongLong(&ok,16);
    if(ok)
    {
        ui->lineEdit_errCode->setStyleSheet("background-color: rgb(100, 255, 100);");// 绿色正确
        // 生成错误码
        qsl.append(QString("%1").arg((num>> 24)&0xFF,2,16,QChar('0'))); // 命令类型
        qsl.append(QString("%1").arg((num>> 16)&0xFF,2,16,QChar('0'))); // 命令对象
        qsl.append(QString("%1").arg(0,2,16,QChar('0'))); // 命令内容-随便
        qsl.append(QString("%1").arg((num>> 8) &0xFF,2,16,QChar('0'))); // 附带参数
        qsl.append(QString("%1").arg((num>> 0) &0xFF,2,16,QChar('0'))); // 附带参数
        errPack->setCanPack_OrderArg(qsl);
    }
    else
    {
        ui->lineEdit_errCode->setStyleSheet("background-color: rgb(255, 100, 100);");// 红色错误
    }
}
// 修改ID码
void FmakeError::idCodeChange(void)
{
    // 生成设置板块ID 的编码
    QStringList qsl;
    qsl.append("00"); // 命令类型
    qsl.append("00"); // 命令对象
    qsl.append("00"); // 命令内容
    qsl.append(QString("%1").arg(ui->spinBox_ID->value()&0xFF,2,16,QChar('0'))); // 附带参数 -发送ID
    qsl.append("00"); // 附带参数 -接收ID
    idPack->setCanPack_OrderArg(qsl);
}
