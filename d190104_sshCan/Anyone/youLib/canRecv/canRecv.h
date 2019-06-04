#ifndef CANRECV_H
#define CANRECV_H

#include <QWidget>
#include "ftreeDabeBase.h"
#include "FsshGui.h"
#include "fdebug.h"
#include "fcanshow.h"

namespace Ui {class canRecv;}


// һ��can���ϳɵĹ������ݣ����ݲ�ͬ��ԴID��Ŀ��ID���գ�Ŀ���Ƿ�ֹ���յ�ʱ��can������
#define CAN_PACK_MAX_SIZE   5   // can�������ݸ���
class canPack_t
{
public:
    QStringList     date      ;  // ���ֵ�����
    uchar           destID    ;  // Ŀ��ID
    uchar           srcID     ;  // ԴID
    uint            curLen    ;  // ��ǰ�����ݳ���
    uint            needLen   ;  // ��Ҫ�����ݳ���
    uint            sign      ;  // ���ձ�־��0=���У�1=���ڽ�����
};

class canRecv : public QWidget
{
    Q_OBJECT

public:
    explicit canRecv(QWidget *parent = 0, QString titleName = "canRecvNoTitleName");
    ~canRecv();

public slots:
    void translate(const QStringList strList);  // strList = canDate
    bool explain(QString str);
    void openSsh()              {on_button_open_clicked();  }
    void closeSsh()             {sshPort->closeSsh();       }
    bool isConnected()          {return sshPort->isConnected();}
    void setSshIP(QString str)  {sshPort->setSshIP(str);   }
    void clear()                {sshPort->clear();canFilter->clear();}
signals:
//    void canExplainFinish(QString ogl,QString exp,QColor col);    // ���ͺú�����ݷ��ͳ�ȥ
    void canRevErr(int errCode);                        // ���ճ����ź�
    void candumpIsDown(void);                           // ����candump�Ҷϵ��ź�

private slots:
    void initTreeDate(void);        // ���³�ʼ��Tree����
    void sendCanDumpMsg();          // �ӳٷ��͡�candump������

    void showSshOpenMsg(){myShow->setTextStyle(QString("canRecv SSH is Open->")+windowTitle(),Qt::green,Qt::white,16);}
    void showSshCloseMsg(){myShow->setTextStyle(QString("canRecv SSH is Close->")+windowTitle(),Qt::red,Qt::white,16);}

    void on_button_open_clicked();  // // ��� ������candump���ӡ�
    void on_checkBox_filter_clicked();

private:
    Ui::canRecv *ui;
    FsshGui         *sshPort;       // SSH�˿�
    FtreeDabeBase   *treeOredr;     // ���������
    FcanShow        *canFilter;     // can������
    void dat_config_save(void);
    void dat_config_load(void);

    QTreeWidget     *mTree;         // ��Ҫ�ĵ�ַ
    QTreeWidgetItem *idAddr;        // ����Ľ��͵�ַ
    QTreeWidgetItem *ctrCodeAddr;   // ������Ľ��͵�ַ
    QTreeWidgetItem *orderCodeAddr; // ������Ľ��͵�ַ
    QTreeWidgetItem *errCodeAddr;   // ������Ľ��͵�ַ

    canPack_t       canPackRec[CAN_PACK_MAX_SIZE];    // can�������ݣ����ȿ���20�����棬�����Ŀ�ĺ�ԴIDһ�·���һ��
//    QStringList     canDate      ;  // ���ֵ�����
//    uchar           canDestID    ;  // Ŀ��ID
//    uchar           canSrcID     ;  // ԴID
//    uint            canCurLen    ;  // ��ǰ�����ݳ���
//    uint            canNeedLen   ;  // ��Ҫ�����ݳ���
//    uint            canSign      ;  // ���ձ�־��0=���У�1=���ڽ�����

    uint            reQuestNum   ;  // ����֡����

};

#endif // CANRECV_H
