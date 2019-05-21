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
    bool hidSend(const QVector<char> send);   // ����usb����
    bool frameTx(const QVector<char> send);   // ����usb����
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
#endif // USERHID_H
