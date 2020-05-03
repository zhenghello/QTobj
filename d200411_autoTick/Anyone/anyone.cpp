#include "anyone.h"
#include "ui_anyone.h"
#include <windows.h>

QTimer  myTimer;
AnyOne::AnyOne(QWidget *parent):QMainWindow(parent),ui(new Ui::AnyOne)
{
    ui->setupUi(this);
    show();
    // 定时器关联
    connect(&myTimer,SIGNAL(timeout()),this,SLOT(myTimerOut()));

    // 初始化外部器件
    mydebug = Fdebug::myqDebug();    // 如果想要qDebug的打印信息，就用 myqDebug
    mydebug->show();                // 如果没个归属就会关闭不掉
    ui->verticalLayout_debug->addWidget(mydebug);
    // 右下角小图标功能
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/one/icon/happy.ico"));
    trayIcon->show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    // 初始化路径 - 全局通用
    exePath = QCoreApplication::applicationDirPath().replace("/", "\\");
    // 文件导入
    dat_config_load();
    // 编译的时候固定了，后面就不会变
    ui->label_buildTime->setText(QString("building time:%1 %2").arg(__DATE__).arg(__TIME__));
    // 获取屏幕分辨率
    screenWidth  = QApplication::desktop()->screenGeometry().width();
    screenHeight = QApplication::desktop()->screenGeometry().height();

    // 判断是否自动运行
    if(ui->checkBox_startAndRun->isChecked())
    {
        on_button_start_clicked();
    }
}
AnyOne::~AnyOne()
{
    dat_config_save();
    delete ui;
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
// 关闭窗体
void AnyOne::on_pushButton_end_clicked()
{
    qApp->quit();   // 强制退出程序
}

// 点击“b1” - 开始点击
void AnyOne::on_button_start_clicked()
{
    if (ui->button_start->text() == QString("start"))
    {
        hide(); // 自动隐藏
        ui->groupBox_tickOption->setEnabled(false);
        myTimer.start(ui->spinBox_tickInterval->value());
        ui->button_start->setText("stop");
    }
    else
    {
        ui->groupBox_tickOption->setEnabled(true);
        myTimer.stop();
        ui->button_start->setText("start");
    }
}
// 定时触发函数
void AnyOne::myTimerOut()
{
    int xx = ui->spinBox_tickX->value() * 65536 / screenWidth;
    int yy = ui->spinBox_tickY->value() * 65536 / screenHeight;
    mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, xx, yy, 0, 0); // 移动鼠标
    Sleep(10);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0); // 右键按下
    Sleep(10);
    mouse_event(MOUSEEVENTF_RIGHTUP  , 0, 0, 0, 0); // 右键松开

    static int c=0;
    qDebug()<<"c="<<c++;
}
// 点击“b2”-开机启动
void AnyOne::on_button_autoRun_clicked()
{
    QSettings  reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);    // 注册路径
    QString    myAppName = "autoTick";    // 注册名
    // 将exe的路径设置为开机自启动的对象
    QString strAppPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
    reg.setValue(myAppName, strAppPath);
}
// 点击“b3”
void AnyOne::on_b3_clicked()
{

}
// 点击“b4”
void AnyOne::on_b4_clicked()
{

}
// 点击“b5”
void AnyOne::on_b5_clicked()
{

}
// 点击“b6”
void AnyOne::on_b6_clicked()
{

}
// 点击“文件名”
void AnyOne::on_b101_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(nullptr == fileName)return; //没有选择就取消
    fileName.replace ("/","\\");
    ui->lineEdit->setText (fileName);
}
// 点击“测试”
void AnyOne::on_b102_clicked()
{
    mydebug->setText("my just test");
    qDebug()<<"just test!";
}
// 打开文件->用于编辑
void AnyOne::on_b103_clicked()
{
    QString str1 = "explorer " + ui->lineEdit->text();
    QProcess::execute(str1);
}


// ******************************************** 数据保存 ******************************************** begin
//函数功能：保存配置
//输入参数：
//输出参数：
//备注：
void AnyOne::dat_config_save(void)
{
    QString path = QString("%1\\config\\AllConfig.dat").arg(exePath);
    QSettings save_config(path, QSettings::IniFormat);
    save_config.setIniCodec("GB2312");          //支持中文
    save_config.remove(windowTitle());          // 删除组
    save_config.beginGroup(windowTitle());      // 组操作------------------------------------------begin
    save_config.setValue ("have_config"        ,true);
    // ------------------------ 配置的保存 ------------------------
    save_config.setValue ("spinBox_tickInterval" ,ui->spinBox_tickInterval->value());
    save_config.setValue ("spinBox_tickX"        ,ui->spinBox_tickX->value());
    save_config.setValue ("spinBox_tickY"        ,ui->spinBox_tickY->value());
    save_config.setValue ("checkBox_startAndRun" ,ui->checkBox_startAndRun->isChecked());

    save_config.endGroup();                    // 组操作------------------------------------------end
}
//函数功能：导入配置
//输入参数：
//输出参数：
//备注：
void AnyOne::dat_config_load(void)
{
    // 打开时间记录
    QSettings recordOpen(QString("%1\\config\\zRecord.dat").arg(exePath), QSettings::IniFormat);
    recordOpen.setValue(QDateTime::currentDateTime().toString("yyyy-MM-dd--hh-mm-ss"),"");//时间串

    QString path = QString("%1\\config\\AllConfig.dat").arg(exePath);
    QSettings load_config(path, QSettings::IniFormat);// 统一配置地址
    load_config.setIniCodec("GB2312");  // 支持中文
    load_config.beginGroup(windowTitle());              // 组操作------------------------------------------begin
    //判断文件存在
    if(load_config.contains("have_config")==false)
    {
        QMessageBox::warning(NULL, QString("Loading Error"),windowTitle() + " no file!");
        return;
    }

    // ------------------------ 配置的读取 ------------------------
    ui->spinBox_tickInterval->setValue(load_config.value("spinBox_tickInterval").toInt());
    ui->spinBox_tickX->setValue(load_config.value("spinBox_tickX").toInt());
    ui->spinBox_tickY->setValue(load_config.value("spinBox_tickY").toInt());
    ui->checkBox_startAndRun->setChecked(load_config.value("checkBox_startAndRun").toBool());

    load_config.endGroup();                            // 组操作------------------------------------------end
}




