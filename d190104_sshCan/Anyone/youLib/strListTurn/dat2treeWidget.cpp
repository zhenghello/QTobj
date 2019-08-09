
#include "strlist2dat.h"
#include "strlist2treewidget.h"

bool dat2treeWidget(QString datName,QTreeWidget *tree)
{
    QList<QStringList> listAll;
    bool bret;
    bret = dat2ListAll(datName,&listAll);
    if(bret == false)return false;
    bret = listAll2treeWidget(tree,&listAll);
    if(bret == false)return false;
    return true;
}

bool treeWidget2dat(QString datName,QTreeWidget *tree)
{
    QList<QStringList> listAll;
    bool bret;
    treeWidget2listAll(tree,&listAll);
    bret = ListAll2dat(datName,&listAll);
    if(bret == false)return false;
    return true;
}

