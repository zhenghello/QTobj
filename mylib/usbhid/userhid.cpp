#include "userhid.h"

userHid::userHid(int VID, int PID, char PORT)
{
    phid = 0;
    vid  = VID;
    pid  = PID;
    port = PORT;    // HID 设备的端口号，默认是0，除非设备中有多个HID对象
    qRegisterMetaType<QVector<char> >("QVector<char>");
}
// 打开hid设备
bool userHid::hidOpen()
{
    bool b;
    if(phid){CloseHandle(phid);phid=0;};//关闭过去的 handle
    b = open_hid(&phid, vid, pid);
    if(false == b){phid=0;}
    start();                // 启动线程
    return b;
}
// 关闭hid设备
bool userHid::hidClose()
{
    if(phid){CloseHandle(phid);phid=0;};//关闭过去的handle
    terminate();                // 退出线程
    return true;
}
// 发送usb数据->注意，这个buff是会被修改的
bool userHid::hidSend(QVector<char> *buff)
{
    bool b = false;
    // 输入错误
    if(nullptr == buff || buff->size()==0)
    {
        return false;
    }
    // 没有打开就尝试打开hid
    if(0==phid)
    {
        b=hidOpen();
        if(false == b)return false;
    }
    // 把数据分包发送
    buff->insert(0,port);        // 头部插入HID端口号
    while(1)
    {
        b = write_hid(phid,buff->data());// usb 写入数据->65个
        if(b==false)return false;
        if(buff->size() > WRITE_PACK_LEN+1)        //还有没发送完
        {
            // 去掉64个，它们已经被发送了
            buff->remove(1,WRITE_PACK_LEN);
        }
        else
        {
            // 已经发生完毕
            break;
        }
    }
    return b;
}
// 读取usb数据
// 这里没有设置buff的校验，所以 buff保险为 INPUT_MAX_LEN 长度最好
bool userHid::hidRead(QVector<char> *buff)
{
    char rbuff[INPUT_MAX_LEN];//接收缓冲
    ulong real_len;
    bool b;
    // 没有先打开是不可能读到数据的
    if(0==phid || nullptr == buff)
    {
        return false;
    }
    //读操作
    b = read_hid(phid,rbuff,INPUT_MAX_LEN,&real_len);
    if(b)
    {
        uint index=0;
        buff->clear();
        while(index <= real_len)
        {
            if(0==index % (WRITE_PACK_LEN+1))// 去掉usb设备的端口号；在每帧的数组的第一个数据就是它
            {
                index++;
                continue;
            }
            buff->append(rbuff[index++]);
        }
    }
    else
    {   //读取失败就要重新打开hid
        hidOpen();
    }
    return b;
}
// 发送->"AA....55"已经制作好的包
bool userHid::sendPack(QVector<char> *w)
{
    if(nullptr == w || w->size() < 8 )return false;

    // 到这里，一包数据就组合好了，现在用自定义的协议拆包成帧
    if(w->size()<=USB_FRAME_PARA_LEN)//单帧的情况
    {
        w->insert(0,FRAME_NONE_SEG);
        w->insert(1,0x00);
    }
    else                           //多帧的情况
    {
        int index=0;
        int frameCnt=0;
        w->insert(index,FRAME_FIRST_SEG);// 第一帧
        w->insert(index+1,frameCnt++);
        index += 64;
        while (index+USB_FRAME_PARA_LEN < w->size())
        {
            w->insert(index,FRAME_MIDDLE_SEG);// 中间帧
            w->insert(index+1,frameCnt++);
            index += 64;
        }
        w->insert(index,FRAME_END_SEG);// 结束帧
        w->insert(index+1,frameCnt);
    }
    // 到这里，数据就拆包完成，放在w中了，可以发送数据了
    return  hidSend(w);
}
// 发送->控制码,长度，命令，对象，内容，参数
bool userHid::sendPack(const char control,const int datalen,const char command,const char num,const char contend,const char *param)
{
    if(nullptr == param || datalen < 3 || datalen > PACK_MAX_LEN)return false;
    // 先计算需要多少帧
    QVector<char>w;
    w.reserve(PACK_MAX_LEN);
    w.append(PROTOCOL_FRAME_START_CODE);// 头部
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
    //计数校验和
    for(i=0;i<w.size();i++)
    {
        c+=w.at(i);
    }
    w.append(c%256);
    w.append(PROTOCOL_FRAME_STOP_CODE);// 尾部
    // 到这里，一包数据就组合好了，现在用自定义的协议拆包成帧
    if(w.size()<=USB_FRAME_PARA_LEN)//单帧的情况
    {
       w.prepend(0x00);
       w.prepend(FRAME_NONE_SEG);
    }
    else                           //多帧的情况
    {
        int index=0;
        int frameCnt=0;
        w.insert(index,FRAME_FIRST_SEG);// 第一帧
        w.insert(index+1,frameCnt++);
        index += 64;
        while (index+USB_FRAME_PARA_LEN < w.size())
        {
            w.insert(index,FRAME_MIDDLE_SEG);// 中间帧
            w.insert(index+1,frameCnt++);
            index += 64;
        }
        w.insert(index,FRAME_END_SEG);// 结束帧
        w.insert(index+1,frameCnt);
    }
    // 到这里，数据就拆包完成，放在w中了，可以发送数据了
    return  hidSend(&w);
}
// 读取->"AA....55"已经制作好的包
// 这里没想好如何规划，还是用signal来发送信号吧...
void userHid::pollingPack(void)
{
    bool b;
    QVector<char>R;
    // 由于采用的是阻塞读取，所以理论上一个包中的多个帧不会隔离100ms才传输到
    // 这样就可以认为，一旦读到数据，那就是读到一个或者多个包
    // 这里如果不是一个完整的包，就放弃掉
    b = hidRead(&R);
    // 没有读到就退出
    if(false == b)return;
    // 接下来是有读到的情况，理论上长度是64的整数倍
    if(R.size()%64)return ;
    int index = 0;
    int segNum = 0;
    QVector<char>pack;
    while(index<R.size())
    {
        switch(R.at(index++))
        {
            case FRAME_NONE_SEG  : // 不分段
                index++;               // 去掉num
                pack.clear();
                for(int j=0;j<62;j++)
                    pack<<R.at(index++);
                emit receive_pack(pack);
            break;
            case FRAME_FIRST_SEG :
                index++;               // 去掉num
                segNum=0;
                pack.clear();
                for(int j=0;j<62;j++)
                    pack<<R.at(index++);
            break;
            case FRAME_MIDDLE_SEG:
                segNum++;
                if(R.at(index++) != segNum) // 校验num
                {
                    index+=62;               // 校验出错，抛弃
                }
                else
                {
                    for(int j=0;j<62;j++)
                        pack<<R.at(index++);
                }
            break;
            case FRAME_END_SEG   :
                segNum++;
                if(R.at(index++) != segNum) // 校验num
                {
                    index+=62;               // 校验出错，抛弃
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
// 该线程中不断运行的函数
void userHid::run(void)
{
    while(1)
    {
        pollingPack();     //  轮询接收包，会以signal的形式发送出去
        msleep(200);    //  每200ms查询一次usbHid
    }
}
