#ifndef STRLIST2TREEWIDGET_H
#define STRLIST2TREEWIDGET_H

#include <QString>
#include <QTreeWidget>

// 基本转换元素
bool listAll2treeWidget(QTreeWidget *tree,QList<QStringList> *listAll);
void treeWidget2listAll(QTreeWidget *tree,QList<QStringList> *listAll);

// 对树的其他操作
void delTreeItem(QTreeWidgetItem *itemP);                               // 将tree节点删除
void setTreeItemIsEditable(QTreeWidget *tree);                          // 设置树全部为可编辑模式
void setTreeItemIsEditable(QTreeWidgetItem *item);                      // 设置树节点为可编辑模式
QTreeWidgetItem* treeFindKey(QTreeWidget *tree,int column,QString key); // 从树中查找关键词
QTreeWidgetItem* treeFindKey(QTreeWidget *tree, int column, QString key, int childCount);// 从树中查找匹配子参数个数的关键词
QTreeWidgetItem* findKeyTopTree(QTreeWidgetItem *tree, int column, QString key);    // 查找树item类的顶层对象
QTreeWidgetItem* findKeyTopTree(QTreeWidget *tree, int column, QString key);        // 查找树类的顶层对象

















#endif // STRLIST2TREEWIDGET_H
