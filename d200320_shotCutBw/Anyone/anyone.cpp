#include "anyone.h"
#include "ui_anyone.h"
#include "windows.h"
#include<QImage>


AnyOne::AnyOne(QWidget *parent):QMainWindow(parent),ui(new Ui::AnyOne)
{
    ui->setupUi(this);

    // 初始化外部器件
    mydebug = Fdebug::myqDebug();    // 如果想要qDebug的打印信息，就用 myqDebug
    mydebug->show();// 如果没个归属就会关闭不掉
    ui->verticalLayout_debug->addWidget(mydebug);

//    dat_config_load();  // 文件导入

    connect(&myTimer,SIGNAL(timeout()),this,SLOT(myTimerOut()));
}
AnyOne::~AnyOne()
{
//    dat_config_save();
    delete ui;
}
void AnyOne::myTimerOut()
{
    if(ui->spinBox_CutCountResidual->value() > 0)
    {
        ui->spinBox_CutCountResidual->setValue(ui->spinBox_CutCountResidual->value()-1);    // 剩余次数-1

        QString strPath = ui->lineEdit_SavePath->text();
        saveBit s1 = saveBit::BW;
        imgType s2 = imgType::PNG;
        if(ui->radioButton_rgb->isChecked()) s1 = saveBit::RGB;
        if(ui->radioButton_gray->isChecked())s1 = saveBit::GRAY;
        if(ui->radioButton_bw->isChecked())  s1 = saveBit::BW;
        if(ui->radioButton_bmp->isChecked()) s2 = imgType::BMP;
        if(ui->radioButton_jpg->isChecked()) s2 = imgType::JPG;
        if(ui->radioButton_png->isChecked()) s2 = imgType::PNG;

        //    QString filePathName = savePath + QString("S");   // 保存文件名的组合
        //    filePathName += QDateTime::currentDateTime().toString("yyMMddhhmmsszzz.");
        QString strName = ui->lineEdit_prefix->text();
        if(ui->radioButton_order->isChecked())
        {
            uint i = ui->spinBox_CutCount->value() - ui->spinBox_CutCountResidual->value();
            strName += QString("%1").arg(i,5,10,QLatin1Char('0'));
        }
        if(ui->radioButton_time->isChecked()) strName += QDateTime::currentDateTime().toString("yyMMddhhmmsszzz.");

        cutAllScreen(strPath,strName, s1,s2);
        keybd_event(40,0,0,0);                  // press down
        Sleep(10);
        keybd_event(40,0,KEYEVENTF_KEYUP,0);    // release down

    }
    else
    {
        myTimer.stop();
        qDebug()<<"finish";
        showNormal();       // 切回正常显示状态
        ui->button_start->setText("start");

    }
}

// 关闭窗体
void AnyOne::on_pushButton_end_clicked()
{
    qApp->quit();   // 强制退出程序
}

// 点击“b1” - 启动 程序
void AnyOne::on_button_start_clicked()
{
    if (ui->button_start->text() != QString("start"))
    {
        ui->spinBox_CutCountResidual->setValue(0);
        return;
    }
    QDir dir;    // 没有文件夹就新建
    if (!dir.exists(ui->lineEdit_SavePath->text()))
    {
        bool res = dir.mkpath(ui->lineEdit_SavePath->text());
        qDebug() << "new forder!"<<res;
    }
    ui->spinBox_CutCountResidual->setValue(ui->spinBox_CutCount->value());  // 设定剩余次数
    this->showMinimized();  // 最小化自己
    myTimer.start(ui->spinBox_timeInterval->value());                       // 启动时间间隔
    ui->button_start->setText("runing,click stop!");
}

// 更改文件夹
void AnyOne::on_button_SelectSavePath_clicked()
{
    //文件夹路径
    QString srcDirPath =    QFileDialog::getExistingDirectory(
                            this, "choose src Directory",
                            ui->lineEdit_SavePath->text());
    if (srcDirPath.isEmpty())
    {
        return;
    }
    else
    {
            qDebug() << "srcDirPath=" << srcDirPath;
            srcDirPath += "/";
        ui->lineEdit_SavePath->setText(srcDirPath);
    }
}
// 打开文件夹"
void AnyOne::on_button_OpenSavePath_clicked()
{
    QString str = QString("file:%1").arg(ui->lineEdit_SavePath->text());
    QDesktopServices::openUrl(QUrl(str, QUrl::TolerantMode));             //打开
}


// 将RGB图片转为纯黑白图
bool AnyOne::imgRbg2bw(QString filePathAndName,QString outPathAndName,QString fileType)
{
    // 1.文件不存在就跳过
    QFile f(filePathAndName);
    if(!f.exists())return false;
    // 2.导入图片
    QImage img(filePathAndName,"Format_RGB32");
    // 3.图片转灰色
    img=img.convertToFormat(QImage::QImage::Format_Grayscale8);
    // 4.图片转黑白-因为QT知道的转黑白功能有问题
    uchar *imgBit=img.bits();
    for (int i = 0; i < img.width()*img.height(); i++)
    {
        *imgBit = (uchar)((*imgBit>128)*0xFF);
        imgBit++;
    }
    // 5.保存图片 ->会被压缩，压缩率自动
    // 类型是文件名单的后缀
    return img.save(outPathAndName,fileType.toLatin1().data());
}

// 打开文件夹和导入所有文件
// fileType :只能输入一种文件类型 比如"*.jpg"
bool AnyOne::loadForderFile(QString &forderPath, QStringList &filePathAndNames, QStringList &fileNames,
                    QString defaultPath,QString fileType)
{
    filePathAndNames.clear();
    fileNames.clear();
    // 1.选择要打开的文件夹
    forderPath = QFileDialog::getExistingDirectory(this,
                                                        "open Forder",
                                                        defaultPath);               // 默认路径
    if(nullptr == forderPath)return false; //没有选择就取消

    // 2.文件夹下的所有文件
    forderPath.append('/');
    QDir dir(forderPath);
    QStringList filters;
    filters<<QString(fileType);
    dir.setFilter(QDir::Files | QDir::NoSymLinks); // 设置类型过滤器，只为文件格式
    dir.setNameFilters(filters);                   // 设置文件名称过滤器，只为filters格式

    // 3.存储文件名称
    for(uint i=0; i<dir.count(); i++)
    {
        QString str = dir[i];  //文件名称
        fileNames.append(str);
        str.prepend(forderPath);
        filePathAndNames.append(str);
        qDebug()<<str;
    }
    return true;
}
// 截取当前整个屏幕并保存
// savePath :保存路径
// bit      :保存位数
// type     :保存类型
bool AnyOne::cutAllScreen(QString savePath,QString saveName,saveBit bit,imgType type)
{
    // 1. 设置保存的格式和名称，以当前时间为名称
    const char *fmat = "png";
    switch (type)
    {
        case JPG:   fmat = "jpg"; break;
        case PNG:   fmat = "png"; break;
        case BMP:   fmat = "bmp"; break;
        default:    qDebug()<<"error type!"; break;
    }
    QString strPathAndName = QString("%1%2.%3").arg(savePath,saveName,fmat);
    // 2. 获取屏幕信息
    QScreen *curScreen = QGuiApplication::primaryScreen();  // 当前屏幕的句柄
    QPixmap img = curScreen->grabWindow(0);                 // 获取当前屏幕图像
    // 3. 保存图片
    bool ret = false;
    if (bit == saveBit::RGB)
    {
        ret = img.save(strPathAndName, fmat);
    }
    else
    {
        QImage gimg = img.toImage().convertToFormat(QImage::QImage::Format_Grayscale8);
        if(bit == saveBit::GRAY)
        {
            ret = gimg.save(strPathAndName, fmat);
        }
        else if(bit == saveBit::BW)
        {
            // 4.图片转黑白-因为QT知道的转黑白功能有问题
            uchar *imgBit=gimg.bits();
            for (int i = 0; i < gimg.width()*gimg.height(); i++)
            {
                *imgBit = (uchar)((*imgBit>128)*0xFF);
                imgBit++;
            }
            ret = gimg.save(strPathAndName, fmat);
        }
    }
    if(ret) qDebug()<<"save success->"<<strPathAndName;
    else    qDebug()<<"save fail";
    return ret;
}


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
    QSettings recordOpen(QString("%1\\config\\zRecord.dat").arg(exePath), QSettings::IniFormat);
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

    // ------------------------ 配置的读取 ------------------------


    load_config.endGroup();                            // 组操作------------------------------------------end
}




