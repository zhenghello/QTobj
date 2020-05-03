#include "excel2map.h.h"
#include <QAxObject> // QT       += axcontainer      # use excel function
#include <QFile>
#include <QDebug>
// 创建excel文件，如果原来存在，就会被询问
void creatExcel(QString excelName)
{
    excelName.replace("/","\\");                // 为了配合文件名
    QAxObject *excelApp         = NULL;         // 本例中，excelApp设定为excel文件的操作对象
    QAxObject *excelWorkBookS   = NULL;         // 用 QAxObject 的功能
    QAxObject *excelWorkBook    = NULL;        // 最后Excel操作对象
    excelApp = new QAxObject("Excel.Application");
    excelApp->dynamicCall("SetVisible(bool)", false); //true 表示操作文件时可见，false表示为不可见
    excelWorkBookS = excelApp->querySubObject("WorkBooks");
    excelWorkBookS->dynamicCall("Add");
    //———————————————— 按文件路径打开文件 ————————————————————
    excelWorkBook = excelApp->querySubObject("ActiveWorkBook");
    excelWorkBook->dynamicCall("SaveAs(const QString&, int,QString,QString,bool,bool,int,int)",excelName);
    // 获取打开的excel文件中所有的工作sheet
    //QAxObject *excelSheets = excelWorkBook->querySubObject("WorkSheets");
    // 一定要记得close，不然系统进程里会出现n个EXCEL.EXE进程
    excelWorkBook->dynamicCall("Close(Boolean)",false);
    excelApp->dynamicCall("Quit(void)");
    if (excelApp)
    {
        delete excelApp;
        excelApp = NULL;
    }
}
// 将excel文件转为list,数据会保存到 listAll中
bool excel2ListAll(QString excelName,QList<QStringList> *listAll)
{
    excelName.replace("/","\\");                // 为了配合文件名
    // 1.判断excel文件存在，没有excel就直接退出
    if(!QFile::exists(excelName))return false ;
    // 2.读取excel
    QStringList strlist;
    QAxObject *excelApp         = NULL;         // 本例中，excelApp设定为excel文件的操作对象
    QAxObject *excelWorkBookS   = NULL;         // 用 QAxObject 的功能
    QAxObject *excelWorkBook    = NULL;         // 最后Excel操作对象
    excelApp = new QAxObject("Excel.Application");
    excelApp->dynamicCall("SetVisible(bool)", false);                           // true 表示操作文件时可见，false表示为不可见
    excelWorkBookS = excelApp->querySubObject("WorkBooks");                     // 操作对象
    excelWorkBook = excelWorkBookS->querySubObject("Open(QString&)", excelName);    // 按文件路径打开文件
    QAxObject *excelSheets = excelWorkBook->querySubObject("WorkSheets");    // 获取打开的excel文件中所有的工作sheet
 //    int excelSheetSize = excelSheets->property("Count").toInt();     // Excel文件中表的个数
    //if(excelSheetSize<1);
    QAxObject *excelSheet = excelSheets->querySubObject("Item(int)",1);// 获取第1个工作表
    QAxObject * usedRange = excelSheet->querySubObject("UsedRange");   //  获取该sheet的数据范围（可以理解为有数据的矩形区域）
    QAxObject * rowObj = usedRange->querySubObject("Rows");            // 获取行数
    int rowNum = rowObj->property("Count").toInt();
    QAxObject * columnObj = usedRange->querySubObject("Columns");      // 获取列数
    int columnNum = columnObj->property("Count").toInt();
    // 3.——————————————————— 读取全部数据 ———————————————————
    listAll->clear();
    for(int row=0; row<rowNum;row++ )
    {
        strlist.clear();
        for(int column=0; column<columnNum;column++ )
        {   // 获取行列的位置
            QAxObject *cell = excelSheet->querySubObject("Cells(int,int)",row+1,column+1);
            strlist.append(cell->property("Value").toString()); // 读取数据, 第row行，第column列
        }
        listAll->append(strlist);
    }
    // 一定要记得close，不然系统进程里会出现n个EXCEL.EXE进程
    excelWorkBook->dynamicCall("Close()");
    excelApp->dynamicCall("Quit()");
    if (excelApp)
    {
        delete excelApp;
        excelApp = NULL;
    }
    // 到这里，就获得了excel的所有数据，在listAll中-------------------------------------
    return true;
}
// 将ListAll转为 excel ,数据会保存到 excel中
bool ListAll2excel(QString excelName,QList<QStringList> *listAll)
{
    // 到这里，所有数据都在listAll中了-------------------------------------
    // 3.判断excel文件存在，没有excel就创建
    if(!QFile::exists(excelName))
    {
        creatExcel( excelName);
    }
    // 4.数据保存
    QAxObject *excelApp         = NULL;         // 本例中，excelApp设定为excel文件的操作对象
    QAxObject *excelWorkBookS   = NULL;         // 用 QAxObject 的功能
    QAxObject *excelWorkBook    = NULL;         // 最后Excel操作对象
    excelApp = new QAxObject("Excel.Application");
    excelApp->dynamicCall("SetVisible(bool)", false); //true 表示操作文件时可见， false 表示为不可见
    excelWorkBookS = excelApp->querySubObject("WorkBooks");

    excelWorkBook = excelWorkBookS->querySubObject("Open(QString&)", excelName);// 按文件路径打开文件
    // 获取打开的excel文件中所有的工作sheet
    QAxObject *excelSheets = excelWorkBook->querySubObject("WorkSheets");

 //   int excelSheetSize = excelSheets->property("Count").toInt();// Excel文件中表的个数:
    QAxObject *excelSheet = excelSheets->querySubObject("Item(int)", 1);// 获取第1个工作表
    QAxObject *usedRange  = excelSheet->querySubObject("UsedRange");
    usedRange->dynamicCall("ClearContents()");
    // ————————————— 写入数据 —————————————
    for(int row=0; row<listAll->size();row++ )
    {
        for(int column=0; column<listAll->at(row).size();column++ )
        {
            QAxObject *cell = excelSheet->querySubObject("Cells(int,int)",row+1,column+1);// 获取行列的位置
            cell->setProperty("Value", listAll->at(row).at(column));        // 写入数据, 第row行，第column列
        }
    }
    // 一定要记得close，不然系统进程里会出现n个EXCEL.EXE进程
    excelWorkBook->dynamicCall("Save()");   // 如果excel被打开，就会询问
    excelWorkBook->dynamicCall("Close()");
    excelApp->dynamicCall("Quit()");
    if (excelApp)
    {
        delete excelApp;
        excelApp = NULL;
    }
    return true;
}


