/* 这个文件的功能是负责CAN的信息显示方式，can的解释由canExplain.c的文件负责处理
 * 这个显示方式有过滤模式和非过滤模式，如果讲过滤按键隐藏就会自动进入非过滤模式
*/

#include "fcanshow.h"
#include "ui_fcanshow.h"
FcanShow::FcanShow(QWidget *parent) :QWidget(parent),ui(new Ui::FcanShow)
{
    ui->setupUi(this);
    // 初始化关联
    filter_init();
}

FcanShow::~FcanShow()
{
    delete ui;
}

// 隐藏过滤器的同时，会清除缓存
void FcanShow::setFilterEnable(bool enable)
{
    ui->frame_filter->setHidden(!enable);
    if(ui->frame_filter->isHidden())
    {
        clear();
    }
}
// 清除数据
void FcanShow::clear()
{
    canNum=0;
    ui->label_recNum->setText(QString("%1").arg(canNum));   // 显示次数
    canDateList.clear();
    emit clearMyShow();     // 回发清屏信息
}
// 过滤器内容函数                          **************************************************** begin
// 过滤操作初始化
void FcanShow::filter_init(void)
{
    canNum=0;
    ui->label_recNum->setText(QString("%1").arg(canNum));// 显示次数

    canDateList.clear();
    connect(ui->c_filterSource ,SIGNAL(clicked(bool)),ui->spinBox_filterSource ,SLOT(setDisabled(bool)));
    connect(ui->c_filterObject ,SIGNAL(clicked(bool)),ui->spinBox_filterObject ,SLOT(setDisabled(bool)));
    connect(ui->c_filterType   ,SIGNAL(clicked(bool)),ui->spinBox_filterType   ,SLOT(setDisabled(bool)));
    connect(ui->c_filterNumber ,SIGNAL(clicked(bool)),ui->spinBox_filterNumber ,SLOT(setDisabled(bool)));
    connect(ui->c_filterContent,SIGNAL(clicked(bool)),ui->spinBox_filterContent,SLOT(setDisabled(bool)));
    connect(ui->b_filterReload ,SIGNAL(clicked()),this,SLOT(filter_reload()));  // 重载按键
}
// 重新过滤CAN帧信息
void FcanShow::filter_reload(void)
{
    int i;
    emit clearMyShow();                         // 清屏请求
    for(i=0;i<canDateList.size();i++)
    {
        emit needTranslate(canDateList.at(i));  // 发送翻译请求
    }
}
// 添加can数据
void FcanShow::append(const QStringList canDate)
{
    // 把can数据收藏
    canDateList.append(canDate);
    canNum++;
    ui->label_recNum->setText(QString("%1").arg(canNum));// 显示次数
}
// 根据选项允许的条件，判断输入的字符串是否允许显示
bool FcanShow::filter_show(const QStringList canDate)
{
    // 1.只有开启过滤器才会过滤数据,不符合条件就会提前退出
    if(false == ui->frame_filter->isHidden())
    {
        // 2.过滤控制码
        // 2.1.命令码
        if((canDate.at(3).toLower()=="00")||(canDate.at(3).toLower()=="40")||(canDate.at(3).toLower()=="41")||(canDate.at(3).toLower()=="42")||(canDate.at(3).toLower()=="43"))
        {
            if(ui->c_filterOredr->isChecked() == false)return false;
        }
        // 2.2.REP码
        else if(canDate.at(3).toLower()=="c0")
        {
            if(ui->c_filterRep->isChecked() == false)return false;
        }
        // 2.3.ACK码
        else if(canDate.at(3).toLower()=="d4")
        {
            if(ui->c_filterAck->isChecked() == false)return false;
        }
        // 2.4.evt码
        else if(canDate.at(3).toLower()=="f8")
        {
            if(ui->c_filterEvt->isChecked() == false)return false;
        }
        // 2.5.upload码
        else if(canDate.at(3).toLower()=="d8")
        {
            if(ui->c_filterUpload->isChecked() == false)return false;
        }
        // 2.6.其他 码
        else if(ui->c_filterUpload->isChecked() == false)return false;

        // 3.过滤源ID
        if(ui->c_filterSource->isChecked())
        {
            if(canDate.at(0).toInt(nullptr,16) != ui->spinBox_filterSource->value()) return false;
        }
        // 3.过滤目标ID
        if(ui->c_filterObject->isChecked())
        {
            if(canDate.at(1).toInt(nullptr,16) != ui->spinBox_filterObject->value()) return false;
        }
        // 4.过滤类型
        if(ui->c_filterType->isChecked())
        {
            if(canDate.at(5).toInt(nullptr,16) != ui->spinBox_filterType->value())   return false;
        }
        // 5.过滤对象
        if(ui->c_filterNumber->isChecked())
        {
            if(canDate.at(6).toInt(nullptr,16) != ui->spinBox_filterNumber->value()) return false;
        }
        // 6.过滤内容
        if(ui->c_filterContent->isChecked())
        {
            if(canDate.at(7).toInt(nullptr,16) != ui->spinBox_filterContent->value())return false;
        }
    }
    // 允许显示
    return true;
}
// 过滤器内容函数                          **************************************************** end
