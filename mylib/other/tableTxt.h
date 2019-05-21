#ifndef TABLETXT
#define TABLETXT

#include <QFile>
#include <QList>
#include <QTableWidget>
#include <QDebug>
bool txt2table(QString filename,QTableWidget *myTable); // 导入txt文件
void table2txt(QTableWidget *myTable,QString filename); // 导入txt文件

#endif // TABLETXT

