#include "tableTxt.h"
//输入一个文本文档的路径和名字，转换为excel表,这些数据会覆盖原表。
bool txt2table(QString filename,QTableWidget *myTable)
{
    QFile       file(filename); // 文件handle
    QStringList allLine;     // 所有行数据
    // 打开文件
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
         qDebug()<<"txt2table -> open faile!";//打印读取到的数据
        return false;
    }
    // 导出所有行
    allLine.clear();
    while(!file.atEnd())
    {   // 1.读取一行数据
        QByteArray line = file.readLine();
        QString str = QString::fromUtf8(line.data ());
        str = str.simplified();//去掉非识别字符
        allLine.append(str);
    }
    int i,j;
    QList<QStringList> listLineStr;//存放所有已经分割的行
    // 根据"%%"分割行内容,所有数据缓存在 listLineStr 中
    listLineStr.clear();
    for(i=0;i<allLine.length();i++)
    {
        QStringList listStr;
        listStr=allLine.at(i).split("%%");
        if(listStr.size()>1)listLineStr.append(listStr); //将有单元格数据的行保存
    }
    // listLineStr 存到excel中，覆盖原表
    myTable->setRowCount(0);
    for(j=0;j<listLineStr.size();j++)
    {
        myTable->insertRow(myTable->rowCount());//创建新行
        for(int i=1;i<listLineStr.at(j).size();i++)
        {
            QTableWidgetItem *n=new QTableWidgetItem(); // 创建一个Item
            QString str = listLineStr.at(j).at(i);      // 抽出该单元格的字符串
            n->setText(str.simplified());               // 去除不识别的字符和空格
            myTable->setItem (myTable->rowCount()-1,i-1,n);//在这里，第一个"%%"前是空白，被放弃了。
            //qDebug()<<listLineStr.at(j).at(i);//打印读取到的数据
        }
    }
    myTable->selectRow(myTable->rowCount()); //选择到新行
    file.close();
    return true;
}
//输入一个文本文档的路径和名字，将excel表转换到txt中
void table2txt(QTableWidget *myTable,QString filename)
{
    QFile       file(filename); // 文件handle
    // 打开文件
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        //Fdebug::mydebug()->debug_char("E:fkey->have no file!");
        return;
    }
    int i,j;
    QString str;
    for(i=0;i<myTable->rowCount();i++)
    {
        str.clear();
        for(j=0;j<myTable->columnCount();j++)
        {
            str += "%%";   //第一个"%%"
            if((nullptr == myTable->item(i,j))||(nullptr == myTable->item(i,j)->text()))str += " ";//空白内容添加一个空格
                else str += myTable->item(i,j)->text().simplified();// 只保存可识别的字符
        }
        str += "\n";   //补齐换行
        //Fdebug::mydebug()->debug_text(str); //打印每个单元格的内容
        file.write(str.toUtf8());
    }
    file.close();
}
