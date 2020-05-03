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
    //
    void on_b1_clicked();
    void on_b2_clicked();
    void on_b3_clicked();
    void on_b4_clicked();
    void on_b5_clicked();

    void on_b101_clicked();
    void on_b102_clicked();
    void on_b103_clicked();

    void myTimerOut();

    void on_b104_clicked();

private:
    QTimer  myTimer;

    Fdebug *mydebug;
    QString exePath;                // 可执行文件的路径,即使在其他位置启动，也可以正常找到配置文件
    QSystemTrayIcon *trayIcon;      // 小图标

    void dat_config_save(void);
    void dat_config_load(void);
    Ui::AnyOne *ui;
};

#endif // ANYONE_H
