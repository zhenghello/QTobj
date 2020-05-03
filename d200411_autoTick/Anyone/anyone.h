#ifndef ANYONE_H
#define ANYONE_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include<QSettings>
#include "fdebug.h"

namespace Ui {class AnyOne;}

class AnyOne : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnyOne(QWidget *parent = 0);
    ~AnyOne();

private slots:
    // 点击图标操作
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    // 结束按键
    void on_pushButton_end_clicked();
    // 启动按键
    void on_button_start_clicked();
    // 开机运行
    void on_button_autoRun_clicked();

    void on_b3_clicked();
    void on_b4_clicked();
    void on_b5_clicked();
    void on_b6_clicked();

    void on_b101_clicked();
    void on_b102_clicked();
    void on_b103_clicked();

    void myTimerOut();
private:
    Ui::AnyOne *ui;
    int screenWidth;    // 屏幕宽度
    int screenHeight;   // 屏幕高度
    Fdebug *mydebug;
    QString exePath;                // 可执行文件的路径,即使在其他位置启动，也可以正常找到配置文件
    QSystemTrayIcon *trayIcon;      // 小图标

    void dat_config_save(void);
    void dat_config_load(void);
};

#endif // ANYONE_H
