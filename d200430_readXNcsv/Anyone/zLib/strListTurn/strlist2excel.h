#ifndef STRLIST2EXCEL_H
#define STRLIST2EXCEL_H
#include<QString>

// pro��Ҫ���  QT       += axcontainer   # for use excel tool

// ����ת��Ԫ��
bool ListAll2excel(QString excelName,QList<QStringList> *listAll);
bool excel2ListAll(QString excelName,QList<QStringList> *listAll);

void creatExcel(QString excelName);                 // ����excel

#endif // STRLIST2EXCEL_H
