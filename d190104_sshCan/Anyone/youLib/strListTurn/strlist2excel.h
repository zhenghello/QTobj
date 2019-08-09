#ifndef STRLIST2EXCEL_H
#define STRLIST2EXCEL_H
#include<QString>

// pro需要添加  QT       += axcontainer   # for use excel tool

// 基本转换元素
bool ListAll2excel(QString excelName,QList<QStringList> *listAll);
bool excel2ListAll(QString excelName,QList<QStringList> *listAll);

void creatExcel(QString excelName);                 // 创建excel

#endif // STRLIST2EXCEL_H
