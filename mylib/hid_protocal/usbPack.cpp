/*  这个函数用于
 *  帧的合包和拆包
*/
#include "usbPack.h"
#include <QVector>

usbPack::usbPack(int VID, int PID):usbFrame(VID, PID)
{
    connect(this,SIGNAL(frameRx(QVector<char>)),this,SLOT(frame2pack(QVector<char>)));
}
// 合包 -> 由frameRx触发
void usbPack::frame2pack(QVector<char> frame)
{
    char seg_polo;
    char seg_num ;
    static char last_seg_num;            // 上个帧号

    static QVector<char> pack;
    seg_polo = frame.at(0)>>6;            // 根据协议，第1个数是标识符
    seg_num  = frame.at(0)&0x3F;          // 根据协议，第7,6位是polo,5~0位是数字

    switch(seg_polo)
    {
        case U_FRAME_NONE_SEG:        // 不分段
        {
            frame.removeFirst();
            emit packRx(frame);//接收包入队
          break;
        }
        case U_FRAME_FIRST_SEG:       // 第一个分段
        {
            pack.clear();
            frame.removeFirst();
            pack.append(frame);
            last_seg_num  = seg_num;
          break;
        }
        case U_FRAME_MIDDLE_SEG:      // 中间分段
        {
           // 序号不对
           if( seg_num != last_seg_num+1)
           {
             qDebug()<<"E:pack_joint is error!";
             //lret = // 错误码
             break;
           }
           // 正常传递
           frame.removeFirst();
           pack.append(frame);
           last_seg_num  = seg_num;
           break;
        }
        case U_FRAME_END_SEG:         // 最后分段
        {
          // 序号不对
          if( seg_num != last_seg_num+1)
          {
            qDebug()<<"E:pack_joint is error!";
            //lret = // 错误码
            break;
          }
          // 正常传递
          frame.removeFirst();
          pack.append(frame);
          last_seg_num  = seg_num;
          emit packRx(frame);//接收包入队
          break;
        }
        default :break;
    }
}
//重定义函数名
void usbPack::packTx(QVector<char> pack)
{
    pack2frame(pack);
}
// 拆包 -> 拆解后触发frameTx
void usbPack::pack2frame(QVector<char> pack)
{
    QVector<char>  frame;
    char  seg_num;               // 帧号


    // 报文不分段
    if(pack.size()<USB_FRAME_SIZE)
    {
      pack.prepend(0);                    // 根据协议，第1个数是标识符
      frameTx(pack);                     // 发送包入队
      return;
    }
    // 报文分段的情况
    // 段头
    seg_num  = 0;
    frame.append(U_FRAME_FIRST_SEG<<6);
    frame.append(pack);
    frame.remove(USB_FRAME_SIZE,frame.size()-USB_FRAME_SIZE);//USB_FRAME_SIZE(64)长度以后的数据不要
    frameTx(frame);                     // 发送包入队
    pack.remove(0,USB_FRAME_SIZE-1);    // 去掉USB_FRAME_SIZE-1(63)个

    // 中间段
    while(pack.size() > (USB_FRAME_SIZE-1))
    {
      seg_num  ++;
      frame.clear();
      frame.append( (U_FRAME_MIDDLE_SEG<<6) + seg_num );
      frame.append(pack);
      frame.remove(USB_FRAME_SIZE,frame.size()-USB_FRAME_SIZE);//USB_FRAME_SIZE(64)长度以后的数据不要
      frameTx(frame);                     // 发送包入队
      pack.remove(0,USB_FRAME_SIZE-1);    // 去掉USB_FRAME_SIZE-1(63)个
    }
    // 结束段
    seg_num  ++;
    frame.clear();
    frame.append( (U_FRAME_END_SEG<<6) + seg_num );
    frame.append(pack);
    frameTx(frame);                     // 发送包入队
    return;
}
