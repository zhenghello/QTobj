#ifndef FCANSHOW_H
#define FCANSHOW_H

#include <QWidget>
#include "fdebug.h"
//#include "./zkpku/packExp/pack_explain.h"
#include "canExplain.h"
namespace Ui {class FcanShow;}

class FcanShow : public QWidget
{
    Q_OBJECT

public:
    explicit FcanShow(QWidget *parent = 0);
    ~FcanShow();
    /* 懒汉式->单例模式*/
    static FcanShow *myCanShow()      //
    {
        static FcanShow *my1;
        if(my1 == NULL) //判断是否第一次调用
            my1 = new FcanShow();
        return my1;
    }
    // 对外参数
    QStringList     canStrBuf;       // 消息的字符串缓存
    //QByteArrayList  canByteBuf;      // 消息的二进制缓存
    QList< QVector<uint> > canByteBuf;
    QList<QColor>   canColorBuf;     // 颜色缓存
    Fdebug          *myShow;
public slots:
    // 对外函数
    void setFilterEnable(bool enable);    // 隐藏过滤器


    void deal_can_order(QByteArray qby);

private slots:
    void filter_reload(void);

private:
    Ui::FcanShow *ui;

    void filter_init(void);
    void filter_show(QVector<uint> qby, QString str, QColor col);
};

#endif // FCANSHOW_H
