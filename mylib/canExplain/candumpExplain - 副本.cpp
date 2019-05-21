#include "candumpExplain.h"
int htoi(char s[]);

candumpExplain::candumpExplain()
{
    canSign      =0;
}
// ����һ��can֡���ݣ��磺<0x00800000> [8] aa d4 03 01 00 00 d8 55
// ת��������ɲ���У��õ����ݣ�ǰ��λ��Դ��Ŀ�� ��ID
bool candumpExplain::explain(QByteArray qby)
{
  //1.�ж�������Ч�ԣ���0���ǡ�<��,��11���ǡ�>��,��13�ǡ�[������15���ǡ�]��
  if(qby.at(0)!='<') return false;
  if(qby.at(11)!='>')return false;
  if(qby.at(13)!='[')return false;
  if(qby.at(15)!=']')return false;
  //2.������ݣ����ո񻮷�
  QList<QByteArray> list=qby.simplified().split(' ');
  uint  id      ; // * ID��
  int  len     ; // * �������ݳ���
  QByteArray da ; // * ����
  QByteArray id_qby = list.at(0);
  QByteArray len_qby = list.at(1);

  id_qby.remove(11,1);  // ȥ����>��
  id_qby.remove(0,3);   // ȥ����<0x��
  len_qby.remove(2,1);   // ȥ����]��
  len_qby.remove(0,1);   // ȥ����[��
  id = htoi(id_qby.data());  // id��
  len = len_qby.toInt(); // ���ݳ���
  if(len != list.size()-2)return false;//�ж����ݳ�����ȷ
  for(int i=0;i<len;i++)
  {
    QByteArray d = list.at(i+2);
    char c = (char)htoi(d.data());
    da.append(c);
  }
  //3.��������
//  qDebug("%x",id);            // ����
//  qDebug()<<len;              // ����
//  qDebug()<<(QByteArray)da;   // ����
  // 3.1.֮ǰû�н�������
  if(canSign == 0)
  { // ͷ����
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
    canSign = 1;  //�������״̬
    canNeedLen = da.at(2)+5;// ����������Լ���հ忨���б䶯
  }
  // 3.2.�Ѿ��ڽ���������
  else
  {
    // 3.2.1.Ŀ��ID��һ��
    if(canDestID != (char)((id >> 16) & 0x1f))
    {
      emit canRevErr(1);
      canSign = 0;//�������
      return false;
    }
    // 3.2.2.ԴID��һ��
    if(canSrcID  != (char)((id >> 22) & 0x1f))
    {
      emit canRevErr(2);
      canSign = 0;//�������
      return false;
    }
    canDate.append(da);
    canCurLen += len;
  }
  // 3.3.1���ճ��ȳ���
  if(canNeedLen < canCurLen)
  {
    emit canRevErr(3);
    canSign = 0;//�������
    return false;
  }
  // 3.3.2.���ճ�����ȷ->У������
  if(canNeedLen == canCurLen)
  {
    char c = 0;
    uint  i ;
    for(i=1;i<(canCurLen-2);i++)
    {
        c+=canDate.at(i);
    }
    // 3.3.3.У�����
    if(c!=canDate.at(i))
    {
      emit canRevErr(4);
      canSign = 0;//�������
      return false;
    }
    // 3.3.4.������ȷ,����ת����ȥ
    qDebug()<<"canSrcID="<<(uchar)canSrcID;        // ����
    qDebug()<<"canDestID="<<(uchar)canDestID;      // ����
    qDebug()<<"canDate="<<(QByteArray)canDate;     // ����

    emit canRevPack(canDestID,canSrcID,canDate);   // �����յ�������ת����ȥ
    canSign = 0;//�������
    return true;
  }

  return true;
}



//��ʮ�����Ƶ��ַ���ת��������
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
