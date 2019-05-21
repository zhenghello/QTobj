#include "fdebug.h"

Fdebug::Fdebug(QString firstShow, bool hideKey, QWidget *parent) :QWidget(parent)
{
    // 外框设置
    if (this->objectName().isEmpty())this->setObjectName(QStringLiteral("Fdebug"));
    this->resize(300, 600);
    this->setMinimumSize(QSize(100, 100));
    QPalette palette;
    palette.setColor(QPalette::Background,QColor(250,100,250));
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    // 外框布局
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(2);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setContentsMargins(2, 2, 2, 2);
    // 主显示文本
    t_show = new QTextBrowser(this);
    t_show->setObjectName(QStringLiteral("t_show"));
    t_show->setMinimumSize(QSize(200, 100));
    t_show->setMaximumSize(QSize(1000,1000));
    QFont font;
    font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
    font.setPointSize(8);
    t_show->setFont(font);
    t_show->setStyleSheet(QStringLiteral(""));
    t_show->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    t_show->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    t_show->setOverwriteMode(false);
    verticalLayout->addWidget(t_show);
    // 隐藏框的内容
    frame_hide = new QFrame(this);
    frame_hide->setObjectName(QStringLiteral("frame_hide"));
    frame_hide->setMinimumSize(QSize(0, 30));
    frame_hide->setMaximumSize(QSize(16777215, 100));
    QPalette palette1;
    palette1.setColor(QPalette::Background,QColor(85,255,255));
    frame_hide->setAutoFillBackground(true);
    frame_hide->setPalette(palette1);
    // 隐藏框的布局
    gridLayout = new QGridLayout(frame_hide);
    gridLayout->setSpacing(1);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(1, 1, 1, 1);
    // 文本输入1
    e_debug1 = new QLineEdit(frame_hide);
    e_debug1->setObjectName(QStringLiteral("e_debug1"));
    e_debug1->setClearButtonEnabled(true);
    gridLayout->addWidget(e_debug1, 0, 1, 1, 1);
    // 文本输入2
    e_debug2 = new QTextEdit(frame_hide);
    e_debug2->setObjectName(QStringLiteral("e_debug2"));
    e_debug2->setMaximumSize(QSize(16777215, 100));
    gridLayout->addWidget(e_debug2, 1, 1, 2, 1);
    // 按键1
    b_debug1 = new QPushButton(frame_hide);
    b_debug1->setObjectName(QStringLiteral("b_debug1"));
    b_debug1->setMinimumSize(QSize(0, 0));
    b_debug1->setMaximumSize(QSize(16777215, 200));
    b_debug1->setText(QString::fromLocal8Bit("调试1"));
    gridLayout->addWidget(b_debug1, 0, 2, 1, 1);
    // 按键2
    b_debug2 = new QPushButton(frame_hide);
    b_debug2->setObjectName(QStringLiteral("b_debug2"));
    b_debug2->setMinimumSize(QSize(0, 0));
    b_debug2->setMaximumSize(QSize(16777215, 200));
    b_debug2->setText(QString::fromLocal8Bit("调试2"));
    gridLayout->addWidget(b_debug2, 1, 2, 1, 1);
    // 按键3
    b_clear = new QPushButton(frame_hide);
    b_clear->setObjectName(QStringLiteral("b_clear"));
    b_clear->setMinimumSize(QSize(0, 0));
    b_clear->setMaximumSize(QSize(16777215, 200));
    b_clear->setText(QString::fromLocal8Bit("清空"));
    gridLayout->addWidget(b_clear, 2, 2, 1, 1);
    verticalLayout->addWidget(frame_hide);
    // 自定义设置
    my_str.clear();
    show_count=0;
    setText(firstShow);
    hide_key(hideKey);  // 默认设置隐藏
    // 按键关联部分
    connect(b_clear,SIGNAL(clicked()),this,SLOT(clear()));
    connect(b_debug1,SIGNAL(clicked()),this,SLOT(click_b_debug1()));
    connect(b_debug2,SIGNAL(clicked()),this,SLOT(click_b_debug2()));
}

Fdebug::~Fdebug()
{
    qInstallMessageHandler(0);// 因为DEBUG重定向的问题
    qDebug()<<"\r\nFdebug delete ==================";
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
    t_show->setTextBackgroundColor(bcol);
    t_show->setTextColor(fcol);
    t_show->setFontPointSize(fontW);
    t_show->append (str);//这个指定用来显示调试信息的文本框
    t_show->setTextBackgroundColor(QColor(255,255,255));
    t_show->setTextColor(QColor(0,0,0));
    t_show->setFontPointSize(8);
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
    t_show->append (strTime);//这个指定用来显示调试信息的文本框
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
    t_show->append (my_str);//这个指定用来显示调试信息的文本框

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
    if(hide)frame_hide->hide();
      else  frame_hide->show();
}
// 设置 “调试1” 的内容
void Fdebug::set_debug1(QString str)
{
    e_debug1->setText(str);
}
// 设置 “调试2” 的内容
void Fdebug::set_debug2(QString str)
{
    e_debug2->setText(str);
}
// *********************************************************************************** 点击“清空显示”
void Fdebug::clear(void)
{
    show_count = 0;
    my_str.clear();
    t_show->clear();
}
// *********************************************************************************** 点击 “调试1”
void Fdebug::click_b_debug1(void)
{
    setText("D:Fdebug1->"+e_debug1->text());
    emit debug_signal1(e_debug1->text());   //发送信号
}
// *********************************************************************************** 点击 “调试2”
void Fdebug::click_b_debug2(void)
{
    QStringList strlist;
    // 2.2.分割字符段
    strlist = e_debug2->toPlainText().split("\n");
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
