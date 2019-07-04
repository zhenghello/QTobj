#include "canSend.h"
#include "ui_canSend.h"

#include "canpack.h"
canPack *cp;

canSend::canSend(QWidget *parent, QString titleName) :QWidget(parent),ui(new Ui::canSend)
{
    ui->setupUi(this);
    setWindowTitle(titleName);
    dat_config_load();

    // Tree�����ݿ�
    treeOredr = new FtreeDabeBase(this,"canOrder");
    treeOredr->setMinimumHeight(300);
    ui->tab_tree->layout()->addWidget(treeOredr);
    ui->label_ssh->deleteLater();

    // SSH�Ķ˿�
    sshPort = new FsshGui(this,"canSendSSH");
    sshPort->setMinimumHeight(300);
    ui->tab_ssh->layout()->addWidget(sshPort);
    ui->label_order->deleteLater();

    connect(treeOredr,&FtreeDabeBase::sendMsgTree                           ,this, &canSend::msgTreeAnalyze);           // ����tree���һ��¼�ת�����ش���
    connect(sshPort,SIGNAL(connectSuccess())                                ,this, SLOT(showSshOpenMsg()));                               // ���ӳɹ��ź�
    connect(sshPort,SIGNAL(connectFailure())                                ,this, SLOT(showSshCloseMsg()));                              // ����ʧ���ź�
    connect(sshPort,SIGNAL(sFtpFinished(QSsh::SftpJobId, const QString))    ,this, SIGNAL(sFtpFinished(QSsh::SftpJobId, const QString))); // FTP�ļ����������ź�

    // �ļ����ؿ�
    treeFile = new FtreeDabeBase(this,"sshFile");
    treeFile->setWhatsThis("�����Դ��ַ�������ص�����\n�����������ַ�����ϴ���������");
    ui->tab_fileDownload->layout()->addWidget(treeFile);
    ui->label_file->deleteLater();
    connect(treeFile,SIGNAL(sendMsgTree(QTreeWidgetItem*,int)),this,SLOT(fileTreeOperate(QTreeWidgetItem*,int)));   // ����tree���һ��¼�ת�����ش���

    //����ʾ��
    ui->tabWidget->setCurrentWidget(ui->tab_tree);

    // �¶ȵ���
    pTmpCfg = NULL;

    // ����
    cp = new canPack(this,10);
    cp->setWindowFlags(cp->windowFlags()|Qt::Window);//����Ϊ���
    // cp->show();
    // cp->setCanPack_ArgNum(20);
    // ui->verticalLayout_test->addWidget(cp);
}
canSend::~canSend()
{
    dat_config_save();
    delete ui;
}
// ����������������
void canSend::on_button_reboot_clicked()
{
    if(sshPort->isConnected())
    {
        sshPort->sendSshCmd("sh /dymind/appStart.sh");   // ����SSH����
        QTimer::singleShot(60000, sshPort, SLOT(closeSsh()));  // 1���Ӻ�ر�ssh
        QTimer::singleShot(62000, sshPort, SLOT(openSsh()));   // ��62����ssh
//        QMessageBox msg(QMessageBox::NoIcon, QString("Please Wait"), QString("Please Wait reboot"));
//        QTimer::singleShot(11000, &msg, SLOT(close()));     // ����һ��ʱ��󴥷�,������ʱһ���ȴ���
//        msg.exec();
    }
    else
    {
        QMessageBox msg(QMessageBox::NoIcon, QString("NO Open SSH"), QString("NO Open SSH"));
        QTimer::singleShot(1000, &msg, SLOT(close()));  // ����һ��ʱ��󴥷�,������ʱһ���ȴ���
        msg.exec();
    }
}
// �ļ���ص��������ͳ���������
void canSend::fileTreeOperate(QTreeWidgetItem *tree,int column)
{

    if(isConnected() == false)
    {
        QMessageBox::warning(NULL, QString("No Open SSH9"),QString("No Open SSH"));
        return;
    }

    if(column==1)// ���ص�����
    {
        if(tree->text(0)=="F")// �����ļ�
        {
            if(tree->text(1).isNull()||tree->text(1).isEmpty())return;// �հ���Ч
            if(tree->text(2).isNull()||tree->text(2).isEmpty())return;// �հ���Ч
            sshPort->SSH_downloadFile(tree->text(1),tree->text(2));
            return;
        }
        else if(tree->text(0)=="D")// �����ļ���
        {
            if(tree->text(1).isNull()||tree->text(1).isEmpty())return;// �հ���Ч
            if(tree->text(2).isNull()||tree->text(2).isEmpty())return;// �հ���Ч
            sshPort->SSH_downloadDir(tree->text(1),tree->text(2));
            return;
        }
    }
    else if(column==2)// �ϴ���������
    {
        if(tree->text(0)=="F")// �ϴ��ļ�
        {
            if(tree->text(1).isNull()||tree->text(1).isEmpty())return;// �հ���Ч
            if(tree->text(2).isNull()||tree->text(2).isEmpty())return;// �հ���Ч
            QFileInfo file(tree->text(2));//�ж��ļ�����
            if(file.isFile()==false)
            {
                QMessageBox::warning(NULL, QString("No File"),QString("No File : ")+tree->text(2));
                return;
            }
            // �ϴ�
            sshPort->SSH_uploadFile(tree->text(2),tree->text(1));
            QMessageBox msg(QMessageBox::NoIcon, QString("upload File"), QString("upload File : ")+tree->text(2)+QString(" -> ")+tree->text(1) );
            QTimer::singleShot(1000, &msg, SLOT(close()));  // ����һ��ʱ��󴥷�,������ʱһ���ȴ���
            msg.exec();
            sshPort->sendSshCmd("sync");// ����ͬ������
            return;
        }
        else if(tree->text(0)=="D")// �ϴ��ļ���
        {
            if(tree->text(1).isNull()||tree->text(1).isEmpty())return;// �հ���Ч
            if(tree->text(2).isNull()||tree->text(2).isEmpty())return;// �հ���Ч
            QFileInfo file(tree->text(2));//�ж��ļ�����
            if(file.isDir()==false)
            {
                QMessageBox::warning(NULL, QString("No Dir"),QString("No Dir : ")+tree->text(2));
                return;
            }
            sshPort->SSH_uploadDir(tree->text(2),tree->text(1));
            QMessageBox msg(QMessageBox::NoIcon, QString("upload Dir"), QString("upload Dir : ")+tree->text(2)+QString(" -> ")+tree->text(1) );
            QTimer::singleShot(1000, &msg, SLOT(close()));  // ����һ��ʱ��󴥷�
            msg.exec();                                     // ������ʱһ���ȴ���
            sshPort->sendSshCmd("sync");// ����ͬ������
            return;
        }
    }
}

// ���Ҫ���͵�����
void canSend::msgTreeAnalyze(QTreeWidgetItem *tree,int column)
{
    if(column==1)
    {
        sendCanMsg(tree->text(column));
    }
}
// ����Ҫ���͵�����
void canSend::sendCanMsg(QString str)
{
    QStringList strlist = str.simplified().split(' ');
    // ����̫��
    if(strlist.size()<8) return ;

    uint        canDestID    ; // Ŀ��ID
    uint        canSrcID     ; // ԴID
    uint        segnum       ; //
    uint        idCode       ; // ID��
    QString     canStr       ; //
    // �Դ���ַ�����->û����ַ�ӿ���ȡ
    if((strlist.at(0).at(0)=='0')&&((strlist.at(0).at(1)=='x')||(strlist.at(0).at(1)=='X'))&&(strlist.at(1).at(0)=='0')&&((strlist.at(1).at(1)=='x')||(strlist.at(1).at(1)=='X')))
    {
        canSrcID  = strlist.at(0).toInt(NULL,16);
        canDestID = strlist.at(1).toInt(NULL,16);
        strlist.removeFirst();// �õ����ݺ�ȥ��
        strlist.removeFirst();
    }
    else
    {
        canDestID = ui->spinBox_destID->value();
        canSrcID  = ui->spinBox_srcID->value();
    }

    idCode = (canDestID<<16)+(canSrcID<<22); // ��ID�ı���
    // �ֽ����
    // ֻ��һ֡�����
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
    // �ж�֡�����
    else
    {
        // ͷ��
        idCode = (canDestID<<16)+(canSrcID<<22)+0x4000; // ��ID�ı���+��ͷ����
        segnum = 0;
        canStr = QString("cansend can0 -i 0x%1").arg(idCode+(segnum<<8),0,16);
        for(int i=0;i<8;i++)
        {
            canStr += QString(" 0x%1").arg(strlist.first().toInt(NULL,16),0,16);
            strlist.removeFirst();
        }
        canStr += " -e && ";
        // �м��
        idCode = (canDestID<<16)+(canSrcID<<22)+0x8000; // ��ID�ı���+�м�α���
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
        // β�Ͷ�
        idCode = (canDestID<<16)+(canSrcID<<22)+0xc000; // ��ID�ı���+��β����
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

// ******************************************** �ⲿ���� ******************************************** begin

// ******************************************** �ⲿ���� ******************************************** end

// ******************************************** ���ݱ��� ******************************************** begin
//�������ܣ���������
//���������
//���������
//��ע��
void canSend::dat_config_save(void)
{
    QString path = ".\\config\\AllConfig.dat";  // ͳһ���õ�ַ
    QSettings save_config(path,QSettings::IniFormat);
    save_config.setIniCodec("GB2312");          //֧������
    save_config.remove(windowTitle());          // ɾ����
    save_config.beginGroup(windowTitle());      // �����------------------------------------------begin
    save_config.setValue ("have_config"        ,true);

    // ------------------------ ���õı��� ------------------------


    save_config.endGroup();                    // �����------------------------------------------end

}
//�������ܣ���������
//���������
//���������
//��ע��
void canSend::dat_config_load(void)
{
    QString path = ".\\config\\AllConfig.dat";          // ͳһ���õ�ַ
    QSettings load_config(path,QSettings::IniFormat);
    load_config.setIniCodec("GB2312");  // ֧������
    load_config.beginGroup(windowTitle());              // �����------------------------------------------begin
    //�ж��ļ�����
    if(load_config.contains("have_config")==false)
    {
        QMessageBox::warning(NULL, QString("Loading Error"),windowTitle() + " no file!");
        return;
    }
    // ------------------------ ���õĶ�ȡ ------------------------


    load_config.endGroup();                            // �����------------------------------------------end
}
// ���µ����¶Ȱ���
void canSend::on_button_temp_clicked()
{
    if(pTmpCfg == NULL)
    {
        pTmpCfg = new canTmpConfig(this);
        pTmpCfg->setWindowFlags(pTmpCfg->windowFlags()|Qt::Window);//����Ϊ���
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
