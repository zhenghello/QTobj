/* 备注：
 * dat文件中，单元格用 %% 隔开，读取时会自动去掉前后空格
 *
*/
#include "strlist2dat.h"
#include <QFile>
#include <QDebug>

// 将dat文件转为list,数据会保存到 listAll中
bool dat2ListAll(QString datName,QList<QStringList> *listAll)
{
    QFile       file(datName); // 文件handle
    // 1.打开文件
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }
    listAll->clear();
    // 2.导出所有行
    while(!file.atEnd())
    {   // 2.1.读取一行数据
        QByteArray line = file.readLine();
        QString str = QString::fromUtf8(line.data ());
        // 2.2.分割数据
        QStringList list=str.split("%%");
        QStringList list2;
        // 2.3.去掉前后空格
        for(int i=1;i<list.size();i++) // 这里不要第一个参数，因为是多余的分割出来的
        {
            list2.append(list.at(i).simplified());//去掉非识别字符
        }
        // 2.4.缓存数据
        listAll->append(list2);
    }
    file.close();
    // 到这里，所有数据都在listAll中了-------------------------------------
    return true;
}
// 将ListAll转为 dat文件 ,数据会保存到 dat中
bool ListAll2dat(QString datName,QList<QStringList> *listAll)
{
    // 4.往dat中添加数据
    QFile       file(datName); // 文件handle
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))// 打开文件
    {
        qDebug()<<" open dat fail!";
        return false;
    }
    QString str;
    for(int i=0;i<listAll->size();i++)
    {
        str.clear();
        for(int j=0;j<listAll->at(i).size();j++)
        {
            str += "%% ";   //第一个"%%"
            str += listAll->at(i).at(j).simplified();
            int spaceNum = (j+1)*DAT_CELL_MINIWIDTH - str.toLocal8Bit().size(); // 这个写法有对其的效果
            if(spaceNum>0)
            {
                str += QString("%1").arg("",spaceNum);
            }
        }
        str += "\n";   //补齐换行
        //Fdebug::mydebug()->debug_text(str); //打印每个单元格的内容
        file.write(str.toUtf8());
    }
    file.close();
    return true;
}
