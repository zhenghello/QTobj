#include "excel2tableWidget.h"
#include "strlist2tableWidget.h"
#include "strlist2excel.h"

//  QTableWidget 2 excel file
bool tableWidget2excel(QString excelName,QTableWidget *table)
{
    QList<QStringList> listAll;
    bool bret;
    tableWidget2listAll(table,&listAll);
    bret = ListAll2excel(excelName,&listAll);
    if(bret == false)return false;
    return true;
}
// excel file 2 QtableWidget
bool excel2tableWidget(QString excelName, QTableWidget *table)
{
	QList<QStringList> listAll;
    bool bret;
    bret = excel2ListAll(excelName,&listAll);
    if(bret == false)return false;
    bret = listAll2tableWidget(table,&listAll);
    if(bret == false)return false;
    return true;	
}
