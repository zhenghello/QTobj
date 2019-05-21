#ifndef EXCEL2TREEWIDGET_H
#define EXCEL2TREEWIDGET_H

#include "strlist2treeWidget.h"
#include "strlist2excel.h"

// 复合转换元素 
bool treeWidget2excel(QString excelName,QTreeWidget *tree);
bool excel2treeWidget(QString excelName,QTreeWidget *tree);  // excel转tree
//

#endif // EXCEL2TREEWIDGET_H
