// 将excel文件导出并保存成 QVector<QVector<QString>> 格式保存
// 目前只导入excel 第一个sheet
#ifndef EXCEL2MAT_H
#define EXCEL2MAT_H

#include<QDebug>
#include <QAxObject> //在pro文件中添加 QT       += axcontainer      # use excel function
#include <QFile>

class Excel2Mat
{
public:
    Excel2Mat();
    bool load(QString eName);
    int rowSize();              // 行数
    int colunmSize();           // 列数
    QString d(int r,int c); // 返回数据
    bool columnFind(QString str,int r,int& c);

private:
    QVector<QVector<QString>> mat;
    QString excelName;      // excel的路径和名字
};

#endif // EXCEL2MAT_H

bool xls2mat(QString excelName, QVector<QVector<QString>> *listAll);

