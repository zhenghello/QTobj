#include "fssh.h"

Fssh::Fssh()
{
    sshConnection = NULL;
    sshShell      = NULL;
    sftpChannel   = NULL;
}
// ******************************************** �ⲿ���� **************************************************************************************** begin
// �ⲿ����->��������
void Fssh::SSH_connectToHost(const QString& host, quint16 port, const QString& user, const QString& password,quint16 timeout)
{
    // SSH����
    QSsh::SshConnectionParameters sshParameters;
    sshParameters.port                  = port;
    sshParameters.host                  = host;
    sshParameters.timeout               = timeout;
    sshParameters.userName              = user;
    sshParameters.password              = password;
    sshParameters.authenticationType    = QSsh::SshConnectionParameters::AuthenticationByPassword;
    // ��������
    sshConnection = new QSsh::SshConnection(sshParameters);
    connect(sshConnection, SIGNAL(connected()), this, SLOT(onSshConnected()));
    connect(sshConnection, SIGNAL(disconnected()), this, SLOT(onSshDisconnected()));
    connect(sshConnection, SIGNAL(error(QSsh::SshError)), this, SLOT(onSshError(QSsh::SshError)));

    connect(sshConnection, SIGNAL(dataAvailable(const QString &)), this, SLOT(onSshDataAvailable(const QString&)));
    // ��������
    sshConnection->connectToHost();
}
// �ⲿ����->�ر�����
void Fssh::SSH_disconnectFromHost()
{
    qDebug() << "Ssh disconnectFromHost";

    // �Ͽ����� -- ������bug
    if (sshConnection)
    {
        sshShell        = NULL;
        sftpChannel     = NULL;
        sshConnection->disconnectFromHost();
    }
}
// �ⲿ����->����״̬
bool Fssh::isConnected()
{
    return (sshConnection && sshConnection->state() == QSsh::SshConnection::Connected);
}
// �ⲿ����->ִ������
bool Fssh::SSH_sendCommand(const QString& command)
{
    // qDebug() << "rawCommand:" << command;
    // �ж�����
    if (sshConnection->state() != QSsh::SshConnection::Connected)
    {
        qWarning() << "Ssh rawCommand unconnected";
        return false;
    }
    // ��ӻس�
    QString shell = (command + "\r");
    // ִ������
    int writed = sshShell->write(shell.toStdString().c_str());
    return (shell.length() == writed);
}
// ******************************************** �ⲿ���� **************************************************************************************** end



// ******************************************** �ڲ�����-> Ssh����ز�  **************************************************************************************** begin
// ���Ӵ������� -> ����Ssh����
void Fssh::onSshConnected()
{
    qDebug() << "Ssh:onSshConnected ";
    // ��ȡȡ���Ӷ�Ӧ��������
    QSharedPointer<QSsh::SshRemoteProcess> shareSshShell = sshConnection->createRemoteShell();
    if (!shareSshShell.isNull())
    {
        sshShell = shareSshShell.data();
        connect(sshShell, SIGNAL(started()),                    this, SLOT(onSshShellStarted()));
        connect(sshShell, SIGNAL(closed(int)),                  this, SLOT(onSshShellClosed(int)));
        connect(sshShell, SIGNAL(readyReadStandardError()),     this, SLOT(onSshShellStandardError()));
        connect(sshShell, SIGNAL(readyReadStandardOutput()),    this, SLOT(onSshShellStandardOutputReady()));

//        connect(sshShell, SIGNAL(readyReadStandardOutput()), this, SIGNAL(readyReadStandardOutput()));
        // ���������н���
        sshShell->start();
        // �������ӳɹ��ź�
        emit sshIsConnected();
    }
    else
    {
        qWarning() << "Ssh onSshConnected no sshShell";
    }


    // ��ȡȡ���Ӷ�Ӧ��FTP����
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
// ���Ӵ������� -> Ssh���ӶϿ�
// Ssh���ӶϿ�
void Fssh::onSshDisconnected()
{
    qDebug() << "Ssh:onSshDisconnected ";
    sshConnection->deleteLater();
    sshConnection   = NULL;
    sshShell        = NULL;
    sftpChannel     = NULL;
    emit sshIsDisconnected();
}
// Ssh����
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
// Ssh���ݾ���
void Fssh::onSshDataAvailable(const QString& message)
{
    qDebug() << "Ssh:onSshDataAvailable " << message;
}
// ******************************************** �ڲ�����-> Ssh����ز�  **************************************************************************************** end

// ******************************************** �ڲ�����-> SshShell����ز� **************************************************************************************** begin
// SshShell ��ʼ
void Fssh::onSshShellStarted()
{
    qDebug() << "SshShell:onSshShellStarted";
}
// SshShell��׼�������
void Fssh::onSshShellStandardError()
{
    // ����̨���
    QString output = sshShell->readAllStandardOutput();
    qDebug() << "SshShell:onSshShellStandardError" << output;
}
// SshShell��׼������� -> ������յ�����
void Fssh::onSshShellStandardOutputReady()
{
    // ����̨���
    //    qDebug() << d->output;
    emit receiveSshDate(sshShell->readAllStandardOutput());
}

// SshShell�˳�
void Fssh::onSshShellClosed(int exitStatus)
{
    qDebug() << "SshShell:onSshShellClosed" << exitStatus;
}
// ******************************************** �ڲ�����-> SshShell����ز� **************************************************************************************** end
// ******************************************** �ڲ�����-> sftp����ز� **************************************************************************************** begin
// �ⲿ����->ִ��ftp�ļ�����
QSsh::SftpJobId Fssh::SSH_downloadFile(const QString &remotePath, const QString &localPath)
{
    if(sftpChannel==NULL || sftpChannel->state() != QSsh::SftpChannel::Initialized )    return 0;
    return sftpChannel->downloadFile(remotePath, localPath, QSsh::SftpOverwriteExisting);   // ����ģʽ
}
// �ⲿ����->ִ��ftp�ļ��ϴ�
QSsh::SftpJobId Fssh::SSH_uploadFile(const QString &localPath, const QString &remotePath)
{
    if(sftpChannel==NULL || sftpChannel->state() != QSsh::SftpChannel::Initialized )    return 0;
    return sftpChannel->uploadFile(localPath, remotePath, QSsh::SftpOverwriteExisting);   // ����ģʽ
}
// �ⲿ����->ִ��ftp�ļ��ϴ��ļ���
QSsh::SftpJobId Fssh::SSH_uploadDir(const QString &localDirPath,           const QString &remoteDirPath)
{
    if(sftpChannel==NULL || sftpChannel->state() != QSsh::SftpChannel::Initialized )    return 0;
    return sftpChannel->uploadDir(localDirPath, remoteDirPath);
}
// �ⲿ����->ִ��ftp�ļ������ļ���
QSsh::SftpJobId Fssh::SSH_downloadDir(const QString &remoteDirPath,     const QString &localDirPath)
{
    if(sftpChannel==NULL || sftpChannel->state() != QSsh::SftpChannel::Initialized )    return 0;
    return sftpChannel->downloadDir(remoteDirPath, localDirPath, QSsh::SftpOverwriteExisting);
}
// �ⲿ����->ִ��FTP��ʼ��
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
    emit sFtpFinished(job, error);  //  ת������FTP���������ĺ���
}

//void Fssh::OnFileInfoAvailable(QSsh::SftpJobId job, const QList<QSsh::SftpFileInfo> &fileInfoList)
//{

//}
// ******************************************** �ڲ�����-> sftp����ز� **************************************************************************************** end

// �����ַ�������
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

