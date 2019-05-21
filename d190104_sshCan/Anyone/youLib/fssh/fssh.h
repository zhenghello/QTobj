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




public slots:
    /* Sftp库相关槽 */
    QSsh::SftpChannel::State state(){if(sftpChannel!=NULL)return sftpChannel->state();}
    QSsh::SftpJobId SSH_downloadFile(const QString &remotePath, const QString &localPath);      // 下载文件
    QSsh::SftpJobId SSH_uploadFile  (const QString &localPath, const QString &remotePath );     // 上传文件

    QSsh::SftpJobId SSH_uploadDir(const QString &localDirPath,    const QString &remoteParentDirPath);// 文件夹
    QSsh::SftpJobId SSH_downloadDir(const QString &remoteDirPath,       const QString &localDirPath);

    void statFile(const QString &path){ sftpChannel->statFile(path); }                          // 判断文件状态

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
//    void OnFileInfoAvailable(QSsh::SftpJobId job, const QList<QSsh::SftpFileInfo> &fileInfoList);





signals:
    void sshIsConnected();                                      // SSH连接成功
    void sshIsDisconnected();                                   // SSH连接断开
    void receiveSshDate(QString str);                           // SSH发送回数据
    void sshConnectErr(QString str);                            // SSH连接出错信号

    void sFtpFinished(QSsh::SftpJobId job, const QString &error);// FTP文件操作结束信号
private:
    // 内部函数
    QString sshErrorToString(QSsh::SshError error);

    // 内部ssh的相关参数
    QSsh::SshConnection     *sshConnection; // Ssh连接
    QSsh::SshRemoteProcess  *sshShell     ;      // Ssh命令行
    QSsh::SftpChannel       *sftpChannel  ;   // sftp通道
};

#endif // FSSH_H
