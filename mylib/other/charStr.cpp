#include "charStr.h"

// 输入一行字符串，字符串中是16进制的数据，每个数据用空格隔开，返回数据的列表
// 例如："11 22 33”输出 0x11 0x22 0x33
void lineStr2charVector(QString str, QVector<char> *vector)
{
    QStringList strlist;
    int i;
    // 1.去掉首尾空白 + 去掉多空格为1空格，去掉非识别字符
    str = str.trimmed();
    str = str.simplified();
    // 2.分割字符段
    strlist = str.split (" ");
    // 3.转为十进制
    vector->clear();
    for(i=0;i<strlist.length();i++)
    {
        vector->append(strlist.at(i).toInt(nullptr,16));    //转换进制
    }
}
// 输入一行字符串，字符串中是16进制的数据，每个数据用空格隔开，返回数据的列表
// 例如："11 22 33”输出 0x11 0x22 0x33
void lineStr2charList(QString str, QList<char> *list)
{
    QStringList strlist;
    int i;
    // 1.去掉首尾空白 + 去掉多空格为1空格，去掉非识别字符
    str = str.trimmed();
    str = str.simplified();
    // 2.分割字符段
    strlist = str.split (" ");
    // 3.转为十进制
    list->clear();
    for(i=0;i<strlist.length();i++)
    {
        list->append(strlist.at(i).toInt(nullptr,16));    //转换进制
    }
}
// 输入一行字符串，字符串中是16进制的数据，每个数据用空格隔开，返回数据的 QByteArray
// 例如："11 22 33”输出 0x11 0x22 0x33
void lineStr2charArray(QString str, QByteArray *array)
{
    QStringList strlist;
    int i;
    // 1.去掉首尾空白 + 去掉多空格为1空格，去掉非识别字符
    str = str.trimmed();
    str = str.simplified();
    // 2.分割字符段
    strlist = str.split (" ");
    // 3.转为十进制
    array->clear();
    for(i=0;i<strlist.length();i++)
    {
        array->append(strlist.at(i).toInt(nullptr,16));    //转换进制
    }
}
