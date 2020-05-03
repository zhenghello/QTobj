#include "dat2excel.h"
#include "strlist2dat.h"
#include "strlist2excel.h"
#include <QDebug>

// excel2dat file
bool excel2dat(QString datName,QString excelName)
{
    QList<QStringList> listAll;
    bool bret;
    bret = excel2ListAll(excelName,&listAll);
    if(bret == false)return false;
    bret = ListAll2dat(datName,&listAll);
    if(bret == false)return false;
    return true;
}
// dat file 2 excel
bool dat2excel(QString datName,QString excelName)
{
    QList<QStringList> listAll;
    bool bret;
    bret = dat2ListAll(datName,&listAll);
    if(bret == false)return false;
    bret = ListAll2excel(excelName,&listAll);
    if(bret == false)return false;
    return true;
}



