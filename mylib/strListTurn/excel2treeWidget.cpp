#include "excel2treeWidget.h"

// �� QTreeWidget תΪ excel
bool treeWidget2excel(QString excelName,QTreeWidget *tree)
{
    QList<QStringList> listAll;
    bool bret;
    treeWidget2listAll(tree,&listAll);
    bret = ListAll2excel(excelName,&listAll);
    if(bret == false)return false;
    return true;
}
// �� excel תΪ QTreeWidget 
bool excel2treeWidget(QString excelName,QTreeWidget *tree)
{
	QList<QStringList> listAll;
    bool bret;
    bret = excel2ListAll(excelName,&listAll);
    if(bret == false)return false;
    bret = listAll2treeWidget(tree,&listAll);
    if(bret == false)return false;
    return true;	
	
}
