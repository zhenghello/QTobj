/*  这个函数用包和报文之间的转换
 * 主要就是对报文和包之间进行校验和转发
*/


#include "usbGram.h"


usbGram::usbGram(int VID, int PID):usbPack(VID, PID)
{
    connect(this,SIGNAL(packRx(QVector<char>)),this,SLOT(pack2gram(QVector<char>)));
}
// 校验包 -> 由packRx触发
void usbGram::pack2gram(QVector<char> pack)
{
    int   lret;
    // 校验包的正确性
    lret = pack_checksum(pack.data(),pack.size());
    // 校验出错的情况
    if(lret<0)return;
    // 抽出报文，保存
    gramRx(pack);// 入队
    return ;
}
// 报文转成包
// 计算报文校验码，TXgram再转成的Txpack包
void usbGram::gram2pack(QVector<char> gram)
{
  uint16  gram_size;
  uint16  i;

  gram_size = gram.at(U_LEN_H_INDEX)*256 + gram.at(U_LEN_L_INDEX);// 有效数据长度
  // 计算校验码
  gram[gram_size+1]=0;
  for(i=1;i<(gram_size+1);i++)
  {
    gram[gram_size+1]+=gram[i];
  }
  gram[0] = (char)PROTOCOL_FRAME_START_CODE;          // 包头
  gram[gram_size+2] = (char)PROTOCOL_FRAME_START_CODE;// 包尾
  emit gramRx(gram);                                  // 入队
  return ;
}
/**
  * 函数功能：包校验
  * 参数：    ppack  一包数据
  * 参数：    pack_max_len  包数据的最大长度
  * 返回：    EXIT_FAILURE_LOCOAL 失败 EXIT_SUCCESS_LOCOAL 成功
  * 备注：    这里是一帧或多帧数据合并后，校验缓存区的合法性,包括校验头、尾、校验和，可能尾部有空间剩余。
  *           比如“aa 00 03 01 00 01 05 55”
  */
int pack_checksum(char *pack, uint pack_size)
{
  uint     i;
  char     check_sum;          // 校验和
  uint     length = (uint)pack[U_LEN_H_INDEX]*256 + (uint)pack[U_LEN_L_INDEX];// 数据长度

  printf("D:开始校验\r\n");
  //  检测头部
  if(PROTOCOL_FRAME_START_CODE != pack[U_START_INDEX])
  {
    // debug_msg("E:ERR_DB_CMD_FORMAT_START",__FILE__,__LINE__);
    qDebug()<<"E:ERR_DB_CMD_FORMAT_START";
    return -1;
  }
  //  检测控制码
  if( (FRAME_CONTROL_CODE_COMMAND_REP != pack[U_CONTROL_INDEX])\
    &&(FRAME_CONTROL_CODE_COMMAND_NO_REP != pack[U_CONTROL_INDEX]))
  {
    //debug_msg("ERR_DB_CMD_FORMAT_CONTROL",__FILE__,__LINE__);
    qDebug()<<"E:ERR_DB_CMD_FORMAT_CONTROL";
    return -1;
  }
  //  检测长度
  if(pack_size < length+3)
  {
    //debug_msg("E:ERR_DB_CMD_FORMAT_DATALEN",__FILE__,__LINE__);
    qDebug()<<"E:ERR_DB_CMD_FORMAT_DATALEN";
    return -1;
  }
  //  检测尾部
  if(PROTOCOL_FRAME_STOP_CODE != pack[length+5])
  {
    //debug_msg("E:ERR_DB_CMD_FORMAT_STOP",__FILE__,__LINE__);
    qDebug()<<"E:ERR_DB_CMD_FORMAT_STOP";
    return -1;
  }
  //  检验和
  check_sum = 0;
  for(i=1;i<length+4;i++)
  {
    check_sum += pack[i];
  }
  if( check_sum != pack[length+4])
  { // 出错
    //debug_msg("E:ERR_DB_CMD_FORMAT_CONTROL",__FILE__,__LINE__);
    qDebug()<<"E:ERR_DB_CMD_FORMAT_CONTROL";
    return -1;
  }
  printf("D:校验通过\r\n");
  return TRUE;
}
