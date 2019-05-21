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
    void canRevErr(uint errCode);   // 接收出错信号
    void canRevPack(char destID,char srcID,QByteArray qby);// 接收到完整的数据帧
private:
    QByteArray  canDate   ; // 保持的数据
    char        canDestID    ; // 目的ID
    char        canSrcID     ; // 源ID
    uint        canCurLen ; // 当前的数据长度
    uint        canNeedLen; // 需要的数据长度
    uint        canSign      ; // 接收标志，0=空闲，1=正在接收中
};

#endif // CANDUMPEXPLAIN_H
