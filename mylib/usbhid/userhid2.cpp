/*  这个函数用于HID 的打开，关闭，读取，和发送
    因为windows的API没有中断的原因，所以在这个里面对读取进行线程调用
    读到数据以后，会以frameRx的信号向外发送。
*/




#include "userhid2.h"

userHid2::userHid2(int VID, int PID, char PORT)
{
    phid = 0;
    vid  = VID;
    pid  = PID;
    port = PORT;    // HID 设备的端口号，默认是0，除非设备中有多个HID对象
    qRegisterMetaType<QVector<char> >("QVector<char>");
}
// 判断hid设备是否连接
bool userHid2::hidState(void)
{
    if(nullptr == phid)
        return FALSE;
    else
        return TRUE;
}
// 判断hid设备是否连接
bool userHid2::hidIsConnect(void)
{
    return hid_is_connect(phid,vid,pid);
}
// 打开hid设备
bool userHid2::hidOpen()
{
    bool b;
    if(phid){CloseHandle(phid);phid=0;};//关闭过去的 handle
    b = open_hid(&phid, vid, pid);
    if(false == b){phid=0;}
    start();                // 启动线程
    hid_is_connect(phid,vid,pid);
    return b;
}
// 关闭hid设备
bool userHid2::hidClose()
{
    if(phid){CloseHandle(phid);phid=0;};//关闭过去的handle
    terminate();                // 退出线程
    return true;
}
// 重定义的名字
bool userHid2::frameTx(QVector<char> *buff)
{
    return hidSend(buff);
}
// 发送usb数据->注意，这个buff是会被修改的
bool userHid2::hidSend(QVector<char> *buff)
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
bool userHid2::hidRead(void)
{
    char rbuff[65];//接收缓冲
    ulong real_len;
    bool b;
    QVector<char>frame;

    // 没有先打开是不可能读到数据的
    if(0==phid)
    {
        return false;
    }
    //读操作
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

// 该线程中不断运行的函数
void userHid2::run(void)
{

    while(1)
    {
        if(hidRead()==FALSE)    //  轮询接收包，会以signal的形式发送出去
        {
            msleep(200);         //  m没有数据的话，就每200ms查询一次usbHid
        }            
    }
}
