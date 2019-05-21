#ifndef USERHID2_H
#define USERHID2_H

#include "myhid.h"
#include <QVector>
#include <QThread>

class userHid2 : public QThread
{
    Q_OBJECT
public:
    userHid2(int VID, int PID , char PORT=0);
    bool hidOpen();
    bool hidClose();
    bool hidSend(QVector<char> *buff);   // ����usb����
    bool frameTx(QVector<char> *buff);   // ����usb����
    bool hidIsConnect(void);
    bool hidState(void);
signals:
    void frameRx(QVector<char> r);        //  ���յ�֡���ݣ��ͷ����ź�
protected:
    HANDLE  phid;       // ���������HID��handle
    int     vid;
    int     pid;
    char    port;
private:
    void run(void);     // �̵߳Ĳ�ѯ
    bool hidRead(void);        // ��ȡusb����
};
////�ֶα�־����
//typedef enum
//{
//    FRAME_NONE_SEG   = (char)0x00,  // ���ֶ�
//    FRAME_FIRST_SEG  = (char)0x40,  // ��һ���ֶ�
//    FRAME_MIDDLE_SEG = (char)0x80,  // �м�ֶ�
//    FRAME_END_SEG    = (char)0xC0,  // ���ֶ�
//} frame_seg_e;

//// Э��֡��ʼ��
//#define PROTOCOL_FRAME_START_CODE               (char)(0xAA)
//// Э��ֹ֡ͣ��
//#define PROTOCOL_FRAME_STOP_CODE                (char)(0x55)
//// usb֡���ݵĲ�������
//#define USB_FRAME_PARA_LEN                      (62)
//// �Զ�������ȣ���û�����ô��
//#define PACK_MAX_LEN                            1000

#endif // USERHID_H
