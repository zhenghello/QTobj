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

public slots:   // 外部接口函数
    void setSshIP(QString str);     // 设置IP
    void openSsh();                 // 打开SSH
    void closeSsh();                // 关闭SSH
    bool sendSshCmd(QString str);   // 发送SSH命令
    bool isConnected(){return myssh.isConnected();}    //  判断连接
    void clear(void);   // 清除接收
    // 文件操作相关
    void SSH_downloadFile(const QString &remotePath,   const QString &localPath);
    void SSH_uploadFile(const QString &localPath,      const QString &remotePath);
    void SSH_downloadDir(const QString &remoteDirPath, const QString &localDirPath);
    void SSH_uploadDir(const QString &localDirPath,    const QString &remoteDirPath);


private slots:
    void autoConnect();
    void resizeEvent(QResizeEvent *event);
    void on_checkBox_SrceenAutoExpand_clicked();    // 自动扩屏

    // ssh 触发相关
    void on_button_open_clicked();                 //
    void mysshIsConnect();                         //
    void mysshIsDisConnect();                      //
    void mysshCommandBack(QString str);            //
    void mysshIsError(QString str);                //

    void OnSftpFinished(QSsh::SftpJobId job, const QString &error); // FTP 文件操作结束

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
    void connectSuccess(void);          // 连接成功信号
    void connectFailure(void);          // 连接失败信号
    void revMsg(QString str);           // 收到SSH数据信号
    void sFtpFinished(QSsh::SftpJobId job, const QString &error);// FTP文件操作结束信号

private:
    Ui::FsshGui *ui;
    Fdebug      *sshOut;
    Fssh        myssh;     // 声明一个ssh对象
    QMessageBox *msgBox;
    QMessageBox *ftpBox;
    QTimer      *timerAutoConnect;          // 自动重连定时器 ->5秒自动重连
    QVector<FsshGuiAutoAck*> autoAck;      // 自动应答的地址

    void dat_config_save(void);
    void dat_config_load(void);
};

#endif // FSSHGUI_H
