#ifndef CANTMPCONFIG_H
#define CANTMPCONFIG_H

#include <QWidget>

#include "fdebug.h"
#include "canpack.h"

namespace Ui {class canTmpConfig;}

class canTmpConfig : public QWidget
{
    Q_OBJECT

public:
    explicit canTmpConfig(QWidget *parent = 0);
    ~canTmpConfig();
signals:
    void send_can_pack(QString);    // 发送can包
private slots:
    void on_b_setPID_clicked();
    void on_b_setTmp_clicked();
    void on_b_openTmp_clicked();

    void on_b_closeTmp_clicked();
    void on_checkBox_setPidEnable_clicked(bool checked);
    void on_b_readTmp_clicked();
    void on_b_getPID_clicked();


private:
    Ui::canTmpConfig *ui;
    canPack *configPID;
    canPack *configTmp;
    canPack *openTmp;
    canPack *readTmp;
};

#endif // CANTMPCONFIG_H
