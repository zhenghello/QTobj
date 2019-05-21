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

//// Э��֡��ʼ��
//#define PROTOCOL_FRAME_START_CODE               (char)(0xAA)
//// Э��ֹ֡ͣ��
//#define PROTOCOL_FRAME_STOP_CODE                (char)(0x55)
//// usb֡���ݵĲ�������
//#define USB_FRAME_PARA_LEN                      (62)
//// �Զ�������ȣ���û�����ô��
//#define PACK_MAX_LEN                            1000

#endif // USERHID_H
