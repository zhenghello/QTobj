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
    sshPort = pSshPort;
    // 导入配置
    QString strPath = "./config/upgradeModelFile/upgarde_config_file.dat";

    dat2tableWidget(strPath,ui->tableWidget);

}

UpgradeModel::~UpgradeModel()
{
    delete ui;
}

// 1114中，文件对应的升级命令
const QString order1114[8][4]={
    "dbmcu",  ".hex", "./config/upgradeModelFile/1114/upgrade/mcu/"  ,"sh /dymind/app/upgrade/script/up_driver_mcu_1114.sh"  ,
    "asmcu",  ".hex", "./config/upgradeModelFile/1114/upgrade/mcu/"  ,"sh /dymind/app/upgrade/script/up_as_mcu_1114.sh"      ,
    "crpmcu", ".hex", "./config/upgradeModelFile/1114/upgrade/mcu/"  ,"sh /dymind/app/upgrade/script/up_crp_mcu_1114.sh"     ,
    "rfmcu",  ".hex", "./config/upgradeModelFile/1114/upgrade/mcu/"  ,"sh /dymind/app/upgrade/script/up_rf_mcu.sh"           ,
    "imemcu", ".hex", "./config/upgradeModelFile/1114/upgrade/mcu/"  ,"sh /dymind/app/upgrade/script/up_immune_mcu_1114.sh"  ,
    "dbfpga", ".rbf", "./config/upgradeModelFile/1114/upgrade/fpga/" ,"sh /dymind/app/upgrade/script/up_driver_fpga_1114.sh" ,
    "asfpga", ".rbf", "./config/upgradeModelFile/1114/upgrade/fpga/" ,"sh /dymind/app/upgrade/script/up_as_fpga_1114.sh"     ,
    "mbfpga", ".rbf", "./config/upgradeModelFile/1114/upgrade/fpga/" ,"sh /dymind/app/upgrade/script/up_main_fpga.sh"        ,
};



// const QString upgradeRbfFileName[]={"dbfpga","asfpga","mbfpga"};


// 选择文件并升级
int order1114_index=0;
void UpgradeModel::on_pushButton_clicked()
{
    // 打开文件
    QString fileName = QFileDialog::getOpenFileName(this,QString(""),QString("./config"),"*.hex *.rbf *.rpd");
    if(nullptr == fileName)return; //没有选择就取消

    // 判断文件名-获取偏移
    for(order1114_index=0;order1114_index<8;order1114_index++)
    {
        if(fileName.indexOf(order1114[order1114_index][0]) !=-1)break;
    }
    // 没有合适文件
    if(order1114_index >=8)
    {
        QMessageBox::warning(NULL, QString("File Error"),QString("File Error\r\n")+QString::fromLocal8Bit(__FILE__)+QString("\r\n")+QString::number(__LINE__)+QString("\r\n")+QString::fromLocal8Bit(__FUNCTION__));
        return;
    }
    // 复制文件
    QString objName = order1114[order1114_index][0]+order1114[order1114_index][1];
    qDebug()<<fileName;
    qDebug()<<order1114[order1114_index][2]+objName;
    QFile::copy(fileName,order1114[order1114_index][2]+objName);

    // 上传文件
    upgradeOrder();
    //
    QTimer::singleShot(10000,this,SLOT(sendSsCmd()));

}
// 延迟发送命令
void UpgradeModel::sendSsCmd(void)
{
    // 发送升级命令
    sshPort->sendSshCmd(order1114[order1114_index][3]);
}
// 升级操作
// 复制文件到 upgrade
void UpgradeModel::upgradeOrder()
{
    if(sshPort->isConnected() == false)
    {
        QMessageBox::warning(NULL, QString("No Open SSH"),QString("No Open SSH\r\n")+QString::fromLocal8Bit(__FILE__)+QString::number(__LINE__)+QString::fromLocal8Bit(__FUNCTION__));
        return;
    }
    // 升级文件存放路径
    QString upgrade_file_path;
    QString remoteDirPath = "/dymind/app/";
    if(ui->radioButton_1114->isChecked())
    {
        upgrade_file_path = ui->lineEdit_1114->text();
    }
    else if(ui->radioButton_1101->isChecked())
    {
        upgrade_file_path = ui->lineEdit_1101->text();
    }
    else if(ui->radioButton_other->isChecked())
    {
        upgrade_file_path = ui->lineEdit_other->text();
    }
    //判断文件存在
    QFileInfo file(upgrade_file_path);
    if(file.isDir()==false)
    {
        QString msgStr = QString("\r\n")+QString::fromLocal8Bit(__FILE__)+QString::number(__LINE__)+QString::fromLocal8Bit(__FUNCTION__);
        QMessageBox::warning(NULL, QString("No Dir"),QString("No File : ")+upgrade_file_path+msgStr);
        return;
    }
    // 上传文件
    sshPort->SSH_uploadDir(upgrade_file_path, remoteDirPath);

}
