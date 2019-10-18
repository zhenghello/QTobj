/*
    ����ģ�飬Ŀǰ����mcu��1114��1101����
*/
#include "upgradeModel.h"
#include "ui_upgradeModel.h"

#include "dat2tableWidget.h"


UpgradeModel::UpgradeModel(QWidget *parent, FsshGui *pSshPort) : QWidget(parent), ui(new Ui::UpgradeModel)
{
    //QTableWidget qtw;
    ui->setupUi(this);

    // ssh��������
    sshPort = pSshPort;

    // ��������
    QString strPath = ui->label_tablePath->text();
    tableWidget = new QTableWidget(this);
    layout()->addWidget(tableWidget);
    dat2tableWidget(strPath,tableWidget);
    ui->label_table->deleteLater();

    // ��ǰ�ϴ���Ŀ���ļ�������
    //
    QList<QTableWidgetItem*> proList = tableWidget->findItems(QString("Dir"),Qt::MatchExactly);
    QStringList strList;
    strList.clear();
    // ����������Ŀ��
    for(int i=0;i<proList.size();i++)
    {
        strList.append(tableWidget->item(proList[i]->row(),0)->text());
    }
    // ѡ��Ҫ�õ���Ŀ
    proName = QInputDialog::getItem(this,QString::fromLocal8Bit("ѡ����Ŀ"),QString::fromLocal8Bit("ѡ����Ŀ"),strList);
    qDebug()<<proName;
    ui->label_name->setText(QString::fromLocal8Bit("��Ŀ��:")+proName);
    // �ҵ���Ӧ��Ŀ���ϴ�·��
    // 0�У���Ŀ��
    // 1�У��ؼ���-Dir
    // 2�У�����·��
    // 3�У�Զ��·��
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
#define FILE_RECOGNIZE_KET_ROW_NUM      1   // �ļ�ʶ���к�
#define REMOTE_PATH_ROW_NUM             2   // Զ��·��
#define SSH_ORDER_ROW_NUM               3   // �ļ�ʶ���к�


void UpgradeModel::on_pushButton_2_clicked()
{
    // ���ļ� -> �ļ�����fileName
    QString fileName = QFileDialog::getOpenFileName(this,QString(""),QString("./config/upgradeModelFile"),"*.hex *.rbf *.rpd");
    if(nullptr == fileName)return; //û��ѡ���ȡ��

    // ��� proName �����йؼ��ֶ���
    QList<QTableWidgetItem*> tabList = tableWidget->findItems(QString(proName),Qt::MatchExactly);

    // �ҵ���Ӧ����
    for(int i=0; i<tabList.size(); i++)
    {
        int row = tabList[i]->row(); // ��ǰ�к�
        objName         = fileName;
        sshOrder        = tableWidget->item(row, SSH_ORDER_ROW_NUM)->text(); // 4�д����Ҫִ�е�����

        // ƥ�䵽Ҫ�������ļ�
        if(fileName.indexOf(tableWidget->item(row, FILE_RECOGNIZE_KET_ROW_NUM)->text()) !=-1)
        {
            // �ϴ��ļ�
            sshPort->SSH_uploadFile(objName, tableWidget->item(row, REMOTE_PATH_ROW_NUM)->text());
            qDebug()<<objName;
            qDebug()<<tableWidget->item(row, REMOTE_PATH_ROW_NUM)->text();
            // ������������,��ftp���ݴ�����ɺ󴥷�
             connect(sshPort,SIGNAL(sFtpFinished(QSsh::SftpJobId, const QString))    ,this, SLOT(sFtpFinished(QSsh::SftpJobId, const QString))); // FTP�ļ����������ź�
             return;
        }
    }
    QMessageBox::warning(NULL, QString("File Error"),QString("File Error\r\n")+QString::fromLocal8Bit(__FILE__)+QString("\r\n")+QString::number(__LINE__)+QString("\r\n")+QString::fromLocal8Bit(__FUNCTION__));
}

// �ӳٷ�������
void UpgradeModel::sFtpFinished(QSsh::SftpJobId job, const QString &error)
{
    if(error.isEmpty())
    {
        // ������������
        sshPort->sendSshCmd(sshOrder);
    }
    else
    {
        QMessageBox::warning(NULL, QString("File Error"),QString("SSH upload File Error\r\n")+QString::fromLocal8Bit(__FILE__)+QString("\r\n")+QString::number(__LINE__)+QString("\r\n")+QString::fromLocal8Bit(__FUNCTION__));
    }
    qDebug()<< QString("SftpJobId = %1,error=%2").arg(job).arg(error);
    disconnect(sshPort,SIGNAL(sFtpFinished(QSsh::SftpJobId, const QString))    ,this, SLOT(sFtpFinished(QSsh::SftpJobId, const QString))); // FTP�ļ����������ź�

}



