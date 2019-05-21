/*  �����������HID �Ĵ򿪣��رգ���ȡ���ͷ���
    ��Ϊwindows��APIû���жϵ�ԭ���������������Զ�ȡ�����̵߳���
    ���������Ժ󣬻���frameRx���ź����ⷢ�͡�
*/




#include "userhid2.h"

userHid2::userHid2(int VID, int PID, char PORT)
{
    phid = 0;
    vid  = VID;
    pid  = PID;
    port = PORT;    // HID �豸�Ķ˿ںţ�Ĭ����0�������豸���ж��HID����
    qRegisterMetaType<QVector<char> >("QVector<char>");
}
// �ж�hid�豸�Ƿ�����
bool userHid2::hidState(void)
{
    if(nullptr == phid)
        return FALSE;
    else
        return TRUE;
}
// �ж�hid�豸�Ƿ�����
bool userHid2::hidIsConnect(void)
{
    return hid_is_connect(phid,vid,pid);
}
// ��hid�豸
bool userHid2::hidOpen()
{
    bool b;
    if(phid){CloseHandle(phid);phid=0;};//�رչ�ȥ�� handle
    b = open_hid(&phid, vid, pid);
    if(false == b){phid=0;}
    start();                // �����߳�
    hid_is_connect(phid,vid,pid);
    return b;
}
// �ر�hid�豸
bool userHid2::hidClose()
{
    if(phid){CloseHandle(phid);phid=0;};//�رչ�ȥ��handle
    terminate();                // �˳��߳�
    return true;
}
// �ض��������
bool userHid2::frameTx(QVector<char> *buff)
{
    return hidSend(buff);
}
// ����usb����->ע�⣬���buff�ǻᱻ�޸ĵ�
bool userHid2::hidSend(QVector<char> *buff)
{
    bool b = false;
    // �������
    if(nullptr == buff || buff->size()==0)
    {
        return false;
    }
    // û�д򿪾ͳ��Դ�hid
    if(0==phid)
    {
        b=hidOpen();
        if(false == b)return false;
    }
    // �����ݷְ�����
    buff->insert(0,port);        // ͷ������HID�˿ں�
    while(1)
    {
        b = write_hid(phid,buff->data());// usb д������->65��
        if(b==false)return false;
        if(buff->size() > WRITE_PACK_LEN+1)        //����û������
        {
            // ȥ��64���������Ѿ���������
            buff->remove(1,WRITE_PACK_LEN);
        }
        else
        {
            // �Ѿ��������
            break;
        }
    }
    return b;
}
// ��ȡusb����
// ����û������buff��У�飬���� buff����Ϊ INPUT_MAX_LEN �������
bool userHid2::hidRead(void)
{
    char rbuff[65];//���ջ���
    ulong real_len;
    bool b;
    QVector<char>frame;

    // û���ȴ��ǲ����ܶ������ݵ�
    if(0==phid)
    {
        return false;
    }
    //������
    b = read_hid(phid,rbuff,65,&real_len);
    if(b)
    {
        for(int i=1;i<65;i++)
        {
            frame.append(rbuff[i]);
        }
        emit frameRx(frame);
    }
    return b;
}

// ���߳��в������еĺ���
void userHid2::run(void)
{

    while(1)
    {
        if(hidRead()==FALSE)    //  ��ѯ���հ�������signal����ʽ���ͳ�ȥ
        {
            msleep(200);         //  mû�����ݵĻ�����ÿ200ms��ѯһ��usbHid
        }            
    }
}
