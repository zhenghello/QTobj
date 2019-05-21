/*
 * Ĭ������£����dat���ݽ��е���͵���
 * �����ļ������ƹ̶�Ϊ ��configName = ".\\config\\"+titleName+"_FtreeDabeBase_Config.dat";
 * tree���������ƹ̶�Ϊ��treeDatName= ".\\config\\"+titleName+"_TreeDb.dat";
 */
#include "ftreeDabeBase.h"
#include "ui_ftreeDabeBase.h"
#include <QFileDialog>
#include <QProcess>
#include <QSettings>
#include <QMessageBox>


#include <QDebug>
FtreeDabeBase::FtreeDabeBase(QWidget *parent, QString titleName) :QWidget(parent),ui(new Ui::FtreeDabeBase)
{
    ui->setupUi(this);
    setWindowTitle(titleName);
    dat_config_load();


    setWindowFlags(Qt::Window);     // Ĭ�����
    treeWidgetInit();               // ��ʼ�� ��
    // �������
    connect(ui->treeWidget,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(pressTree(QTreeWidgetItem*,int)));   // tree���һ�
    connect(ui->checkBox_hide,SIGNAL(clicked(bool)),this,SLOT(hideFrame(bool)));    // ���ؿ�
    connect(ui->checkBox_fix_width,SIGNAL(clicked(bool)),this,SLOT(fixWidth(bool)));    // �̶���


    treeDatName= ".\\config\\"+titleName+"_TreeDb.dat";
    ui->lineEdit_db->setText(treeDatName);

    bool bret;
    // �Զ��������ݿ��dat
    bret = dat2treeWidget(treeDatName,ui->treeWidget);
    if(bret == false)
    {
        QMessageBox::warning(NULL, titleName+QString::fromLocal8Bit(" error"),QString::fromLocal8Bit("tree auto loading error"));
    }
    setTreeItemIsEditable(ui->treeWidget);    // ����༭
}
FtreeDabeBase::~FtreeDabeBase()
{
    // ���õ���
    dat_config_save();
    // �Զ�����dat
    treeWidget2dat(treeDatName,ui->treeWidget);
    delete ui;
}
// --------------------------- ͨ���ڲ����� -------------------------------------------------------------------------------------------------------
// 1.��ʼ�� QTreeWidget
void FtreeDabeBase::treeWidgetInit(void)
{
    QTreeWidget *tree = ui->treeWidget;
    // ��    ��ʾ
//    tree = new QTreeWidget(this);
//    tree->setObjectName("tree");
//    tree->setMinimumSize(QSize(200, 100));
//    tree->setMaximumSize(QSize(1000,1000));
//    verticalLayout->addWidget(tree);  // ����ŵĵط�

    QFont font;
    font.setFamily(QString::fromUtf8("\345\256\213\344\275\223")); //����
    font.setPointSize(8);
    tree->setFont(font);
    tree->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    tree->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tree->header()->setSectionsMovable(false);              // ���Ҳ����϶�
    // �����϶�
    tree->setDragEnabled(true);
    tree->setDefaultDropAction(Qt::MoveAction);
    tree->setDragDropMode(QAbstractItemView::DragDrop);
    // ������ʾ
    tree->header()->setToolTip(QString::fromLocal8Bit("��Ҫ�޸��п�����޸ı�ͷ��,��json�ļ����޸�,+������,-�Ǽ���,�п�����ק"));
    // ��������
    tree->setStyleSheet("QTreeWidget::item{border: 1px solid rgb(200, 200, 200);background-color: rgb(200, 255, 255);height: 20px}QTreeWidget::item:selected{background-color:rgb(255,0,0,100)}");
}
// 2.��ǰѡ���� ���� item
void FtreeDabeBase::treeDecChose(void)
{
    QTreeWidget *tree = ui->treeWidget;
    // û��ѡ�񲻲���
    if(tree->currentIndex().row() ==  -1)return;
    // ֻ�ж���һ�е�ʱ�򣬲���ɾ������
    if((tree->topLevelItemCount() == 1)&&(tree->currentItem() == tree->topLevelItem(0)))return;
    // ɾ���ڵ�
    delTreeItem(tree->currentItem());
}
// 3.��ǰѡ���� ���� item
void FtreeDabeBase::treeAddChose(void)
{
    QTreeWidget *tree = ui->treeWidget;
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,"new"+QString::number(tree->topLevelItemCount()));
    // �ж��Ƿ�ѡ��
    if(tree->currentItem() == NULL)
    {
        tree->insertTopLevelItem(tree->topLevelItemCount(),item);
        item->setText(0,"new"+QString::number(tree->topLevelItemCount()));
    }
    // �ж��Ƿ��ڶ���
    else if(-1==tree->indexOfTopLevelItem(tree->currentItem()))
    {   // ���ڶ���
        item->setText(0,"new"+QString::number(tree->currentItem()->parent()->childCount()));
        tree->currentItem()->parent()->insertChild(tree->currentIndex().row()+1,item);
    }
    else
    {   // �ڶ���
        tree->insertTopLevelItem(tree->indexOfTopLevelItem(tree->currentItem())+1,item);
        item->setText(0,"new"+QString::number(tree->topLevelItemCount()));
    }
    setTreeItemIsEditable(item); // ����༭
}
// 3.��ǰѡ���� ���� ��item
void FtreeDabeBase::treeAddChildChose(void)
{
    QTreeWidget *tree = ui->treeWidget;

    // �ж��Ƿ�ѡ��
    if(tree->currentItem() == NULL)
    {
        return;
    }
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,"new"+QString::number(tree->currentItem()->childCount()));
    // �����Ӷ���
    tree->currentItem()->insertChild(0,item);

    setTreeItemIsEditable(item); // ����༭
}
// ����� tree �����ݲ��� -------------------------------------------------------------------------------------------------------
// 1.��ѯ�����Ƿ���ƥ����� - �еĻ��ͷ��� ��ǰ�ĵ�Ԫ������
QTreeWidgetItem* FtreeDabeBase::findKey(int column,QString key)
{
    return treeFindKey(ui->treeWidget, column, key); // �����в��ҹؼ���
}
// 1.��ѯ�����Ƿ���ƥ���Ӹ������� - �еĻ��ͷ��� ��ǰ�ĵ�Ԫ������
QTreeWidgetItem* FtreeDabeBase::findKey(int column,QString key,int chileCount)
{
    return treeFindKey(ui->treeWidget, column, key, chileCount); // �����в��ҹؼ���
}

// �������ĵ�ַ������ֻ��
QTreeWidget* FtreeDabeBase::mainTree(void)
{
    return ui->treeWidget;
}
// --------------------------- tree press������� ----------------------------------------------------------------------------------------------------------
// �������ĵ�Ԫ��
void FtreeDabeBase::pressTree(QTreeWidgetItem *item, int column)
{
    QTreeWidget *tree = ui->treeWidget;
    // 0.ֻ���һ���������
    if( qApp->mouseButtons() != Qt::RightButton)return ;
    // 1.������ - ��ͷΪ "+"
    if(tree->headerItem()->text(column)== "+")
    {
        treeAddChose();
    }
    // 2.������ - ��ͷΪ "-"
    if(tree->headerItem()->text(column)== "-")
    {
        treeDecChose();
    }
    // 3.������е���Ϊ - ��ͷΪ "C"
    if(tree->headerItem()->text(column)== "C")
    {
        treeAddChildChose();
    }
    // 3.���͵�Ԫ����Ϣ-��item��ʽ
    emit sendMsgTree(item,column);
}


// --------------------------- �������� --------------------------------------------------------------------------------------------------------------------
// �������ؿ�
void FtreeDabeBase::hideFrame(bool hide)
{
    ui->frame_hide->setHidden(hide);
}
// ���ù̶����
void FtreeDabeBase::fixWidth(bool fix)
{
    if(fix)
    {
        setMaximumWidth(400);
    }
    else
    {
        setMaximumWidth(2000);
    }
}
// ����excel����
void FtreeDabeBase::on_bLoadExcel_clicked()
{
    QMessageBox msg(QMessageBox::NoIcon,"please wait","wait 10 second!");
    msg.show();// ����һ���ȴ���
    QString excelName = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("��Ҫ��ȡ��excel��"),QString("./config"),"*.xl*");
    if(nullptr == excelName)return; //û��ѡ���ȡ��

    qDebug()<<"excelName = "<<excelName;
    qDebug()<<"excel2treeWidget = "<< excel2treeWidget(excelName, ui->treeWidget);
    setTreeItemIsEditable(ui->treeWidget);      // ����༭
    emit reloadExcelFinish();                   // ������������ź�
}
// ����excel����
void FtreeDabeBase::on_bSaveExcel_clicked()
{
    QMessageBox msg(QMessageBox::NoIcon,"please wait","wait 10 second!",QMessageBox::Ok);
    msg.show();// ����һ���ȴ���
    QString excelName = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("��Ҫ��excel��"),QString("./config"),"*.xl*");
    if(nullptr == excelName)return; //û��ѡ���ȡ��
    qDebug()<<"excelName = "<<excelName;
    qDebug()<<"treeWidget2excel = "<< treeWidget2excel(excelName, ui->treeWidget);
}
// ����dat����
void FtreeDabeBase::on_bLoadDAt_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,QString(""),QString("./config"),"*.dat");
    if(nullptr == fileName)return; //û��ѡ���ȡ��
    qDebug()<<"fileName = "<<fileName;
    qDebug()<<"dat2treeWidget = "<< dat2treeWidget(fileName, ui->treeWidget);
    setTreeItemIsEditable(ui->treeWidget);    // ����༭
}
// ����dat����
void FtreeDabeBase::on_bSaveDat_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,QString(""),QString("./config"),"*.dat");
    if(nullptr == fileName)return; //û��ѡ���ȡ��
    qDebug()<<"fileName = "<<fileName;
    qDebug()<<"treeWidget2dat = "<< treeWidget2dat(fileName, ui->treeWidget);
}
// ����excel�ļ���
void FtreeDabeBase::on_bExcelFileName_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,QString(""),QString("./config"),"*.xl*");
    if(nullptr == fileName)return; //û��ѡ���ȡ��
    ui->lineEdit_excel->setText (fileName.replace ("/","\\"));
}
// ����dat�ļ���
void FtreeDabeBase::on_bDatFileName_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,QString(""),QString("./config"),"*.dat");
    if(nullptr == fileName)return; //û��ѡ���ȡ��
    ui->lineEdit_dat->setText (fileName.replace ("/","\\"));
}
// �� excel�ļ��� �ļ�
void FtreeDabeBase::on_bOpenExcel_clicked()
{
    QString str = "explorer " + ui->lineEdit_excel->text().replace ("/","\\");
    QProcess::execute(str);
}
// �� dat�ļ��� �ļ�
void FtreeDabeBase::on_bOpenDat_clicked()
{
    QString str = "explorer " + ui->lineEdit_dat->text().replace ("/","\\");
    QProcess::execute(str);
}
// �� ���� �ļ�
void FtreeDabeBase::on_bDbFileName_clicked()
{
    QString str = "explorer " + ui->lineEdit_db->text().replace ("/","\\");
    QProcess::execute(str);
}
// ���ҹؼ�key
void FtreeDabeBase::on_bFindKey_clicked()
{
    int column = ui->spinBox_FindKeyColumn->value();
    QString key = ui->lineEdit_key->text();
    if(column > ui->treeWidget->headerItem()->columnCount())return;   // ����������Χ,����
    QTreeWidgetItemIterator it(ui->treeWidget);
    QTreeWidgetItem *item = *it;
    while (*it)
    {
        //do something like
        item = *it;
        if(item->text(column) == key)
        {
            ui->treeWidget->setItemSelected(item,true);
            ui->treeWidget->scrollToItem(item);
        }
        it++;
    }
}
// ******************************************** ���ݱ��� ******************************************** begin
//�������ܣ���������
//���������
//���������
//��ע��
void FtreeDabeBase::dat_config_save(void)
{
    QString path = ".\\config\\AllConfig.dat";  // ͳһ���õ�ַ
    QSettings save_config(path,QSettings::IniFormat);
    save_config.setIniCodec("GB2312");//֧������
    save_config.remove(windowTitle());  // ɾ����
    save_config.beginGroup(windowTitle());     // �����------------------------------------------begin
    save_config.setValue ("have_config"        ,true);


    // ------------------------ ���õı���
    save_config.setValue ("lineEdit_dat"           ,ui->lineEdit_dat->text());
    save_config.setValue ("lineEdit_excel"         ,ui->lineEdit_excel->text());
    save_config.setValue ("lineEdit_key"           ,ui->lineEdit_key->text());
    save_config.setValue ("spinBox_FindKeyColumn"  ,ui->spinBox_FindKeyColumn->value());
    save_config.setValue("checkBox_hide"           ,ui->checkBox_hide->isChecked());

    save_config.endGroup();                    // �����------------------------------------------end
}
//�������ܣ���������
//���������
//���������
//��ע��
void FtreeDabeBase::dat_config_load(void)
{
    QString path = ".\\config\\AllConfig.dat";  // ͳһ���õ�ַ
    QSettings load_config(path,QSettings::IniFormat);
    load_config.setIniCodec("GB2312");  // ֧������
    load_config.beginGroup(windowTitle());     // �����------------------------------------------begin
    //�ж��ļ�����
    if(load_config.contains("have_config")==false)
    {
        qDebug()<< QString("FsshGui:dat_config_load error")+windowTitle() + " no file!";
        return;
    }

    // ------------------------ ���õĶ�ȡ
    ui->lineEdit_dat->setText(load_config.value("lineEdit_dat").toString());
    ui->lineEdit_excel->setText(load_config.value("lineEdit_excel").toString());
    ui->lineEdit_key->setText(load_config.value("lineEdit_key").toString());
    ui->spinBox_FindKeyColumn->setValue(load_config.value("spinBox_FindKeyColumn").toInt());
    ui->checkBox_hide->setChecked(load_config.value("checkBox_hide").toBool());
    hideFrame(load_config.value("checkBox_hide").toBool());


    load_config.endGroup();                    // �����------------------------------------------end
}
// ******************************************** ���ݱ��� ******************************************** end
