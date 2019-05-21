#include "fssh.h"

Fssh::Fssh()
{
    sshConnection = NULL;
    sshShell      = NULL;
    sftpChannel   = NULL;
}
// ******************************************** 外部函数 **************************************************************************************** begin
// 外部函数->建立连接
void Fssh::SSH_connectToHost(const QString& host, quint16 port, const QString& user, const QString& password,quint16 timeout)
{
    // SSH参数
    QSsh::SshConnectionParameters sshParameters;
    sshParameters.port                  = port;
    sshParameters.host                  = host;
    sshParameters.timeout               = timeout;
    sshParameters.userName              = user;
    sshParameters.password              = password;
    sshParameters.authenticationType    = QSsh::SshConnectionParameters::AuthenticationByPassword;
    // 建立连接
    sshConnection = new QSsh::SshConnection(sshParameters);
    connect(sshConnection, SIGNAL(connected()), this, SLOT(onSshConnected()));
    connect(sshConnection, SIGNAL(disconnected()), this, SLOT(onSshDisconnected()));
    connect(sshConnection, SIGNAL(error(QSsh::SshError)), this, SLOT(onSshError(QSsh::SshError)));

    connect(sshConnection, SIGNAL(dataAvailable(const QString &)), this, SLOT(onSshDataAvailable(const QString&)));
    // 启动连接
    sshConnection->connectToHost();
}
// 外部函数->关闭连接
void Fssh::SSH_disconnectFromHost()
{
    qDebug() << "Ssh disconnectFromHost";

    // 断开连接 -- 这里有bug
    if (sshConnection)
    {
        sshShell        = NULL;
        sftpChannel     = NULL;
        sshConnection->disconnectFromHost();
    }
}
// 外部函数->连接状态
bool Fssh::isConnected()
{
    return (sshConnection && sshConnection->state() == QSsh::SshConnection::Connected);
}
// 外部函数->执行命令
bool Fssh::SSH_sendCommand(const QString& command)
{
    // qDebug() << "rawCommand:" << command;
    // 判断连接
    if (sshConnection->state() != QSsh::SshConnection::Connected)
    {
        qWarning() << "Ssh rawCommand unconnected";
        return false;
    }
    // 添加回车
    QString shell = (command + "\r");
    // 执行命令
    int writed = sshShell->write(shell.toStdString().c_str());
    return (shell.length() == writed);
}
// ******************************************** 外部函数 **************************************************************************************** end



// ******************************************** 内部函数-> Ssh库相关槽  **************************************************************************************** begin
// 连接触发函数 -> 建立Ssh连接
void Fssh::onSshConnected()
{
    qDebug() << "Ssh:onSshConnected ";
    // 获取取连接对应的命令行
    QSharedPointer<QSsh::SshRemoteProcess> shareSshShell = sshConnection->createRemoteShell();
    if (!shareSshShell.isNull())
    {
        sshShell = shareSshShell.data();
        connect(sshShell, SIGNAL(started()),                    this, SLOT(onSshShellStarted()));
        connect(sshShell, SIGNAL(closed(int)),                  this, SLOT(onSshShellClosed(int)));
        connect(sshShell, SIGNAL(readyReadStandardError()),     this, SLOT(onSshShellStandardError()));
        connect(sshShell, SIGNAL(readyReadStandardOutput()),    this, SLOT(onSshShellStandardOutputReady()));

//        connect(sshShell, SIGNAL(readyReadStandardOutput()), this, SIGNAL(readyReadStandardOutput()));
        // 启动命令行进程
        sshShell->start();
        // 发送连接成功信号
        emit sshIsConnected();
    }
    else
    {
        qWarning() << "Ssh onSshConnected no sshShell";
    }


    // 获取取连接对应的FTP对象
    QSharedPointer<QSsh::SftpChannel> shareSftpChannel = sshConnection->createSftpChannel();
    if(!shareSftpChannel.isNull())
    {
        sftpChannel = shareSftpChannel.data();

        connect(sftpChannel, SIGNAL(initialized())                                                , this, SLOT(OnSftpInitialized()));
        connect(sftpChannel, SIGNAL(initializationFailed(QString))                                , this, SLOT(OnSftpInitializationFailed(QString)));
        connect(sftpChannel, SIGNAL(closed())                                                     , this, SLOT(OnSftpChannelClosed()));
        connect(sftpChannel, SIGNAL(finished(QSsh::SftpJobId, QString))                           , this, SLOT(OnSftpFinished(QSsh::SftpJobId, QString)));
//        connect(sftpChannel, SIGNAL(fileInfoAvailable(QSsh::SftpJobId, QList<QSsh::SftpFileInfo>)), this, SLOT(OnFileInfoAvailable(QSsh::SftpJobId, QList<QSsh::SftpFileInfo>)));

        sftpChannel->initialize();
    }
    else
    {
        qWarning() << "Ssh onSshConnected no sshFtp";
    }
}
// 连接触发函数 -> Ssh连接断开
// Ssh连接断开
void Fssh::onSshDisconnected()
{
    qDebug() << "Ssh:onSshDisconnected ";
    sshConnection->deleteLater();
    sshConnection   = NULL;
    sshShell        = NULL;
    sftpChannel     = NULL;
    emit sshIsDisconnected();
}
// Ssh错误
void Fssh::onSshError(QSsh::SshError error)
{
    QString str = sshErrorToString(error);
    qDebug() << "Ssh:onSshError " << error << str;
    sshConnection->deleteLater();
    sshConnection   = NULL;
    sshShell        = NULL;
    sftpChannel     = NULL;
    emit sshConnectErr(str);
}
// Ssh数据就绪
void Fssh::onSshDataAvailable(const QString& message)
{
    qDebug() << "Ssh:onSshDataAvailable " << message;
}
// ******************************************** 内部函数-> Ssh库相关槽  **************************************************************************************** end

// ******************************************** 内部函数-> SshShell库相关槽 **************************************************************************************** begin
// SshShell 开始
void Fssh::onSshShellStarted()
{
    qDebug() << "SshShell:onSshShellStarted";
}
// SshShell标准错误就绪
void Fssh::onSshShellStandardError()
{
    // 控制台输出
    QString output = sshShell->readAllStandardOutput();
    qDebug() << "SshShell:onSshShellStandardError" << output;
}
// SshShell标准输出就绪 -> 这里接收到数据
void Fssh::onSshShellStandardOutputReady()
{
    // 控制台输出
    //    qDebug() << d->output;
    emit receiveSshDate(sshShell->readAllStandardOutput());
}

// SshShell退出
void Fssh::onSshShellClosed(int exitStatus)
{
    qDebug() << "SshShell:onSshShellClosed" << exitStatus;
}
// ******************************************** 内部函数-> SshShell库相关槽 **************************************************************************************** end
// ******************************************** 内部函数-> sftp库相关槽 **************************************************************************************** begin
// 外部函数->执行ftp文件下载
QSsh::SftpJobId Fssh::SSH_downloadFile(const QString &remotePath, const QString &localPath)
{
    if(sftpChannel==NULL || sftpChannel->state() != QSsh::SftpChannel::Initialized )    return 0;
    return sftpChannel->downloadFile(remotePath, localPath, QSsh::SftpOverwriteExisting);   // 覆盖模式
}
// 外部函数->执行ftp文件上传
QSsh::SftpJobId Fssh::SSH_uploadFile(const QString &localPath, const QString &remotePath)
{
    if(sftpChannel==NULL || sftpChannel->state() != QSsh::SftpChannel::Initialized )    return 0;
    return sftpChannel->uploadFile(localPath, remotePath, QSsh::SftpOverwriteExisting);   // 覆盖模式
}
// 外部函数->执行ftp文件上传文件夹
QSsh::SftpJobId Fssh::SSH_uploadDir(const QString &localDirPath,           const QString &remoteDirPath)
{
    if(sftpChannel==NULL || sftpChannel->state() != QSsh::SftpChannel::Initialized )    return 0;
    return sftpChannel->uploadDir(localDirPath, remoteDirPath);
}
// 外部函数->执行ftp文件下载文件夹
QSsh::SftpJobId Fssh::SSH_downloadDir(const QString &remoteDirPath,     const QString &localDirPath)
{
    if(sftpChannel==NULL || sftpChannel->state() != QSsh::SftpChannel::Initialized )    return 0;
    return sftpChannel->downloadDir(remoteDirPath, localDirPath, QSsh::SftpOverwriteExisting);
}
// 外部函数->执行FTP初始化
void Fssh::OnSftpInitialized()
{
    qDebug() << "sftp:OnSftpInitialized" << sftpChannel->state();
}

void Fssh::OnSftpInitializationFailed(const QString &reason)
{
    qDebug() << "sftp:OnSftpInitialization Failed" << reason;
}

void Fssh::OnSftpChannelClosed()
{
    qDebug() << "sftp:OnSftpChannelClosed";
}

void Fssh::OnSftpFinished(QSsh::SftpJobId job, const QString &error)
{
//    qDebug()<<"SftpJobId= "<<job<<"error="<<error;
    emit sFtpFinished(job, error);  //  转发操作FTP操作结束的函数
}

//void Fssh::OnFileInfoAvailable(QSsh::SftpJobId job, const QList<QSsh::SftpFileInfo> &fileInfoList)
//{

//}
// ******************************************** 内部函数-> sftp库相关槽 **************************************************************************************** end

// 错误字符串翻译
QString Fssh::sshErrorToString(QSsh::SshError error)
{
    if (QSsh::SshNoError == error)
    {
        return "SshNoError";
    }
    else if (QSsh::SshSocketError == error)
    {
        return "SshSocketError";
    }
    else if (QSsh::SshTimeoutError == error)
    {
        return "SshTimeoutError";
    }
    else if (QSsh::SshProtocolError == error)
    {
        return "SshProtocolError";
    }
    else if (QSsh::SshHostKeyError == error)
    {
        return "SshHostKeyError";
    }
    else if (QSsh::SshKeyFileError == error)
    {
        return "SshKeyFileError";
    }
    else if (QSsh::SshAuthenticationError == error)
    {
        return "SshAuthenticationError";
    }
    else if (QSsh::SshClosedByServerError == error)
    {
        return "SshClosedByServerError";
    }
    else if (QSsh::SshInternalError == error)
    {
        return "SshInternalError";
    }
    else
    {
        return "Ssh NULL Error";
    }
}

