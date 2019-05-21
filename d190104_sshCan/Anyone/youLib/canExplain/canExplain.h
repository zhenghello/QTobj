#ifndef CANEXPLAIN_H
#define CANEXPLAIN_H

#include <QObject>
#include "ftreeDabeBase.h"

//#define ID＿CODE_FLAG   "ID对象"   // excel规则中，ID码的标识符
//#define ID＿CODE_COLUMN 0x00      // excel规则中，ID码的列位置
//#define ID＿NAME_COLUMN 0x01      // excel规则中，ID码的解释的位置

//#define CONTROL＿CODE_FLAG   "控制码类"    // excel规则中，控制码的标识符
//#define CONTROL＿CODE_COLUMN 0x00        // excel规则中，控制码的列位置
//#define CONTROL＿NAME_COLUMN 0x01        // excel规则中，控制码的解释的位置

//#define ORDER＿CODE_FLAG   "命令码类"  // excel规则中，命令码的标识符
//#define ORDER＿CODE_COLUMN 0x00      // excel规则中，命令码的列位置
//#define ORDER＿NAME_COLUMN 0x01      // excel规则中，命令码的解释的位置

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
    void canExplainFinish(QString ogl,QString exp);     // 解释好后的数据发送出去
    void canRevErr(int errCode);                        // 接收出错信号

   void  candumpIsDown(void);                           // 发送candump挂断的信号
private:
    QTreeWidget     *mTree;         // 主要的地址
    QTreeWidgetItem *idAddr;        // 命令的解释地址
    QTreeWidgetItem *ctrCodeAddr;   // 控制码的解释地址
    QTreeWidgetItem *orderCodeAddr; // 命令码的解释地址
    QTreeWidgetItem *errCodeAddr;   // 错误码的解释地址

    QStringList  canDate      ; // 保持的数据
    uchar        canDestID    ; // 目的ID
    uchar        canSrcID     ; // 源ID
    uint         canCurLen    ; // 当前的数据长度
    uint         canNeedLen   ; // 需要的数据长度
    uint         canSign      ; // 接收标志，0=空闲，1=正在接收中
};

#endif // CANEXPLAIN_H
