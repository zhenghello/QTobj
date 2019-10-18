/*
    这个界面用于生成一个CAN包数据
    这个can包数据可以自动合成。
    可以外部设置参数
*/
#include "canpack.h"

#define CELL_HEIGHT 20 //单元格高度
#define CELL_WIDTH  25 //单元格宽度

canPack::canPack(QWidget *parent, int argNum):QTableWidget(parent)
{
    // 列表初始化
    setParent(parent);
    table_init(argNum);
}
#include"QDebug"
// table框初始化
void canPack::table_init(int argNum)
{
    int columnNum = 10 + argNum; // 列数 can头+头尾标识符+校验位+3个固定命令码
    int i;
    // 设置全部的高度和宽度
    setMaximumHeight(CELL_HEIGHT * 3+2);
    setMaximumWidth(CELL_WIDTH*(argNum+10+2)+2);

    clear ();
    //设置行列
    setRowCount(2);               // 行数
    setColumnCount(columnNum);    // 列数
    //设置行表头和列表头隐藏
    horizontalHeader()->hide();
    verticalHeader()->hide();
    horizontalHeader()->setDefaultSectionSize(CELL_WIDTH);   //设置默认列宽
    verticalHeader()->setDefaultSectionSize(CELL_HEIGHT);    //设置默认行高
    //设置内容->创建一堆单元格
    QTableWidgetItem *qtab;
    for(i=0;i<8;i++)
    {
        //  重入出错
        qtab = new QTableWidgetItem();
        qtab->setText("00");
        setItem(0,i,qtab);
    }
    for(;i<columnNum;i++)
    {
        //  重入出错
        qtab = new QTableWidgetItem();
        qtab->setText("");
        setItem(0,i,qtab);
    }
    // 设置头两个ID选项默认为空
    qtab = item(0,0);
    qtab->setBackgroundColor(QColor(255, 50, 255));//颜色
    qtab->setText("");
    qtab = item(0,1);
    qtab->setBackgroundColor(QColor(255, 50, 255));//颜色
    qtab->setText("");
    // 设置前两列宽点
    setColumnWidth(0,CELL_WIDTH*2);
    setColumnWidth(1,CELL_WIDTH*2);

    // 设置头尾和长度不可编辑
    qtab = item(0,2);
    qtab->setBackgroundColor(QColor(200, 200, 100));//颜色
    qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//不可编辑
    qtab->setText("aa");

    qtab = item(0,columnNum-1);
    qtab->setBackgroundColor(QColor(200, 200, 100));//颜色
    qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//不可编辑
    qtab->setText("55");

    qtab = item(0,columnNum-2);// 校验
    qtab->setBackgroundColor(QColor(100, 200, 200));//颜色
    qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//不可编辑

    qtab = item(0,4);   // 长度
    qtab->setBackgroundColor(QColor(200, 200, 200));//颜色
    //qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//不可编辑
    qtab->setText(QString::number(argNum+3));
    //setItem(0,2,qtab);

    // 设置特殊颜色
    qtab = item(0,5);
    qtab->setBackgroundColor(QColor(255, 85, 127));//颜色
    qtab = item(0,6);
    qtab->setBackgroundColor(QColor(255, 85, 127));//颜色
    qtab = item(0,7);
    qtab->setBackgroundColor(QColor(255, 85, 127));//颜色

    //合并第二行
    setSpan(1,0,1,columnCount());
    qtab = new QTableWidgetItem();
    qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//不可编辑
    qtab->setText(" ");
    qtab->setTextAlignment(Qt::AlignCenter);    //居中
    qtab->setBackgroundColor(QColor(85,255,255));//颜色
    setItem(1,0,qtab);
    //关联触发按键
    QObject::connect(this,SIGNAL(pressed(QModelIndex)),this,SLOT(table_pressed(QModelIndex)));
    QObject::connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(table_cellChanged(int,int)));
    composeStr(); //合成
}
#include <QtWidgets/QApplication>
//鼠标按下,excel的动作，会把合成后的数据发送信号出来
void canPack::table_pressed(const QModelIndex &index)
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
    qtab=item(cur_row,cur_column);
    if ( qtab == NULL || (qtab->text() == "") )return; //空白退出
    QString str = qtab->text();

    emit send_can_pack( str);//发送数据
}
// 合成字符串，根据第一行，计算参数长度，合成第二行数据，空白格会被忽略，
void canPack::composeStr(void)
{
    QObject::disconnect(this,SIGNAL(cellChanged(int,int)),this,SLOT(table_cellChanged(int,int)));
    int i;
    QTableWidgetItem *qtab;
    // 计算个数
    int count=0;
    for(i=3+2;i<columnCount()-2;i++)
    {
        qtab = item(0,i);
        if ( qtab == NULL || (qtab->text().trimmed() == "") )continue;
        else count++;
    }
    qtab = item(0,2+2);
    qtab->setText(QString("%1").arg(count,2,16,QChar('0')));
    // 计算校验和
    int sumcheck=0;
    for(i=1+2;i<columnCount()-2;i++)
    {
        qtab = item(0,i);
        if ( qtab == NULL || (qtab->text() == "") )continue;
        else sumcheck += qtab->text().toInt(nullptr,16);
    }
    qtab = item(0,columnCount()-2);
    qtab->setText(QString("%1").arg(sumcheck%256,2,16,QChar('0')));
    // 合成字符串
    QString str;
    for(i=0;i<columnCount();i++)
    {
        qtab = item(0,i);
        if ( qtab == NULL || (qtab->text() == "") )continue;
        str += qtab->text() + " ";
    }
    qtab = item(1,0);
    qtab->setText(str);
    QObject::connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(table_cellChanged(int,int)));
}
// 单元格改变，内部关联，自动合成数据
void canPack::table_cellChanged(int row, int column)
{
    if(column){;}
    if(row!=0)return;//只处理第一行
    //qDebug()<<column;
    composeStr();//重新合成
}
// 外部函数 ---------------------------------------------------------------------------------------
// 设置单元格参数-只设置命令和参数区，输入参数不足就会补空
void canPack::setCanPack_OrderArg(QStringList qsl)
{
    int i;
    QTableWidgetItem *qtab;
    // 如果个数不够就补空白，如果太过就会被截断
    for(i=0;i<columnCount()-7;i++)
    {
        qtab = item(0,i+3+2);
        if(qsl.size()<=i)//超出范围补空白
        {
           qtab->setText("");
        }
        else
        {
            qtab->setText(qsl.at(i));
        }
    }
}
// 设置单元格参数-只设置控制码
void canPack::setCanPack_ctlCode(QString str)
{
    QTableWidgetItem *qtab;
    qtab = item(0,1+2);
    qtab->setText(str);
}
// 设置单元格参数-只设置发送收发ID
void canPack::setCanPack_IdCode(QString str1,QString str2)
{
    QTableWidgetItem *qtab;
    qtab = item(0,0);
    qtab->setText(str1);
    qtab = item(0,1);
    qtab->setText(str2);
}
// 发送单元格参数
void canPack::sendCanPack(void)
{
    QTableWidgetItem *qtab;
    //获取单元格
    qtab=item(1,0);
    if ( qtab == NULL || (qtab->text() == "") )return; //空白退出
    QString str = qtab->text();
    emit send_can_pack(str);//发送数据
}


