#ifndef ANYONE_H
#define ANYONE_H

#include <QMainWindow>
#include <QDebug>
#include "fdebug.h"

namespace Ui {class AnyOne;}

class AnyOne : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnyOne(QWidget *parent = 0);
    ~AnyOne();

private slots:
    void b1_clicked(void);
        void b2_clicked(void);

        void autoRun_clicked(void);
        void openConfig_clicked(void);

        // table的操作
        void tableWidgetInit(void);
        void tableWidgetNoworkItemChanged(QTableWidgetItem *item);
        void tableWidgetItemPressed(QTableWidgetItem * item);
        void tableWidgetAddOne(QTableWidget *table, int row = 0, QString str = "");
        void tableWidgetMoveOne(QTableWidget *table1, int row1, QTableWidget *table2, int row2);
        void tableWidgetDelEmptyLine(QTableWidget * table);

        // 点击图标操作
        void iconActivated(QSystemTrayIcon::ActivationReason reason);
        // 注册自动运行
        void registerAppAutoRun(bool bAutoRun);
        // 自动保存
        void autoSaveTimerOut(void);
        // 捕获事件
        bool nativeEvent(const QByteArray &event_Type, void *message, long *result);
        // 标配文件-保存和导出
        void dat_config_save(void);
        void dat_config_load(void);
private:
    Ui::AnyOne *ui;

    int  isEventColseSystem;        // 触发了关机事件，关闭程序不再保存配置
    Fdebug *mydebug;
    QString exePath;                // 可执行文件的路径,即使在其他位置启动，也可以正常找到配置文件
    QSystemTrayIcon *trayIcon;      // 小图标

    // 自动保存定时器
    QTimer    autoSaveTimer;

    // 固定的保存地址
    QString pathNowork;  // 未完成地址
    QString pathFinish;  // 已完成地址
    QString pathDelete;  // 已删除地址
    QString pathMemory;  // 备忘录地址

    // table 常用的索引
    QTableWidget *tableNowork;
    QTableWidget *tableFinish;
    QTableWidget *tableDelete;
    QTableWidget *tableMemory;
    // table 列的索引的含义
    enum tableRowSense
    {
        tableRowContent        = 0,    // 内容的列
        tableRowLevel         = 1,    // 级别的列
        tableRowStartTime    = 2,    // 起始时间的
        tableRowChangeTime    = 3,    // 修改时间的
    };
    // 右击的字符串
    QString mstr_new;
    QString mstr_del;
    QString mstr_del2;
    QString mstr_finish;
    QString mstr_nowork;
    QString mstr_mulLine;

};

#endif // ANYONE_H
