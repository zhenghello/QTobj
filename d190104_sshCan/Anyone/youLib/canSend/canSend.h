#ifndef CANSEND_H
#define CANSEND_H

#include <QWidget>
#include "ftreeDabeBase.h"
#include "FsshGui.h"

#include "cantmpconfig.h"   // 温度调节界面.
#include "fOptMotor.h"      // 电机调试界面
#include "upgradeModel.h"   // 升级模块


namespace Ui {class canSend;}

class canSend : public QWidget
{
    Q_OBJECT
public:
    explicit canSend(QWidget *parent = 0,QString titleName = "canSendNoTitleName");
    ~canSend();

public slots:
    void openSsh()              {sshPort->closeSsh();sshPort->openSsh();}   //先关再开
    void closeSsh()             {sshPort->closeSsh();   }
    bool isConnected()          {return sshPort->isConnected();}
    void setSshIP(QString str)  {sshPort->setSshIP(str);   }
//    void sendSshCmd(QString str){sshPort->sendSshCmd(str); }
    void clear()                {sshPort->clear();}
    void sendCanMsg(QString str);  // 解析要发送的命令

private slots:
    void msgTreeAnalyze(QTreeWidgetItem *tree,int column);  // Can命令的树形点击对应 操作
    void showSshOpenMsg(){myShow->setTextStyle(QString("canSend SSH is Open->")+windowTitle(),Qt::green,Qt::white,16);} // 打开ssh操作
    void showSshCloseMsg(){myShow->setTextStyle(QString("canRecv SSH is Close->")+windowTitle(),Qt::red,Qt::white,16);}
    void fileTreeOperate(QTreeWidgetItem *tree,int column);  // 文件相关的树形点击对应 操作
    void on_button_reboot_clicked();    //
    void button_reboot_setEnableTrue(void); // 按键恢复


    void on_button_temp_clicked();

    void on_button_upgrade_modular_clicked();

    void on_pushButton_debug_clicked();

    void on_button_motor_clicked();

    void on_button_text_clicked();

    void on_pushButton_bathcOrder_clicked();
    void bathcOrder_timeout();

signals:
    void sFtpFinished(QSsh::SftpJobId job, const QString &error);// FTP文件操作结束信号
private:
    Ui::canSend *ui;
    FsshGui         *sshPort    = NULL;     // SSH端口
    FtreeDabeBase   *treeOredr  = NULL;     // 树形命令框
    FtreeDabeBase   *treeFile   = NULL;     // 树形命令框
    canTmpConfig    *pTmpCfg    = NULL;     // 温度配置
    FOptMotor       *pMotor     = NULL;
    UpgradeModel    *pupgrade   = NULL;     // 升级模块

    QStringList     strList_batch ;     // 批量发送模块
    QTimer          timer_batch ;       // 批量发送模块的定时器

    void dat_config_save(void);
    void dat_config_load(void);

};

#endif // CANSEND_H
