#include "tree2file.h"

#define CHILD_FLAG QString("zkp%1").arg(index,3,10,QChar('0')) // 子层在文件中的标示
#define ARG_FLAG   QString("ARG")               // 参数在文件中的标示

// 递归算法
// 将tree转成map数据
QVariantMap treeItem2map(const QTreeWidgetItem *itemP)
{
    // 插入对象参数
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
    // 插入子对象
    for(int index=0;index<itemP->childCount();index++)
    {
        map.insert(CHILD_FLAG,treeItem2map(itemP->child(index)));
    }
    return map;
}
// 递归算法
// 将map数据转成tree
QTreeWidgetItem *map2treeItem(QVariantMap mapP)
{
    QTreeWidgetItem *treeItem=new QTreeWidgetItem();
    QVariantList vlist;
    // 截取ARG值
    vlist = mapP.take(ARG_FLAG).toList();
    for(int index=0;index<vlist.size();index++)
    {
        treeItem->setText(index,vlist.at(index).toString());
    }
    // 获取子对象 的 ARG值->不区分key值，这样外部编辑就不受影响
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
// 递归算法
// 将tree节点删除
void delTreeItem(QTreeWidgetItem *itemP)
{
    if(itemP ==  NULL)return;
    // 删除子对象
    while(itemP->childCount())
    {
        qDebug()<<"delTreeItem = " << itemP->childCount();
        delTreeItem(itemP->child(0));
    }
    // 删除对象
    delete itemP;
}
// 树形类转成json文件
void treeWidget2file(const QTreeWidget *tree,const QString fileName)
{
    QVariantMap mapAll ; // 最后要保存的map数据
    // 1.对树的基本参数保存
    // 1.1.保存列个数
    mapAll.insert("columnCount",tree->columnCount());
    mapAll.insert("columnCount_explain",QString::fromLocal8Bit("设置列的个数"));
    // 1.2.保存列宽度
    QVariantList list;
    list.clear();
    for(int index = 0;index < tree->columnCount();index++)
        list.append(tree->columnWidth(index));

    mapAll.insert("columnWidth",list);
    mapAll.insert("columnWidth_explain",QString::fromLocal8Bit("设置列的宽度"));

    // 1.3.保存表头名字
    list.clear();
    for(int index = 0;index < tree->columnCount();index++)
        list.append(tree->headerItem()->text(index));
    mapAll.insert("headerItemText",list);
    mapAll.insert("headerItemText_explain",QString::fromLocal8Bit("设置列的表头名字"));

    // 2.将树的横向数据 递归读取到map中
    for(int index = 0;index < tree->topLevelItemCount();index++)
    {
        mapAll.insert(CHILD_FLAG, treeItem2map(tree->topLevelItem(index)));
    }
    // 3.数据保存
    QFile file(fileName);
    file.open(QFile::WriteOnly);
    file.write(QJsonDocument::fromVariant(mapAll).toJson());
    file.close();
}

// json文件转成树形类
void file2treeWidget(QTreeWidget *tree,const QString fileName)
{
    // 1.从文件中抽出数据
    QFile       file(fileName);
    bool bret = file.open(QFile::ReadOnly);
    if(bret == false)return;    // 没有文件提前退出
    QVariantMap mapAll = QJsonDocument::fromJson(file.readAll()).toVariant().toMap();
    file.close();
    // 2.准备树形
    // 2.1.清空
    tree->clear();
    // 2.2.设置列个数->最少有3个
    if(mapAll.value("columnCount").toInt()<3)
        mapAll.insert("columnCount",3);
    tree->setColumnCount(mapAll.take("columnCount").toInt());
    mapAll.remove("columnCount_explain");

    // 2.3.拉伸属性 ->最后两个不能拉伸
    tree->header()->setSectionResizeMode(tree->columnCount()-2,QHeaderView::Fixed);
    tree->header()->setSectionResizeMode(tree->columnCount()-1,QHeaderView::Fixed);
    tree->header()->setStretchLastSection(false);   // 最后一列的拉伸属性
    // 2.4.设置列宽度->最后两个固定为20
    QVariantList list;
    list=mapAll.take("columnWidth").toList();
    mapAll.remove("columnWidth_explain");
    for(int index = 0;index < list.size();index++)
    {
        tree->setColumnWidth(index,list.at(index).toInt());
    }
    tree->setColumnWidth(tree->columnCount()-2,20);
    tree->setColumnWidth(tree->columnCount()-1,20);


    // 2.5.设置头标题
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
    // 3.将文件内容转换出来 -> 不区分key值，这样外部编辑就不受影响
    QMapIterator<QString, QVariant> mapit(mapAll);
    while (mapit.hasNext())
    {
        mapit.next();
        QTreeWidgetItem *treeItemChild = new QTreeWidgetItem();
        treeItemChild = map2treeItem(mapit.value().toMap());
        tree->addTopLevelItem(treeItemChild);
    }
    // 4.如果是空的树，默认创建一个
    if(tree->topLevelItemCount()<1)
    {
        QTreeWidgetItem *item=new QTreeWidgetItem();
        tree->addTopLevelItem(item);
    }
}
// 将树的单元格全部设置为可编辑模式
void setTreeItemIsEditable(QTreeWidget *tree)
{
    QTreeWidgetItemIterator it(tree);
    while (*it)
    {
        //do something like
        QTreeWidgetItem *item = *it;
        item->setFlags(Qt::ItemIsEditable |Qt::ItemIsEnabled |Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled);// 设置全部可编辑,选择，使能
        it++;
    }
}
// 将树单元的单元格全部设置为可编辑模式
void setTreeItemIsEditable(QTreeWidgetItem *item)
{
    QTreeWidgetItemIterator it(item);
    while (*it)
    {
        //do something like
        QTreeWidgetItem *item = *it;
        item->setFlags(Qt::ItemIsEditable |Qt::ItemIsEnabled |Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled);// 设置全部可编辑,选择，使能
        it++;
    }
}
// 在树中查找对于列的关键词，找到就返回对于的item，否则返回空
QTreeWidgetItem* treeFindKey(QTreeWidget *tree,int column,QString key)
{
    QTreeWidgetItemIterator it(tree);
    QTreeWidgetItem *item = *it;
    if(column>item->columnCount())return NULL;   // 列数超出范围
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

