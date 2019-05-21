#ifndef CANDUMPEXPLAIN_H
#define CANDUMPEXPLAIN_H

#include <QObject>
#include <QDebug>
class candumpExplain :public QObject
{
    Q_OBJECT
public:
    candumpExplain();
    bool explain(QByteArray qby);
signals:
    void canRevErr(uint errCode);   // ���ճ����ź�
    void canRevPack(char destID,char srcID,QByteArray qby);// ���յ�����������֡
private:
    QByteArray  canDate   ; // ���ֵ�����
    char        canDestID    ; // Ŀ��ID
    char        canSrcID     ; // ԴID
    uint        canCurLen ; // ��ǰ�����ݳ���
    uint        canNeedLen; // ��Ҫ�����ݳ���
    uint        canSign      ; // ���ձ�־��0=���У�1=���ڽ�����
};

#endif // CANDUMPEXPLAIN_H
