#include "userhid.h"

userHid::userHid(int VID, int PID, char PORT)
{
    phid = 0;
    vid  = VID;
    pid  = PID;
    port = PORT;    // HID �豸�Ķ˿ںţ�Ĭ����0�������豸���ж��HID����
    qRegisterMetaType<QVector<char> >("QVector<char>");
}
// ��hid�豸
bool userHid::hidOpen()
{
    bool b;
    if(phid){CloseHandle(phid);phid=0;};//�رչ�ȥ�� handle
    b = open_hid(&phid, vid, pid);
    if(false == b){phid=0;}
    start();                // �����߳�
    return b;
}
// �ر�hid�豸
bool userHid::hidClose()
{
    if(phid){CloseHandle(phid);phid=0;};//�رչ�ȥ��handle
    terminate();                // �˳��߳�
    return true;
}
// ����usb����->ע�⣬���buff�ǻᱻ�޸ĵ�
bool userHid::hidSend(QVector<char> *buff)
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
bool userHid::hidRead(QVector<char> *buff)
{
    char rbuff[INPUT_MAX_LEN];//���ջ���
    ulong real_len;
    bool b;
    // û���ȴ��ǲ����ܶ������ݵ�
    if(0==phid || nullptr == buff)
    {
        return false;
    }
    //������
    b = read_hid(phid,rbuff,INPUT_MAX_LEN,&real_len);
    if(b)
    {
        uint index=0;
        buff->clear();
        while(index <= real_len)
        {
            if(0==index % (WRITE_PACK_LEN+1))// ȥ��usb�豸�Ķ˿ںţ���ÿ֡������ĵ�һ�����ݾ�����
            {
                index++;
                continue;
            }
            buff->append(rbuff[index++]);
        }
    }
    else
    {   //��ȡʧ�ܾ�Ҫ���´�hid
        hidOpen();
    }
    return b;
}
// ����->"AA....55"�Ѿ������õİ�
bool userHid::sendPack(QVector<char> *w)
{
    if(nullptr == w || w->size() < 8 )return false;

    // �����һ�����ݾ���Ϻ��ˣ��������Զ����Э������֡
    if(w->size()<=USB_FRAME_PARA_LEN)//��֡�����
    {
        w->insert(0,FRAME_NONE_SEG);
        w->insert(1,0x00);
    }
    else                           //��֡�����
    {
        int index=0;
        int frameCnt=0;
        w->insert(index,FRAME_FIRST_SEG);// ��һ֡
        w->insert(index+1,frameCnt++);
        index += 64;
        while (index+USB_FRAME_PARA_LEN < w->size())
        {
            w->insert(index,FRAME_MIDDLE_SEG);// �м�֡
            w->insert(index+1,frameCnt++);
            index += 64;
        }
        w->insert(index,FRAME_END_SEG);// ����֡
        w->insert(index+1,frameCnt);
    }
    // ��������ݾͲ����ɣ�����w���ˣ����Է���������
    return  hidSend(w);
}
// ����->������,���ȣ�����������ݣ�����
bool userHid::sendPack(const char control,const int datalen,const char command,const char num,const char contend,const char *param)
{
    if(nullptr == param || datalen < 3 || datalen > PACK_MAX_LEN)return false;
    // �ȼ�����Ҫ����֡
    QVector<char>w;
    w.reserve(PACK_MAX_LEN);
    w.append(PROTOCOL_FRAME_START_CODE);// ͷ��
    w.append(control);
    w.append(datalen/256);
    w.append(datalen%256);
    w.append(command);
    w.append(num);
    w.append(contend);
    int i;
    uint c=0;
    for(i=0;i<datalen-3;i++)
        w.append(*param+i);
    //����У���
    for(i=0;i<w.size();i++)
    {
        c+=w.at(i);
    }
    w.append(c%256);
    w.append(PROTOCOL_FRAME_STOP_CODE);// β��
    // �����һ�����ݾ���Ϻ��ˣ��������Զ����Э������֡
    if(w.size()<=USB_FRAME_PARA_LEN)//��֡�����
    {
       w.prepend(0x00);
       w.prepend(FRAME_NONE_SEG);
    }
    else                           //��֡�����
    {
        int index=0;
        int frameCnt=0;
        w.insert(index,FRAME_FIRST_SEG);// ��һ֡
        w.insert(index+1,frameCnt++);
        index += 64;
        while (index+USB_FRAME_PARA_LEN < w.size())
        {
            w.insert(index,FRAME_MIDDLE_SEG);// �м�֡
            w.insert(index+1,frameCnt++);
            index += 64;
        }
        w.insert(index,FRAME_END_SEG);// ����֡
        w.insert(index+1,frameCnt);
    }
    // ��������ݾͲ����ɣ�����w���ˣ����Է���������
    return  hidSend(&w);
}
// ��ȡ->"AA....55"�Ѿ������õİ�
// ����û�����ι滮��������signal�������źŰ�...
void userHid::pollingPack(void)
{
    bool b;
    QVector<char>R;
    // ���ڲ��õ���������ȡ������������һ�����еĶ��֡�������100ms�Ŵ��䵽
    // �����Ϳ�����Ϊ��һ���������ݣ��Ǿ��Ƕ���һ�����߶����
    // �����������һ�������İ����ͷ�����
    b = hidRead(&R);
    // û�ж������˳�
    if(false == b)return;
    // ���������ж���������������ϳ�����64��������
    if(R.size()%64)return ;
    int index = 0;
    int segNum = 0;
    QVector<char>pack;
    while(index<R.size())
    {
        switch(R.at(index++))
        {
            case FRAME_NONE_SEG  : // ���ֶ�
                index++;               // ȥ��num
                pack.clear();
                for(int j=0;j<62;j++)
                    pack<<R.at(index++);
                emit receive_pack(pack);
            break;
            case FRAME_FIRST_SEG :
                index++;               // ȥ��num
                segNum=0;
                pack.clear();
                for(int j=0;j<62;j++)
                    pack<<R.at(index++);
            break;
            case FRAME_MIDDLE_SEG:
                segNum++;
                if(R.at(index++) != segNum) // У��num
                {
                    index+=62;               // У���������
                }
                else
                {
                    for(int j=0;j<62;j++)
                        pack<<R.at(index++);
                }
            break;
            case FRAME_END_SEG   :
                segNum++;
                if(R.at(index++) != segNum) // У��num
                {
                    index+=62;               // У���������
                }
                else
                {
                    for(int j=0;j<62;j++)
                        pack<<R.at(index++);
                    emit receive_pack(pack);
                }
            break;
            default:

            break;
        }
    }
    return ;
}
// ���߳��в������еĺ���
void userHid::run(void)
{
    while(1)
    {
        pollingPack();     //  ��ѯ���հ�������signal����ʽ���ͳ�ȥ
        msleep(200);    //  ÿ200ms��ѯһ��usbHid
    }
}
