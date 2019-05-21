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
    bool isConnected();                                                                                                     // 连接状态
    bool SSH_sendCommand(const QString& command);                                                                           //
    QSsh::SftpJobId SSH_downloadFile(const QString &remotePath, const QString &localPath);                                      //

private slots:
    /* Ssh库相关槽 */
    void onSshConnected();
    void onSshDisconnected();
    void onSshError(QSsh::SshError error);
    void onSshDataAvailable(const QString& message);
    /* SshShell库相关槽 */
    void onSshShellStarted();
    void onSshShellStandardError();
    void onSshShellStandardOutputReady();
    void onSshShellClosed(int exitStatus);
    /* Sftp库相关槽 */
    void OnSftpInitialized();
    void OnSftpInitializationFailed(const QString &reason);
    void OnSftpChannelClosed();
    void OnSftpFinished(QSsh::SftpJobId job, const QString &error);
    void OnFileInfoAvailable(QSsh::SftpJobId job, const QList<QSsh::SftpFileInfo> &fileInfoList);


signals:
    void sshIsConnected();                                      // SSH连接成功
    void sshIsDisconnected();                                   // SSH连接断开
    void receiveSshDate(QString str);                           // SSH发送回数据


    void downloadFileFinished(QSsh::SftpJobId job, const QString &error);// 下载文件结束
private:
    // 内部函数
    QString sshErrorToString(QSsh::SshError error);

    // 内部ssh的相关参数
    QSsh::SshConnection     *sshConnection; // Ssh连接
    QSsh::SshRemoteProcess  *sshShell;      // Ssh命令行
    QSsh::SftpChannel       *sftpChannel;   // sftp通道
};

#endif // FSSH_H
