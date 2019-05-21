#ifndef USERHID_H
#define USERHID_H

#include "myhid.h"
#include <QVector>
#include <QThread>

class userHid : public QThread
{
    Q_OBJECT
public:
    userHid(int VID, int PID , char PORT=0);
    bool hidOpen();
    bool hidClose();
    bool hidSend(QVector<char> *buff);   // 发送usb数据

    // 发送->控制码,长度，命令，对象，内容，参数
    bool sendPack(const char control,const int datalen,const char command,const char num,const char contend,const char *param);
    bool sendPack(QVector<char> *w);
signals:
    void receive_pack(QVector<char> r);         //  接收到数据，就发送信号
protected:
    HANDLE  phid;       // 定义的用于HID的handle
    int     vid;
    int     pid;
    char    port;
private:
    void run(void);     // 线程的查询
    void pollingPack(void);// 轮询地查阅数据包
    bool hidRead(QVector<char> *buff);        // 读取usb数据
};
//分段标志定义
typedef enum
{
    FRAME_NONE_SEG   = (char)0x00,  // 不分段
    FRAME_FIRST_SEG  = (char)0x40,  // 第一个分段
    FRAME_MIDDLE_SEG = (char)0x80,  // 中间分段
    FRAME_END_SEG    = (char)0xC0,  // 最后分段
} frame_seg_e;

// 协议帧起始码
#define PROTOCOL_FRAME_START_CODE               (char)(0xAA)
// 协议帧停止码
#define PROTOCOL_FRAME_STOP_CODE                (char)(0x55)
// usb帧数据的参数长度
#define USB_FRAME_PARA_LEN                      (62)
// 自定义包长度，还没想好怎么用
#define PACK_MAX_LEN                            1000

#endif // USERHID_H
