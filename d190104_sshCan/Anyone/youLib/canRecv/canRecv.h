#ifndef CANRECV_H
#define CANRECV_H

#include <QWidget>
#include "ftreeDabeBase.h"
#include "FsshGui.h"
#include "fdebug.h"
#include "fcanshow.h"

namespace Ui {class canRecv;}


// 一个can包合成的过程数据，根据不同的源ID和目的ID接收，目的是防止接收的时候can被乱序。
#define CAN_PACK_MAX_SIZE   5   // can包的数据个数
class canPack_t
{
public:
    QStringList     date      ;  // 保持的数据
    uchar           destID    ;  // 目的ID
    uchar           srcID     ;  // 源ID
    uint            curLen    ;  // 当前的数据长度
    uint            needLen   ;  // 需要的数据长度
    uint            sign      ;  // 接收标志，0=空闲，1=正在接收中
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
//    void canExplainFinish(QString ogl,QString exp,QColor col);    // 解释好后的数据发送出去
    void canRevErr(int errCode);                        // 接收出错信号
    void candumpIsDown(void);                           // 发送candump挂断的信号

private slots:
    void initTreeDate(void);        // 重新初始化Tree数据
    void sendCanDumpMsg();          // 延迟发送“candump”命令

    void showSshOpenMsg(){myShow->setTextStyle(QString("canRecv SSH is Open->")+windowTitle(),Qt::green,Qt::white,16);}
    void showSshCloseMsg(){myShow->setTextStyle(QString("canRecv SSH is Close->")+windowTitle(),Qt::red,Qt::white,16);}

    void on_button_open_clicked();  // // 点击 “启动candump连接”
    void on_checkBox_filter_clicked();

private:
    Ui::canRecv *ui;
    FsshGui         *sshPort;       // SSH端口
    FtreeDabeBase   *treeOredr;     // 树形命令框
    FcanShow        *canFilter;     // can过滤器
    void dat_config_save(void);
    void dat_config_load(void);

    QTreeWidget     *mTree;         // 主要的地址
    QTreeWidgetItem *idAddr;        // 命令的解释地址
    QTreeWidgetItem *ctrCodeAddr;   // 控制码的解释地址
    QTreeWidgetItem *orderCodeAddr; // 命令码的解释地址
    QTreeWidgetItem *errCodeAddr;   // 错误码的解释地址

    canPack_t       canPackRec[CAN_PACK_MAX_SIZE];    // can包的数据，就先开辟20个缓存，会根据目的和源ID一致放在一起
//    QStringList     canDate      ;  // 保持的数据
//    uchar           canDestID    ;  // 目的ID
//    uchar           canSrcID     ;  // 源ID
//    uint            canCurLen    ;  // 当前的数据长度
//    uint            canNeedLen   ;  // 需要的数据长度
//    uint            canSign      ;  // 接收标志，0=空闲，1=正在接收中

    uint            reQuestNum   ;  // 请求帧个数

};

#endif // CANRECV_H
