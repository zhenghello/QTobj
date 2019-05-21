#ifndef FCANSHOW_H
#define FCANSHOW_H

#include <QWidget>
namespace Ui {class FcanShow;}

class FcanShow : public QWidget
{
    Q_OBJECT

public:
    explicit FcanShow(QWidget *parent = 0);
    ~FcanShow();
    // 对外参数
    QList< QStringList > canDateList;// 消息的字符串缓存
    uint                 canNum;
public slots:
    // 对外函数
    void setFilterEnable(bool enable);              // 隐藏过滤器
    bool filter_show(const QStringList canDate);    // 过滤显示内容
    void append(const QStringList canDate);         // 保存can数据
    void clear();                                   // 清除数据

signals:
    void clearMyShow();                             // 请求清除屏幕
    void needTranslate(const QStringList strList);  // 需要翻译的信号
private slots:
    void filter_reload(void);                       // 重载内容

private:
    Ui::FcanShow *ui;
    void filter_init(void);
};

#endif // FCANSHOW_H
