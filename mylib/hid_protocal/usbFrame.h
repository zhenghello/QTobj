#ifndef USBFRAME_H
#define USBFRAME_H

#include "myhid.h"
#include <QVector>
#include <QThread>
#include "usb_user_commonres.h"

class usbFrame : public QThread
{
    Q_OBJECT
public:
    usbFrame(int VID=0x6666, int PID=0x6666 , char PORT=0);
    bool hidOpen();
    bool hidClose();
    bool hidSend(const QVector<char> send);   // 发送usb数据
    bool frameTx(const QVector<char> send);   // 发送usb数据
    bool hidIsConnect(void);
    bool hidState(void);
signals:
    void frameRx(QVector<char> r);        //  接收到帧数据，就发送信号
protected:
    HANDLE  phid;       // 定义的用于HID的handle
    int     vid;
    int     pid;
    char    port;
private:
    void run(void);     // 线程的查询
    bool hidRead(void);        // 读取usb数据
};
#endif // USERHID_H
