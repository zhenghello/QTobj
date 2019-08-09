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
    void on_pushButton_clicked();
    void upgradeOrder();
    void sendSsCmd(void);

private:
    Ui::UpgradeModel *ui;
    FsshGui         *sshPort;    // SSH¶Ë¿Ú

};


#endif // UPGRADEMODEL_H
