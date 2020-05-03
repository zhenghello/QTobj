#include "fdebug.h"
#include "ui_fdebug.h"

Fdebug::Fdebug(QWidget *parent, QString firstShow, bool hideKey) :QWidget(parent),ui(new Ui::Fdebug)
{
    ui->setupUi(this);
//    setWindowFlags(windowFlags()|Qt::Window);//设置为从类
    // 设置背景色
    QPalette pal;
    pal.setColor(QPalette::Background,QColor(250,100,250));
    ui->frame_hide->setAutoFillBackground(true);
    ui->frame_hide->setPalette(pal);
    my_str.clear();

    show_count=0;
    setText(firstShow);
    hide_key(hideKey);  // 默认设置隐藏
    // 按键关联部分
    connect(ui->b_clear,SIGNAL(clicked()),this,SLOT(clear()));
    connect(ui->b_debug1,SIGNAL(clicked()),this,SLOT(click_b_debug1()));
    connect(ui->b_debug2,SIGNAL(clicked()),this,SLOT(click_b_debug2()));
}

Fdebug::~Fdebug()
{
    qInstallMessageHandler(0);// 因为DEBUG重定向的问题
    qDebug()<<"\r\nFdebug delete ==================";

    delete ui;
}
//函数名：  调试显示文本框->将输入的字符串依次显示到文本框中
//函数功能：将调试函数依次显示在调试文本框上
//输入参数：str=要添加显示的字符串
//输入参数：bcol=背景色
//输入参数：fcol=字体色
//输出参数：无
//备注：    如果输入的字符串为空，就会清空显示内容
//备注：   显示字符串 ZhengWindow::setText(QString::fromLocal8Bit("send message"));
//备注：   显示数字   ZhengWindow::setText(QString::number(count,10));

void Fdebug::setTextStyle(QString str,QColor bcol,QColor fcol,int fontW)
{
    if(str.isEmpty()||str.isNull())return; // 忽略空白内容
    ui->t_show->setTextBackgroundColor(bcol);
    ui->t_show->setTextColor(fcol);
    ui->t_show->setFontPointSize(fontW);
    ui->t_show->append (str);//这个指定用来显示调试信息的文本框
    ui->t_show->setTextBackgroundColor(QColor(255,255,255));
    ui->t_show->setTextColor(QColor(0,0,0));
    ui->t_show->setFontPointSize(8);
}
//函数名：  调试显示文本框->先打印当前时间，再打印内容
//函数功能：将调试函数依次显示在调试文本框上
//输入参数：str=要添加显示的字符串
//输出参数：无
//备注：    如果输入的字符串为空，就会清空显示内容
//备注：   显示字符串 ZhengWindow::setText(QString::fromLocal8Bit("send message"));
//备注：   显示数字   ZhengWindow::setText(QString::number(count,10));

void Fdebug::setTextAutoTime(QString str)
{
    QDateTime curTime = QDateTime::currentDateTime();
    QString   strTime = curTime.toString("hh:mm:ss  ");//时间串
    strTime = strTime + str;
    ui->t_show->append (strTime);//这个指定用来显示调试信息的文本框
}
//函数名：  调试显示文本框->将输入的字符串依次显示到文本框中
//函数功能：将调试函数依次显示在调试文本框上
//输入参数：str=要添加显示的字符串
//输出参数：无
//备注：    如果输入的字符串为空，就会清空显示内容
//备注：   显示字符串 ZhengWindow::setText(QString::fromLocal8Bit("send message"));
//备注：   显示数字   ZhengWindow::setText(QString::number(count,10));
void Fdebug::setText(QString str)
{
    show_count++;
    QString num_str = QString::number(show_count,10);//将i 转为字符串
    my_str = (num_str + "." + str);
    ui->t_show->append (my_str);//这个指定用来显示调试信息的文本框

}
//函数名：  调试显示文本框->中文在uit8下自己转
//函数功能：显示字符串
//输入参数：
//输出参数：无
//备注：
void Fdebug::setChar(char *s)
{
    setText(QString::fromLocal8Bit(s));
}
//函数名：  调试显示文本框->将输入的字符串和数字依次显示到文本框中
//函数功能：显示数字
//输入参数：
//输出参数：无
//备注：
void Fdebug::setCharNum(char *s,int num)
{
    setText(QString::fromLocal8Bit(s)+QString::number (num));
}
// 函数功能:隐藏按键
void Fdebug::hide_key(bool hide)
{
    if(hide)ui->frame_hide->hide();
      else  ui->frame_hide->show();
}
// 设置 “调试1” 的内容
void Fdebug::set_debug1(QString str)
{
    ui->e_debug1->setText(str);
}
// 设置 “调试2” 的内容
void Fdebug::set_debug2(QString str)
{
    ui->e_debug2->setText(str);
}
// *********************************************************************************** 点击“清空显示”
void Fdebug::clear(void)
{
    show_count = 0;
    my_str.clear();
    ui->t_show->clear();
}
// *********************************************************************************** 点击 “调试1”
void Fdebug::click_b_debug1(void)
{
    setText("D:Fdebug1->"+ui->e_debug1->text());
    emit debug_signal1(ui->e_debug1->text());   //发送信号
}
// *********************************************************************************** 点击 “调试2”
void Fdebug::click_b_debug2(void)
{
    QStringList strlist;
    // 2.2.分割字符段
    strlist = ui->e_debug2->toPlainText().split("\n");
    for(int i=0;i<strlist.size();i++)
    {
        setText("D:Fdebug2->"+strlist.at(i));
        emit debug_signal2(strlist.at(i));   //发送信号
    }
}




#include <QMutex>
//日志打印到myDebug
void qDebugOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QMutex mutex;//日志代码互斥锁
    mutex.lock();
    //QString line_str = QString::number(context.line);
    QString fun_str;
#ifdef QDEBUG_PRINT_FUNCTION
    fun_str = QString(context.function) + "\r\n";
#endif
    QString str = fun_str + msg;
    switch (type)
    {
      case QtDebugMsg:
        Fdebug::myqDebug()->setText(str);
        break;
      case QtInfoMsg:
        Fdebug::myqDebug()->setText(str);
        break;
      case QtWarningMsg:
        Fdebug::myqDebug()->setText(str);
        break;
      case QtCriticalMsg:
        Fdebug::myqDebug()->setText(str);
        break;
      case QtFatalMsg:
        Fdebug::myqDebug()->setText(str);
        abort();
    }
    mutex.unlock();
}
