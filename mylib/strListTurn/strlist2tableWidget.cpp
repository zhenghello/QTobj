/*
    �ĵ�������֣����
    ����ĵ�����Ҫ�����ǽ� QTableWidget �� QList<QStringList> ���ݻ���ת��
    QTableWidget ת QList<QStringList>��Э�飺
    1.QStringList �ĵ�һ�����ݴ�������ͷ����
    2.QStringList �ĵ�һ������Ϊ0����Ե��룬�������ⲿ�ļ���������ע�ͣ������������û����
    3.QStringList �ĵ�һ����������Ϊ֮�ܱ��ϴεĴ�1��������1����

    4.ǰ10�����ڲ������룬����Ϊ��������
    4.1.��1�б����и�������СΪ3
    4.2.��2�б���ÿ�еĿ�ȣ���СΪ20
    4.3.��3�б���ÿ�еı�ͷ��
*/
#include "strlist2tableWidget.h"
#include <QHeaderView>

//#include <QDebug>
// �� �� תΪ listAll
void tableWidget2listAll(QTableWidget *table,QList<QStringList> *listAll)
{
    QStringList strlist;

    // 1.�Ա�Ļ�����������
    // 1.1.�����и���
    listAll->clear();
    strlist.clear();
    strlist.append("columnCount");
    strlist.append(QString::number(table->columnCount()));
    listAll->append(strlist);

    // 1.2.�����п��
    strlist.clear();
    strlist.append("columnWidth");
    for(int index = 0;index < table->columnCount();index++)
        strlist.append(QString::number(table->columnWidth(index)));
    listAll->append(strlist);
    // 1.3.�����ͷ����
    strlist.clear();
    strlist.append("horizontalHeaderItem");
    for(int index=0;index<table->columnCount();index++)
    {
        QTableWidgetItem *item = table->horizontalHeaderItem(index);
        if((item == NULL)||(item->text() == NULL))
            strlist.append(" ");
        else
            strlist.append(item->text());
    }
    listAll->append(strlist);
    // 1.4.Ԥ��
    strlist.clear();
    strlist<<"test";
    listAll->append(strlist);
    // 1.5.Ԥ��
    strlist.clear();
    strlist<<"test";
    listAll->append(strlist);
    // 1.6.Ԥ��
    strlist.clear();
    strlist<<"test";
    listAll->append(strlist);
    // 1.7.Ԥ��
    strlist.clear();
    strlist<<"test";
    listAll->append(strlist);
    // 1.8.Ԥ��
    strlist.clear();
    strlist<<"test";
    listAll->append(strlist);
    // 1.9.Ԥ��
    strlist.clear();
    strlist<<"test";
    listAll->append(strlist);
    // 1.10.Ԥ��
    strlist.clear();
    strlist<<"test";
    listAll->append(strlist);
    // 2.�����ĺ������� ��ȡ�� listAll ��

    for(int row = 0;row < table->rowCount();row++)
    {
        strlist.clear();
        for(int column = 0;column < table->columnCount();column++)
        {
            QTableWidgetItem *item = table->item(row,column);

            if((item == NULL)||(item->text() == NULL))
                strlist.append(" ");
            else
                strlist.append(item->text());
        }
        listAll->append(strlist);
    }
}
// �� listAll תΪ��
bool listAll2tableWidget(QTableWidget *table,QList<QStringList> *listAll)
{
    QStringList strlist;
    QString str;
    int columnCount;
    // 1.0.���
    table->clear();
    // 2.1.�����и���->������3��
    strlist.clear();
    strlist.append(listAll->takeFirst());                       // ȡ��
    if(strlist.takeFirst() != "columnCount"){return false;}     // û�йؼ���
    str = strlist.first();
    columnCount = str.toInt();
    if(columnCount<3)columnCount=3;
    table->setColumnCount(columnCount);
    // 2.2.�������Ժ��п� ->���������������->��������̶�Ϊ20
    strlist.clear();
    strlist.append(listAll->takeFirst());                // ȡ��
    if(strlist.takeFirst()!="columnWidth"){return false;} // û�йؼ���
    for(int column = 0;column < strlist.size();column++)
    {
        if(column>=table->columnCount()){ break;}
        int width=strlist.at(column).toInt();
        if(width<20)width=20;
        table->setColumnWidth(column,width);
        table->horizontalHeader()->setSectionResizeMode(column,QHeaderView::Interactive);
    }
    table->horizontalHeader()->setSectionResizeMode(table->columnCount()-2,QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(table->columnCount()-1,QHeaderView::Fixed);
    table->setColumnWidth(table->columnCount()-2,20);
    table->setColumnWidth(table->columnCount()-1,20);

    // 2.3.����ͷ����
    strlist.clear();
    strlist.append(listAll->takeFirst());        // ȡ��
    if(strlist.takeFirst()!="horizontalHeaderItem"){return false;} // û�йؼ���
    table->setHorizontalHeaderLabels(strlist);

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

    // 3.���ļ�����ת����table
    QTableWidgetItem *item;
    for(int row=0;row<listAll->size();row++)
    {
        strlist.clear();
        strlist.append(listAll->at(row));
        for(int column=0;column<strlist.size();column++)
        {
            if(column>=table->columnCount()){break;}
            item = new QTableWidgetItem(strlist.at(column));
            table->setItem(row,column,item);
        }
    }
    return true;
}





