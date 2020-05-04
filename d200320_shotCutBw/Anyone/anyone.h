#ifndef ANYONE_H
#define ANYONE_H

#include <QMainWindow>
#include <QSettings>
#include "fdebug.h"

namespace Ui {class AnyOne;}

class AnyOne : public QMainWindow
{
    Q_OBJECT

    enum saveBit { // 文件保存位数
        RGB  = 0x00,
        GRAY = 0x01,
        BW   = 0x02,
    };
    enum imgType {  // 文件保存类型
        JPG  = 0x00,
        PNG  = 0x01,
        BMP  = 0x02,
    };
public:
    explicit AnyOne(QWidget *parent = 0);
    ~AnyOne();

    bool imgRbg2bw(QString filePathAndName, QString outPathAndName, QString fileType);  // 将RGB图片转为纯黑白图
    bool loadForderFile(QString &forderPath, QStringList &filePathAndNames, QStringList &fileNames,
                        QString defaultPath, QString fileType);                         // 打开文件夹和导入所有文件
    bool cutAllScreen(QString savePath="./", QString saveName="S", saveBit bit=RGB, imgType type=JPG);                                        // 截取当前整个屏幕

private slots:
    void on_pushButton_end_clicked();
    void myTimerOut();

    void on_button_SelectSavePath_clicked();
    void on_button_OpenSavePath_clicked();
    void on_button_start_clicked();


    void on_button_one_clicked();

private:
    Ui::AnyOne *ui;
    QTimer  myTimer;
    Fdebug *mydebug;
    QString exePath;                // 可执行文件的路径,即使在其他位置启动，也可以正常找到配置文件
    QSystemTrayIcon *trayIcon;      // 小图标

    void dat_config_save(void);
    void dat_config_load(void);


};

#endif // ANYONE_H
