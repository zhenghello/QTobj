#ifndef UPGRADEMODEL_H
#define UPGRADEMODEL_H

#include <QWidget>
#include "FsshGui.h"

namespace Ui {class UpgradeModel;}

class UpgradeModel : public QWidget
{
    Q_OBJECT

public:
    explicit UpgradeModel(QWidget *parent ,FsshGui *pSshPort);
    ~UpgradeModel();

private slots:
    void on_pushButton_2_clicked();
    void sFtpFinished(QSsh::SftpJobId job, const QString &error);// FTP文件操作结束信号

private:
    Ui::UpgradeModel *ui;
    FsshGui         *sshPort;       // SSH端口
    QTableWidget    *tableWidget;   // 存放数据的table
    QString         proName;        // 升级的项目对象

    QString objName               ; // 2列存放着路径
    QString sshOrder              ; // 3列存放着要执行的命令
};


#endif // UPGRADEMODEL_H
