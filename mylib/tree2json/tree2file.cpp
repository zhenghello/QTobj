#include "tree2file.h"

#define CHILD_FLAG QString("zkp%1").arg(index,3,10,QChar('0')) // �Ӳ����ļ��еı�ʾ
#define ARG_FLAG   QString("ARG")               // �������ļ��еı�ʾ

// �ݹ��㷨
// ��treeת��map����
QVariantMap treeItem2map(const QTreeWidgetItem *itemP)
{
    // ����������
    QVariantList vlist;    
    QVariantMap  map ;
    for(int i=0;i<itemP->columnCount();i++)
    {
        if((itemP->text(i)=="")||(itemP->text(i)==NULL))
            vlist.append(" ");
        else
            vlist.append(itemP->text(i));
    }
    map.insert(ARG_FLAG,vlist);
    // �����Ӷ���
    for(int index=0;index<itemP->childCount();index++)
    {
        map.insert(CHILD_FLAG,treeItem2map(itemP->child(index)));
    }
    return map;
}
// �ݹ��㷨
// ��map����ת��tree
QTreeWidgetItem *map2treeItem(QVariantMap mapP)
{
    QTreeWidgetItem *treeItem=new QTreeWidgetItem();
    QVariantList vlist;
    // ��ȡARGֵ
    vlist = mapP.take(ARG_FLAG).toList();
    for(int index=0;index<vlist.size();index++)
    {
        treeItem->setText(index,vlist.at(index).toString());
    }
    // ��ȡ�Ӷ��� �� ARGֵ->������keyֵ�������ⲿ�༭�Ͳ���Ӱ��
    QMapIterator<QString, QVariant> mapit(mapP);
    while (mapit.hasNext())
    {
        mapit.next();
        QTreeWidgetItem *treeItemChild = new QTreeWidgetItem();
        treeItemChild = map2treeItem(mapit.value().toMap());
        treeItem->addChild(treeItemChild);
    }
    return treeItem;
}
// �ݹ��㷨
// ��tree�ڵ�ɾ��
void delTreeItem(QTreeWidgetItem *itemP)
{
    if(itemP ==  NULL)return;
    // ɾ���Ӷ���
    while(itemP->childCount())
    {
        qDebug()<<"delTreeItem = " << itemP->childCount();
        delTreeItem(itemP->child(0));
    }
    // ɾ������
    delete itemP;
}
// ������ת��json�ļ�
void treeWidget2file(const QTreeWidget *tree,const QString fileName)
{
    QVariantMap mapAll ; // ���Ҫ�����map����
    // 1.�����Ļ�����������
    // 1.1.�����и���
    mapAll.insert("columnCount",tree->columnCount());
    mapAll.insert("columnCount_explain",QString::fromLocal8Bit("�����еĸ���"));
    // 1.2.�����п��
    QVariantList list;
    list.clear();
    for(int index = 0;index < tree->columnCount();index++)
        list.append(tree->columnWidth(index));

    mapAll.insert("columnWidth",list);
    mapAll.insert("columnWidth_explain",QString::fromLocal8Bit("�����еĿ��"));

    // 1.3.�����ͷ����
    list.clear();
    for(int index = 0;index < tree->columnCount();index++)
        list.append(tree->headerItem()->text(index));
    mapAll.insert("headerItemText",list);
    mapAll.insert("headerItemText_explain",QString::fromLocal8Bit("�����еı�ͷ����"));

    // 2.�����ĺ������� �ݹ��ȡ��map��
    for(int index = 0;index < tree->topLevelItemCount();index++)
    {
        mapAll.insert(CHILD_FLAG, treeItem2map(tree->topLevelItem(index)));
    }
    // 3.���ݱ���
    QFile file(fileName);
    file.open(QFile::WriteOnly);
    file.write(QJsonDocument::fromVariant(mapAll).toJson());
    file.close();
}

// json�ļ�ת��������
void file2treeWidget(QTreeWidget *tree,const QString fileName)
{
    // 1.���ļ��г������
    QFile       file(fileName);
    bool bret = file.open(QFile::ReadOnly);
    if(bret == false)return;    // û���ļ���ǰ�˳�
    QVariantMap mapAll = QJsonDocument::fromJson(file.readAll()).toVariant().toMap();
    file.close();
    // 2.׼������
    // 2.1.���
    tree->clear();
    // 2.2.�����и���->������3��
    if(mapAll.value("columnCount").toInt()<3)
        mapAll.insert("columnCount",3);
    tree->setColumnCount(mapAll.take("columnCount").toInt());
    mapAll.remove("columnCount_explain");

    // 2.3.�������� ->���������������
    tree->header()->setSectionResizeMode(tree->columnCount()-2,QHeaderView::Fixed);
    tree->header()->setSectionResizeMode(tree->columnCount()-1,QHeaderView::Fixed);
    tree->header()->setStretchLastSection(false);   // ���һ�е���������
    // 2.4.�����п��->��������̶�Ϊ20
    QVariantList list;
    list=mapAll.take("columnWidth").toList();
    mapAll.remove("columnWidth_explain");
    for(int index = 0;index < list.size();index++)
    {
        tree->setColumnWidth(index,list.at(index).toInt());
    }
    tree->setColumnWidth(tree->columnCount()-2,20);
    tree->setColumnWidth(tree->columnCount()-1,20);


    // 2.5.����ͷ����
    QTreeWidgetItem *headItem = new QTreeWidgetItem();
    list=mapAll.take("headerItemText").toList();
    mapAll.remove("headerItemText_explain");
    for(int index = 0;index < tree->columnCount();index++)
    {
        headItem->setText(index,"new");
    }
    for(int index = 0;index < list.size();index++)
    {
        headItem->setText(index,list.at(index).toString());
    }
    tree->setHeaderItem(headItem);
    // 3.���ļ�����ת������ -> ������keyֵ�������ⲿ�༭�Ͳ���Ӱ��
    QMapIterator<QString, QVariant> mapit(mapAll);
    while (mapit.hasNext())
    {
        mapit.next();
        QTreeWidgetItem *treeItemChild = new QTreeWidgetItem();
        treeItemChild = map2treeItem(mapit.value().toMap());
        tree->addTopLevelItem(treeItemChild);
    }
    // 4.����ǿյ�����Ĭ�ϴ���һ��
    if(tree->topLevelItemCount()<1)
    {
        QTreeWidgetItem *item=new QTreeWidgetItem();
        tree->addTopLevelItem(item);
    }
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
QTreeWidgetItem* treeFindKey(QTreeWidget *tree,int column,QString key)
{
    QTreeWidgetItemIterator it(tree);
    QTreeWidgetItem *item = *it;
    if(column>item->columnCount())return NULL;   // ����������Χ
    while (*it)
    {
        //do something like
        item = *it;
        if(item->text(column) == key)
        {
            return item;
        }
        it++;
    }
    return NULL;
}

