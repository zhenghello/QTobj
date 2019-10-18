#ifndef CANSEND_H
#define CANSEND_H

#include <QWidget>
#include "ftreeDabeBase.h"
#include "FsshGui.h"

#include "cantmpconfig.h"   // �¶ȵ��ڽ���.
#include "fOptMotor.h"      // ������Խ���
#include "upgradeModel.h"   // ����ģ��


namespace Ui {class canSend;}

class canSend : public QWidget
{
    Q_OBJECT
public:
    explicit canSend(QWidget *parent = 0,QString titleName = "canSendNoTitleName");
    ~canSend();

public slots:
    void openSsh()              {sshPort->closeSsh();sshPort->openSsh();}   //�ȹ��ٿ�
    void closeSsh()             {sshPort->closeSsh();   }
    bool isConnected()          {return sshPort->isConnected();}
    void setSshIP(QString str)  {sshPort->setSshIP(str);   }
//    void sendSshCmd(QString str){sshPort->sendSshCmd(str); }
    void clear()                {sshPort->clear();}
    void sendCanMsg(QString str);  // ����Ҫ���͵�����

private slots:
    void msgTreeAnalyze(QTreeWidgetItem *tree,int column);  // Can��������ε����Ӧ ����
    void showSshOpenMsg(){myShow->setTextStyle(QString("canSend SSH is Open->")+windowTitle(),Qt::green,Qt::white,16);} // ��ssh����
    void showSshCloseMsg(){myShow->setTextStyle(QString("canRecv SSH is Close->")+windowTitle(),Qt::red,Qt::white,16);}
    void fileTreeOperate(QTreeWidgetItem *tree,int column);  // �ļ���ص����ε����Ӧ ����
    void on_button_reboot_clicked();    //
    void button_reboot_setEnableTrue(void); // �����ָ�


    void on_button_temp_clicked();

    void on_button_upgrade_modular_clicked();

    void on_pushButton_debug_clicked();

    void on_button_motor_clicked();

    void on_button_text_clicked();

    void on_pushButton_bathcOrder_clicked();
    void bathcOrder_timeout();

signals:
    void sFtpFinished(QSsh::SftpJobId job, const QString &error);// FTP�ļ����������ź�
private:
    Ui::canSend *ui;
    FsshGui         *sshPort    = NULL;     // SSH�˿�
    FtreeDabeBase   *treeOredr  = NULL;     // ���������
    FtreeDabeBase   *treeFile   = NULL;     // ���������
    canTmpConfig    *pTmpCfg    = NULL;     // �¶�����
    FOptMotor       *pMotor     = NULL;
    UpgradeModel    *pupgrade   = NULL;     // ����ģ��

    QStringList     strList_batch ;     // ��������ģ��
    QTimer          timer_batch ;       // ��������ģ��Ķ�ʱ��

    void dat_config_save(void);
    void dat_config_load(void);

};

#endif // CANSEND_H
