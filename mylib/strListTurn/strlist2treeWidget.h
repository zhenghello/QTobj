#ifndef STRLIST2TREEWIDGET_H
#define STRLIST2TREEWIDGET_H

#include <QString>
#include <QTreeWidget>

// ����ת��Ԫ��
bool listAll2treeWidget(QTreeWidget *tree,QList<QStringList> *listAll);
void treeWidget2listAll(QTreeWidget *tree,QList<QStringList> *listAll);

// ��������������
void delTreeItem(QTreeWidgetItem *itemP);                               // ��tree�ڵ�ɾ��
void setTreeItemIsEditable(QTreeWidget *tree);                          // ������ȫ��Ϊ�ɱ༭ģʽ
void setTreeItemIsEditable(QTreeWidgetItem *item);                      // �������ڵ�Ϊ�ɱ༭ģʽ
QTreeWidgetItem* treeFindKey(QTreeWidget *tree,int column,QString key); // �����в��ҹؼ���
QTreeWidgetItem* treeFindKey(QTreeWidget *tree, int column, QString key, int childCount);// �����в���ƥ���Ӳ��������Ĺؼ���
QTreeWidgetItem* findKeyTopTree(QTreeWidgetItem *tree, int column, QString key);    // ������item��Ķ������
QTreeWidgetItem* findKeyTopTree(QTreeWidget *tree, int column, QString key);        // ��������Ķ������

















#endif // STRLIST2TREEWIDGET_H
