#ifndef STRLIST2TABLEWIDGET_H
#define STRLIST2TABLEWIDGET_H

#include <QString>
#include <QTableWidget>

// ����ת��Ԫ��
bool listAll2tableWidget(QTableWidget *table,QList<QStringList> *listAll);
void tableWidget2listAll(QTableWidget *table,QList<QStringList> *listAll);

// ��table����������
//void delTreeItem(QTreeWidgetItem *itemP);                               // ��tree�ڵ�ɾ��
//void setTreeItemIsEditable(QTreeWidget *tree);                          // ������ȫ��Ϊ�ɱ༭ģʽ
//void setTreeItemIsEditable(QTreeWidgetItem *item);                      // �������ڵ�Ϊ�ɱ༭ģʽ
//QTreeWidgetItem* treeFindKey(QTreeWidget *tree,int column,QString key); // �����в��ҹؼ���
//QTreeWidgetItem* treeFindKey(QTreeWidget *tree, int column, QString key, int childCount);// �����в���ƥ���Ӳ��������Ĺؼ���
















#endif // STRLIST2TABLEWIDGET_H
