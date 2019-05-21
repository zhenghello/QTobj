#ifndef FSSHGUI_H
#define FSSHGUI_H

#include <QWidget>
#include <QList>
#include <QMessageBox>
#include <QProcess>

#include "fssh.h"
#include "sshconnection.h"
#include "qsharedpointer.h"
#include "sshremoteprocess.h"
#include "sftpchannel.h"

#include "fdebug.h"
#include "FsshGuiAutoAck.h"

namespace Ui {class FsshGui;}

class FsshGui : public QWidget
{
    Q_OBJECT
public:
    explicit FsshGui(QWidget *parent = 0, QString name = "sshGui");
    ~FsshGui();

public slots:   // �ⲿ�ӿں���
    void setSshIP(QString str);     // ����IP
    void openSsh();                 // ��SSH
    void closeSsh();                // �ر�SSH
    bool sendSshCmd(QString str);   // ����SSH����
    bool isConnected(){return myssh.isConnected();}    //  �ж�����
    void clear(void);   // �������
    // �ļ��������
    void SSH_downloadFile(const QString &remotePath,   const QString &localPath);
    void SSH_uploadFile(const QString &localPath,      const QString &remotePath);
    void SSH_downloadDir(const QString &remoteDirPath, const QString &localDirPath);
    void SSH_uploadDir(const QString &localDirPath,    const QString &remoteDirPath);


private slots:
    void autoConnect();
    void resizeEvent(QResizeEvent *event);
    void on_checkBox_SrceenAutoExpand_clicked();    // �Զ�����

    // ssh �������
    void on_button_open_clicked();                 //
    void mysshIsConnect();                         //
    void mysshIsDisConnect();                      //
    void mysshCommandBack(QString str);            //
    void mysshIsError(QString str);                //

    void OnSftpFinished(QSsh::SftpJobId job, const QString &error); // FTP �ļ���������

    void on_button_send_clicked();
    void on_pushButton_clicked();




    void on_lineEdit_sendSingle_editingFinished();
    void on_button_uploadFile_clicked();
    void on_button_recvFile_clicked();
    void on_button_openLocalFile_clicked();
    void on_button_downloadDir_clicked();
    void on_button_uploadDir_clicked();
    void on_button_openLocalDir_clicked();
    void on_groupBox_file_clicked();
    void on_groupBox_order_clicked();
    void on_groupBox_land_clicked();
    void on_groupBox_autoAck_clicked();

signals:
    void connectSuccess(void);          // ���ӳɹ��ź�
    void connectFailure(void);          // ����ʧ���ź�
    void revMsg(QString str);           // �յ�SSH�����ź�
    void sFtpFinished(QSsh::SftpJobId job, const QString &error);// FTP�ļ����������ź�

private:
    Ui::FsshGui *ui;
    Fdebug      *sshOut;
    Fssh        myssh;     // ����һ��ssh����
    QMessageBox *msgBox;
    QMessageBox *ftpBox;
    QTimer      *timerAutoConnect;          // �Զ�������ʱ�� ->5���Զ�����
    QVector<FsshGuiAutoAck*> autoAck;      // �Զ�Ӧ��ĵ�ַ

    void dat_config_save(void);
    void dat_config_load(void);
};

#endif // FSSHGUI_H
