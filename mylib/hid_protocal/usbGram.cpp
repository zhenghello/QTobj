/*  ��������ð��ͱ���֮���ת��
 * ��Ҫ���ǶԱ��ĺͰ�֮�����У���ת��
*/


#include "usbGram.h"


usbGram::usbGram(int VID, int PID):usbPack(VID, PID)
{
    connect(this,SIGNAL(packRx(QVector<char>)),this,SLOT(pack2gram(QVector<char>)));
}
// У��� -> ��packRx����
void usbGram::pack2gram(QVector<char> pack)
{
    int   lret;
    // У�������ȷ��
    lret = pack_checksum(pack.data(),pack.size());
    // У���������
    if(lret<0)return;
    // ������ģ�����
    gramRx(pack);// ���
    return ;
}
// ����ת�ɰ�
// ���㱨��У���룬TXgram��ת�ɵ�Txpack��
void usbGram::gram2pack(QVector<char> gram)
{
  uint16  gram_size;
  uint16  i;

  gram_size = gram.at(U_LEN_H_INDEX)*256 + gram.at(U_LEN_L_INDEX);// ��Ч���ݳ���
  // ����У����
  gram[gram_size+1]=0;
  for(i=1;i<(gram_size+1);i++)
  {
    gram[gram_size+1]+=gram[i];
  }
  gram[0] = (char)PROTOCOL_FRAME_START_CODE;          // ��ͷ
  gram[gram_size+2] = (char)PROTOCOL_FRAME_START_CODE;// ��β
  emit gramRx(gram);                                  // ���
  return ;
}
/**
  * �������ܣ���У��
  * ������    ppack  һ������
  * ������    pack_max_len  �����ݵ���󳤶�
  * ���أ�    EXIT_FAILURE_LOCOAL ʧ�� EXIT_SUCCESS_LOCOAL �ɹ�
  * ��ע��    ������һ֡���֡���ݺϲ���У�黺�����ĺϷ���,����У��ͷ��β��У��ͣ�����β���пռ�ʣ�ࡣ
  *           ���硰aa 00 03 01 00 01 05 55��
  */
int pack_checksum(char *pack, uint pack_size)
{
  uint     i;
  char     check_sum;          // У���
  uint     length = (uint)pack[U_LEN_H_INDEX]*256 + (uint)pack[U_LEN_L_INDEX];// ���ݳ���

  printf("D:��ʼУ��\r\n");
  //  ���ͷ��
  if(PROTOCOL_FRAME_START_CODE != pack[U_START_INDEX])
  {
    // debug_msg("E:ERR_DB_CMD_FORMAT_START",__FILE__,__LINE__);
    qDebug()<<"E:ERR_DB_CMD_FORMAT_START";
    return -1;
  }
  //  ��������
  if( (FRAME_CONTROL_CODE_COMMAND_REP != pack[U_CONTROL_INDEX])\
    &&(FRAME_CONTROL_CODE_COMMAND_NO_REP != pack[U_CONTROL_INDEX]))
  {
    //debug_msg("ERR_DB_CMD_FORMAT_CONTROL",__FILE__,__LINE__);
    qDebug()<<"E:ERR_DB_CMD_FORMAT_CONTROL";
    return -1;
  }
  //  ��ⳤ��
  if(pack_size < length+3)
  {
    //debug_msg("E:ERR_DB_CMD_FORMAT_DATALEN",__FILE__,__LINE__);
    qDebug()<<"E:ERR_DB_CMD_FORMAT_DATALEN";
    return -1;
  }
  //  ���β��
  if(PROTOCOL_FRAME_STOP_CODE != pack[length+5])
  {
    //debug_msg("E:ERR_DB_CMD_FORMAT_STOP",__FILE__,__LINE__);
    qDebug()<<"E:ERR_DB_CMD_FORMAT_STOP";
    return -1;
  }
  //  �����
  check_sum = 0;
  for(i=1;i<length+4;i++)
  {
    check_sum += pack[i];
  }
  if( check_sum != pack[length+4])
  { // ����
    //debug_msg("E:ERR_DB_CMD_FORMAT_CONTROL",__FILE__,__LINE__);
    qDebug()<<"E:ERR_DB_CMD_FORMAT_CONTROL";
    return -1;
  }
  printf("D:У��ͨ��\r\n");
  return TRUE;
}
