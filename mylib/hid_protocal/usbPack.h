#ifndef USBPACK_H
#define USBPACK_H

#include "usbFrame.h"

class usbPack : public usbFrame
{
    Q_OBJECT
public:
    usbPack(int VID, int PID);
    void packTx(QVector<char> pack);
    void pack2frame(QVector<char> pack);
protected slots:
    void frame2pack(QVector<char> frame);
signals:
    void packRx(QVector<char>);
private:

};

//// 协议帧起始码
//#define PROTOCOL_FRAME_START_CODE               (char)(0xAA)
//// 协议帧停止码
//#define PROTOCOL_FRAME_STOP_CODE                (char)(0x55)
//// usb帧数据的参数长度
//#define USB_FRAME_PARA_LEN                      (62)
//// 自定义包长度，还没想好怎么用
//#define PACK_MAX_LEN                            1000

#endif // USERHID_H
