/*
    文档声明：郑凯鹏
    这个文档的主要功能是将 QTableWidget 和 QList<QStringList> 数据互相转换
    QTableWidget 转 QList<QStringList>的协议：
    1.QStringList 的第一行数据代表他的头声明
    2.QStringList 的第一个数据为0则忽略导入，可以在外部文件中用来做注释，不过导出后就没有了
    3.QStringList 的第一个数据数据为之能比上次的大1，超过按1处理
    4.dat中的第一列数据没用

    4.前10行用于参数导入，不作为树的内容
    4.1.第1行保存列个数，最小为3
    4.2.第2行保存每列的宽度，最小为20
    4.3.第3行保存每行的表头名
*/
#include "strlist2tableWidget.h"
#include <QHeaderView>

#include <QDebug>
// 将 表 转为 listAll
void tableWidget2listAll(QTableWidget *table,QList<QStringList> *listAll)
{
    QStringList strlist;

    // 1.对表的基本参数保存
    // 1.1.保存列个数
    listAll->clear();
    strlist.clear();
    strlist.append("columnCount");
    strlist.append(QString::number(table->columnCount()));
    listAll->append(strlist);

    // 1.2.保存列宽度
    strlist.clear();
    strlist.append("columnWidth");
    for(int index = 0;index < table->columnCount();index++)
        strlist.append(QString::number(table->columnWidth(index)));
    listAll->append(strlist);
    // 1.3.保存表头名字
    strlist.clear();
    strlist.append("horizontalHeaderItem");
    for(int index=0;index<table->columnCount();index++)
    {
        QTableWidgetItem *item = table->horizontalHeaderItem(index);
        if((item == NULL)||(item->text() == NULL))
            strlist.append(" ");
        else
            strlist.append(item->text());
    }
    listAll->append(strlist);
    // 1.4.预留
    strlist.clear();
    strlist<<"test";
    listAll->append(strlist);
    // 1.5.预留
    strlist.clear();
    strlist<<"test";
    listAll->append(strlist);
    // 1.6.预留
    strlist.clear();
    strlist<<"test";
    listAll->append(strlist);
    // 1.7.预留
    strlist.clear();
    strlist<<"test";
    listAll->append(strlist);
    // 1.8.预留
    strlist.clear();
    strlist<<"test";
    listAll->append(strlist);
    // 1.9.预留
    strlist.clear();
    strlist<<"test";
    listAll->append(strlist);
    // 1.10.预留
    strlist.clear();
    strlist<<"test";
    listAll->append(strlist);
    // 2.将表格的横向数据 读取到 listAll 中
    if (table->rowCount() == 0)table->insertRow(0);// 2.3.一行都没有就空一行
    for(int row = 0;row < table->rowCount();row++)
    {
        strlist.clear();
        strlist.append("1");                                // 兼容协议，第一个数据固定为1
        for(int column = 0;column < table->columnCount();column++)
        {
            QTableWidgetItem *item = table->item(row,column);

            if((item == NULL)||(item->text() == NULL))
                strlist.append(" ");
            else
                strlist.append(item->text().replace('\n', "\\n"));  // 替换为可识别文字
        }
        listAll->append(strlist);
    }
}
// 将 listAll 转为表
bool listAll2tableWidget(QTableWidget *table,QList<QStringList> *listAll)
{
    QStringList strlist;
    QString str;
    int columnCount;
    // 1.0.清空
    table->clear();
    // 1.1.设置全表格的默认字体 
    table->setFont(QFont("SimSun",9)); //  SimSun 是宋体
    // 1.2.表头属性默认设置
    table->horizontalHeader()->setStyleSheet("QHeaderView::section{background: rgb(200, 200, 200) }");	// 设置标题颜色
    table->horizontalHeader()->setFixedHeight(25);// 设置行表头固定高度
    table->verticalHeader()->setStyleSheet("QHeaderView::section{background: rgb(200, 200, 200) }");	// 设置标题颜色
    table->verticalHeader()->setFixedWidth(35); // 设置列表头固定宽度
    // 1.3.判断输入出错
    if(listAll->size()<10)
        return false;
    // 2.1.设置列个数->最少有3个
    strlist.clear();
    strlist.append(listAll->takeFirst());                       // 取走
    if(strlist.takeFirst() != "columnCount")
    {
        // 没有关键字
        qDebug()<<QString("no key") + QString::fromLocal8Bit(__FILE__)+QString("\r\n")+QString::number(__LINE__)+QString("\r\n")+QString::fromLocal8Bit(__FUNCTION__);
        return false;
    }
    str = strlist.first();
    columnCount = str.toInt();
    if(columnCount<3)columnCount=3;
    table->setColumnCount(columnCount);
    // 2.2.拉伸属性和列宽
    strlist.clear();
    strlist.append(listAll->takeFirst());                // 取走
    if(strlist.takeFirst()!="columnWidth")
    {// 没有关键字
        qDebug()<<QString("no key") + QString::fromLocal8Bit(__FILE__)+QString("\r\n")+QString::number(__LINE__)+QString("\r\n")+QString::fromLocal8Bit(__FUNCTION__);
        return false;
    }

    for(int column = 0;column < strlist.size();column++)
    {
        if(column>=table->columnCount()){ break;}// 列数据没有实际的多，跳出
        int width=strlist.at(column).toInt();
        if(width<20)width=20;
        table->setColumnWidth(column,width);
        table->horizontalHeader()->setSectionResizeMode(column,QHeaderView::Interactive);
    }
    // 2.3.一行都没有就空一行
    if (table->rowCount() == 0)table->insertRow(0);
    // 2.3.设置头标题
    strlist.clear();
    strlist.append(listAll->takeFirst());        // 取走
    if(strlist.takeFirst()!="horizontalHeaderItem")
    {
        qDebug()<<QString("no key") + QString::fromLocal8Bit(__FILE__)+QString("\r\n")+QString::number(__LINE__)+QString("\r\n")+QString::fromLocal8Bit(__FUNCTION__);
        // 没有关键字
        return false;
    }
    table->setHorizontalHeaderLabels(strlist);

    // 2.4.预留
    strlist.append(listAll->takeFirst());        // 取走
    // 2.5.预留
    strlist.append(listAll->takeFirst());        // 取走
    // 2.6.预留
    strlist.append(listAll->takeFirst());        // 取走
    // 2.7.预留
    strlist.append(listAll->takeFirst());        // 取走
    // 2.8.预留
    strlist.append(listAll->takeFirst());        // 取走
    // 2.9.预留
    strlist.append(listAll->takeFirst());        // 取走
    // 2.10.预留
    strlist.append(listAll->takeFirst());        // 取走

    // 3.将文件内容转换成table
    QTableWidgetItem *item;
    qDebug()<< "listAll->size() = " << listAll->size();
    table->setRowCount(listAll->size());        // 设置列个数
    for(int row=0;row<listAll->size();row++)
    {
        strlist.clear();
        strlist.append(listAll->at(row));
        strlist.removeFirst();                      // 根据协议，第一个数据无效
        for(int column=0;column<strlist.size();column++)
        {
            if(column>=table->columnCount()){break;}
            str = strlist.at(column);
            str = str.replace(QString("\\n"), QString("\n"));
            item = new QTableWidgetItem(str);// 反替换
            table->setItem(row,column,item);
            /*根据内容调整行高度*/
            int h = (str.length() - str.remove('\n').length() + 1) * 16;  // 15 和字符格式有关的，用的是字符：宋体9pt
            table->setRowHeight(row, qMax(h, table->rowHeight(row)));
        }
    }
    return true;
}





