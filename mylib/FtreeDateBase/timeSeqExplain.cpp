/* 这个文件用于解析时序的规则
 * 时序的协议库在 timeSeq_TreeDb.dat 中，已经固定好
 * 时序协议的存放规则：
 * 主item放 1.关键字，2.解释内容
 * 次item放参数内容，参数个数就是次item的个数。（没有参数就没有子类）
 * 次item的内容：1.空，2.参数含义 3.参数类型，1，普通数字 2，字符串匹配数据，匹配对象在子类
 * 次次item的内容：1.空，2.参数的为匹配参数时的参数关键字，3.参数关键字解释
 * 次次次item依次类推
 *
*/
#include "timeSeqExplain.h"
#include <QFile>
#include<QDebug>
// timeSeq 是配置文件的固定名字
timeSeqExplain::timeSeqExplain(QWidget *parent):FtreeDabeBase(parent,"timeSeq")
{


}
// 协议解析
// 输入 strPack :原始的一行数据  ，比如     0 VU_PUMP -1 END
// 输出 strExplain :解析的数据
// 输出 strExplain :原始+解析的数据
// 解析失败返会false 成功true
bool timeSeqExplain::protocolExplain(const QByteArray *qbyPack,QByteArray *qbyExplain,QByteArray *qbyAll)
{
    // 0.填充数据
    qbyAll->clear();
    qbyAll->append(*qbyPack);
    // 0.去除多余空格
    QByteArray qby_deal;
    qby_deal=qbyPack->simplified();
    // 1.按空格分隔开
    QList<QByteArray> list;
    list.append(qby_deal.split(' '));
    // 2.没有END的，或者位置不对的，不解释
    if(2 > list.indexOf("END"))
    {
        return false;
    }
    // 4.查找关键字命令 - // 0->时间，1->关键字命令，2->参数。。。
    // 4.1.参数个数
    int argCount;
    argCount = list.indexOf("END")-2;
//    qDebug()<<argCount;
    // 4.1.时间参数
    double runTime=list.at(0).toDouble();
//    qDebug()<<runTime;2
    // 4.2.关键字参数 - 在库中的第0列
    QByteArray key=list.at(1);
    const QTreeWidgetItem *item;
    item = findKey(0,key,argCount);
    if(item == NULL)
    {

        // 抽出解析失败的关键字，添加到 explainFailstr 中
        if(explainFailKey.indexOf(key) == -1)
        {   // 原本库中没有的，就添加进来
            explainFailKey.append(key);
        }
        return false;
    }
    // 5.生成解释
    qbyExplain->clear();
    // 5.1.关键字解释
    qbyExplain->append("// zkp " + item->text(1).toLocal8Bit()+":");
    // 5.2.参数解释
    for(int i=0;i<argCount;i++)
    {
        const QTreeWidgetItem *itemChild;
        itemChild = item->child(i);
        if(itemChild == NULL)break;
        // 参数名称 ,0位置为空, 1.是参数名称，2是参数类型
        qbyExplain->append(" " + itemChild->text(1).toLocal8Bit() + "=");
        // 参数类型 -> 数字，直接相等
        if(itemChild->text(2) == "number")
        {
            qbyExplain->append(list.at(2+i));
        }
        // 字符匹配 -> 在子类中
        if(itemChild->text(2) == "match")
        {
            QString str = list.at(2+i);
            for(int j=0;j<itemChild->childCount();j++)
            {
                const QTreeWidgetItem *itemChildChild;
                itemChildChild = itemChild->child(j);
                // 字符匹配 -> 在子类中
                if(itemChildChild->text(1) == str)
                {
                    qbyExplain->append(itemChildChild->text(2).toLocal8Bit());
                }
            }
        }
    }

    // 6.原始+解释 = 合成数据
    QString strSpace;
    if(qbyPack->indexOf("END")<50)   // 只从END以后算起
    {
        strSpace = QString("%1").arg("",50-qbyPack->indexOf("END"));
    }
    qbyExplain->prepend(strSpace.toLatin1());//起到全局对齐的作用

    qbyAll->clear();
    qbyAll->append(*qbyPack);
    qbyAll->insert(qbyPack->indexOf("END")+3,*qbyExplain);

    return false;
}
// 文件协议解析
// 输入:文件路径+文件名
// 会在改目录下，生成 文件名+explain.txt 标志
bool timeSeqExplain::txtExplain(QString timeSeqName)
{
    QByteArrayList byteList;
    QByteArrayList byteList_explain;

    byteList.clear();
    // 1.将文件读取，放到 byteList 中
    QFile       file(timeSeqName); // 文件handle
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))return false;    // 打不开就失败
    while(!file.atEnd())
    {   // 读行数据
        QByteArray line = file.readLine();
        // 数据操作
        byteList.append(line);
    }
    file.close();
    // 2.将数据分行解析，放到byteList_explain 中
    byteList_explain.clear();
    explainFailKey.clear();
    for(int i=0;i<byteList.size();i++)
    {
        QByteArray qbyPack,qbyExplain,qbyAll;
        qbyPack = byteList.at(i);
        bool bret ;
        bret = protocolExplain(&qbyPack,&qbyExplain,&qbyAll);
        byteList_explain.append(qbyAll);
    }
    // 3.将文件放回原位置+_explain
    // 3.1.修改文件名
    int index = timeSeqName.indexOf(".txt");
    if(index == -1)return false;
    timeSeqName.insert(index,"_explain");
    // 3.2.打开文件
    file.setFileName(timeSeqName); // 文件handle
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))return false;    // 打不开就失败
    // 3.3.写入文件
    for(int i=0;i<byteList_explain.size();i++)
    {
        file.write(byteList_explain.at(i));
    }
    file.close();
    return true;
}

// 获取解析失败的关键字信息
QStringList timeSeqExplain::getExplainFailKey()
{
    return  explainFailKey;

}

