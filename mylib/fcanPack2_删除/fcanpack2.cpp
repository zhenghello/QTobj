// 这个文件和 fcanpack  的区别在于，多了一位长度位的标识
#include "fcanpack2.h"
#include "ui_fcanpack2.h"

FcanPack2::FcanPack2(int num,int table_max_hight, QWidget *parent) :QWidget(parent),ui(new Ui::FcanPack2)
{
    ui->setupUi(this); 
    setWindowFlags(windowFlags()|Qt::Window);//设置为外框
    table_init(num);//num 是附带的参数长度,总长度为 num+5
    // 设最大高度
    ui->table_pack->setMaximumHeight(table_max_hight);
    setMaximumHeight(table_max_hight);
}
FcanPack2::~FcanPack2()
{
    delete ui;
}
// ******************************************** excel 操作 ******************************************** begin
// 初始化一个新的excel表
void FcanPack2::table_init(int argNum)
{
    int columnCount = 9 + argNum;
    int i;
    ui->table_pack->clear ();
    // 设置行列
    ui->table_pack->setRowCount(2);               // 行数
    ui->table_pack->setColumnCount(columnCount);  // 列数
    // 设置行高
    ui->table_pack->horizontalHeader()->hide();
    ui->table_pack->verticalHeader()->hide();
    ui->table_pack->horizontalHeader()->setDefaultSectionSize(22);  //设置默认列宽
    ui->table_pack->verticalHeader()->setDefaultSectionSize(20);    //设置默认行高
    ui->table_pack->setFont(QFont(QString::fromLocal8Bit("宋体"),8));
    //设置内容
    QTableWidgetItem *qtab;

    qtab = new QTableWidgetItem();
    qtab->setText(QString::asprintf("%02d",0));
    ui->table_pack->setItem(0,1,qtab);

    for(i=1;i<=argNum;i++)
    {
        qtab = new QTableWidgetItem();
        qtab->setText(QString::asprintf("%02d",i));
        ui->table_pack->setItem(0,i+6,qtab);
    }
    // 设置头尾不可编辑
    qtab = new QTableWidgetItem();
    qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//不可编辑
    qtab->setText("AA");
    ui->table_pack->setItem(0,0,qtab);
    qtab = new QTableWidgetItem();
    qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//不可编辑
    qtab->setText("55");
    ui->table_pack->setItem(0,columnCount-1,qtab);

    // 设置特殊颜色
    qtab = new QTableWidgetItem("00");
    qtab->setBackgroundColor(QColor(85, 127, 255));//颜色
    ui->table_pack->setItem(0,2,qtab);             // 长度
    qtab = new QTableWidgetItem("00");
    qtab->setBackgroundColor(QColor(85, 127, 255));//颜色
    ui->table_pack->setItem(0,3,qtab);
    qtab = new QTableWidgetItem("00");

    qtab = new QTableWidgetItem("00");
    qtab->setBackgroundColor(QColor(255, 85, 127));//颜色
    ui->table_pack->setItem(0,4,qtab);             // 控制
    qtab = new QTableWidgetItem("00");
    qtab->setBackgroundColor(QColor(255, 85, 127));//颜色
    ui->table_pack->setItem(0,5,qtab);
    qtab = new QTableWidgetItem("00");
    qtab->setBackgroundColor(QColor(255, 85, 127));//颜色
    ui->table_pack->setItem(0,6,qtab);
    qtab = new QTableWidgetItem("00");
    qtab->setBackgroundColor(QColor(85, 255, 127));//颜色
    ui->table_pack->setItem(0,argNum+7,qtab);      // 校验

    //合并第二行
    ui->table_pack->setSpan(1,0,1,ui->table_pack->columnCount());
    qtab = new QTableWidgetItem();
    qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//不可编辑
    qtab->setText(" ");
    qtab->setTextAlignment(Qt::AlignCenter);    //居中
    qtab->setBackgroundColor(QColor(85,255,255));//颜色
    ui->table_pack->setItem(1,0,qtab);
    //关联触发按键
    composeStr();//先合成一下
    QObject::connect(ui->table_pack,SIGNAL(pressed(QModelIndex)),this,SLOT(table_pressed(QModelIndex)));
    QObject::connect(ui->table_pack,SIGNAL(cellChanged(int,int)),this,SLOT(table_cellChanged(int,int)));
}
//鼠标按下,excel的动作
void FcanPack2::table_pressed(const QModelIndex &index)
{
    int cur_row     =index.row();    //当前行
    int cur_column  =index.column(); //当前列
    QTableWidgetItem *qtab;
    // 0.只有右击触发有用
    if( qApp->mouseButtons() != Qt::RightButton)return ;
    if(1!=cur_row || 0!=cur_column)return;//只有第二行才有用

    //发送前先合成
    composeStr();
    //获取单元格
    qtab=ui->table_pack->item(cur_row,cur_column);
    if ( qtab == NULL || (qtab->text() == "") )return; //空白退出
    QString str = qtab->text();

    //Fdebug::mydebug()->write_serial_signal(str,true,false);//发送串口数据
    emit send_can_pack(str);
}
// 合成字符串
void FcanPack2::composeStr(void)
{
    QObject::disconnect(ui->table_pack,SIGNAL(cellChanged(int,int)),this,SLOT(table_cellChanged(int,int)));
    int i;
    QTableWidgetItem *qtab;
    // 计算个数
    int count=0;
    for(i=4;i<ui->table_pack->columnCount()-2;i++)
    {
        qtab = ui->table_pack->item(0,i);
        if ( qtab == NULL || (qtab->text() == "") )continue;
        else count++;
    }
    qtab = ui->table_pack->takeItem(0,2);// 高位
    qtab->setText(QString("%1").arg(count/256,2,16,QChar('0')));
    ui->table_pack->setItem(0,2,qtab);
    qtab = ui->table_pack->takeItem(0,3);// 地位
    qtab->setText(QString("%1").arg(count%256,2,16,QChar('0')));
    ui->table_pack->setItem(0,3,qtab);
    // 计算校验和
    int sumcheck=0;
    for(i=1;i<ui->table_pack->columnCount()-2;i++)
    {
        qtab = ui->table_pack->item(0,i);
        if ( qtab == NULL || (qtab->text() == "") )continue;
        else sumcheck += qtab->text().toInt(nullptr,16);
    }
    qtab = ui->table_pack->takeItem(0,ui->table_pack->columnCount()-2);
    qtab->setText(QString("%1").arg(sumcheck%256,2,16,QChar('0')));
    ui->table_pack->setItem(0,ui->table_pack->columnCount()-2,qtab);
    // 合成字符串
    QString str;
    for(i=0;i<ui->table_pack->columnCount();i++)
    {
        qtab = ui->table_pack->item(0,i);
        if ( qtab == NULL || (qtab->text() == "") )continue;
        str += qtab->text() + " ";
    }
    qtab = ui->table_pack->takeItem(1,0);
    qtab->setText(str);
    ui->table_pack->setItem(1,0,qtab);
    QObject::connect(ui->table_pack,SIGNAL(cellChanged(int,int)),this,SLOT(table_cellChanged(int,int)));
}
// 单元格改变
void FcanPack2::table_cellChanged(int row, int column)
{
    if(row!=0)return;//只处理第一行
    //qDebug()<<column;
    composeStr();//重新合成
}
// 设置单元格参数
// 只设置命令和参数区
void FcanPack2::setCanPack(QStringList qsl)
{
    if(qsl.size()!=ui->table_pack->columnCount()-5)return;//个数不符，退出
    int i;
    QTableWidgetItem *qtab;
    for(i=0;i<qsl.size();i++)
    {
        qtab = ui->table_pack->takeItem(0,i+3);
        qtab->setText(qsl.at(i));
        ui->table_pack->setItem(0,i+3,qtab);
    }
}
// 发送单元格参数
void FcanPack2::sendCanPack(void)
{
    QTableWidgetItem *qtab;
    //获取单元格
    qtab=ui->table_pack->item(1,0);
    if ( qtab == NULL || (qtab->text() == "") )return; //空白退出
    QString str = qtab->text();

    //Fdebug::mydebug()->write_serial_signal(str,true,false);//发送串口数据
    emit send_can_pack(str);    // 往外部传输数据
}

// 获取单元格参数
// 有两种输出方式，一种是QString,一种是连续字符串，数值的长度应该是事先知道的。
// QVector 支持将数据的 char地址直接引用出来
void FcanPack2::getCanPack(QString *str, QVector<char>* qvr)
{
    QTableWidgetItem *qtab;
    //输出前先合成
    composeStr();

    if(qvr!=nullptr)
    {
        // 输出QList
        qvr->clear();
        for(int i=0;i<ui->table_pack->columnCount();i++)
        {
            qtab = ui->table_pack->item(0,i);
            if ( qtab == NULL || (qtab->text() == "") )continue;
            else qvr->append(qtab->text().toInt(nullptr,16));
        }
    }
    if(str!=nullptr)
    {
        // 输出Qstring
        qtab=ui->table_pack->item(1,0);// 获取单元格
        if ( qtab == NULL || (qtab->text() == "") )return; //空白退出
        *str = qtab->text();
    }
}
