/*  �����������
 *  ֡�ĺϰ��Ͳ��
*/
#include "usbPack.h"
#include <QVector>

usbPack::usbPack(int VID, int PID):usbFrame(VID, PID)
{
    connect(this,SIGNAL(frameRx(QVector<char>)),this,SLOT(frame2pack(QVector<char>)));
}
// �ϰ� -> ��frameRx����
void usbPack::frame2pack(QVector<char> frame)
{
    char seg_polo;
    char seg_num ;
    static char last_seg_num;            // �ϸ�֡��

    static QVector<char> pack;
    seg_polo = frame.at(0)>>6;            // ����Э�飬��1�����Ǳ�ʶ��
    seg_num  = frame.at(0)&0x3F;          // ����Э�飬��7,6λ��polo,5~0λ������

    switch(seg_polo)
    {
        case U_FRAME_NONE_SEG:        // ���ֶ�
        {
            frame.removeFirst();
            emit packRx(frame);//���հ����
          break;
        }
        case U_FRAME_FIRST_SEG:       // ��һ���ֶ�
        {
            pack.clear();
            frame.removeFirst();
            pack.append(frame);
            last_seg_num  = seg_num;
          break;
        }
        case U_FRAME_MIDDLE_SEG:      // �м�ֶ�
        {
           // ��Ų���
           if( seg_num != last_seg_num+1)
           {
             qDebug()<<"E:pack_joint is error!";
             //lret = // ������
             break;
           }
           // ��������
           frame.removeFirst();
           pack.append(frame);
           last_seg_num  = seg_num;
           break;
        }
        case U_FRAME_END_SEG:         // ���ֶ�
        {
          // ��Ų���
          if( seg_num != last_seg_num+1)
          {
            qDebug()<<"E:pack_joint is error!";
            //lret = // ������
            break;
          }
          // ��������
          frame.removeFirst();
          pack.append(frame);
          last_seg_num  = seg_num;
          emit packRx(frame);//���հ����
          break;
        }
        default :break;
    }
}
//�ض��庯����
void usbPack::packTx(QVector<char> pack)
{
    pack2frame(pack);
}
// ��� -> ���󴥷�frameTx
void usbPack::pack2frame(QVector<char> pack)
{
    QVector<char>  frame;
    char  seg_num;               // ֡��


    // ���Ĳ��ֶ�
    if(pack.size()<USB_FRAME_SIZE)
    {
      pack.prepend(0);                    // ����Э�飬��1�����Ǳ�ʶ��
      frameTx(pack);                     // ���Ͱ����
      return;
    }
    // ���ķֶε����
    // ��ͷ
    seg_num  = 0;
    frame.append(U_FRAME_FIRST_SEG<<6);
    frame.append(pack);
    frame.remove(USB_FRAME_SIZE,frame.size()-USB_FRAME_SIZE);//USB_FRAME_SIZE(64)�����Ժ�����ݲ�Ҫ
    frameTx(frame);                     // ���Ͱ����
    pack.remove(0,USB_FRAME_SIZE-1);    // ȥ��USB_FRAME_SIZE-1(63)��

    // �м��
    while(pack.size() > (USB_FRAME_SIZE-1))
    {
      seg_num  ++;
      frame.clear();
      frame.append( (U_FRAME_MIDDLE_SEG<<6) + seg_num );
      frame.append(pack);
      frame.remove(USB_FRAME_SIZE,frame.size()-USB_FRAME_SIZE);//USB_FRAME_SIZE(64)�����Ժ�����ݲ�Ҫ
      frameTx(frame);                     // ���Ͱ����
      pack.remove(0,USB_FRAME_SIZE-1);    // ȥ��USB_FRAME_SIZE-1(63)��
    }
    // ������
    seg_num  ++;
    frame.clear();
    frame.append( (U_FRAME_END_SEG<<6) + seg_num );
    frame.append(pack);
    frameTx(frame);                     // ���Ͱ����
    return;
}
