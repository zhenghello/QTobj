#include "anyone.h"
#include "ui_anyone.h"
#include<QSplitter>

#include<QSettings>

QString     filename = ".\\config\\anyone_config.dat";


Fdebug *mydebug;
QTimer  myTimer;
AnyOne::AnyOne(QWidget *parent):QMainWindow(parent),ui(new Ui::AnyOne)
{
    ui->setupUi(this);

    // 初始化外部器件
    mydebug = Fdebug::myDebug();
    QHBoxLayout *hlayout = new QHBoxLayout(ui->frame_user);// 为frame_user添加一个布局

    hlayout->addWidget(Fdebug::myDebug());
 // hlayout->addWidget(Fdebug::myShow());
 // hlayout->addWidget(Fdebug::myTest());

    dat_config_load();  // 文件导入

    connect(&myTimer,SIGNAL(timeout()),this,SLOT(myTimerOut()));
    myTimer.start(1000);

}
AnyOne::~AnyOne()
{
    dat_config_save();
    delete ui;
}
void AnyOne::myTimerOut()
{
    static int c=0;
    qDebug()<<"c="<<c++;
}

// 关闭窗体
void AnyOne::on_pushButton_end_clicked()
{
    close();
}




// 点击“b1” - 导入并保存
void AnyOne::on_b1_clicked()
{

}
// 点击“b2”
void AnyOne::on_b2_clicked()
{

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
    QString path = ".\\config\\AllConfig.dat";  // 统一配置地址
    QSettings save_config(path,QSettings::IniFormat);
    save_config.setIniCodec("GB2312");          //支持中文
    save_config.remove(windowTitle());          // 删除组
    save_config.beginGroup(windowTitle());      // 组操作------------------------------------------begin
    save_config.setValue ("have_config"        ,true);

    // ------------------------ 配置的保存 ------------------------


    save_config.endGroup();                    // 组操作------------------------------------------end

}
//函数功能：导入配置
//输入参数：
//输出参数：
//备注：
void AnyOne::dat_config_load(void)
{
    // 打开时间记录
    QSettings recordOpen(".\\config\\openRecord.dat" , QSettings::IniFormat);
    recordOpen.setValue(QDateTime::currentDateTime().toString("yyyy-MM-dd--hh-mm-ss"),"");//时间串

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


    load_config.endGroup();                            // 组操作------------------------------------------end
}




