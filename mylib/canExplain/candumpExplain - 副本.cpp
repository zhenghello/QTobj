#include "candumpExplain.h"
int htoi(char s[]);

candumpExplain::candumpExplain()
{
    canSign      =0;
}
// 输入一行can帧数据，如：<0x00800000> [8] aa d4 03 01 00 00 d8 55
// 转出解析完成并被校验好的数据，前两位是源和目的 的ID
bool candumpExplain::explain(QByteArray qby)
{
  //1.判断数据有效性，第0个是‘<’,第11个是‘>’,第13是‘[’，第15个是‘]’
  if(qby.at(0)!='<') return false;
  if(qby.at(11)!='>')return false;
  if(qby.at(13)!='[')return false;
  if(qby.at(15)!=']')return false;
  //2.抽出数据，按空格划分
  QList<QByteArray> list=qby.simplified().split(' ');
  uint  id      ; // * ID号
  int  len     ; // * 附带数据长度
  QByteArray da ; // * 数据
  QByteArray id_qby = list.at(0);
  QByteArray len_qby = list.at(1);

  id_qby.remove(11,1);  // 去掉‘>’
  id_qby.remove(0,3);   // 去掉‘<0x’
  len_qby.remove(2,1);   // 去掉‘]’
  len_qby.remove(0,1);   // 去掉‘[’
  id = htoi(id_qby.data());  // id号
  len = len_qby.toInt(); // 数据长度
  if(len != list.size()-2)return false;//判断数据长度正确
  for(int i=0;i<len;i++)
  {
    QByteArray d = list.at(i+2);
    char c = (char)htoi(d.data());
    da.append(c);
  }
  //3.处理数据
//  qDebug("%x",id);            // 调试
//  qDebug()<<len;              // 调试
//  qDebug()<<(QByteArray)da;   // 调试
  // 3.1.之前没有接收数据
  if(canSign == 0)
  { // 头错误
    if(da.at(0)!=(char)0xaa)
    {
      emit canRevErr(1);
      return false;
    }
    canDate.clear();
    canDate.append(da);
    canCurLen = len;
    canDestID = (id >> 16) & 0x1f;
    canSrcID  = (id >> 22) & 0x1f;
    canSign = 1;  //进入接收状态
    canNeedLen = da.at(2)+5;// 这个参数在试剂封闭板卡中有变动
  }
  // 3.2.已经在接收数据中
  else
  {
    // 3.2.1.目的ID不一样
    if(canDestID != (char)((id >> 16) & 0x1f))
    {
      emit canRevErr(1);
      canSign = 0;//接收清空
      return false;
    }
    // 3.2.2.源ID不一样
    if(canSrcID  != (char)((id >> 22) & 0x1f))
    {
      emit canRevErr(2);
      canSign = 0;//接收清空
      return false;
    }
    canDate.append(da);
    canCurLen += len;
  }
  // 3.3.1接收长度出错
  if(canNeedLen < canCurLen)
  {
    emit canRevErr(3);
    canSign = 0;//接收清空
    return false;
  }
  // 3.3.2.接收长度正确->校验数据
  if(canNeedLen == canCurLen)
  {
    char c = 0;
    uint  i ;
    for(i=1;i<(canCurLen-2);i++)
    {
        c+=canDate.at(i);
    }
    // 3.3.3.校验出差
    if(c!=canDate.at(i))
    {
      emit canRevErr(4);
      canSign = 0;//接收清空
      return false;
    }
    // 3.3.4.接收正确,数据转发出去
    qDebug()<<"canSrcID="<<(uchar)canSrcID;        // 调试
    qDebug()<<"canDestID="<<(uchar)canDestID;      // 调试
    qDebug()<<"canDate="<<(QByteArray)canDate;     // 调试

    emit canRevPack(canDestID,canSrcID,canDate);   // 将接收到的数据转发出去
    canSign = 0;//接收清空
    return true;
  }

  return true;
}



//将十六进制的字符串转换成整数
int htoi(char s[])
{
  int i;
  int n = 0;
  if (s[0] == '0' && (s[1]=='x' || s[1]=='X'))
  {
      i = 2;
  }
  else
  {
    i = 0;
  }
  for (; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >='A' && s[i] <= 'Z');++i)
  {
    if (tolower(s[i]) > '9')
    {
      n = 16 * n + (10 + tolower(s[i]) - 'a');
    }
    else
    {
      n = 16 * n + (tolower(s[i]) - '0');
    }
  }
  return n;
}
