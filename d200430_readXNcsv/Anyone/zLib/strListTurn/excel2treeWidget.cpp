#include "excel2treeWidget.h"

// 将 QTreeWidget 转为 excel
bool treeWidget2excel(QString excelName,QTreeWidget *tree)
{
    QList<QStringList> listAll;
    bool bret;
    treeWidget2listAll(tree,&listAll);
    bret = ListAll2excel(excelName,&listAll);
    if(bret == false)return false;
    return true;
}
// 将 excel 转为 QTreeWidget 
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
