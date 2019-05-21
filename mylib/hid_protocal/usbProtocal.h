#ifndef USBFRAME_H
#define USBFRAME_H

#include "myhid.h"
#include <QVector>
#include <QThread>

class usbFrame : public QThread
{
    Q_OBJECT
public:
    usbFrame(int VID, int PID , char PORT=0);
    bool hidOpen();
    bool hidClose();
    bool hidSend(QVector<char> *buff);   // 发送usb数据
    bool frameTx(QVector<char> *buff);   // 发送usb数据
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
////分段标志定义
//typedef enum
//{
//    FRAME_NONE_SEG   = (char)0x00,  // 不分段
//    FRAME_FIRST_SEG  = (char)0x40,  // 第一个分段
//    FRAME_MIDDLE_SEG = (char)0x80,  // 中间分段
//    FRAME_END_SEG    = (char)0xC0,  // 最后分段
//} frame_seg_e;

//// 协议帧起始码
//#define PROTOCOL_FRAME_START_CODE               (char)(0xAA)
//// 协议帧停止码
//#define PROTOCOL_FRAME_STOP_CODE                (char)(0x55)
//// usb帧数据的参数长度
//#define USB_FRAME_PARA_LEN                      (62)
//// 自定义包长度，还没想好怎么用
//#define PACK_MAX_LEN                            1000

#endif // USERHID_H
