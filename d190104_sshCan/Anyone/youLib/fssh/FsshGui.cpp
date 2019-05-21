#include "FsshGui.h"
#include "ui_FsshGui.h"


FsshGui::FsshGui(QWidget *parent, QString name) :QWidget(parent),ui(new Ui::FsshGui)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);     // 默认外框
    setWindowTitle(name);           // 设置文件名
    // 显示框
    sshOut = new Fdebug(this,"ssh Show message",true);
    sshOut->show();
    // 替换 label_sshOut 的位置
    ui->mainLayout->insertWidget(0,sshOut);
    ui->label_sshOut->deleteLater();

    // 文键保存
    dat_config_load();  // 配置导入

    // ssh 信号关联相关 -- begin
    connect(&myssh,SIGNAL(sshIsConnected(void))          ,this, SLOT(mysshIsConnect(void))      );
    connect(&myssh,SIGNAL(sshIsDisconnected(void))       ,this, SLOT(mysshIsDisConnect(void))   );
    connect(&myssh,SIGNAL(receiveSshDate(QString))       ,this, SLOT(mysshCommandBack(QString)) );
    connect(&myssh,SIGNAL(sshConnectErr(QString))        ,this, SLOT(mysshIsError(QString)) );
    connect(&myssh,SIGNAL(sFtpFinished(QSsh::SftpJobId,QString)),this,SLOT(OnSftpFinished(QSsh::SftpJobId,QString)));
    // ssh 信号关联相关 -- end    

    // 弹出消息框创建
    msgBox = new QMessageBox(QMessageBox::Information,QString("Please Wait!"), "Connecting SSH, IP = "+ui->lineEdit_IP->text(),QMessageBox::Ok);
    msgBox->button(QMessageBox::Ok)->hide();
    ftpBox = new QMessageBox(QMessageBox::Information,QString("Please Wait!"), QString("NULL"),QMessageBox::Ok);
    ftpBox->button(QMessageBox::Ok)->hide();
    //
    timerAutoConnect = new QTimer();
    timerAutoConnect->setInterval(5000);    // 每隔秒钟自动重连
    connect(timerAutoConnect,SIGNAL(timeout()),this,SLOT(autoConnect()));

    // 自动创建自动应答框
    ui->label_autoAck->deleteLater();
    ui->groupBox_autoAck->setMaximumHeight(ui->spinBox_autoAckNum->value()*25+50); // 扩高容器
    for(int i=0;i<ui->spinBox_autoAckNum->value();i++)
    {
        FsshGuiAutoAck *autoAckOne = new FsshGuiAutoAck(this,windowTitle()+QString("-FsshGuiAutoAck-Num%1").arg(i));
        ui->autoAckLayout->addWidget(autoAckOne);
        autoAck.append(autoAckOne);
        connect(this,SIGNAL(revMsg(QString))                ,autoAckOne ,   SLOT(dealRecMsg(QString)) );// 关联信号:FsshGui发给自动应答模块
        connect(autoAckOne,SIGNAL(autoAckSting(QString))    ,this       ,   SLOT(sendSshCmd(QString)) );          // 关联信号:自动应答模块发给FsshGui
    }
}
FsshGui::~FsshGui()
{
    dat_config_save();  // 保存配置

    closeSsh();                 // 关闭ssh
    delete sshOut;
    delete ui;
}
// 启动自动重连
void FsshGui::autoConnect()
{
    if(ui->checkBox_autoConnect->isChecked())
    {
        if(ui->button_open->text() == "open_ssh")
            on_button_open_clicked();
    }
}
// 形状改变事件，重定义函数
void FsshGui::resizeEvent(QResizeEvent *event)
{
    // 允许显示扩展
    if(ui->checkBox_SrceenAutoExpand->isChecked())
        sshOut->setMinimumHeight(height()-5);
    else
        sshOut->setMinimumHeight(100);
    if(event==NULL)return;
}
// 点击“屏幕扩展”
void FsshGui::on_checkBox_SrceenAutoExpand_clicked()
{
    resizeEvent(NULL);
}

// 点击"open_ssh" - 启动连接
void FsshGui::on_button_open_clicked()
{
    if(ui->button_open->text() == "open_ssh")
    {
        myssh.SSH_connectToHost(ui->lineEdit_IP->text(),ui->spinBox_port->value(),ui->lineEdit_name->text(),ui->lineEdit_password->text(),50);
        ui->button_open->setText("connecting_ssh");
        msgBox->setText("Connecting SSH, IP = "+ui->lineEdit_IP->text());
        msgBox->show(); // 不影响后台程序
    }
    else if(ui->button_open->text() == "close_ssh")
    {
        myssh.SSH_disconnectFromHost();
        ui->button_open->setText("disconnecting_ssh");
    }
}
// ssh 连接成功操作
void FsshGui::mysshIsConnect()
{
    sshOut->setTextStyle("mysshIsConnect",Qt::white,Qt::green,12);
    ui->button_open->setText("close_ssh");
    emit connectSuccess();      // 发送连接成功信号
    msgBox->hide(); // 关闭提示窗口
}
// ssh 断开
void FsshGui::mysshIsDisConnect()
{
    sshOut->setTextStyle("mysshIsDisConnect",Qt::white,Qt::red,12);
    ui->button_open->setText("open_ssh");
    emit connectFailure();      // 发送连接失败信号
    msgBox->hide(); // 关闭提示窗口
}
// ssh 连接出错
void FsshGui::mysshIsError(QString str)
{
    sshOut->setTextStyle("mysshIsError = "+str,Qt::white,Qt::red,12);
    ui->button_open->setText("open_ssh");
    emit connectFailure();      // 发送连接失败信号
    msgBox->hide(); // 关闭提示窗口
    QMessageBox msg(QMessageBox::Warning,QString("SSH CONNECT ERROR"), "MSG:"+str,QMessageBox::Ok);
    msg.exec();
}
// ssh 发来数据,将多行数据拆分成单行发送出去
void FsshGui::mysshCommandBack(QString str)
{
    str = str.trimmed();// 去掉无效字符
    if(str.isEmpty()||str.isNull())return;  // 忽略空白字符
    sshOut->setTextStyle(str);                      // 插入字符串到界面显示
    QStringList strList;
    strList = str.trimmed().split("\n");            // 同时接收到多行就要分解
    for(int i=0;i<strList.size();i++)
    {
        QString str = strList.at(i).simplified();
        if(str.isEmpty()||str.isNull())continue;    // 空白数据不要
        emit revMsg(str);                           // 转发接收到的ssh数据出去
    }
}
// 完成ftp操作函数
void FsshGui::OnSftpFinished(QSsh::SftpJobId job, const QString &error)
{
    //    qDebug()<<"SftpJobId= "<<job<<"error="<<error;
    if(error.isEmpty())
    {
        sshOut->setTextStyle(QString("SftpJobId = %1,Operate success").arg(job),Qt::white,Qt::gray,12);
    }
    else
    {
        sshOut->setTextStyle(QString("SftpJobId = %1,error=%2").arg(job).arg(error),Qt::white,Qt::gray,12);
    }
    ftpBox->hide();                 //  自动关闭显示框
    emit sFtpFinished(job, error);  //  转发操作FTP操作结束的函数
}
// 清屏
void FsshGui::clear(void)
{
    sshOut->clear();
}


// 点击 收发文件 框
void FsshGui::on_groupBox_file_clicked()
{
    ui->frame_file->setVisible(ui->groupBox_file->isChecked());
}
// 点击 发送命令 框
void FsshGui::on_groupBox_order_clicked()
{
    ui->frame_order->setVisible(ui->groupBox_order->isChecked());
}
// 点击 登录 框
void FsshGui::on_groupBox_land_clicked()
{
    ui->frame_land->setVisible(ui->groupBox_land->isChecked());
}
// 点击 应答 框
void FsshGui::on_groupBox_autoAck_clicked()
{
    ui->frame_autoAck->setVisible(ui->groupBox_autoAck->isChecked());
}

// 点击 “发送命令”
void FsshGui::on_button_send_clicked()
{
    // 没有打开SSH就跳过
    if(myssh.isConnected() == false)
    {
        sshOut->setTextStyle("No Open SSH6",Qt::white,Qt::red,12);
        QMessageBox::warning(NULL, QString("No Open SSH6"),QString("No Open SSH"));
        return;
    }
     myssh.SSH_sendCommand(ui->plainTextEdit_in->toPlainText());
}
// 行编辑结束
void FsshGui::on_lineEdit_sendSingle_editingFinished()
{
    // 没有打开SSH就跳过
    if(myssh.isConnected() == false)
    {
        sshOut->setTextStyle("No Open SSH5",Qt::white,Qt::red,12);
        QMessageBox::warning(NULL, QString("No Open SSH5"),QString("No Open SSH"));
        return;
    }
     myssh.SSH_sendCommand(ui->lineEdit_sendSingle->text());
}


// 文件操作相关------------------------------------------------------------------------------------------------------------------------------------------------------------
// 外部函数->执行ftp文件下载
void FsshGui::SSH_downloadFile(const QString &remotePath,   const QString &localPath)
{
    if(myssh.isConnected() == false)// 没有打开SSH就跳过
    {
        sshOut->setTextStyle("No Open SSH1",Qt::white,Qt::red,12);
        QMessageBox::warning(NULL, QString("No Open SSH1"),QString("No Open SSH"));
        return;
    }
    QSsh::SftpJobId job = myssh.SSH_downloadFile(remotePath,localPath);// ftp文件下载命令
    ftpBox->setText(QString("SSH_downloadFile : ")+remotePath+QString(" -> ")+localPath);
    ftpBox->show();
    sshOut->setTextStyle(QString("SSH_downloadFile -> SftpJobId = %1").arg(job),Qt::white,Qt::gray,12);
}
// 外部函数->执行ftp文件上传
void FsshGui::SSH_uploadFile(const QString &localPath,      const QString &remotePath)
{
    if(myssh.isConnected() == false)// 没有打开SSH就跳过
    {
        sshOut->setTextStyle("No Open SSH2",Qt::white,Qt::red,12);
        QMessageBox::warning(NULL, QString("No Open SSH2"),QString("No Open SSH"));
        return;
    }
    QSsh::SftpJobId job = myssh.SSH_uploadFile(localPath,remotePath);// 发送文件命令
    ftpBox->setText(QString("SSH_uploadFile : ")+localPath+QString(" -> ")+remotePath);
    ftpBox->show();
    sshOut->setTextStyle(QString("SSH_uploadFile -> SftpJobId = %1").arg(job),Qt::white,Qt::gray,12);
}
// 外部函数->执行ftp文件上传文件夹
void FsshGui::SSH_uploadDir(const QString &localDirPath,    const QString &remoteDirPath)
{
    if(myssh.isConnected() == false)// 没有打开SSH就跳过
    {
        sshOut->setTextStyle("No Open SSH3",Qt::white,Qt::red,12);
        QMessageBox::warning(NULL, QString("No Open SSH3"),QString("No Open SSH"));
        return;
    }
    QSsh::SftpJobId job = myssh.SSH_uploadDir(localDirPath,remoteDirPath);// 发送文件夹命令
    ftpBox->setText(QString("SSH_uploadDir : ")+localDirPath+QString(" -> ")+remoteDirPath);
    ftpBox->show();
    sshOut->setTextStyle(QString("SSH_uploadDir -> SftpJobId = %1").arg(job),Qt::white,Qt::gray,12);
}
// 外部函数->执行ftp文件下载文件夹
void FsshGui::SSH_downloadDir(const QString &remoteDirPath, const QString &localDirPath)
{
    if(myssh.isConnected() == false)// 没有打开SSH就跳过
    {
        sshOut->setTextStyle("No Open SSH4",Qt::white,Qt::red,12);
        QMessageBox::warning(NULL, QString("No Open SSH4"),QString("No Open SSH"));
        return;
    }
    QSsh::SftpJobId job = myssh.SSH_downloadDir(remoteDirPath,localDirPath);// 接收文件夹命令
    ftpBox->setText(QString("SSH_downloadDir : ")+remoteDirPath+QString(" -> ")+localDirPath);
    ftpBox->show();
    sshOut->setTextStyle(QString("SSH_downloadDir -> SftpJobId = %1").arg(job),Qt::white,Qt::gray,12);
}



// 点击 “发送文件”
void FsshGui::on_button_uploadFile_clicked()
{
    SSH_uploadFile(ui->lineEdit_local_addr->text(),     ui->lineEdit_obj_addr->text());
}
// 点击 “接收文件”
void FsshGui::on_button_recvFile_clicked()
{
    SSH_downloadFile(ui->lineEdit_obj_addr->text(),     ui->lineEdit_local_addr->text());
}
// 点击 “下载文件夹”
void FsshGui::on_button_downloadDir_clicked()
{
    SSH_downloadDir(ui->lineEdit_objDir_addr->text(), ui->lineEdit_localDir_addr->text());
}
// 点击 “上传文件夹”
void FsshGui::on_button_uploadDir_clicked()
{
    SSH_uploadDir( ui->lineEdit_localDir_addr->text(), ui->lineEdit_objDir_addr->text());
}
// 点击 “本地文件”
void FsshGui::on_button_openLocalFile_clicked()
{
    // 打开对应的文件夹
    QProcess process;
    QString filePath = ui->lineEdit_local_addr->text();
    filePath.replace("/", "\\"); // 只能识别 "\"
    QString cmd = QString("explorer.exe /select,\"%1\"").arg(filePath);
    process.startDetached(cmd);
}

// 点击 “本地文件夹”
void FsshGui::on_button_openLocalDir_clicked()
{
    // 打开对应的文件夹
    QProcess process;
    QString filePath = ui->lineEdit_localDir_addr->text();
    filePath.replace("/", "\\"); // 只能识别 "\"
    QString cmd = QString("explorer.exe %1").arg(filePath);
    process.startDetached(cmd);
}
// 点击 “清屏”
void FsshGui::on_pushButton_clicked()
{
    sshOut->clear();
}
// ******************************************** 外部接口命令 ******************************************** begin
// 设置IP
void FsshGui::setSshIP(QString str)
{
    // IP地址带着3个小数点
    if( str.count('.') !=3)return;
    ui->lineEdit_IP->setText(str);
}
// 打开SSH
void FsshGui::openSsh()
{
    // 原本没打开，就执行打开操作
    if(ui->button_open->text() == "open_ssh")
    {
        on_button_open_clicked();
    }
}
// 关闭SSH
void FsshGui::closeSsh()
{
    // 原本关闭，就执行关闭操作
    if(ui->button_open->text() == "close_ssh")
    {
        on_button_open_clicked();
    }
}
// 发送SSH命令,会修改输入栏数据
bool FsshGui::sendSshCmd(QString str)
{
//    ui->plainTextEdit_in->setPlainText(str); // 保存发送参数
    // 没有打开SSH就跳过
    if(myssh.isConnected() == false)
    {
        sshOut->setTextStyle("No Open SSH8",Qt::white,Qt::red,12);
        QMessageBox::warning(NULL, QString("No Open SSH8"),QString("No Open SSH"));
        return false;
    }
    else
    {
        myssh.SSH_sendCommand(str);
        return true;
    }
}
// ******************************************** 外部接口命令 ******************************************** end

// ******************************************** 数据保存 ******************************************** begin
#include<QSettings>
//函数功能： 导出配置
//输入参数： 导出配置的Qsetting的指针
//输出参数：
//备注：
void FsshGui::dat_config_save(void)
{
    QString path = ".\\config\\AllConfig.dat";  // 统一配置地址
    QSettings save_config(path,QSettings::IniFormat);
    save_config.setIniCodec("GB2312");//支持中文
    save_config.remove(windowTitle());  // 删除组
    save_config.beginGroup(windowTitle());     // 组操作------------------------------------------begin
    save_config.setValue ("have_config"        ,true);

    // ------------------------ 配置的保存 ------------------------
    save_config.setValue ("lineEdit_IP"        ,ui->lineEdit_IP->text());             // 基本配置
    save_config.setValue ("lineEdit_name"      ,ui->lineEdit_name->text());           //
    save_config.setValue ("lineEdit_password"  ,ui->lineEdit_password->text());       //
    save_config.setValue ("spinBox_port"  ,ui->spinBox_port->value());                //
    save_config.setValue ("plainTextEdit_in"   ,ui->plainTextEdit_in->toPlainText()); // 发送命令
    save_config.setValue ("lineEdit_sendSingle"   ,ui->lineEdit_sendSingle->text()); // 发送命令

    save_config.setValue("lineEdit_obj_addr"    ,ui->lineEdit_obj_addr->text());
    save_config.setValue("lineEdit_local_addr"    ,ui->lineEdit_local_addr->text());
    save_config.setValue("lineEdit_objDir_addr"    ,ui->lineEdit_objDir_addr->text());
    save_config.setValue("lineEdit_localDir_addr"    ,ui->lineEdit_localDir_addr->text());

    save_config.setValue("groupBox_order"       ,ui->groupBox_order->isChecked());//
    save_config.setValue("groupBox_land"        ,ui->groupBox_land->isChecked()); //
    save_config.setValue("groupBox_file"        ,ui->groupBox_file->isChecked()); //
    save_config.setValue("groupBox_autoAck"     ,ui->groupBox_autoAck->isChecked()); //

    save_config.setValue("spinBox_autoAckNum"   ,ui->spinBox_autoAckNum->value());

    save_config.endGroup();                    // 组操作------------------------------------------end
}
//函数功能：导入配置
//输入参数：导入配置的Qsetting的指针
//输出参数：
//备注：
void FsshGui::dat_config_load(void)
{
    QString path = ".\\config\\AllConfig.dat";  // 统一配置地址
    QSettings load_config(path,QSettings::IniFormat);
    load_config.setIniCodec("GB2312");  // 支持中文

    load_config.beginGroup(windowTitle());     // 组操作------------------------------------------begin
    //判断文件存在
    if(load_config.contains("have_config")==false)
    {
        qDebug()<< QString("FsshGui:dat_config_load error")+windowTitle() + " no file!";
        return;
    }
    // ------------------------ 配置的读取 ------------------------
    ui->lineEdit_IP->setText(load_config.value("lineEdit_IP").toString());
    ui->lineEdit_name->setText(load_config.value("lineEdit_name").toString());
    ui->lineEdit_password->setText(load_config.value("lineEdit_password").toString());
    ui->spinBox_port->setValue(load_config.value("spinBox_port").toInt());
    ui->plainTextEdit_in->setPlainText(load_config.value("plainTextEdit_in").toString());       // 发送命令
    ui->lineEdit_sendSingle->setText(load_config.value("lineEdit_sendSingle").toString());

    ui->lineEdit_local_addr->setText(load_config.value("lineEdit_local_addr").toString());      // 文件地址
    ui->lineEdit_obj_addr->setText(load_config.value("lineEdit_obj_addr").toString());
    ui->lineEdit_localDir_addr->setText(load_config.value("lineEdit_localDir_addr").toString());
    ui->lineEdit_objDir_addr->setText(load_config.value("lineEdit_objDir_addr").toString());

    ui->groupBox_order->setChecked(load_config.value("groupBox_order").toBool()); //
    ui->groupBox_land->setChecked(load_config.value("groupBox_land").toBool());   //
    ui->groupBox_file->setChecked(load_config.value("groupBox_file").toBool());     //
    ui->groupBox_autoAck->setChecked(load_config.value("groupBox_autoAck").toBool());     //

    on_groupBox_file_clicked();
    on_groupBox_order_clicked();
    on_groupBox_land_clicked();
    on_groupBox_autoAck_clicked();

    ui->spinBox_autoAckNum->setValue(load_config.value("spinBox_autoAckNum").toInt()); // 设置自动应答个数

    load_config.endGroup();                    // 组操作------------------------------------------end
}






// ******************************************** 自动应答创建 ******************************************** begin















