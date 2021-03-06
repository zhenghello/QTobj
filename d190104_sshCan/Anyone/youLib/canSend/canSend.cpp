#include "canSend.h"
#include "ui_canSend.h"

#include "canpack.h"


canSend::canSend(QWidget *parent, QString titleName) :QWidget(parent),ui(new Ui::canSend)
{
    ui->setupUi(this);
    setWindowTitle(titleName);
    dat_config_load();

    // Tree的数据库
    treeOredr = new FtreeDabeBase(this,"canOrder");
    treeOredr->setMinimumHeight(300);
    ui->tab_tree->layout()->addWidget(treeOredr);
    ui->label_ssh->deleteLater();

    // SSH的端口
    sshPort = new FsshGui(this,"canSendSSH");
    sshPort->setMinimumHeight(300);
    ui->tab_ssh->layout()->addWidget(sshPort);
    ui->label_order->deleteLater();

    connect(treeOredr,&FtreeDabeBase::sendMsgTree                           ,this, &canSend::msgTreeAnalyze);           // 将对tree的右击事件转到本地处理
    connect(sshPort,SIGNAL(connectSuccess())                                ,this, SLOT(showSshOpenMsg()));                               // 连接成功信号
    connect(sshPort,SIGNAL(connectFailure())                                ,this, SLOT(showSshCloseMsg()));                              // 连接失败信号
    connect(sshPort,SIGNAL(sFtpFinished(QSsh::SftpJobId, const QString))    ,this, SIGNAL(sFtpFinished(QSsh::SftpJobId, const QString))); // FTP文件操作结束信号

    // 文件下载框
    treeFile = new FtreeDabeBase(this,"sshFile");
    treeFile->setWhatsThis("点击“源地址”列下载到本地\n点击“本机地址”列上传到服务器");
    ui->tab_fileDownload->layout()->addWidget(treeFile);
    ui->label_file->deleteLater();
    connect(treeFile,SIGNAL(sendMsgTree(QTreeWidgetItem*,int)),this,SLOT(fileTreeOperate(QTreeWidgetItem*,int)));   // 将对tree的右击事件转到本地处理

    // 选择 ->主显示框
    ui->tabWidget->setCurrentWidget(ui->tab_tree);
   // ui->tabWidget->setCurrentWidget(ui->tab_base);
    //基本框
    canPack *cp;
    cp = new canPack(this,12);
    ui->tab_base->layout()->addWidget(cp);

    // 测试

    //QTimer::singleShot(10000, this, SLOT(on_button_upgrade_modular_clicked()));

}
canSend::~canSend()
{
    dat_config_save();
    delete ui;
}
// 发送重启机器命令
void canSend::on_button_reboot_clicked()
{
    if(sshPort->isConnected())
    {
        sshPort->sendSshCmd("sh /dymind/appStart.sh");  // 发送SSH命令
        ui->button_reboot->setEnabled(false);           //

        ui->tabWidget->setCurrentIndex(2);                                     // 直接跳去SSH显示区
        QTimer::singleShot(62000, this, SLOT(button_reboot_setEnableTrue()));  // 不让再按按键
        QTimer::singleShot(60000, sshPort, SLOT(closeSsh()));  // 1分钟后关闭ssh
        QTimer::singleShot(62000, sshPort, SLOT(openSsh()));   // 再62秒后打开ssh
//        QMessageBox msg(QMessageBox::NoIcon, QString("Please Wait"), QString("Please Wait reboot"));
//        QTimer::singleShot(11000, &msg, SLOT(close()));     // 阻塞一段时间后触发,设置临时一个等待框
//        msg.exec();
    }
    else
    {
        QMessageBox msg(QMessageBox::NoIcon, QString("NO Open SSH"), QString("NO Open SSH"));
        QTimer::singleShot(1000, &msg, SLOT(close()));  // 阻塞一段时间后触发,设置临时一个等待框
        msg.exec();
    }
}

// button_reboot()
void canSend::button_reboot_setEnableTrue(void)
{
    ui->button_reboot->setEnabled(true);
    ui->tabWidget->setCurrentIndex(1);                                     // 直接跳回命令显示区

}

// 文件相关的树，发送出来的命令
void canSend::fileTreeOperate(QTreeWidgetItem *tree,int column)
{

    if(isConnected() == false)
    {
        QMessageBox::warning(NULL, QString("No Open SSH9"),QString("No Open SSH"));
        return;
    }

    if(column==1)// 下载到本地
    {
        if(tree->text(0)=="F")// 下载文件
        {
            if(tree->text(1).isNull()||tree->text(1).isEmpty())return;// 空白无效
            if(tree->text(2).isNull()||tree->text(2).isEmpty())return;// 空白无效
            sshPort->SSH_downloadFile(tree->text(1),tree->text(2));
            return;
        }
        else if(tree->text(0)=="D")// 下载文件夹
        {
            if(tree->text(1).isNull()||tree->text(1).isEmpty())return;// 空白无效
            if(tree->text(2).isNull()||tree->text(2).isEmpty())return;// 空白无效
            sshPort->SSH_downloadDir(tree->text(1),tree->text(2));
            return;
        }
    }
    else if(column==2)// 上传到服务器
    {
        if(tree->text(0)=="F")// 上传文件
        {
            if(tree->text(1).isNull()||tree->text(1).isEmpty())return;// 空白无效
            if(tree->text(2).isNull()||tree->text(2).isEmpty())return;// 空白无效
            QFileInfo file(tree->text(2));//判断文件存在
            if(file.isFile()==false)
            {
                QMessageBox::warning(NULL, QString("No File"),QString("No File : ")+tree->text(2));
                return;
            }
            // 上传
            sshPort->SSH_uploadFile(tree->text(2),tree->text(1));
            QMessageBox msg(QMessageBox::NoIcon, QString("upload File"), QString("upload File : ")+tree->text(2)+QString(" -> ")+tree->text(1) );
            QTimer::singleShot(1000, &msg, SLOT(close()));  // 阻塞一段时间后触发,设置临时一个等待框
            msg.exec();
            sshPort->sendSshCmd("sync");// 发送同步命令
            return;
        }
        else if(tree->text(0)=="D")// 上传文件夹
        {
            if(tree->text(1).isNull()||tree->text(1).isEmpty())return;// 空白无效
            if(tree->text(2).isNull()||tree->text(2).isEmpty())return;// 空白无效
            QFileInfo file(tree->text(2));//判断文件存在
            if(file.isDir()==false)
            {
                QMessageBox::warning(NULL, QString("No Dir"),QString("No Dir : ")+tree->text(2));
                return;
            }
            sshPort->SSH_uploadDir(tree->text(2),tree->text(1));
            QMessageBox msg(QMessageBox::NoIcon, QString("upload Dir"), QString("upload Dir : ")+tree->text(2)+QString(" -> ")+tree->text(1) );
            QTimer::singleShot(1000, &msg, SLOT(close()));  // 阻塞一段时间后触发
            msg.exec();                                     // 设置临时一个等待框
            sshPort->sendSshCmd("sync");// 发送同步命令
            return;
        }
    }
}

// 表格要发送的命令
void canSend::msgTreeAnalyze(QTreeWidgetItem *tree,int column)
{
    if(column==1)
    {
        sendCanMsg(tree->text(column));
    }
}
// 解析要发送的命令
void canSend::sendCanMsg(QString str)
{
    QStringList strlist = str.simplified().split(' ');
    // 长度太短
    if(strlist.size()<8) return ;

    uint        canDestID    ; // 目的ID
    uint        canSrcID     ; // 源ID
    uint        segnum       ; //
    uint        idCode       ; // ID码
    QString     canStr       ; //
    // 自带地址的情况->没带地址从框内取
    if((strlist.at(0).at(0)=='0')&&((strlist.at(0).at(1)=='x')||(strlist.at(0).at(1)=='X'))&&(strlist.at(1).at(0)=='0')&&((strlist.at(1).at(1)=='x')||(strlist.at(1).at(1)=='X')))
    {
        canSrcID  = strlist.at(0).toInt(NULL,16);
        canDestID = strlist.at(1).toInt(NULL,16);
        strlist.removeFirst();// 拿到数据后去掉
        strlist.removeFirst();
    }
    else
    {
        canDestID = ui->spinBox_destID->value();
        canSrcID  = ui->spinBox_srcID->value();
    }

    idCode = (canDestID<<16)+(canSrcID<<22); // 含ID的编码
    // 分解编码
    // 只有一帧的情况
    if(strlist.size()<=8)
    {
        canStr = QString("cansend can0 -i 0x%1").arg(idCode,0,16);
        for(int i=0;i<8;i++)
        {
            canStr += QString(" 0x%1").arg(strlist.first().toInt(NULL,16),0,16);
            strlist.removeFirst();
        }
        canStr += " -e";
        sshPort->sendSshCmd(canStr);
    }
    // 有多帧的情况
    else
    {
        // 头段
        idCode = (canDestID<<16)+(canSrcID<<22)+0x4000; // 含ID的编码+段头编码
        segnum = 0;
        canStr = QString("cansend can0 -i 0x%1").arg(idCode+(segnum<<8),0,16);
        for(int i=0;i<8;i++)
        {
            canStr += QString(" 0x%1").arg(strlist.first().toInt(NULL,16),0,16);
            strlist.removeFirst();
        }
        canStr += " -e && ";
        // 中间段
        idCode = (canDestID<<16)+(canSrcID<<22)+0x8000; // 含ID的编码+中间段编码
        if(strlist.size()>8)
        {
            segnum ++;
            canStr += QString("cansend can0 -i 0x%1").arg(idCode+(segnum<<8),0,16);
            for(int i=0;i<8;i++)
            {
                canStr += QString(" 0x%1").arg(strlist.first().toInt(NULL,16),0,16);
                strlist.removeFirst();
            }
            canStr += " -e && ";
        }
        // 尾巴段
        idCode = (canDestID<<16)+(canSrcID<<22)+0xc000; // 含ID的编码+段尾编码
        segnum ++;
        canStr += QString("cansend can0 -i 0x%1").arg(idCode+(segnum<<8),0,16);
        while (strlist.size())
        {
            canStr += QString(" 0x%1").arg(strlist.first().toInt(NULL,16),0,16);
            strlist.removeFirst();
        }
        canStr += " -e";
        sshPort->sendSshCmd(canStr);
    }
}
// 按下批量发送操作 ------------------------------------------------ begin
void canSend::on_pushButton_bathcOrder_clicked()
{
    if(sshPort->isConnected()==false)
    {
        QMessageBox::warning(NULL, QString("No Open SSH5"),QString("No Open SSH"));
        return;
    }
    strList_batch = ui->plainTextEdit_BatchOrder->toPlainText().split("\n");
    QString bstr;
    // 过滤无效信息
    for(int i=0; i<strList_batch.size(); i++)
    {
        QString str = strList_batch.at(i);
        if(str.indexOf("0x00") == 9)
        {
            bstr += str.mid(9)+"\n";
        }
        qDebug()<<"u="<<str.indexOf("0x00");
    }
    ui->plainTextEdit_BatchOrder->setPlainText(bstr);
    strList_batch = ui->plainTextEdit_BatchOrder->toPlainText().split("\n");
    qDebug()<<strList_batch.size();

    connect(&timer_batch, SIGNAL(timeout()), this, SLOT(bathcOrder_timeout()) );
    timer_batch.start(20);
}
void canSend::bathcOrder_timeout()
{
    QString str = strList_batch.takeFirst();
    sshPort->sendSshCmd(str);
    if(strList_batch.size() == 0)
    {
        timer_batch.stop();
        disconnect(&timer_batch, SIGNAL(timeout()), this, SLOT(bathcOrder_timeout()) );
    }
}
// 按下批量发送操作 ------------------------------------------------ end

// ******************************************** 外部函数 ******************************************** begin

// ******************************************** 外部函数 ******************************************** end

// ******************************************** 数据保存 ******************************************** begin
//函数功能：保存配置
//输入参数：
//输出参数：
//备注：
void canSend::dat_config_save(void)
{
    QString path = ".\\config\\AllConfig.dat";  // 统一配置地址
    QSettings save_config(path,QSettings::IniFormat);
    save_config.setIniCodec("GB2312");          //支持中文
    save_config.remove(windowTitle());          // 删除组
    save_config.beginGroup(windowTitle());      // 组操作------------------------------------------begin
    save_config.setValue ("have_config"        ,true);
    save_config.setValue ("plainTextEdit_BatchOrder"        ,ui->plainTextEdit_BatchOrder->toPlainText());
    // ------------------------ 配置的保存 ------------------------


    save_config.endGroup();                    // 组操作------------------------------------------end

}
//函数功能：导入配置
//输入参数：
//输出参数：
//备注：
void canSend::dat_config_load(void)
{
    QString path = ".\\config\\AllConfig.dat";          // 统一配置地址
    QSettings load_config(path,QSettings::IniFormat);
    load_config.setIniCodec("GB2312");  // 支持中文
    load_config.beginGroup(windowTitle());              // 组操作------------------------------------------begin
    //判断文件存在
    if(load_config.contains("have_config")==false)
    {
        QMessageBox::warning(NULL, QString("Loading Error"),windowTitle() + " no file!");
        return;
    }
    // ------------------------ 配置的读取 ------------------------
    ui->plainTextEdit_BatchOrder->setPlainText(load_config.value("plainTextEdit_BatchOrder").toString());

    load_config.endGroup();                            // 组操作------------------------------------------end
}



// 按下调试温度按键
void canSend::on_button_temp_clicked()
{
    if(pTmpCfg == NULL)
    {
        pTmpCfg = new canTmpConfig(this);
        pTmpCfg->setWindowFlags(pTmpCfg->windowFlags()|Qt::Window);//设置为外框
        pTmpCfg->show();
        connect(pTmpCfg,SIGNAL(send_can_pack(QString)),this,SLOT(sendCanMsg(QString)));
    }
    else
    {
        disconnect(pTmpCfg,SIGNAL(send_can_pack(QString)),this,SLOT(sendCanMsg(QString)));
        pTmpCfg->deleteLater();
        pTmpCfg = NULL;
    }
//      cp->setCanPack_ArgNum(20);
//      cp->table_init(20);
}

// 电机调试模块
void canSend::on_button_motor_clicked()
{
    if(pMotor == NULL)
    {
        pMotor = new FOptMotor(this);
        pMotor->setWindowFlags(pMotor->windowFlags()|Qt::Window);//设置为外框
        pMotor->show();
        connect(pMotor,SIGNAL(send_can_pack(QString)),this,SLOT(sendCanMsg(QString)));
    }
    else
    {
        disconnect(pMotor,SIGNAL(send_can_pack(QString)),this,SLOT(sendCanMsg(QString)));
        pMotor->deleteLater();
        pMotor = NULL;
    }
}
// 选择升级功能
void canSend::on_button_upgrade_modular_clicked()
{
    // 由于升级需要用到ssh的发送文件和命令功能，要把ssh的接口传递进去
    if(pupgrade == NULL)
    {
        if(sshPort->isConnected()==false)
        {
            QMessageBox::warning(NULL, QString("No Open SSH4"),QString("No Open SSH"));
            return;
        }
        // 直接跳去SSH显示区
        ui->tabWidget->setCurrentIndex(2);
        pupgrade = new UpgradeModel(this,sshPort);
        pupgrade->setWindowFlags(pupgrade->windowFlags()|Qt::Window);//设置为外框
        pupgrade->show();
        pupgrade->move(100,100);
    }
    else
    {
        pupgrade->deleteLater();
        pupgrade = NULL;
    }
}




void canSend::on_pushButton_debug_clicked()
{

}




void canSend::on_button_text_clicked()
{

}

