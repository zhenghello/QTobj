/*
    �ĵ�������֣����
    ����ĵ�����Ҫ�����ǽ�QTreeWidget �� QList<QStringList> ���ݻ���ת��
    �������ĵݹ飬��������QList<QStringList> �ĵ�һ����Ϊ�Ӳ����������Խ�ߣ�����Խ��
    QTreeWidget ת QList<QStringList>��Э�飺
    1.QStringList �ĵ�һ�����ݴ����������еĲ㼶������Ϊ1��
    2.QStringList �ĵ�һ������Ϊ0����Ե��룬�������ⲿ�ļ���������ע�ͣ������������û����
    3.QStringList �ĵ�һ����������Ϊ֮�ܱ��ϴεĴ�1��������1����

    4.ǰ10�����ڲ������룬����Ϊ��������
    5.��1�б����и�������СΪ3
    6.��2�б���ÿ�еĿ�ȣ���СΪ20
    7.��3�б���ÿ�еı�ͷ��
*/
#include "strlist2treewidget.h"
#include <QHeaderView>
QList<QStringList> treeItem2listAll(const QTreeWidgetItem *itemP, const int level);
// �ڲ�����
// �ݹ��㷨->�� QTreeWidgetItem ת�� QList<QStringList> ����
// �涨��һ�����ݴ����ӹ�ϵ��
// ����Խ�͵ȼ�Խ��
QList<QStringList> treeItem2listAll(const QTreeWidgetItem *itemP,const int level)
{
    QList<QStringList> listAll;
    // ����������
    QStringList strList;
    strList.append(QString("%1").arg(level,3,10,QChar('0')));    // ����ȼ�����
    for(int i=0;i<itemP->columnCount();i++)
    {
        if((itemP->text(i)=="")||(itemP->text(i)==NULL))
            strList.append(" ");
        else
            strList.append(itemP->text(i));
    }
    listAll.append(strList);
    // �����Ӷ���
    for(int index=0;index<itemP->childCount();index++)
    {
        QList<QStringList> listFun = treeItem2listAll(itemP->child(index),level+1);
        for(int i=0;i<listFun.size();i++)
            listAll.append(listFun.at(i));
    }
    return listAll;
}
// �� QTreeWidget ����תΪ QList<QStringList> ����ͷ�������Զ���� QTreeWidget ���Ե����ݣ������ļ���Ҫƥ��ʹ�ò���
void treeWidget2listAll(QTreeWidget *tree,QList<QStringList> *listAll)
{
    QStringList strlist;
    // 1.�����Ļ�����������
    // 1.1.�����и���
    listAll->clear();
    strlist.clear();
    strlist.append("columnCount");
    strlist.append(QString::number(tree->columnCount()));
    listAll->append(strlist);
    // 1.2.�����п��
    strlist.clear();
    strlist.append("columnWidth");
    for(int index = 0;index < tree->columnCount();index++)
        strlist.append(QString::number(tree->columnWidth(index)));
    listAll->append(strlist);
    // 1.3.�����ͷ����
    strlist.clear();
    strlist.append("headerItemText");
    for(int index = 0;index < tree->columnCount();index++)
        strlist.append(tree->headerItem()->text(index));
    listAll->append(strlist);
    // 1.4.Ԥ��
    strlist.clear();
    strlist<<"0"<<"test";
    listAll->append(strlist);
    // 1.5.Ԥ��
    strlist.clear();
    strlist<<"0"<<"test";
    listAll->append(strlist);
    // 1.6.Ԥ��
    strlist.clear();
    strlist<<"0"<<"test";
    listAll->append(strlist);
    // 1.7.Ԥ��
    strlist.clear();
    strlist<<"0"<<"test";
    listAll->append(strlist);
    // 1.8.Ԥ��
    strlist.clear();
    strlist<<"0"<<"test";
    listAll->append(strlist);
    // 1.9.Ԥ��
    strlist.clear();
    strlist<<"0"<<"test";
    listAll->append(strlist);
    // 1.10.Ԥ��
    strlist.clear();
    strlist<<"0"<<"test";
    listAll->append(strlist);

    // 2.�����ĺ������� �ݹ��ȡ�� listAll ��
    for(int index = 0;index < tree->topLevelItemCount();index++)
    {
        QList<QStringList> listFun = treeItem2listAll(tree->topLevelItem(index),1);
        for(int i=0;i<listFun.size();i++)
            listAll->append(listFun.at(i));
    }
}
// �� QList<QStringList> ����תΪ QTreeWidget
bool listAll2treeWidget(QTreeWidget *tree,QList<QStringList> *listAll)
{
    QStringList strlist;
    QString str;
    int columnCount;
    // 2.0.���
    tree->clear();
    // 2.1.�����и���->������3�� listAll
    strlist.clear();
    strlist.append(listAll->takeFirst());               // ȡ��
    if(strlist.takeFirst() != "columnCount"){return false;}   // û�йؼ���
    str = strlist.first();
    columnCount = str.toInt();
    if(columnCount<3)columnCount=3;
    tree->setColumnCount(columnCount);
    // 2.2.�������� ->���������������
    tree->header()->setSectionResizeMode(tree->columnCount()-2,QHeaderView::Fixed);
    tree->header()->setSectionResizeMode(tree->columnCount()-1,QHeaderView::Fixed);
    tree->header()->setStretchLastSection(false);   // ���һ�е���������
    // 2.2.�����п��->��������̶�Ϊ20
    strlist.clear();
    strlist.append(listAll->takeFirst());        // ȡ��
    if(strlist.takeFirst()!="columnWidth"){return false;} // û�йؼ���

    for(int index = 0;index < strlist.size();index++)
    {
        tree->setColumnWidth(index,strlist.at(index).toInt());
    }
    tree->setColumnWidth(tree->columnCount()-2,20);
    tree->setColumnWidth(tree->columnCount()-1,20);
    // 2.3.����ͷ����
    strlist.clear();
    strlist.append(listAll->takeFirst());        // ȡ��
    if(strlist.takeFirst()!="headerItemText"){return false;} // û�йؼ���
    tree->setHeaderLabels(strlist);
    // 2.4.Ԥ��
    strlist.append(listAll->takeFirst());        // ȡ��
    // 2.5.Ԥ��
    strlist.append(listAll->takeFirst());        // ȡ��
    // 2.6.Ԥ��
    strlist.append(listAll->takeFirst());        // ȡ��
    // 2.7.Ԥ��
    strlist.append(listAll->takeFirst());        // ȡ��
    // 2.8.Ԥ��
    strlist.append(listAll->takeFirst());        // ȡ��
    // 2.9.Ԥ��
    strlist.append(listAll->takeFirst());        // ȡ��
    // 2.10.Ԥ��
    strlist.append(listAll->takeFirst());        // ȡ��

    // 3.���ļ�����ת����tree
    QTreeWidgetItem *lastItem = 0;
    int lastCount = 0;
    int index;
    while(!listAll->isEmpty())
    {
        strlist.clear();
        strlist.append(listAll->takeFirst());        // ȡ��
        index = strlist.takeFirst().toInt();        // ��ȡ���εݹ�ƫ��ֵ
        QTreeWidgetItem *treeItemChild = new QTreeWidgetItem(strlist);// ��������
        if(index > (lastCount+1))lastCount=index+1; // ������������ǿ�Ƽ�С
        // 0 ������ 1 �Ƕ��㣬���������Ӷ���
        if(index == 0)
        {
            continue;
        }
        if(index == 1)
        {
            tree->addTopLevelItem(treeItemChild);
        }
        else
        {   // ���˼��㸸����
            for(int i=index;i<=lastCount;i++)
            {
                lastItem=lastItem->parent();
            }
            lastItem->addChild(treeItemChild);
        }
        lastItem = treeItemChild;
        lastCount = index;
    }
    // 4.�����ݣ������һ��
    if(tree->topLevelItemCount() == 0)
    {
        QTreeWidgetItem *treeItemChild = new QTreeWidgetItem();// ��������
        treeItemChild->setText(0,"empty");
        tree->addTopLevelItem(treeItemChild);
    }
    // 5.ǿ��ȥ���������
    tree->setColumnCount(columnCount);
    return true;
}

// �����ĵ�Ԫ��ȫ������Ϊ�ɱ༭ģʽ
void setTreeItemIsEditable(QTreeWidget *tree)
{
    QTreeWidgetItemIterator it(tree);
    while (*it)
    {
        //do something like
        QTreeWidgetItem *item = *it;
        item->setFlags(Qt::ItemIsEditable |Qt::ItemIsEnabled |Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled);// ����ȫ���ɱ༭,ѡ��ʹ��
        it++;
    }
}
// ������Ԫ�ĵ�Ԫ��ȫ������Ϊ�ɱ༭ģʽ
void setTreeItemIsEditable(QTreeWidgetItem *item)
{
    QTreeWidgetItemIterator it(item);
    while (*it)
    {
        //do something like
        QTreeWidgetItem *item = *it;
        item->setFlags(Qt::ItemIsEditable |Qt::ItemIsEnabled |Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled);// ����ȫ���ɱ༭,ѡ��ʹ��
        it++;
    }
}
// �����в��Ҷ����еĹؼ��ʣ��ҵ��ͷ��ض��ڵ�item�����򷵻ؿ�
// tree   ���ҵĶ���
// column ���ҵ�����
// key    ���ҵĹؼ���
QTreeWidgetItem* treeFindKey(QTreeWidget *tree,int column,QString key)
{
    if(tree==NULL)return NULL;
    QTreeWidgetItemIterator it(tree);
    QTreeWidgetItem *item = *it;
    if(column>item->columnCount())return NULL;   // ����������Χ
    while (*it)
    {
        //do something like
        item = *it;
        if(item->text(column).toLower() == key.toLower())
        {
            return item;
        }
        it++;
    }
    return NULL;
}
// tree   ���ҵĶ���
// column ���ҵ�����
// key    ���ҵĹؼ���
// childCount ������Ӷ������ƥ��
// �����в��Ҷ�Ӧ�еĹؼ��ʣ��ҵ��ͷ��ض��ڵ�item�����򷵻ؿ�
QTreeWidgetItem* treeFindKey(QTreeWidget *tree, int column, QString key, int childCount)
{
    if(tree==NULL)return NULL;
    QTreeWidgetItemIterator it(tree);
    QTreeWidgetItem *item = *it;
    if(column>item->columnCount())return NULL;   // ����������Χ
    while (*it)
    {
        //do something like
        item = *it;
        if((item->text(column).toLower() == key.toLower())&&(item->childCount() == childCount))
        {
            return item;
        }
        it++;
    }
    return NULL;
}
// tree   ���ҵĶ���
// column ���ҵ�����
// key    ���ҵĹؼ���
// �����Ķ����в��Ҷ�Ӧ�еĹؼ��ʣ��ҵ��ͷ��ض��ڵ�item�����򷵻ؿ�
QTreeWidgetItem* findKeyTopTree(QTreeWidgetItem *tree, int column, QString key)
{
    if(tree==NULL)return NULL;
    QTreeWidgetItem *item;
    if(column>tree->columnCount())return NULL;   // ����������Χ
    for(int i=0;i<tree->childCount();i++)
    {
        item = tree->child(i);
        if(item->text(column).toLower() == key.toLower())return item;
    }
    return NULL;
}
// tree   ���ҵĶ���
// column ���ҵ�����
// key    ���ҵĹؼ���
// �����Ķ����в��Ҷ�Ӧ�еĹؼ��ʣ��ҵ��ͷ��ض��ڵ�item�����򷵻ؿ�
QTreeWidgetItem* findKeyTopTree(QTreeWidget *tree, int column, QString key)
{
    if(tree==NULL)return NULL;
    QTreeWidgetItem *item;
    if(column>tree->columnCount())return NULL;   // ����������Χ
    for(int i=0;i<tree->topLevelItemCount();i++)
    {
        item = tree->topLevelItem(i);
        if(item->text(column).toLower() == key.toLower())return item;
    }
    return NULL;
}

// �ݹ��㷨
// ��tree�ڵ�ɾ��
void delTreeItem(QTreeWidgetItem *itemP)
{
    if(itemP ==  NULL)return;
    // ɾ���Ӷ���
    while(itemP->childCount())
    {
        delTreeItem(itemP->child(0));
    }
    // ɾ������
    delete itemP;
}







