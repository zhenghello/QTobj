/*
    文档声明：郑凯鹏
    这个文档的主要功能是将QTreeWidget 和 QList<QStringList> 数据互相转换
    关于树的递归，是利用了QList<QStringList> 的第一列作为子层参数，参数越高，层数越低
    QTreeWidget 转 QList<QStringList>的协议：
    1.QStringList 的第一个数据代表他在树中的层级，顶层为1，
    2.QStringList 的第一个数据为0则忽略导入，可以在外部文件中用来做注释，不过导出后就没有了
    3.QStringList 的第一个数据数据为之能比上次的大1，超过按1处理

    4.前10行用于参数导入，不作为树的内容
    5.第1行保存列个数，最小为3
    6.第2行保存每列的宽度，最小为20
    7.第3行保存每行的表头名
*/
#include "strlist2treewidget.h"
#include <QHeaderView>
QList<QStringList> treeItem2listAll(const QTreeWidgetItem *itemP, const int level);
// 内部函数
// 递归算法->将 QTreeWidgetItem 转成 QList<QStringList> 数据
// 规定第一个数据代表归从关系，
// 数据越低等级越高
QList<QStringList> treeItem2listAll(const QTreeWidgetItem *itemP,const int level)
{
    QList<QStringList> listAll;
    // 插入对象参数
    QStringList strList;
    strList.append(QString("%1").arg(level,3,10,QChar('0')));    // 插入等级参数
    for(int i=0;i<itemP->columnCount();i++)
    {
        if((itemP->text(i)=="")||(itemP->text(i)==NULL))
            strList.append(" ");
        else
            strList.append(itemP->text(i));
    }
    listAll.append(strList);
    // 插入子对象
    for(int index=0;index<itemP->childCount();index++)
    {
        QList<QStringList> listFun = treeItem2listAll(itemP->child(index),level+1);
        for(int i=0;i<listFun.size();i++)
            listAll.append(listFun.at(i));
    }
    return listAll;
}
// 将 QTreeWidget 数据转为 QList<QStringList> 其中头几行是自定义的 QTreeWidget 属性的数据，两个文件都要匹配使用才行
void treeWidget2listAll(QTreeWidget *tree,QList<QStringList> *listAll)
{
    QStringList strlist;
    // 1.对树的基本参数保存
    // 1.1.保存列个数
    listAll->clear();
    strlist.clear();
    strlist.append("columnCount");
    strlist.append(QString::number(tree->columnCount()));
    listAll->append(strlist);
    // 1.2.保存列宽度
    strlist.clear();
    strlist.append("columnWidth");
    for(int index = 0;index < tree->columnCount();index++)
        strlist.append(QString::number(tree->columnWidth(index)));
    listAll->append(strlist);
    // 1.3.保存表头名字
    strlist.clear();
    strlist.append("headerItemText");
    for(int index = 0;index < tree->columnCount();index++)
        strlist.append(tree->headerItem()->text(index));
    listAll->append(strlist);
    // 1.4.预留
    strlist.clear();
    strlist<<"0"<<"test";
    listAll->append(strlist);
    // 1.5.预留
    strlist.clear();
    strlist<<"0"<<"test";
    listAll->append(strlist);
    // 1.6.预留
    strlist.clear();
    strlist<<"0"<<"test";
    listAll->append(strlist);
    // 1.7.预留
    strlist.clear();
    strlist<<"0"<<"test";
    listAll->append(strlist);
    // 1.8.预留
    strlist.clear();
    strlist<<"0"<<"test";
    listAll->append(strlist);
    // 1.9.预留
    strlist.clear();
    strlist<<"0"<<"test";
    listAll->append(strlist);
    // 1.10.预留
    strlist.clear();
    strlist<<"0"<<"test";
    listAll->append(strlist);

    // 2.将树的横向数据 递归读取到 listAll 中
    for(int index = 0;index < tree->topLevelItemCount();index++)
    {
        QList<QStringList> listFun = treeItem2listAll(tree->topLevelItem(index),1);
        for(int i=0;i<listFun.size();i++)
            listAll->append(listFun.at(i));
    }
}
// 将 QList<QStringList> 数据转为 QTreeWidget
bool listAll2treeWidget(QTreeWidget *tree,QList<QStringList> *listAll)
{
    QStringList strlist;
    QString str;
    int columnCount;
    // 2.0.清空
    tree->clear();
    // 2.1.设置列个数->最少有3个 listAll
    strlist.clear();
    strlist.append(listAll->takeFirst());               // 取走
    if(strlist.takeFirst() != "columnCount"){return false;}   // 没有关键字
    str = strlist.first();
    columnCount = str.toInt();
    if(columnCount<3)columnCount=3;
    tree->setColumnCount(columnCount);
    // 2.2.拉伸属性 ->最后两个不能拉伸
    tree->header()->setSectionResizeMode(tree->columnCount()-2,QHeaderView::Fixed);
    tree->header()->setSectionResizeMode(tree->columnCount()-1,QHeaderView::Fixed);
    tree->header()->setStretchLastSection(false);   // 最后一列的拉伸属性
    // 2.2.设置列宽度->最后两个固定为20
    strlist.clear();
    strlist.append(listAll->takeFirst());        // 取走
    if(strlist.takeFirst()!="columnWidth"){return false;} // 没有关键字

    for(int index = 0;index < strlist.size();index++)
    {
        tree->setColumnWidth(index,strlist.at(index).toInt());
    }
    tree->setColumnWidth(tree->columnCount()-2,20);
    tree->setColumnWidth(tree->columnCount()-1,20);
    // 2.3.设置头标题
    strlist.clear();
    strlist.append(listAll->takeFirst());        // 取走
    if(strlist.takeFirst()!="headerItemText"){return false;} // 没有关键字
    tree->setHeaderLabels(strlist);
    // 2.4.预留
    strlist.append(listAll->takeFirst());        // 取走
    // 2.5.预留
    strlist.append(listAll->takeFirst());        // 取走
    // 2.6.预留
    strlist.append(listAll->takeFirst());        // 取走
    // 2.7.预留
    strlist.append(listAll->takeFirst());        // 取走
    // 2.8.预留
    strlist.append(listAll->takeFirst());        // 取走
    // 2.9.预留
    strlist.append(listAll->takeFirst());        // 取走
    // 2.10.预留
    strlist.append(listAll->takeFirst());        // 取走

    // 3.将文件内容转换成tree
    QTreeWidgetItem *lastItem = 0;
    int lastCount = 0;
    int index;
    while(!listAll->isEmpty())
    {
        strlist.clear();
        strlist.append(listAll->takeFirst());        // 取走
        index = strlist.takeFirst().toInt();        // 获取树形递归偏移值
        QTreeWidgetItem *treeItemChild = new QTreeWidgetItem(strlist);// 设置内容
        if(index > (lastCount+1))lastCount=index+1; // 不合理的情况，强制减小
        // 0 被忽略 1 是顶层，其他都是子队列
        if(index == 0)
        {
            continue;
        }
        if(index == 1)
        {
            tree->addTopLevelItem(treeItemChild);
        }
        else
        {   // 倒退计算父对象
            for(int i=index;i<=lastCount;i++)
            {
                lastItem=lastItem->parent();
            }
            lastItem->addChild(treeItemChild);
        }
        lastItem = treeItemChild;
        lastCount = index;
    }
    // 4.空数据，就填充一个
    if(tree->topLevelItemCount() == 0)
    {
        QTreeWidgetItem *treeItemChild = new QTreeWidgetItem();// 设置内容
        treeItemChild->setText(0,"empty");
        tree->addTopLevelItem(treeItemChild);
    }
    // 5.强制去掉多余的列
    tree->setColumnCount(columnCount);
    return true;
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
// tree   查找的对象
// column 查找的列数
// key    查找的关键字
QTreeWidgetItem* treeFindKey(QTreeWidget *tree,int column,QString key)
{
    if(tree==NULL)return NULL;
    QTreeWidgetItemIterator it(tree);
    QTreeWidgetItem *item = *it;
    if(column>item->columnCount())return NULL;   // 列数超出范围
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
// tree   查找的对象
// column 查找的列数
// key    查找的关键字
// childCount 对象的子对象个数匹配
// 在树中查找对应列的关键词，找到就返回对于的item，否则返回空
QTreeWidgetItem* treeFindKey(QTreeWidget *tree, int column, QString key, int childCount)
{
    if(tree==NULL)return NULL;
    QTreeWidgetItemIterator it(tree);
    QTreeWidgetItem *item = *it;
    if(column>item->columnCount())return NULL;   // 列数超出范围
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
// tree   查找的对象
// column 查找的列数
// key    查找的关键字
// 在树的顶层中查找对应列的关键词，找到就返回对于的item，否则返回空
QTreeWidgetItem* findKeyTopTree(QTreeWidgetItem *tree, int column, QString key)
{
    if(tree==NULL)return NULL;
    QTreeWidgetItem *item;
    if(column>tree->columnCount())return NULL;   // 列数超出范围
    for(int i=0;i<tree->childCount();i++)
    {
        item = tree->child(i);
        if(item->text(column).toLower() == key.toLower())return item;
    }
    return NULL;
}
// tree   查找的对象
// column 查找的列数
// key    查找的关键字
// 在树的顶层中查找对应列的关键词，找到就返回对于的item，否则返回空
QTreeWidgetItem* findKeyTopTree(QTreeWidget *tree, int column, QString key)
{
    if(tree==NULL)return NULL;
    QTreeWidgetItem *item;
    if(column>tree->columnCount())return NULL;   // 列数超出范围
    for(int i=0;i<tree->topLevelItemCount();i++)
    {
        item = tree->topLevelItem(i);
        if(item->text(column).toLower() == key.toLower())return item;
    }
    return NULL;
}

// 递归算法
// 将tree节点删除
void delTreeItem(QTreeWidgetItem *itemP)
{
    if(itemP ==  NULL)return;
    // 删除子对象
    while(itemP->childCount())
    {
        delTreeItem(itemP->child(0));
    }
    // 删除对象
    delete itemP;
}







