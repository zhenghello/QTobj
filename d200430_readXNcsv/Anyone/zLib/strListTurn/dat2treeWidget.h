#ifndef DAT2TREEWIDGET_H
#define DAT2TREEWIDGET_H

#include <QString>
#include <QTreeWidget>

// 复合转换元素
bool dat2treeWidget(QString datName,QTreeWidget *tree);
bool treeWidget2dat(QString datName,QTreeWidget *tree);  // tree转dat

#endif // DAT2TREEWIDGET_H
