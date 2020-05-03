#ifndef EXCEL2TABLEWIDGET_H
#define EXCEL2TABLEWIDGET_H
#include<QString>
#include<QTableWidget>
// 复合转换元素 
bool tableWidget2excel(QString excelName,QTableWidget *table);
bool excel2tableWidget(QString excelName,QTableWidget *table);  // excel转table

#endif // EXCEL2TABLEWIDGET_H
