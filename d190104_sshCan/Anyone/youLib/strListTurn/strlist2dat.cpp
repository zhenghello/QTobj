/* ��ע��
 * dat�ļ��У���Ԫ���� %% ��������ȡʱ���Զ�ȥ��ǰ��ո�
 *
*/
#include "strlist2dat.h"
#include <QFile>
#include <QDebug>

// ��dat�ļ�תΪlist,���ݻᱣ�浽 listAll��
bool dat2ListAll(QString datName,QList<QStringList> *listAll)
{
    QFile       file(datName); // �ļ�handle
    // 1.���ļ�
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }
    listAll->clear();
    // 2.����������
    while(!file.atEnd())
    {   // 2.1.��ȡһ������
        QByteArray line = file.readLine();
        QString str = QString::fromUtf8(line.data ());
        // 2.2.�ָ�����
        QStringList list=str.split("%%");
        QStringList list2;
        // 2.3.ȥ��ǰ��ո�
        for(int i=1;i<list.size();i++) // ���ﲻҪ��һ����������Ϊ�Ƕ���ķָ������
        {
            list2.append(list.at(i).simplified());//ȥ����ʶ���ַ�
        }
        // 2.4.��������
        listAll->append(list2);
    }
    file.close();
    // ������������ݶ���listAll����-------------------------------------
    return true;
}
// ��ListAllתΪ dat�ļ� ,���ݻᱣ�浽 dat��
bool ListAll2dat(QString datName,QList<QStringList> *listAll)
{
    // 4.��dat���������
    QFile       file(datName); // �ļ�handle
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))// ���ļ�
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
            str += "%% ";   //��һ��"%%"
            str += listAll->at(i).at(j).simplified();
            int spaceNum = (j+1)*DAT_CELL_MINIWIDTH - str.toLocal8Bit().size(); // ���д���ж����Ч��
            if(spaceNum>0)
            {
                str += QString("%1").arg("",spaceNum);
            }
        }
        str += "\n";   //���뻻��
        //Fdebug::mydebug()->debug_text(str); //��ӡÿ����Ԫ�������
        file.write(str.toUtf8());
    }
    file.close();
    return true;
}
