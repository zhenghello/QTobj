#ifndef STRLIST2TABLEWIDGET_H
#define STRLIST2TABLEWIDGET_H

#include <QString>
#include <QTableWidget>

// 基本转换元素
bool listAll2tableWidget(QTableWidget *table,QList<QStringList> *listAll);
void tableWidget2listAll(QTableWidget *table,QList<QStringList> *listAll);

// 对table的其他操作
//void delTreeItem(QTreeWidgetItem *itemP);                               // 将tree节点删除
//void setTreeItemIsEditable(QTreeWidget *tree);                          // 设置树全部为可编辑模式
//void setTreeItemIsEditable(QTreeWidgetItem *item);                      // 设置树节点为可编辑模式
//QTreeWidgetItem* treeFindKey(QTreeWidget *tree,int column,QString key); // 从树中查找关键词
//QTreeWidgetItem* treeFindKey(QTreeWidget *tree, int column, QString key, int childCount);// 从树中查找匹配子参数个数的关键词
















#endif // STRLIST2TABLEWIDGET_H
