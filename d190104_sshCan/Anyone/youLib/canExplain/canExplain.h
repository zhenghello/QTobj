#ifndef CANEXPLAIN_H
#define CANEXPLAIN_H

#include <QObject>
#include "ftreeDabeBase.h"

//#define ID��CODE_FLAG   "ID����"   // excel�����У�ID��ı�ʶ��
//#define ID��CODE_COLUMN 0x00      // excel�����У�ID�����λ��
//#define ID��NAME_COLUMN 0x01      // excel�����У�ID��Ľ��͵�λ��

//#define CONTROL��CODE_FLAG   "��������"    // excel�����У�������ı�ʶ��
//#define CONTROL��CODE_COLUMN 0x00        // excel�����У����������λ��
//#define CONTROL��NAME_COLUMN 0x01        // excel�����У�������Ľ��͵�λ��

//#define ORDER��CODE_FLAG   "��������"  // excel�����У�������ı�ʶ��
//#define ORDER��CODE_COLUMN 0x00      // excel�����У����������λ��
//#define ORDER��NAME_COLUMN 0x01      // excel�����У�������Ľ��͵�λ��

class canExplain : public FtreeDabeBase
{
    Q_OBJECT
public:
    canExplain(QWidget *parent = 0);
    ~canExplain();

public slots:
    bool explain(QString str);
    void translate(char destID, char srcID, QStringList strList);
signals:
    void canExplainFinish(QString ogl,QString exp);     // ���ͺú�����ݷ��ͳ�ȥ
    void canRevErr(int errCode);                        // ���ճ����ź�

   void  candumpIsDown(void);                           // ����candump�Ҷϵ��ź�
private:
    QTreeWidget     *mTree;         // ��Ҫ�ĵ�ַ
    QTreeWidgetItem *idAddr;        // ����Ľ��͵�ַ
    QTreeWidgetItem *ctrCodeAddr;   // ������Ľ��͵�ַ
    QTreeWidgetItem *orderCodeAddr; // ������Ľ��͵�ַ
    QTreeWidgetItem *errCodeAddr;   // ������Ľ��͵�ַ

    QStringList  canDate      ; // ���ֵ�����
    uchar        canDestID    ; // Ŀ��ID
    uchar        canSrcID     ; // ԴID
    uint         canCurLen    ; // ��ǰ�����ݳ���
    uint         canNeedLen   ; // ��Ҫ�����ݳ���
    uint         canSign      ; // ���ձ�־��0=���У�1=���ڽ�����
};

#endif // CANEXPLAIN_H
