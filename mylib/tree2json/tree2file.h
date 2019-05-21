#ifndef TREE2FILE
#define TREE2FILE

#include <QTreeWidget>
#include <QHeaderView>

#include <QVariantMap>
#include <QJsonDocument>
#include <QFile>
 #include <QDebug>

void treeWidget2file(const QTreeWidget *tree,const QString fileName);   // 树的数据转为json文件
void file2treeWidget(QTreeWidget *tree,const QString fileName);         // 文件转为树的数据

void delTreeItem(QTreeWidgetItem *itemP);                               // 将tree节点删除
void setTreeItemIsEditable(QTreeWidget *tree);                          // 设置树全部为可编辑模式
void setTreeItemIsEditable(QTreeWidgetItem *item);                      // 设置树节点为可编辑模式
QTreeWidgetItem* treeFindKey(QTreeWidget *tree,int column,QString key); // 从树中查找关键词




#endif // TREE2FILE

