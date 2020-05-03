#include "anyone.h"
#include "ui_anyone.h"
//#include "stdio.h"
#include "excel2mat.h"
#include "dat2tableWidget.h"

AnyOne::AnyOne(QWidget *parent):QMainWindow(parent),ui(new Ui::AnyOne)
{
    ui->setupUi(this);

    // 初始化外部器件
    mydebug = Fdebug::myqDebug();    // 如果想要qDebug的打印信息，就用 myqDebug
    mydebug->show();// 如果没个归属就会关闭不掉
    qDebug()<<QString("郑凯鹏你好！");
    ui->verticalLayout_debug->addWidget(mydebug);

    // 初始化路径 - 全局通用
    exePath = QCoreApplication::applicationDirPath().replace("/", "\\");
    dat_config_load();  // 文件导入
    tableWidgetInit();
    ui->label_buildTime->setText(QString("building time:%1 %2").arg(__DATE__).arg(__TIME__));   // 编译的时候固定了，后面就不会变

    mstr_new = QString("添加");
    mstr_del = QString("删除");
    mstr_up  = QString("上移");
    mstr_dowm= QString("下移");
    mstr_uup = QString("置顶");
    emd = new Excel2Mat();

    ui->lineEdit->setAcceptDrops(true);
}
AnyOne::~AnyOne()
{
    dat_config_save();
    delete ui;
}

// 关闭窗体
void AnyOne::on_pushButton_end_clicked()
{
    qApp->quit();   // 强制退出程序
}

// 点击“文件名”
#include "excel2tableWidget.h"
void AnyOne::on_b101_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"open xn-csv file",ui->lineEdit->text(),"*.csv");
    if(nullptr == fileName)return; //没有选择就取消
    fileName.replace ("/","\\");
    ui->lineEdit->setText (fileName);
    bool ret=emd->load(fileName);
    qDebug() << emd->rowSize()<<emd->colunmSize();
    if (ret)
    {
//        if emd->d() // 判断第一个单元格是否正确
        ui->textEdit->setText("D:load success!");
        ui->textEdit->append(QString("obj num = %1").arg(emd->rowSize()-2));
    }
    else ui->textEdit->setText("D:load fail!");
}
// 打开文件->用于编辑
void AnyOne::on_b103_clicked()
{
    QString str1 = "explorer " + ui->lineEdit->text();
    QProcess::execute(str1);
}
// 编辑时快速查找
void AnyOne::on_lineEditFind_textChanged(const QString &arg1)
{
    QList<QTableWidgetItem*> items;
    ui->tableWidget->selectRow(0);
    items = ui->tableWidget->findItems(arg1,Qt::MatchContains);
    if (items.size()>0)
    {
        int r = items.first()->row();
        ui->tableWidget->selectRow(r);
        tableWidgetItemPressed(items.first());
    }
}
// ******************************************** table 操作 ******************************************** begin

// 1.初始化一个新的excel表->在导入配置以后生效
void AnyOne::tableWidgetInit(void)
{
    // 1.导入配置的顺序
    QString datName = QString("%1\\config\\XNobjConfig.dat").arg(exePath);
    dat2tableWidget(datName,ui->tableWidget);
    // 2.设置列宽
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(1,      20);
    ui->tableWidget->setColumnWidth(2,      20);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    // 3.右击菜单
    mstr_new = QString("添加");
    mstr_del = QString("删除");
    mstr_up  = QString("上移");
    mstr_dowm= QString("下移");
    mstr_uup = QString("置顶");
    ui->tableWidget->addAction(new QAction(mstr_uup     ));
    ui->tableWidget->addAction(new QAction(mstr_up      ));
    ui->tableWidget->addAction(new QAction(mstr_dowm    ));
    ui->tableWidget->addAction(new QAction(mstr_new     ));
    ui->tableWidget->addAction(new QAction(mstr_del     ));

    // 4.右击关联
    QObject::connect(ui->tableWidget, SIGNAL(itemPressed(QTableWidgetItem *)), this, SLOT(tableWidgetItemPressed(QTableWidgetItem *)));             // 关联触发按键
 }
// 4.鼠标右键按下,tableWidgetXX的动作
void AnyOne::tableWidgetItemPressed(QTableWidgetItem *item)
{
//    // 0.只有右击触发有用
//    if (qApp->mouseButtons() != Qt::RightButton)return;
    // 1.获取信息
    QTableWidget *table = item->tableWidget();  // 当前的table
    int curRow = table->currentRow() ;          // 当前行
    int curColumn = table->currentColumn();     // 当前列
    QString str = item->text();
    // 2.捕获动作
    if (curColumn==0) // 获取数据
    {
        qDebug()<<str;
        int cNum;  // 所在的列号
        bool ret;
        // 在em的第二个
        ret = emd->columnFind(str,1,cNum); // xn 把标题放在第二行
        if (ret==false)
        {
            ui->textEdit->setText("NO DATA!");
        }
        else
        {
            ui->textEdit->clear();
            int i,len = emd->rowSize();
            for(i=0;i<len;i++)
                ui->textEdit->append(emd->d(i,cNum));
            ui->textEdit->selectAll();
            ui->textEdit->copy();
            ui->textEdit->moveCursor(QTextCursor::Start);
        }
    }
    if (curColumn==1) // 列表移动
    {
        // 2.捕获动作
        QMenu *menu = new QMenu(table);
        menu->addActions(table->actions());
        QAction *act = menu->exec(QCursor::pos());
        menu->deleteLater();
        if (act == nullptr)return;
        // 3.新增
        if (act->text() == mstr_new)
        {
            tableWidgetAddOne(table, curRow);
        }
        // 4.删除
        if (act->text() == mstr_del)
        {
            ui->tableWidget->removeRow(curRow);
        }
        // 5.上移
        if ((act->text() == mstr_up)&&(curRow>1))
        {
            QString str = ui->tableWidget->item(curRow,0)->text();
            ui->tableWidget->removeRow(curRow);
            tableWidgetAddOne(table, curRow-1,str);
        }
        // 6.下移
        if ((act->text() == mstr_dowm)&&(curRow<table->rowCount()))
        {
            QString str = ui->tableWidget->item(curRow,0)->text();
            ui->tableWidget->removeRow(curRow);
            tableWidgetAddOne(table, curRow+1,str);
        }
        // 6.置顶
        if (act->text() == mstr_uup)
        {
            QString str = ui->tableWidget->item(curRow,0)->text();
            ui->tableWidget->removeRow(curRow);
            tableWidgetAddOne(table, 0,str);
        }
    }
}
// 2.table 添加一行
void AnyOne::tableWidgetAddOne(QTableWidget *table, int row, QString str)
{
    table->insertRow(row);
    QTableWidgetItem *item0, *item1, *item2;
    item0 = new QTableWidgetItem(str);
    item1 = new QTableWidgetItem();
    item2 = new QTableWidgetItem();
    table->setItem(row, 0       , item0);
    table->setItem(row, 1       , item1);
    table->setItem(row, 2       , item2);
}
// ******************************************** 数据保存 ******************************************** begin
//函数功能：保存配置
//输入参数：
//输出参数：
//备注：
void AnyOne::dat_config_save(void)
{
    QString str = QString("%1\\config\\AllConfig.dat").arg(exePath);
    qDebug()<<"D:dat_config_save "<<str;
    QSettings save_config(str, QSettings::IniFormat);
    save_config.setIniCodec("GB2312");          //支持中文
    save_config.remove(windowTitle());          // 删除组
    save_config.beginGroup(windowTitle());      // 组操作------------------------------------------begin
    save_config.setValue ("have_config"        ,true);
    save_config.setValue ("lineEdit"        ,ui->lineEdit->text());
    // ------------------------ 配置的保存 ------------------------
    QString datName = QString("%1\\config\\XNobjConfig.dat").arg(exePath);
    tableWidget2dat( datName,ui->tableWidget);
    save_config.endGroup();                    // 组操作------------------------------------------end

}
//函数功能：导入配置
//输入参数：
//输出参数：
//备注：
void AnyOne::dat_config_load(void)
{
    // 打开时间记录
    QString str = QString("%1\\config\\AllConfig.dat").arg(exePath);
    qDebug()<<"D:dat_config_load "<<str;

    QSettings recordOpen(str, QSettings::IniFormat);
    recordOpen.setValue(QDateTime::currentDateTime().toString("yyyy-MM-dd--hh-mm-ss"),"");//时间串

    QSettings load_config(QString("%1\\config\\AllConfig.dat").arg(exePath), QSettings::IniFormat);// 统一配置地址
    load_config.setIniCodec("GB2312");  // 支持中文
    load_config.beginGroup(windowTitle());              // 组操作------------------------------------------begin
    //判断文件存在
    if(load_config.contains("have_config")==false)
    {
        QMessageBox::warning(NULL, QString("Loading Error"),windowTitle() + " no file!");
        return;
    }
    ui->lineEdit->setText( load_config.value("lineEdit").toString());
    // ------------------------ 配置的读取 ------------------------
    load_config.endGroup();                            // 组操作------------------------------------------end
}
