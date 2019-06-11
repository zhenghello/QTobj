#ifndef CANSEND_H
#define CANSEND_H

#include <QWidget>
#include "ftreeDabeBase.h"
#include "FsshGui.h"

#include "cantmpconfig.h"   // �¶ȵ��ڽ���


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

    void on_button_reboot_clicked();


    void on_button_temp_clicked();

signals:
    void sFtpFinished(QSsh::SftpJobId job, const QString &error);// FTP�ļ����������ź�
private:
    Ui::canSend *ui;
    FsshGui         *sshPort;    // SSH�˿�
    FtreeDabeBase   *treeOredr;  // ���������
    FtreeDabeBase   *treeFile;   // ���������
    canTmpConfig    *pTmpCfg;       // �¶�����
    void dat_config_save(void);
    void dat_config_load(void);

};

#endif // CANSEND_H
