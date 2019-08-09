/* ����ļ����ڽ���ʱ��Ĺ���
 * ʱ���Э����� timeSeq_TreeDb.dat �У��Ѿ��̶���
 * ʱ��Э��Ĵ�Ź���
 * ��item�� 1.�ؼ��֣�2.��������
 * ��item�Ų������ݣ������������Ǵ�item�ĸ�������û�в�����û�����ࣩ
 * ��item�����ݣ�1.�գ�2.�������� 3.�������ͣ�1����ͨ���� 2���ַ���ƥ�����ݣ�ƥ�����������
 * �δ�item�����ݣ�1.�գ�2.������Ϊƥ�����ʱ�Ĳ����ؼ��֣�3.�����ؼ��ֽ���
 * �δδ�item��������
 *
*/
#include "timeSeqExplain.h"
#include <QFile>
#include<QDebug>
// timeSeq �������ļ��Ĺ̶�����
timeSeqExplain::timeSeqExplain(QWidget *parent):FtreeDabeBase(parent,"timeSeq")
{


}
// Э�����
// ���� strPack :ԭʼ��һ������  ������     0 VU_PUMP -1 END
// ��� strExplain :����������
// ��� strExplain :ԭʼ+����������
// ����ʧ�ܷ���false �ɹ�true
bool timeSeqExplain::protocolExplain(const QByteArray *qbyPack,QByteArray *qbyExplain,QByteArray *qbyAll)
{
    // 0.�������
    qbyAll->clear();
    qbyAll->append(*qbyPack);
    // 0.ȥ������ո�
    QByteArray qby_deal;
    qby_deal=qbyPack->simplified();
    // 1.���ո�ָ���
    QList<QByteArray> list;
    list.append(qby_deal.split(' '));
    // 2.û��END�ģ�����λ�ò��Եģ�������
    if(2 > list.indexOf("END"))
    {
        return false;
    }
    // 4.���ҹؼ������� - // 0->ʱ�䣬1->�ؼ������2->����������
    // 4.1.��������
    int argCount;
    argCount = list.indexOf("END")-2;
//    qDebug()<<argCount;
    // 4.1.ʱ�����
    double runTime=list.at(0).toDouble();
//    qDebug()<<runTime;2
    // 4.2.�ؼ��ֲ��� - �ڿ��еĵ�0��
    QByteArray key=list.at(1);
    const QTreeWidgetItem *item;
    item = findKey(0,key,argCount);
    if(item == NULL)
    {

        // �������ʧ�ܵĹؼ��֣���ӵ� explainFailstr ��
        if(explainFailKey.indexOf(key) == -1)
        {   // ԭ������û�еģ�����ӽ���
            explainFailKey.append(key);
        }
        return false;
    }
    // 5.���ɽ���
    qbyExplain->clear();
    // 5.1.�ؼ��ֽ���
    qbyExplain->append("// zkp " + item->text(1).toLocal8Bit()+":");
    // 5.2.��������
    for(int i=0;i<argCount;i++)
    {
        const QTreeWidgetItem *itemChild;
        itemChild = item->child(i);
        if(itemChild == NULL)break;
        // �������� ,0λ��Ϊ��, 1.�ǲ������ƣ�2�ǲ�������
        qbyExplain->append(" " + itemChild->text(1).toLocal8Bit() + "=");
        // �������� -> ���֣�ֱ�����
        if(itemChild->text(2) == "number")
        {
            qbyExplain->append(list.at(2+i));
        }
        // �ַ�ƥ�� -> ��������
        if(itemChild->text(2) == "match")
        {
            QString str = list.at(2+i);
            for(int j=0;j<itemChild->childCount();j++)
            {
                const QTreeWidgetItem *itemChildChild;
                itemChildChild = itemChild->child(j);
                // �ַ�ƥ�� -> ��������
                if(itemChildChild->text(1) == str)
                {
                    qbyExplain->append(itemChildChild->text(2).toLocal8Bit());
                }
            }
        }
    }

    // 6.ԭʼ+���� = �ϳ�����
    QString strSpace;
    if(qbyPack->indexOf("END")<50)   // ֻ��END�Ժ�����
    {
        strSpace = QString("%1").arg("",50-qbyPack->indexOf("END"));
    }
    qbyExplain->prepend(strSpace.toLatin1());//��ȫ�ֶ��������

    qbyAll->clear();
    qbyAll->append(*qbyPack);
    qbyAll->insert(qbyPack->indexOf("END")+3,*qbyExplain);

    return false;
}
// �ļ�Э�����
// ����:�ļ�·��+�ļ���
// ���ڸ�Ŀ¼�£����� �ļ���+explain.txt ��־
bool timeSeqExplain::txtExplain(QString timeSeqName)
{
    QByteArrayList byteList;
    QByteArrayList byteList_explain;

    byteList.clear();
    // 1.���ļ���ȡ���ŵ� byteList ��
    QFile       file(timeSeqName); // �ļ�handle
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))return false;    // �򲻿���ʧ��
    while(!file.atEnd())
    {   // ��������
        QByteArray line = file.readLine();
        // ���ݲ���
        byteList.append(line);
    }
    file.close();
    // 2.�����ݷ��н������ŵ�byteList_explain ��
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
    // 3.���ļ��Ż�ԭλ��+_explain
    // 3.1.�޸��ļ���
    int index = timeSeqName.indexOf(".txt");
    if(index == -1)return false;
    timeSeqName.insert(index,"_explain");
    // 3.2.���ļ�
    file.setFileName(timeSeqName); // �ļ�handle
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))return false;    // �򲻿���ʧ��
    // 3.3.д���ļ�
    for(int i=0;i<byteList_explain.size();i++)
    {
        file.write(byteList_explain.at(i));
    }
    file.close();
    return true;
}

// ��ȡ����ʧ�ܵĹؼ�����Ϣ
QStringList timeSeqExplain::getExplainFailKey()
{
    return  explainFailKey;

}

