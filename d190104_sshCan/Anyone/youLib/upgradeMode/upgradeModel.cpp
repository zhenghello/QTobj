/*
    升级模块，目前用于mcu的1114和1101升级
*/
#include "upgradeModel.h"
#include "ui_upgradeModel.h"

#include "dat2tableWidget.h"


UpgradeModel::UpgradeModel(QWidget *parent, FsshGui *pSshPort) : QWidget(parent), ui(new Ui::UpgradeModel)
{
    //QTableWidget qtw;
    ui->setupUi(this);

    // ssh操作对象
    sshPort = pSshPort;

    // 导入配置
    QString strPath = ui->label_tablePath->text();
    tableWidget = new QTableWidget(this);
    layout()->addWidget(tableWidget);
    dat2tableWidget(strPath,tableWidget);
    ui->label_table->deleteLater();

    // 提前上传项目的文件夹内容
    //
    QList<QTableWidgetItem*> proList = tableWidget->findItems(QString("Dir"),Qt::MatchExactly);
    QStringList strList;
    strList.clear();
    // 导出所有项目名
    for(int i=0;i<proList.size();i++)
    {
        strList.append(tableWidget->item(proList[i]->row(),0)->text());
    }
    // 选择要用的项目
    proName = QInputDialog::getItem(this,QString::fromLocal8Bit("选择项目"),QString::fromLocal8Bit("选择项目"),strList);
    qDebug()<<proName;
    ui->label_name->setText(QString::fromLocal8Bit("项目名:")+proName);
    // 找到对应项目的上传路径
    // 0列：项目名
    // 1列：关键字-Dir
    // 2列：本地路径
    // 3列：远程路径
    int i;
    for(i=0;i<proList.size();i++)
    {
        if(tableWidget->item(proList[i]->row(),0)->text() == proName)
        {
            break;
        }
    }
    sshPort->SSH_uploadDir(tableWidget->item(proList[i]->row(),2)->text(), tableWidget->item(proList[i]->row(),3)->text());

}

UpgradeModel::~UpgradeModel()
{
    delete ui;
}
#define FILE_RECOGNIZE_KET_ROW_NUM      1   // 文件识别列号
#define REMOTE_PATH_ROW_NUM             2   // 远程路径
#define SSH_ORDER_ROW_NUM               3   // 文件识别列号


void UpgradeModel::on_pushButton_2_clicked()
{
    // 打开文件 -> 文件名：fileName
    QString fileName = QFileDialog::getOpenFileName(this,QString(""),QString("./config/upgradeModelFile"),"*.hex *.rbf *.rpd");
    if(nullptr == fileName)return; //没有选择就取消

    // 抽出 proName 的所有关键字对象
    QList<QTableWidgetItem*> tabList = tableWidget->findItems(QString(proName),Qt::MatchExactly);

    // 找到对应的行
    for(int i=0; i<tabList.size(); i++)
    {
        int row = tabList[i]->row(); // 当前行号
        objName         = fileName;
        sshOrder        = tableWidget->item(row, SSH_ORDER_ROW_NUM)->text(); // 4列存放着要执行的命令

        // 匹配到要升级的文件
        if(fileName.indexOf(tableWidget->item(row, FILE_RECOGNIZE_KET_ROW_NUM)->text()) !=-1)
        {
            // 上传文件
            sshPort->SSH_uploadFile(objName, tableWidget->item(row, REMOTE_PATH_ROW_NUM)->text());
            qDebug()<<objName;
            qDebug()<<tableWidget->item(row, REMOTE_PATH_ROW_NUM)->text();
            // 发送升级命令,在ftp数据传输完成后触发
             connect(sshPort,SIGNAL(sFtpFinished(QSsh::SftpJobId, const QString))    ,this, SLOT(sFtpFinished(QSsh::SftpJobId, const QString))); // FTP文件操作结束信号
             return;
        }
    }
    QMessageBox::warning(NULL, QString("File Error"),QString("File Error\r\n")+QString::fromLocal8Bit(__FILE__)+QString("\r\n")+QString::number(__LINE__)+QString("\r\n")+QString::fromLocal8Bit(__FUNCTION__));
}

// 延迟发送命令
void UpgradeModel::sFtpFinished(QSsh::SftpJobId job, const QString &error)
{
    if(error.isEmpty())
    {
        // 发送升级命令
        sshPort->sendSshCmd(sshOrder);
    }
    else
    {
        QMessageBox::warning(NULL, QString("File Error"),QString("SSH upload File Error\r\n")+QString::fromLocal8Bit(__FILE__)+QString("\r\n")+QString::number(__LINE__)+QString("\r\n")+QString::fromLocal8Bit(__FUNCTION__));
    }
    qDebug()<< QString("SftpJobId = %1,error=%2").arg(job).arg(error);
    disconnect(sshPort,SIGNAL(sFtpFinished(QSsh::SftpJobId, const QString))    ,this, SLOT(sFtpFinished(QSsh::SftpJobId, const QString))); // FTP文件操作结束信号

}



