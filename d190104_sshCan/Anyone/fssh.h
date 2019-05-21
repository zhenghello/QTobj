#ifndef FSSH_H
#define FSSH_H

#include <QObject>


#include "ssherrors.h"
#include "sftpdefs.h"
#include "sshconnection.h"
#include "qsharedpointer.h"
#include "sshremoteprocess.h"
#include "sftpchannel.h"

class Fssh :public QObject
{
    Q_OBJECT
public:
    Fssh();

    void SSH_connectToHost(const QString& host, quint16 port, const QString& user, const QString& password,quint16 timeout);//
    void SSH_disconnectFromHost();                                                                                          //
    bool isConnected();                                                                                                     // ����״̬
    bool SSH_sendCommand(const QString& command);                                                                           //
    QSsh::SftpJobId SSH_downloadFile(const QString &remotePath, const QString &localPath);                                      //

private slots:
    /* Ssh����ز� */
    void onSshConnected();
    void onSshDisconnected();
    void onSshError(QSsh::SshError error);
    void onSshDataAvailable(const QString& message);
    /* SshShell����ز� */
    void onSshShellStarted();
    void onSshShellStandardError();
    void onSshShellStandardOutputReady();
    void onSshShellClosed(int exitStatus);
    /* Sftp����ز� */
    void OnSftpInitialized();
    void OnSftpInitializationFailed(const QString &reason);
    void OnSftpChannelClosed();
    void OnSftpFinished(QSsh::SftpJobId job, const QString &error);
    void OnFileInfoAvailable(QSsh::SftpJobId job, const QList<QSsh::SftpFileInfo> &fileInfoList);


signals:
    void sshIsConnected();                                      // SSH���ӳɹ�
    void sshIsDisconnected();                                   // SSH���ӶϿ�
    void receiveSshDate(QString str);                           // SSH���ͻ�����


    void downloadFileFinished(QSsh::SftpJobId job, const QString &error);// �����ļ�����
private:
    // �ڲ�����
    QString sshErrorToString(QSsh::SshError error);

    // �ڲ�ssh����ز���
    QSsh::SshConnection     *sshConnection; // Ssh����
    QSsh::SshRemoteProcess  *sshShell;      // Ssh������
    QSsh::SftpChannel       *sftpChannel;   // sftpͨ��
};

#endif // FSSH_H
