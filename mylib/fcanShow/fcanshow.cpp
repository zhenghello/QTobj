/* 这个文件的功能是负责CAN的信息显示方式，can的解释由canExplain.c的文件负责处理
 * 这个显示方式有过滤模式和非过滤模式，如果讲过滤按键隐藏就会自动进入非过滤模式
*/

#include "fcanshow.h"
#include "ui_fcanshow.h"
FcanShow::FcanShow(QWidget *parent) :QWidget(parent),ui(new Ui::FcanShow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()|Qt::Window);//设置为从类
    // 设置 myShow
    myShow = Fdebug::myShow();
    ui->verticalLayout_show->addWidget(myShow);
    // 初始化关联
    filter_init();
}

FcanShow::~FcanShow()
{
    delete ui;
}

void FcanShow::setFilterEnable(bool enable)
{
    ui->frame_filter->setHidden(!enable);
}

//将CAN数据转换为字符串解释                           ****************************************************
void FcanShow::deal_can_order(QByteArray qby)
{
    QString     strIN = qby;
    QVector<uint> uintArrayOUT;
    QString     strOUT;
    QColor      color;
   // QString     strExplain;
    Fdebug::myDebug()->setText(strIN);
    //  把输入的'('前的数据滤除
    int index = strIN.indexOf("(");
    strIN.remove(0,index);
    //  解释字符串
    if(false==canStr2explainStr(strIN,&uintArrayOUT,&strOUT,&color))
    {
        //Fdebug::myDebug()->setChar("非法输入");
        return;
    }
    //  缓存有用的数据
    QDateTime curTime = QDateTime::currentDateTime();   //
    QString   str = curTime.toString("hh:mm:ss ")+strIN+"       "+strOUT;//显示合集
    canStrBuf.append(str);
    canByteBuf.append(uintArrayOUT);
    canColorBuf.append(color);
    // 经过过滤器显示内容
    filter_show( uintArrayOUT, str, color);
}
// 过滤器内容函数                          **************************************************** begin
// 过滤操作初始化
void FcanShow::filter_init(void)
{
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
    myShow->clear();
    for(i=0;i<canByteBuf.size();i++)
    {
        filter_show(canByteBuf.at(i),canStrBuf.at(i),canColorBuf.at(i));
    }
}
// 根据选项过滤显示的内容
void FcanShow::filter_show(QVector<uint> qby,QString str,QColor col)
{
    static int i=0;
    // 1.只有开启过滤器才会过滤数据,不符合条件就会提前退出
    if(false == ui->frame_filter->isHidden())
    {
        // 2.过滤控制码
        // 2.1.命令码
        switch((unsigned char)(qby.at(3)))
        {
            case FRAME_CONTROL_CODE_COMMAND_REP    :
            case FRAME_CONTROL_CODE_COMMAND_NO_REP :
            case FRAME_CONTROL_CODE_TS_HEAD        :
            case FRAME_CONTROL_CODE_TS_BODY        :
            case FRAME_CONTROL_CODE_TS_TAIL        :
                if(ui->c_filterOredr->isChecked() == false)return;
            break;
            case FRAME_CONTROL_CODE_REP            :
                if(ui->c_filterRep->isChecked() == false)return;
            break;
            case FRAME_CONTROL_CODE_ACK            :
                if(ui->c_filterAck->isChecked() == false)return;
            break;
            case FRAME_CONTROL_CODE_EVT            :
                if(ui->c_filterEvt->isChecked() == false)return;
            break;
            case FRAME_CONTROL_CODE_UPLOAD         :
                if(ui->c_filterUpload->isChecked() == false)return;
            break;
            default :
                if(ui->c_filterOther->isChecked() == false)return;
            break;
        }
        // 3.过滤ID
        if(ui->c_filterSource->isChecked())
        {
            if(qby.at(0) != ui->spinBox_filterSource->value())return;
        }
        if(ui->c_filterObject->isChecked())
        {
            if(qby.at(1) != ui->spinBox_filterObject->value())return;
        }
        // 4.过滤类型
        if(ui->c_filterType->isChecked())
        {
            if(qby.at(5) != ui->spinBox_filterType->value())return;
        }
        // 5.过滤对象
        if(ui->c_filterNumber->isChecked())
        {
            if(qby.at(6) != ui->spinBox_filterNumber->value())return;
        }
        // 6.过滤内容
        if(ui->c_filterContent->isChecked())
        {
            if(qby.at(7) != ui->spinBox_filterContent->value())return;
        }
    }
    // 界面显示
    myShow->setTextStyle(str,QColor(255,255,255),col);
}
// 过滤器内容函数                          **************************************************** end
