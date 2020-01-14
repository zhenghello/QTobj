#ifndef DAT2TABLEWIDGET_H
#define DAT2TABLEWIDGET_H

#include <QString>
#include <QTableWidget>

// 复合转换元素
bool dat2tableWidget(QString datName,QTableWidget *table);
bool tableWidget2dat(QString datName,QTableWidget *table);  // table转dat

#endif // DAT2TABLEWIDGET_H
