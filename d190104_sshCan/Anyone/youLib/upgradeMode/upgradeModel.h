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
    void sFtpFinished(QSsh::SftpJobId job, const QString &error);// FTP�ļ����������ź�

private:
    Ui::UpgradeModel *ui;
    FsshGui         *sshPort;       // SSH�˿�
    QTableWidget    *tableWidget;   // ������ݵ�table
    QString         proName;        // ��������Ŀ����

    QString objName               ; // 2�д����·��
    QString sshOrder              ; // 3�д����Ҫִ�е�����
};


#endif // UPGRADEMODEL_H
