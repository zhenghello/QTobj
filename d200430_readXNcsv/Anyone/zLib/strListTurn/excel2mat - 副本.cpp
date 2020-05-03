#include "Excel2Mat.h"

Excel2Mat::Excel2Mat()
{
    excelName = "";
    mat.clear();
}
bool Excel2Mat::load(QString eName)
{
    bool ret = xls2mat(eName, &mat);
    if (ret)
    {
        excelName = eName;
        qDebug()<<"D:file load success:"<<eName;
    }
    else
        qDebug()<<"D:file load fail:"<<eName;
    return ret;
}
// 行数
int Excel2Mat::rowSize()
{
    return mat.size();
}
// 列数
int Excel2Mat::colunmSize()
{
    return mat.at(1).size();
}
// 获取数据 r=行，c=列
QString Excel2Mat::d(int r,int c)
{
    return mat.at(r).at(c);
}
// 在对应的行，查找对象所在的列
bool Excel2Mat::columnFind(QString str,int r,int& c)
{
    // 无数据
    if (mat.size()<r)return false;
    //
    if (mat.at(r).contains(str)==false)return false;
    c = mat.at(r).indexOf(str);
    return true;
}
// 与平台无关的，excel文件读取放在矩阵中
bool xls2mat(QString excelName, QVector<QVector<QString>> *listAll)
{
    excelName.replace("/","\\");                // 为了配合文件名
    // 1.判断excel文件存在，没有excel就直接退出
    if(!QFile::exists(excelName))return false ;
    // 2.读取excel
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
    for(int row=0; row<rowNum;row++ ) // 行
    {
        QVector<QString> strlist;
        for(int column=0; column<columnNum;column++ ) // 列
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
    // 到这里，就获得了excel的所有数据，在 listAll 中-------------------------------------
    return true;
}
