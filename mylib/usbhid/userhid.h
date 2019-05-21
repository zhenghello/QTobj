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
    bool hidSend(QVector<char> *buff);   // ����usb����

    // ����->������,���ȣ�����������ݣ�����
    bool sendPack(const char control,const int datalen,const char command,const char num,const char contend,const char *param);
    bool sendPack(QVector<char> *w);
signals:
    void receive_pack(QVector<char> r);         //  ���յ����ݣ��ͷ����ź�
protected:
    HANDLE  phid;       // ���������HID��handle
    int     vid;
    int     pid;
    char    port;
private:
    void run(void);     // �̵߳Ĳ�ѯ
    void pollingPack(void);// ��ѯ�ز������ݰ�
    bool hidRead(QVector<char> *buff);        // ��ȡusb����
};
//�ֶα�־����
typedef enum
{
    FRAME_NONE_SEG   = (char)0x00,  // ���ֶ�
    FRAME_FIRST_SEG  = (char)0x40,  // ��һ���ֶ�
    FRAME_MIDDLE_SEG = (char)0x80,  // �м�ֶ�
    FRAME_END_SEG    = (char)0xC0,  // ���ֶ�
} frame_seg_e;

// Э��֡��ʼ��
#define PROTOCOL_FRAME_START_CODE               (char)(0xAA)
// Э��ֹ֡ͣ��
#define PROTOCOL_FRAME_STOP_CODE                (char)(0x55)
// usb֡���ݵĲ�������
#define USB_FRAME_PARA_LEN                      (62)
// �Զ�������ȣ���û�����ô��
#define PACK_MAX_LEN                            1000

#endif // USERHID_H
