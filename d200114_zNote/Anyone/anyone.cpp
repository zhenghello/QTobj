#include "anyone.h"
#include "ui_anyone.h"
#include "dat2tableWidget.h"
#include <QSystemTrayIcon>


AnyOne::AnyOne(QWidget *parent):QMainWindow(parent),ui(new Ui::AnyOne)
{
    ui->setupUi(this);
    // 初始化外部器件
    mydebug = Fdebug::myDebug(this); mydebug->show();
    ui->horizontalLayoutShow->addWidget(mydebug);

    // 初始化路径 - 全局通用
    exePath = QCoreApplication::applicationDirPath().replace("/", "\\");

    pathNowork  = QString("%1\\config\\fileNoWork.dat").arg(exePath);  // 未完成地址
    pathFinish  = QString("%1\\config\\fileFinish.dat").arg(exePath);  // 已完成地址
    pathDelete  = QString("%1\\config\\fileDelete.dat").arg(exePath);  // 已删除地址
    pathMemory  = QString("%1\\config\\fileMemory.dat").arg(exePath);  // 已删除地址
    mstr_new    = QString("添加");
    mstr_del    = QString("删除");
    mstr_del2   = QString("彻底删除");
    mstr_finish = QString("完成");
    mstr_nowork = QString("未完成");
    mstr_mulLine = QString("多行输入");

    // 右下角小图标功能
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/one/icon/happy.ico"));
    trayIcon->show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    // 边框和任务栏的隐藏
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);// 无边框显示,无任务栏
    setWindowOpacity(0.8);                               // 设置透明度
    // 文件导入
    dat_config_load();

    // 关联按键
    connect(ui->b1, SIGNAL(clicked()), this, SLOT(b1_clicked()));
    connect(ui->b2, SIGNAL(clicked()), this, SLOT(b2_clicked()));
    connect(ui->autoRun, SIGNAL(clicked()), this, SLOT(autoRun_clicked()));
    connect(ui->openConfig, SIGNAL(clicked()), this, SLOT(openConfig_clicked()));           // 进入配置模式
    connect(ui->pushButton_save, SIGNAL(clicked()), this, SLOT(dat_config_save()));         // 保存按键
    connect(ui->pushButton_hide, SIGNAL(clicked()), this, SLOT(hide()));                    // 隐藏按键
    connect(ui->pushButton_end,  SIGNAL(clicked()), qApp, SLOT(quit()));                    // 退出按键
    qDebug() << "building time" << __DATE__ << __TIME__ ;                                   // 最后编译时间

    // table 的初始化
    ui->tabWidget->setCurrentIndex(2);          // “未完成”是主要显示
    tableWidgetInit();

    // 自动保存的定时器设置 -> 触发后5分钟启动保存 ->     autoSaveTimer.start();会覆盖之前的定时器
    connect(&autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSaveTimerOut()));
    autoSaveTimer.setInterval(5*60*1000);       // 操作后5分钟自动保存
    autoSaveTimer.setSingleShot(true);          // 只能单次触发

    // 添加快速访问table
    tableFaster = new fTableFast(this,QString("%1\\config\\fileFaster.dat").arg(exePath));
    ui->verticalLayoutFast->addWidget(tableFaster);


}

AnyOne::~AnyOne()
{
    dat_config_save();
    delete ui;
}
// 超时处理->自动保存处理
void AnyOne::autoSaveTimerOut(void)
{
    if (isEventColseSystem == 999)return;
    dat_config_save();
    qDebug() << "auto save";
}

void AnyOne::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();  // 接受事件
    qDebug()<<"AnyOne dragEnterEvent";

}

// 捕获关机事件，关机前保存配置
bool AnyOne::nativeEvent(const QByteArray &event_Type, void *message, long *result)
{
    MSG *msg = reinterpret_cast<MSG *>(message);
    switch (msg->message)
    {
        case WM_ENDSESSION:     // 关机事件
            dat_config_save();  // 保存配置
            isEventColseSystem = 999;
        break;
        default:
        break;
    }
    return QWidget::nativeEvent(event_Type, message, result);
}
// 点击小图标的操作 -> 激活程序
void AnyOne::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (isHidden())
    {
        show();             // 显示
        activateWindow();   // 激活，显示到最前端
        raise();            // 提到最前面
    }
    else
    {
        hide();
    }
    if (reason)// 不想看到报警
    {
        ;
    }
}
// 允许开机自启动编码
void AnyOne::registerAppAutoRun(bool bAutoRun)
{
    QSettings  reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);    // 注册路径
    QString    myAppName = "zNote";    // 注册名
    if (bAutoRun)
    {
        // 将exe的路径设置为开机自启动的对象
        QString strAppPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
        reg.setValue(myAppName, strAppPath);
    }
    else
    {
        reg.setValue(myAppName, "");
    }
}
// 点击“b1”
void AnyOne::b1_clicked(void)
{
    qDebug() << QString("郑凯鹏 hello");
}
// 点击“b2”
void AnyOne::b2_clicked(void)
{

}
// 点击“修改配置模式”
#include<QProcess>
void AnyOne::openConfig_clicked(void)
{
    QProcess process;
    process.startDetached(QString("explorer.exe %1%2").arg(exePath).arg("\\config"));
    // 外框模式变为普通
    setWindowFlags(Qt::Window);// 正常显示
    show();raise();

    // 使能内容项目-自适应外框
    tableNowork->horizontalHeader()->setSectionResizeMode(tableRowContent, QHeaderView::Stretch);
    tableFinish->horizontalHeader()->setSectionResizeMode(tableRowContent, QHeaderView::Stretch);
    tableDelete->horizontalHeader()->setSectionResizeMode(tableRowContent, QHeaderView::Stretch);
    tableMemory->horizontalHeader()->setSectionResizeMode(tableRowContent, QHeaderView::Stretch);

}
// 点击“允许开机自启动”
void AnyOne::autoRun_clicked(void)
{
    registerAppAutoRun(true);
}
// ******************************************** table 操作 ******************************************** begin

// 1.初始化一个新的excel表->在导入配置以后生效
void AnyOne::tableWidgetInit(void)
{
    // 1.常用索引
    tableNowork = ui->tableWidgetNowork;
    tableFinish = ui->tableWidgetFinish;
    tableDelete = ui->tableWidgetDelete;
    tableMemory = ui->tableWidgetMemory;
    // 2.几个备忘文件的导入
    dat2tableWidget(pathNowork, tableNowork);  // 未完成
    dat2tableWidget(pathFinish, tableFinish);  // 已完成
    dat2tableWidget(pathDelete, tableDelete);  // 已删除
    dat2tableWidget(pathMemory, tableMemory);  // 备忘录
    // 2.将未完成的级别进行排序，越大级别越高
    tableWidgetLevelFix(tableNowork);
    tableWidgetLevelFix(tableFinish);
    tableWidgetLevelFix(tableDelete);
    tableWidgetLevelFix(tableMemory);
    tableNowork->sortByColumn(tableRowLevel);
    tableMemory->sortByColumn(tableRowLevel);

    // 3.未完成没有行就添加一行
    if (tableNowork->rowCount() == 0)
        tableWidgetAddOne( tableNowork, 0, QString("add empty line") );
    if (tableMemory->rowCount() == 0)
        tableWidgetAddOne(tableMemory, 0, QString("add empty line"));
    // 3.使能编辑性
    //tableNowork->horizontalHeader().setResizeMode(QHeaderView::Fixed);
    // 4.使能水平拉伸
    tableNowork->horizontalHeader()->setSectionResizeMode(tableRowStartTime,    QHeaderView::ResizeToContents);
    tableNowork->horizontalHeader()->setSectionResizeMode(tableRowChangeTime,   QHeaderView::ResizeToContents);
    tableNowork->horizontalHeader()->setSectionResizeMode(tableRowLevel,        QHeaderView::Fixed);
    tableNowork->horizontalHeader()->setSectionResizeMode(tableRowContent,      QHeaderView::Stretch);
    tableNowork->setColumnWidth(tableRowLevel,      20);

    tableFinish->horizontalHeader()->setSectionResizeMode(tableRowStartTime,    QHeaderView::ResizeToContents);
    tableFinish->horizontalHeader()->setSectionResizeMode(tableRowChangeTime,   QHeaderView::ResizeToContents);
    tableFinish->horizontalHeader()->setSectionResizeMode(tableRowLevel,        QHeaderView::Fixed);
    tableFinish->horizontalHeader()->setSectionResizeMode(tableRowContent,      QHeaderView::Stretch);
    tableFinish->setColumnWidth(tableRowLevel,      20);

    tableDelete->horizontalHeader()->setSectionResizeMode(tableRowStartTime,    QHeaderView::ResizeToContents);
    tableDelete->horizontalHeader()->setSectionResizeMode(tableRowChangeTime,   QHeaderView::ResizeToContents);
    tableDelete->horizontalHeader()->setSectionResizeMode(tableRowLevel,        QHeaderView::Fixed);
    tableDelete->horizontalHeader()->setSectionResizeMode(tableRowContent,      QHeaderView::Stretch);
    tableDelete->setColumnWidth(tableRowLevel,      20);

    tableMemory->hideColumn(tableRowStartTime);
    tableMemory->hideColumn(tableRowChangeTime);
    tableMemory->horizontalHeader()->setSectionResizeMode(tableRowLevel     ,   QHeaderView::Fixed);
    tableMemory->horizontalHeader()->setSectionResizeMode(tableRowContent   ,   QHeaderView::Stretch);
    tableMemory->setColumnWidth(tableRowLevel       ,20);

    // 5.1.创建右键菜单 - 未完成
    tableNowork->addAction(new QAction(mstr_new     ));
    tableNowork->addAction(new QAction(mstr_finish  ));
    tableNowork->addAction(new QAction(mstr_mulLine ));
    tableNowork->addAction(new QAction(mstr_del     ));
    QObject::connect(tableNowork, SIGNAL(itemPressed(QTableWidgetItem *)), this, SLOT(tableWidgetItemPressed(QTableWidgetItem *)));         // 关联触发按键
    QObject::connect(tableNowork, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(tableWidgetNoworkItemChanged(QTableWidgetItem *)));   // 关联触发按键-自动保存
    QObject::connect(tableNowork, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(tableWidgetItemDoubleClicked(QTableWidgetItem *)));   // 关联触发按键-自动保存

    // 5.2.创建右键菜单 - 已完成
    tableFinish->addAction(new QAction(mstr_nowork));
    tableFinish->addAction(new QAction(mstr_del));
    QObject::connect(tableFinish, SIGNAL(itemPressed(QTableWidgetItem *)), this, SLOT(tableWidgetItemPressed(QTableWidgetItem *)));         // 关联触发按键
    QObject::connect(tableFinish, SIGNAL(cellChanged(int, int)), &autoSaveTimer, SLOT(start()));                                            // 关联触发按键-自动保存

    // 5.3.创建右键菜单 - 已删除
    tableDelete->addAction(new QAction(mstr_nowork));
    tableDelete->addAction(new QAction(mstr_finish));
    tableDelete->addAction(new QAction(" "));
    tableDelete->addAction(new QAction(" "));
    tableDelete->addAction(new QAction(mstr_del2));
    QObject::connect(tableDelete, SIGNAL(itemPressed(QTableWidgetItem *)), this, SLOT(tableWidgetItemPressed(QTableWidgetItem *)));         // 关联触发按键
    QObject::connect(tableDelete, SIGNAL(cellChanged(int, int)), &autoSaveTimer, SLOT(start()));                                            // 关联触发按键-自动保存

    /* 5.3.创建右键菜单 - 备忘录 */
    tableMemory->addAction(new QAction(mstr_new     ));
    tableMemory->addAction(new QAction(mstr_mulLine ));
    tableMemory->addAction(new QAction(" "));
    tableMemory->addAction(new QAction(" "));
    tableMemory->addAction(new QAction(mstr_del2    ));
    QObject::connect(tableMemory, SIGNAL(itemPressed(QTableWidgetItem *)), this, SLOT(tableWidgetItemPressed(QTableWidgetItem *)));             // 关联触发按键
    QObject::connect(tableMemory, SIGNAL(cellChanged(int, int)), &autoSaveTimer, SLOT(start()));                                                // 关联触发按键-自动保存
    QObject::connect(tableMemory, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(tableWidgetItemDoubleClicked(QTableWidgetItem *)));  // 关联触发按键-自动保存
}

// 2.tableWidget双击，如果是本身是多行，进直接进入多行编辑
void AnyOne::tableWidgetItemDoubleClicked(QTableWidgetItem *item)
{
    // 1.获取信息
    QTableWidget *table = item->tableWidget();      // 当前的table
    int curRow = table->currentRow();               // 当前行
    //int curColumn = table->currentColumn();       // 当前列
    if (curRow < 0)
    {
        return;
    }
    // 2.多行输入
    if (item->text().contains('\n'))
    {
        QString str = QInputDialog::getMultiLineText(this, "多行输入", "单元格一定要输入多行", item->text());
        if (str.isEmpty() == false)
        {
            item->setText(str);
            item->setTextColor(QColor("blue"));
            item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
            /*根据内容调整行高度*/
            int h = (str.length() - str.remove('\n').length() + 1) * 16;  // 15 和字符格式有关的，用的是字符：宋体9pt
            table->setRowHeight(curRow, qMax(h, 25));
        }
    }
}

// 3.tableWidgetNowork修改内容后更新时间
void AnyOne::tableWidgetNoworkItemChanged(QTableWidgetItem *item)
{
    // 如果自己的item被删除，又重写，那么就会进来一个空的item
    if(item->isSelected() == false || item == nullptr)
    {
        qDebug()<< "item is null";
        return;
    }
    // 1.获取信息
    QTableWidget *table = item->tableWidget();      // 当前的table
    int curRow = table->currentRow();              // 当前行
    int curColumn = table->currentColumn();        // 当前列
    if (curRow < 0 || curColumn == tableRowChangeTime)
    {
        return;
    }
    // 2.修改时间
    QString curTime = QDateTime::currentDateTime().toString("yyMMdd");// 当前时间
    table->setItem(curRow, tableRowChangeTime, new QTableWidgetItem(curTime));
    // 3.启动保存倒计时
    autoSaveTimer.start();
}
// 4.鼠标右键按下,tableWidgetXX的动作
void AnyOne::tableWidgetItemPressed(QTableWidgetItem *item)
{
    // 0.只有右击触发有用
    if (qApp->mouseButtons() != Qt::RightButton)return;
    // 1.获取信息
    QTableWidget *table = item->tableWidget();   // 当前的table
    int curRow = table->currentRow() ;          // 当前行
    //int curColumn = table->currentColumn();     // 当前列
    // 2.捕获动作
    QMenu *menu = new QMenu(table);
    menu->addActions(table->actions());
    QAction *act = menu->exec(QCursor::pos());
    menu->deleteLater();
    if (act == nullptr)return;
    // 3.执行动作
    // 3.1.添加新行
    if (act->text() == mstr_new)
    {
        tableWidgetAddOne(table);
    }
    // 3.2.多行编辑
    else if (act->text() == mstr_mulLine)
    {
        QString str = QInputDialog::getMultiLineText(this, "多行输入", "单元格输入", item->text(),nullptr);
        if (str.isEmpty() == false)
        {
            item->setText(str);
            /*根据内容调整行高度*/
            int h = (str.length() - str.remove('\n').length() + 1) * 15;  // 15 和字符格式有关的，用的是字符：宋体9pt
            table->setRowHeight(curRow, qMax(h, 25));
        }
    }
    // 3.2.彻底删除
    else if (act->text() == mstr_del2)
    {
        table->removeRow(curRow);    // 彻底删除
    }
    // 3.3.临时删除
    else if (act->text() == mstr_del)
    {
        tableWidgetMoveOne(table, curRow, tableDelete, 0);
        if (table->rowCount() == 0)
        {// 如果用完了，就添加新行
            tableWidgetAddOne(table);
        }
    }
    // 3.4.完成任务
    else if (act->text() == mstr_finish)
    {
        tableWidgetMoveOne(table, curRow, tableFinish, 0);
    }
    // 3.5.还原任务未完成
    else if (act->text() == mstr_nowork)
    {
        tableWidgetMoveOne(table, curRow, tableNowork, 0);
    }
}

// 5.table 添加一行
void AnyOne::tableWidgetAddOne(QTableWidget *table, int row, QString str)
{
    QString curTime = QDateTime::currentDateTime().toString("yyMMdd");// 当前时间

    table->insertRow(row);
    QTableWidgetItem *item0, *item1, *item2, *item3;
    item0 = new QTableWidgetItem(curTime);
    item1 = new QTableWidgetItem(curTime);
    item2 = new QTableWidgetItem(str);
    item3 = new QTableWidgetItem("10");                                 // 默认优先级=最低级
    table->setItem(row, tableRowLevel       , item3);
    table->setItem(row, tableRowContent     , item2);
    table->setItem(row, tableRowChangeTime  , item1);
    table->setItem(row, tableRowStartTime   , item0);

    // 重新定位单元格
    table->setFocus();                                                  // 设置为活动
    table->setCurrentCell(0,0);                                         // 选择到新的单元格
    table->editItem(item2);
}

// table 转移一行，把table1的row1转到table2的row2上，并更新时间
void AnyOne::tableWidgetMoveOne(QTableWidget *table1, int row1, QTableWidget *table2, int row2)
{
    QString curTime = QDateTime::currentDateTime().toString("yyMMdd");// 当前时间
    QTableWidgetItem *item0, *item1, *item2, *item3;
    item0 = table1->takeItem(row1, tableRowStartTime    );
    item1 = table1->takeItem(row1, tableRowChangeTime   );
    item1->setText(curTime);                                          // 修改编辑时间
    item2 = table1->takeItem(row1, tableRowContent      );
    item3 = table1->takeItem(row1, tableRowLevel);
    table1->removeRow(row1);
    table2->insertRow(row2);
    table2->setItem(row2, tableRowChangeTime    , item1);
    table2->setItem(row2, tableRowStartTime     , item0);
    table2->setItem(row2, tableRowContent       , item2);
    table2->setItem(row2, tableRowLevel         , item3);
    // 重新定位单元格
    table2->setCurrentCell(0,0);                                         // 选择到新的单元格
}

// tableWidget 删除存在空白的空行
void AnyOne::tableWidgetDelEmptyLine(QTableWidget *table)
{
    int rowCount = table->rowCount();
    int columnCount = table->columnCount();
    for (int row = rowCount-1; row >=0 ; row--)
    {
        for (int column = columnCount-1; column >= 0; column--)
        {
            QTableWidgetItem *item = table->item(row, column);
            if ((item == NULL) || (item->text() == NULL))
                table->removeRow(row);
        }
    }
}
// tableWidget 修复级别中的内容长度
void AnyOne::tableWidgetLevelFix(QTableWidget *table)
{
    int rowCount = table->rowCount();
    for (int row = 0; row < rowCount; row++)
    {

        QTableWidgetItem *item = table->item(row, tableRowLevel);
        uint num = item->text().toUInt();
        QString str = QString("%1").arg(num,2,10,QChar('0'));
        //delete(item);
        item = new QTableWidgetItem(str);
        table->setItem(row, tableRowLevel,item);
    }
}
// ******************************************** table 操作 ******************************************** end

// ******************************************** 数据保存 ******************************************** begin
//函数功能：保存配置
//输入参数：
//输出参数：
//备注：
void AnyOne::dat_config_save(void)
{
    QSettings save_config(QString("%1\\config\\AllConfig.dat").arg(exePath), QSettings::IniFormat);
    save_config.setIniCodec("GB2312");          //支持中文
    save_config.remove(windowTitle());          // 删除组
    save_config.beginGroup(windowTitle());      // 组操作------------------------------------------begin
    save_config.setValue("have_config", true);

    // ------------------------ 配置的保存 ------------------------
    save_config.setValue("pos", pos());            // 保存高度
    save_config.setValue("size", size());        // 保存大小

    save_config.endGroup();                    // 组操作------------------------------------------end

    /* 1.删除空白项*/
    tableWidgetDelEmptyLine(tableNowork);
    tableWidgetDelEmptyLine(tableFinish);
    tableWidgetDelEmptyLine(tableDelete);
    tableWidgetDelEmptyLine(tableMemory);

    /* 2.几个文件的每日保存 */
    // 2.1.检查目录是否存在，若不存在则新建
    QString dir_str = QString("%1\\config\\backup").arg(exePath);
    QDir dir;
    if (!dir.exists(dir_str))
    {
        bool res = dir.mkpath(dir_str);
        qDebug() << "新建目录是否成功" << res;
    }

    QString curTime = QDateTime::currentDateTime().toString("yyMMdd_");// 当前时间
    QString pathNowork2 = QString("%1\\config\\backup\\d%2fileNoWork.dat").arg(exePath).arg(curTime);  // 未完成地址
    QString pathFinish2 = QString("%1\\config\\backup\\d%2fileFinish.dat").arg(exePath).arg(curTime);  // 已完成地址
    QString pathDelete2 = QString("%1\\config\\backup\\d%2fileDelete.dat").arg(exePath).arg(curTime);  // 已删除地址
    QString pathMemory2 = QString("%1\\config\\backup\\d%2fileMemory.dat").arg(exePath).arg(curTime);  // 备忘录地址
    QString pathFaster2 = QString("%1\\config\\backup\\d%2fileFast.dat").arg(exePath).arg(curTime);  // 备忘录地址

    tableWidget2dat(pathNowork2, tableNowork);  // 未完成
    tableWidget2dat(pathFinish2, tableFinish);  // 已完成
    tableWidget2dat(pathDelete2, tableDelete);  // 已删除
    tableWidget2dat(pathMemory2, tableMemory);  // 备忘录
    tableWidget2dat(pathFaster2, tableFaster);  // 快速访问

    /* 3.几个文件的保存 */
    tableWidget2dat(pathNowork, tableNowork);  // 未完成
    tableWidget2dat(pathFinish, tableFinish);  // 已完成
    tableWidget2dat(pathDelete, tableDelete);  // 已删除
    tableWidget2dat(pathMemory, tableMemory);  // 备忘录


    // 关闭时间记录
    QSettings recordOpen(QString("%1\\config\\zRecord.dat").arg(exePath), QSettings::IniFormat);
    recordOpen.setValue(QDateTime::currentDateTime().toString("yyyy-MM-dd--hh-mm-ss"), "save");//时间串
}
//函数功能：导入配置
//输入参数：
//输出参数：
//备注：
void AnyOne::dat_config_load(void)
{
    // 打开时间记录
    QSettings recordOpen(QString("%1\\config\\zRecord.dat").arg(exePath), QSettings::IniFormat);
    recordOpen.setValue(QDateTime::currentDateTime().toString("yyyy-MM-dd--hh-mm-ss"), "load");//时间串

    QSettings load_config(QString("%1\\config\\AllConfig.dat").arg(exePath), QSettings::IniFormat);
    load_config.setIniCodec("GB2312");                    // 支持中文
    load_config.beginGroup(windowTitle());              // 组操作------------------------------------------begin
                                                        // 判断文件存在
    if (load_config.contains("have_config") == false)
    {
        QMessageBox::warning(NULL, QString("Loading Error"), windowTitle() + " no file!");
        return;
    }
    // 位置的保存
    if (load_config.contains("pos") == true)
    {
        move(load_config.value("pos").toPoint());
    }
    // 大小的保存
    if (load_config.contains("size") == true)
    {
        resize(load_config.value("size").toSize());
    }

    // ------------------------ 配置的读取 ------------------------




    load_config.endGroup();                            // 组操作------------------------------------------end
}
