#ifndef FDEBUG_H
#define FDEBUG_H


#define QDEBUG_PRINT_FUNCTION // 有这一行，就会显示打印内容的函数,只有调试才用，平时不用。

#include <QWidget>
#include <QtWidgets>
#include <QDebug>

void qDebugOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);// 重定向输出内容

namespace Ui {class Fdebug;}
class Fdebug : public QWidget
{
    Q_OBJECT
public:
    explicit Fdebug(QWidget *parent = 0,QString firstShow = "Hello World!", bool hideKey = true);
    ~Fdebug();
    // 内部参数
    /* 懒汉式->单例模式 Fdebug::myDebug()->*/
    static Fdebug *myDebug(QWidget *parent = 0)      // 用于调试界面
    {
        static Fdebug *my_debug;
        if(my_debug == NULL) //判断是否第一次调用
        {
            my_debug = new Fdebug(parent,"myDebug");
        }
        return my_debug;
    }
    static Fdebug *myqDebug(QWidget *parent = 0)      // 用于调试界面
    {
        static Fdebug *my_qdebug;
        if(my_qdebug == NULL) //判断是否第一次调用
        {
            my_qdebug = new Fdebug(parent,"myqDebug");
            qInstallMessageHandler(qDebugOutput);// 关联
        }
        return my_qdebug;
    }
    static Fdebug *myShow(QWidget *parent = 0)       // 用于主显示
    {
        static Fdebug *my_show;
        if(my_show == NULL)
            my_show = new Fdebug(parent,"myShow");
        return my_show;
    }
    static Fdebug *myTest(QWidget *parent = 0)       // 用于测试
    {
        static Fdebug *my_test;
        if(my_test == NULL)
            my_test = new Fdebug(parent,"myTest");
        return my_test;
    }
    // 显示相关
    void setTextStyle(QString str, QColor bcol = QColor(255,255,255), QColor fcol= QColor(0,0,0), int fontW = 8);    // 可以让显示的字体改变颜色和大小
    void setTextAutoTime (QString str);     // 可以自动打印时间再打印内容
    void setText(QString str);              // 普通打印数据
    void setChar(char *s);                  // 输入字符串
    void setCharNum(char *s,int num);       // 打印数字

    // 操作相关
    void hide_key(bool hide=true);                        // 隐藏按键部分
    void set_debug1(QString str);           // 设置调试1内容
    void set_debug2(QString str);           // 设置调试2内容
signals:
    void debug_signal1(QString str);        // 带有调试功能的按键1
    void debug_signal2(QString str);        // 带有调试功能的按键2
public slots:
    void clear(void);
private slots:
    void click_b_debug1(void);
    void click_b_debug2(void);

private:
    Ui::Fdebug *ui;
    QString my_str;
    quint32 show_count;
};
extern Fdebug *myqDebug;
extern Fdebug *myDebug;
extern Fdebug *myShow;
extern Fdebug *myTest;

#endif // FDEBUG_H
