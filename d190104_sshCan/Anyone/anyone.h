#ifndef ANYONE_H
#define ANYONE_H

#include <QMainWindow>
#include "fdebug.h"
#include "messageBoard.h"
#include "canSend.h"
#include "canRecv.h"

namespace Ui {class AnyOne;}

class AnyOne : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnyOne(QWidget *parent = 0);
    ~AnyOne();

private slots:
    void on_pushButton_end_clicked();
    void on_pushButton_openSSH_clicked();
    void on_pushButton_testExplain_clicked();
    void on_pushButton_clear_clicked();
    void on_checkBox_sendFrame_clicked();
    void on_checkBox_recvFrame_clicked();
    void on_pushButton_check_clicked();
    void OnSftpFinished(QSsh::SftpJobId job, const QString &error); // FTP 文件操作结束

    void on_pushButton_openConfig_clicked();

    void on_b_5_clicked();

private:
    Ui::AnyOne *ui;
    void dat_config_save(void);
    void dat_config_load(void);
};

#endif // ANYONE_H
