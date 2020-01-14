/*
    �ĵ�������֣����
    ����ĵ�����Ҫ�����ǽ� QTableWidget �� QList<QStringList> ���ݻ���ת��
    QTableWidget ת QList<QStringList>��Э�飺
    1.QStringList �ĵ�һ�����ݴ�������ͷ����
    2.QStringList �ĵ�һ������Ϊ0����Ե��룬�������ⲿ�ļ���������ע�ͣ������������û����
    3.QStringList �ĵ�һ����������Ϊ֮�ܱ��ϴεĴ�1��������1����
    4.dat�еĵ�һ������û��

    4.ǰ10�����ڲ������룬����Ϊ��������
    4.1.��1�б����и�������СΪ3
    4.2.��2�б���ÿ�еĿ�ȣ���СΪ20
    4.3.��3�б���ÿ�еı�ͷ��
*/
#include "strlist2tableWidget.h"
#include <QHeaderView>

#include <QDebug>
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
        strlist.append("1");                                // ����Э�飬��һ�����ݹ̶�Ϊ1
        for(int column = 0;column < table->columnCount();column++)
        {
            QTableWidgetItem *item = table->item(row,column);

            if((item == NULL)||(item->text() == NULL))
                strlist.append(" ");
            else
                strlist.append(item->text().replace('\n', "\\n"));  // �滻Ϊ��ʶ������
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
    // 1.1.����ȫ����Ĭ������ 
    table->setFont(QFont("SimSun",9)); //  SimSun ������
    // 1.2.��ͷ����Ĭ������
    table->horizontalHeader()->setStyleSheet("QHeaderView::section{background: rgb(200, 200, 200) }");	// ���ñ�����ɫ
    table->horizontalHeader()->setFixedHeight(20);// �����б�ͷ�̶��߶�
    table->verticalHeader()->setStyleSheet("QHeaderView::section{background: rgb(200, 200, 200) }");	// ���ñ�����ɫ
    table->verticalHeader()->setFixedWidth(30); // �����б�ͷ�̶����
    // 1.3.�ж��������
    if(listAll->size()<10)
        return false;
    // 2.1.�����и���->������3��
    strlist.clear();
    strlist.append(listAll->takeFirst());                       // ȡ��
    if(strlist.takeFirst() != "columnCount")
    {
        // û�йؼ���
        qDebug()<<QString("no key") + QString::fromLocal8Bit(__FILE__)+QString("\r\n")+QString::number(__LINE__)+QString("\r\n")+QString::fromLocal8Bit(__FUNCTION__);
        return false;
    }
    str = strlist.first();
    columnCount = str.toInt();
    if(columnCount<3)columnCount=3;
    table->setColumnCount(columnCount);
    // 2.2.�������Ժ��п�
    strlist.clear();
    strlist.append(listAll->takeFirst());                // ȡ��
    if(strlist.takeFirst()!="columnWidth")
    {// û�йؼ���
        qDebug()<<QString("no key") + QString::fromLocal8Bit(__FILE__)+QString("\r\n")+QString::number(__LINE__)+QString("\r\n")+QString::fromLocal8Bit(__FUNCTION__);
        return false;
    }
    for(int column = 0;column < strlist.size();column++)
    {
        if(column>=table->columnCount()){ break;}// ������û��ʵ�ʵĶ࣬����
        int width=strlist.at(column).toInt();
        if(width<20)width=20;
        table->setColumnWidth(column,width);
        table->horizontalHeader()->setSectionResizeMode(column,QHeaderView::Interactive);
    }
    // ���������������->��������̶�Ϊ20 - d200107_ȡ��
//    table->horizontalHeader()->setSectionResizeMode(table->columnCount()-2,QHeaderView::Fixed);
//    table->horizontalHeader()->setSectionResizeMode(table->columnCount()-1,QHeaderView::Fixed);
//    table->setColumnWidth(table->columnCount()-2,20);
//    table->setColumnWidth(table->columnCount()-1,20);

    // 2.3.����ͷ����
    strlist.clear();
    strlist.append(listAll->takeFirst());        // ȡ��
    if(strlist.takeFirst()!="horizontalHeaderItem")
    {
        qDebug()<<QString("no key") + QString::fromLocal8Bit(__FILE__)+QString("\r\n")+QString::number(__LINE__)+QString("\r\n")+QString::fromLocal8Bit(__FUNCTION__);
        // û�йؼ���
        return false;
    }
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
    qDebug()<< "listAll->size() = " << listAll->size();
    table->setRowCount(listAll->size());        // �����и���
    for(int row=0;row<listAll->size();row++)
    {
        strlist.clear();
        strlist.append(listAll->at(row));
        strlist.removeFirst();                      // ����Э�飬��һ��������Ч
        for(int column=0;column<strlist.size();column++)
        {
            if(column>=table->columnCount()){break;}
            str = strlist.at(column);
            str = str.replace(QString("\\n"), QString("\n"));
            item = new QTableWidgetItem(str);// ���滻
            table->setItem(row,column,item);
            /*�������ݵ����и߶�*/
            int h = (str.length() - str.remove('\n').length() + 1) * 13;  // 13 ���ַ���ʽ�йصģ��õ����ַ�������9pt
            table->setRowHeight(row, qMax(h, table->rowHeight(row)));
        }
    }
    return true;
}





