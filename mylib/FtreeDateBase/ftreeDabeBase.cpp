/*
 * 默认情况下，会对dat数据进行导入和导出
 * 配置文件的名称固定为 ：configName = ".\\config\\"+titleName+"_FtreeDabeBase_Config.dat";
 * tree的数据名称固定为：treeDatName= ".\\config\\"+titleName+"_TreeDb.dat";
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


    setWindowFlags(Qt::Window);     // 默认外框
    treeWidgetInit();               // 初始化 树
    // 点击关联
    connect(ui->treeWidget,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(pressTree(QTreeWidgetItem*,int)));   // tree的右击
    connect(ui->checkBox_hide,SIGNAL(clicked(bool)),this,SLOT(hideFrame(bool)));    // 隐藏框
    connect(ui->checkBox_fix_width,SIGNAL(clicked(bool)),this,SLOT(fixWidth(bool)));    // 固定宽


    treeDatName= ".\\config\\"+titleName+"_TreeDb.dat";
    ui->lineEdit_db->setText(treeDatName);

    bool bret;
    // 自动导入数据库的dat
    bret = dat2treeWidget(treeDatName,ui->treeWidget);
    if(bret == false)
    {
        QMessageBox::warning(NULL, titleName+QString::fromLocal8Bit(" error"),QString::fromLocal8Bit("tree auto loading error"));
    }
    setTreeItemIsEditable(ui->treeWidget);    // 允许编辑
}
FtreeDabeBase::~FtreeDabeBase()
{
    // 配置导出
    dat_config_save();
    // 自动导出dat
    treeWidget2dat(treeDatName,ui->treeWidget);
    delete ui;
}
// --------------------------- 通用内部函数 -------------------------------------------------------------------------------------------------------
// 1.初始化 QTreeWidget
void FtreeDabeBase::treeWidgetInit(void)
{
    QTreeWidget *tree = ui->treeWidget;
    // 树    显示
//    tree = new QTreeWidget(this);
//    tree->setObjectName("tree");
//    tree->setMinimumSize(QSize(200, 100));
//    tree->setMaximumSize(QSize(1000,1000));
//    verticalLayout->addWidget(tree);  // 对象放的地方

    QFont font;
    font.setFamily(QString::fromUtf8("\345\256\213\344\275\223")); //宋体
    font.setPointSize(8);
    tree->setFont(font);
    tree->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    tree->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tree->header()->setSectionsMovable(false);              // 左右不能拖动
    // 上下拖动
    tree->setDragEnabled(true);
    tree->setDefaultDropAction(Qt::MoveAction);
    tree->setDragDropMode(QAbstractItemView::DragDrop);
    // 设置提示
    tree->header()->setToolTip(QString::fromLocal8Bit("想要修改列宽或者修改表头名,到json文件中修改,+是增列,-是减列,行可以拖拽"));
    // 背景属性
    tree->setStyleSheet("QTreeWidget::item{border: 1px solid rgb(200, 200, 200);background-color: rgb(200, 255, 255);height: 20px}QTreeWidget::item:selected{background-color:rgb(255,0,0,100)}");
}
// 2.当前选择下 减少 item
void FtreeDabeBase::treeDecChose(void)
{
    QTreeWidget *tree = ui->treeWidget;
    // 没有选择不操作
    if(tree->currentIndex().row() ==  -1)return;
    // 只有顶层一行的时候，不能删除顶行
    if((tree->topLevelItemCount() == 1)&&(tree->currentItem() == tree->topLevelItem(0)))return;
    // 删除节点
    delTreeItem(tree->currentItem());
}
// 3.当前选择下 新增 item
void FtreeDabeBase::treeAddChose(void)
{
    QTreeWidget *tree = ui->treeWidget;
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,"new"+QString::number(tree->topLevelItemCount()));
    // 判断是否选中
    if(tree->currentItem() == NULL)
    {
        tree->insertTopLevelItem(tree->topLevelItemCount(),item);
        item->setText(0,"new"+QString::number(tree->topLevelItemCount()));
    }
    // 判断是否在顶层
    else if(-1==tree->indexOfTopLevelItem(tree->currentItem()))
    {   // 不在顶层
        item->setText(0,"new"+QString::number(tree->currentItem()->parent()->childCount()));
        tree->currentItem()->parent()->insertChild(tree->currentIndex().row()+1,item);
    }
    else
    {   // 在顶层
        tree->insertTopLevelItem(tree->indexOfTopLevelItem(tree->currentItem())+1,item);
        item->setText(0,"new"+QString::number(tree->topLevelItemCount()));
    }
    setTreeItemIsEditable(item); // 允许编辑
}
// 3.当前选择下 新增 子item
void FtreeDabeBase::treeAddChildChose(void)
{
    QTreeWidget *tree = ui->treeWidget;

    // 判断是否选中
    if(tree->currentItem() == NULL)
    {
        return;
    }
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,"new"+QString::number(tree->currentItem()->childCount()));
    // 插入子对象
    tree->currentItem()->insertChild(0,item);

    setTreeItemIsEditable(item); // 允许编辑
}
// 对外的 tree 的数据操作 -------------------------------------------------------------------------------------------------------
// 1.查询树中是否有匹配符号 - 有的话就返回 当前的单元行数据
QTreeWidgetItem* FtreeDabeBase::findKey(int column,QString key)
{
    return treeFindKey(ui->treeWidget, column, key); // 从树中查找关键词
}
// 1.查询树中是否有匹配子个数符号 - 有的话就返回 当前的单元行数据
QTreeWidgetItem* FtreeDabeBase::findKey(int column,QString key,int chileCount)
{
    return treeFindKey(ui->treeWidget, column, key, chileCount); // 从树中查找关键词
}

// 返回树的地址，内容只读
QTreeWidget* FtreeDabeBase::mainTree(void)
{
    return ui->treeWidget;
}
// --------------------------- tree press点击操作 ----------------------------------------------------------------------------------------------------------
// 按下树的单元格
void FtreeDabeBase::pressTree(QTreeWidgetItem *item, int column)
{
    QTreeWidget *tree = ui->treeWidget;
    // 0.只有右击触发有用
    if( qApp->mouseButtons() != Qt::RightButton)return ;
    // 1.增加行 - 树头为 "+"
    if(tree->headerItem()->text(column)== "+")
    {
        treeAddChose();
    }
    // 2.减少行 - 树头为 "-"
    if(tree->headerItem()->text(column)== "-")
    {
        treeDecChose();
    }
    // 3.添加子行的行为 - 树头为 "C"
    if(tree->headerItem()->text(column)== "C")
    {
        treeAddChildChose();
    }
    // 3.发送单元格消息-以item格式
    emit sendMsgTree(item,column);
}


// --------------------------- 按键操作 --------------------------------------------------------------------------------------------------------------------
// 设置隐藏框
void FtreeDabeBase::hideFrame(bool hide)
{
    ui->frame_hide->setHidden(hide);
}
// 设置固定宽度
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
// 导入excel数据
void FtreeDabeBase::on_bLoadExcel_clicked()
{
    QMessageBox msg(QMessageBox::NoIcon,"please wait","wait 10 second!");
    msg.show();// 设置一个等待框
    QString excelName = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("打开要读取的excel表"),QString("./config"),"*.xl*");
    if(nullptr == excelName)return; //没有选择就取消

    qDebug()<<"excelName = "<<excelName;
    qDebug()<<"excel2treeWidget = "<< excel2treeWidget(excelName, ui->treeWidget);
    setTreeItemIsEditable(ui->treeWidget);      // 允许编辑
    emit reloadExcelFinish();                   // 发送重载完成信号
}
// 导出excel数据
void FtreeDabeBase::on_bSaveExcel_clicked()
{
    QMessageBox msg(QMessageBox::NoIcon,"please wait","wait 10 second!",QMessageBox::Ok);
    msg.show();// 设置一个等待框
    QString excelName = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("打开要的excel表"),QString("./config"),"*.xl*");
    if(nullptr == excelName)return; //没有选择就取消
    qDebug()<<"excelName = "<<excelName;
    qDebug()<<"treeWidget2excel = "<< treeWidget2excel(excelName, ui->treeWidget);
}
// 导入dat数据
void FtreeDabeBase::on_bLoadDAt_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,QString(""),QString("./config"),"*.dat");
    if(nullptr == fileName)return; //没有选择就取消
    qDebug()<<"fileName = "<<fileName;
    qDebug()<<"dat2treeWidget = "<< dat2treeWidget(fileName, ui->treeWidget);
    setTreeItemIsEditable(ui->treeWidget);    // 允许编辑
}
// 导出dat数据
void FtreeDabeBase::on_bSaveDat_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,QString(""),QString("./config"),"*.dat");
    if(nullptr == fileName)return; //没有选择就取消
    qDebug()<<"fileName = "<<fileName;
    qDebug()<<"treeWidget2dat = "<< treeWidget2dat(fileName, ui->treeWidget);
}
// 导入excel文件名
void FtreeDabeBase::on_bExcelFileName_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,QString(""),QString("./config"),"*.xl*");
    if(nullptr == fileName)return; //没有选择就取消
    ui->lineEdit_excel->setText (fileName.replace ("/","\\"));
}
// 导入dat文件名
void FtreeDabeBase::on_bDatFileName_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,QString(""),QString("./config"),"*.dat");
    if(nullptr == fileName)return; //没有选择就取消
    ui->lineEdit_dat->setText (fileName.replace ("/","\\"));
}
// 打开 excel文件名 文件
void FtreeDabeBase::on_bOpenExcel_clicked()
{
    QString str = "explorer " + ui->lineEdit_excel->text().replace ("/","\\");
    QProcess::execute(str);
}
// 打开 dat文件名 文件
void FtreeDabeBase::on_bOpenDat_clicked()
{
    QString str = "explorer " + ui->lineEdit_dat->text().replace ("/","\\");
    QProcess::execute(str);
}
// 打开 数据 文件
void FtreeDabeBase::on_bDbFileName_clicked()
{
    QString str = "explorer " + ui->lineEdit_db->text().replace ("/","\\");
    QProcess::execute(str);
}
// 查找关键key
void FtreeDabeBase::on_bFindKey_clicked()
{
    int column = ui->spinBox_FindKeyColumn->value();
    QString key = ui->lineEdit_key->text();
    if(column > ui->treeWidget->headerItem()->columnCount())return;   // 列数超出范围,不用
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
// ******************************************** 数据保存 ******************************************** begin
//函数功能：导出配置
//输入参数：
//输出参数：
//备注：
void FtreeDabeBase::dat_config_save(void)
{
    QString path = ".\\config\\AllConfig.dat";  // 统一配置地址
    QSettings save_config(path,QSettings::IniFormat);
    save_config.setIniCodec("GB2312");//支持中文
    save_config.remove(windowTitle());  // 删除组
    save_config.beginGroup(windowTitle());     // 组操作------------------------------------------begin
    save_config.setValue ("have_config"        ,true);


    // ------------------------ 配置的保存
    save_config.setValue ("lineEdit_dat"           ,ui->lineEdit_dat->text());
    save_config.setValue ("lineEdit_excel"         ,ui->lineEdit_excel->text());
    save_config.setValue ("lineEdit_key"           ,ui->lineEdit_key->text());
    save_config.setValue ("spinBox_FindKeyColumn"  ,ui->spinBox_FindKeyColumn->value());
    save_config.setValue("checkBox_hide"           ,ui->checkBox_hide->isChecked());

    save_config.endGroup();                    // 组操作------------------------------------------end
}
//函数功能：导入配置
//输入参数：
//输出参数：
//备注：
void FtreeDabeBase::dat_config_load(void)
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

    // ------------------------ 配置的读取
    ui->lineEdit_dat->setText(load_config.value("lineEdit_dat").toString());
    ui->lineEdit_excel->setText(load_config.value("lineEdit_excel").toString());
    ui->lineEdit_key->setText(load_config.value("lineEdit_key").toString());
    ui->spinBox_FindKeyColumn->setValue(load_config.value("spinBox_FindKeyColumn").toInt());
    ui->checkBox_hide->setChecked(load_config.value("checkBox_hide").toBool());
    hideFrame(load_config.value("checkBox_hide").toBool());


    load_config.endGroup();                    // 组操作------------------------------------------end
}
// ******************************************** 数据保存 ******************************************** end
