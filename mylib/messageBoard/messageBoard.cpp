#include "messageBoard.h"


messageBoard::messageBoard(QWidget *parent,QString setTitle) :QWidget(parent)
{

    // 新建器件
    title           = new QLabel(setTitle);
    title->setAlignment(Qt::AlignHCenter);
    title->setStyleSheet("background-color: rgb(200, 200, 200);");
    messageHigh     = new QSpinBox(this);
    messageHigh->setRange(60,1000);
    messageHigh->setValue(50);
    messageHigh->setMaximumWidth(50);   //
    message         = new QTextEdit(this);
    // 新建布局
    mainGridLayout  = new QGridLayout(this);
    mainGridLayout->setHorizontalSpacing(2);
    mainGridLayout->setVerticalSpacing(2);
    mainGridLayout->setContentsMargins(2, 2, 2, 2);
    mainGridLayout->addWidget(title,0,0,1,1);
    mainGridLayout->addWidget(messageHigh,0,1,1,1);
    mainGridLayout->addWidget(message,1,0,1,2);

    // 设置本部件的表面属性
    setWindowTitle(QString::fromLocal8Bit("留言板"));
    // 设置背景色
    QPalette pal;
    pal.setColor(QPalette::Background,QColor(0,0,255));
    setAutoFillBackground(true);
    setPalette(pal);
    setMaximumHeight(messageHigh->value());// 利用输入作为最大高度
    QObject::connect(messageHigh,SIGNAL(valueChanged(int)),this,SLOT(setMaxHeight(int)));// 关联窗口高度

    config_filename =".\\config\\messageBoard_" + title->text() + ".dat";
    dat_config_load(config_filename);
}

messageBoard::~messageBoard(void)
{
    dat_config_save(config_filename);
}
//设置高度
void messageBoard::setMaxHeight(int height)
{
    setMaximumHeight(height);
}
// ******************************************** 数据保存 ******************************************** begin
//函数功能：导出配置
//输入参数：
//输出参数：
//备注：
void messageBoard::dat_config_save(QString filename)
{
    // 保存配置
    QSettings save_dat(filename,QSettings::IniFormat);
    save_dat.clear();
    save_dat.setIniCodec("GB2312");//支持中文
    save_dat.setValue ("have_file"        ,true);
    // ------------------------ 配置的保存
    save_dat.setValue ("message"        ,message->toPlainText());
    save_dat.setValue ("messageHigh"    ,messageHigh->value());
    setMaximumHeight(messageHigh->value());     // 重新设置高度
}
//函数功能：导入配置
//输入参数：
//输出参数：
//备注：
void messageBoard::dat_config_load(QString filename)
{
    QSettings save_dat(filename,QSettings::IniFormat);
    //判断文件存在
    if(save_dat.contains("have_file")==false)
    {
        return;
    }
    save_dat.setIniCodec("GB2312");//支持中文
    messageHigh->setValue( save_dat.value("messageHigh").toInt() );
    message->setText(QString::fromLocal8Bit(save_dat.value("message").toString().toLatin1()));
}
