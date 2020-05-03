#include "dat2tableWidget.h"
#include "strlist2dat.h"
#include "strlist2tableWidget.h"
#include <QDebug>
bool dat2tableWidget(QString datName,QTableWidget *table)
{
    qDebug() << "dat2tableWidget:" << datName;
    QList<QStringList> listAll;
    bool bret;
    bret = dat2ListAll(datName,&listAll);
    if(bret == false)return false;
    bret = listAll2tableWidget(table,&listAll);
    if(bret == false)return false;
    return true;
}

bool tableWidget2dat(QString datName,QTableWidget *table)
{
    qDebug() << "tableWidget2dat:" << datName;
    QList<QStringList> listAll;
    bool bret;
    tableWidget2listAll(table,&listAll);
    bret = ListAll2dat(datName,&listAll);
    if(bret == false)return false;
    return true;
}

