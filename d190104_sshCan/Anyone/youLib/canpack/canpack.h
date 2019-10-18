#ifndef CANPACK_H
#define CANPACK_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>

#include "errtable.h"
#include "command.h"

class canPack : public QTableWidget
{
    Q_OBJECT
public:
    canPack(QWidget *parent = 0,int argNum=0);
    void setCanPack_OrderArg(QStringList qsl);       // 设置单元格_命令和参数
    void setCanPack_ctlCode(QString str);            // 设置单元格_控制码
    void sendCanPack(void);                          // 发送单元格
    void table_init(int argNum);
    void setCanPack_IdCode(QString str1,QString str2); // 设置收发ID区

private:
    void composeStr(void);                          // 合成操作

private slots:
    void table_pressed(const QModelIndex &index);   // 按下操作
    void table_cellChanged(int row, int column);    // 单元格改变操作

signals:
    void send_can_pack(QString);
};

#endif // CANPACK_H
