/* 这个文件用于解析can命令的规则
 * can命令的解析规则在 canExplain.xlsx 中已经编辑好
 * can协议的命令存放规则：
 * 1类：大类别
 * 2类：控制类型的编码
 * 3类：控制命令的编码
 * 4类：发送的参数和接收的参数
 * 5类：参数附带意义
 *
*/
#include "canExplain.h"
#include "QMessageBox"
#include "QDebug"
#include "fdebug.h"
int htoi(char s[]);


// 启动时初始化库内容
canExplain::canExplain(QWidget *parent):FtreeDabeBase(parent)
{
    // 0.获取can解析的树地址
    mTree = mainTree();
    // 1.校验“ID对象”存在
    idAddr = findKeyTopTree(mTree,0,QString::fromLocal8Bit("ID对象"));
    if(idAddr == NULL)
    {
        QMessageBox::warning(NULL, QString::fromLocal8Bit("出错"),QString::fromLocal8Bit("ID对象 出错"));
    }
    // 2.校验“控制码类”存在
    ctrCodeAddr = findKeyTopTree(mTree,0,QString::fromLocal8Bit("控制码类"));
    if(ctrCodeAddr == NULL)
    {
        QMessageBox::warning(NULL, QString::fromLocal8Bit("出错"),QString::fromLocal8Bit("控制码类 出错"));
    }
    // 3.校验“命令码类”存在
    orderCodeAddr = findKeyTopTree(mTree,0,QString::fromLocal8Bit("命令码类"));
    if(orderCodeAddr == NULL)
    {
        QMessageBox::warning(NULL, QString::fromLocal8Bit("出错"),QString::fromLocal8Bit("命令码类 出错"));
    }
    // 4.校验“错误码类”存在
    errCodeAddr = findKeyTopTree(mTree,0,QString::fromLocal8Bit("错误码类"));
    if(errCodeAddr == NULL)
    {
        QMessageBox::warning(NULL, QString::fromLocal8Bit("出错"),QString::fromLocal8Bit("错误码类 出错"));
    }
    // 初始化标志位
    canSign = 0;
}
canExplain::~canExplain()
{

}
// 将can数据进行查表转换,并将转换后的数据发送出去
void canExplain::translate(char destID,char srcID,QStringList strList)
{
    QTreeWidgetItem* treeW;
    QString strResult;
    QColor  strColor=Qt::red;

    strList.prepend(QString("0x%1").arg(destID,2,16,(QChar)'0'));
    strList.prepend(QString("0x%1").arg(srcID,2,16,(QChar)'0'));

    // 1.翻译“源地址”
    treeW = findKeyTopTree(idAddr, 0, strList.at(0));
    if(treeW == NULL)
    {
        strResult += "NULL";
    }
    else
    {
        strResult += treeW->text(1);
    }
    strResult += "->";
    // 2.翻译“目标地址”
    treeW = findKeyTopTree(idAddr, 0, strList.at(1));
    if(treeW == NULL)
    {
        strResult += "NULL";
    }
    else
    {
        strResult += treeW->text(1);
    }
    strResult += " (";
    // 3.翻译“控制类型”
    treeW = findKeyTopTree(ctrCodeAddr, 0, QString("0x")+strList.at(3));
    if(treeW == NULL)
    {
        strResult += "NULL";
    }
    else
    {
        strResult += treeW->text(1);
        strColor = QColor(treeW->text(2).toInt(NULL,16));// 设置颜色
    }
    strResult += ") ";
    // 4.翻译“控制码”
    QTreeWidgetItem* treeCtlCode;
    treeCtlCode = findKeyTopTree(orderCodeAddr, 0, QString("0x")+strList.at(5));
    if(treeCtlCode == NULL)
    {
        strResult += "NULL";
        return;
    }
    else
    {
        strResult += treeCtlCode->text(1);
    }
    strResult += "->";
    // 5.翻译“对象”
    strResult += "OBJ:";
    strResult += strList.at(6);
    strResult += "->";
    // 6.翻译“控制命令” - 这是在找到“控制码”的基础上完成的。
    QTreeWidgetItem* treeCtlOrder;
    treeCtlOrder = findKeyTopTree(treeCtlCode, 0, QString("0x")+strList.at(7));
    if(treeCtlOrder == NULL)
    {
        strResult += "NULL";
        return;
    }
    else
    {
        strResult += treeCtlOrder->text(1);
    }
    strResult += " # ";
    // 7.翻译“参数”
    // 7.1.翻译“故障码”
    if(strList.at(3).toLower() == "f8")
    {
        strResult += "Err:: ";
        QString strErrCode = "0x"+strList.at(8)+strList.at(9);
        treeW = findKeyTopTree(errCodeAddr, 0, strErrCode);
        strResult += treeW->text(1);
    }
    // 7.3.翻译“主动上次帧注释”
    if((strList.at(3).toLower() == "d8")&&(strList.at(5).toLower() == "f0")&&(strList.at(7).toLower() == "00"))
    {
        strResult += "Dbg:: ";
        QByteArray strExplain;
        strExplain.clear();
        for(int i=8;i<strList.size()-2;i++)
        {
            strExplain.append(strList.at(i).toUInt(NULL,16));
        }
        strResult += strExplain.trimmed();
    }

    // 7.2.翻译“命令码参数”
    QTreeWidgetItem* treeOrdArg;    // REP附带参数的Tree地址
    if((strList.at(3).toLower()=="00")||(strList.at(3).toLower()=="40")||(strList.at(3).toLower()=="41")||(strList.at(3).toLower()=="42")||(strList.at(3).toLower()=="43"))
    {
        strResult += "Arg::";
        // 没有附带参数的话，该excel文件中的命令码下就没有"ord"的子项目
        treeOrdArg = findKeyTopTree(treeCtlOrder, 0, "ord");

        if(treeOrdArg != NULL)
        {   // 要把所有子对象都遍历一次
            int curArgIndex = 7;    // 当前的子参数的偏移个数
            for(int i=0;i<treeOrdArg->childCount();i++)
            {
                // 获取需要的参数个数
                int argSize = treeOrdArg->child(i)->text(0).toInt();
                // 获取该参数的注释
                strResult += (treeOrdArg->child(i)->text(1) + "=");
                // 防止访问溢出
                if((curArgIndex+argSize) >= (strList.size()-2))
                {
                    strResult += " ARG IS TOO MANY!";
                    break;
                }
                // 合并参数字符串
                QString argStr;
                argStr.clear();
                for(int i2=0;i2<argSize;i2++)
                {
                    curArgIndex++;
                    argStr += strList.at(curArgIndex);
                }
                // 获取参数类型
                QString argType=treeOrdArg->child(i)->text(2);
                // 1."10"进制转换,先从16进制的字符串转成10进制的数字，再转回10进制的字符串，不兼容负数
                if(argType.toLower()=="10")
                {
                    // 获取数字
                    strResult += QString::number(argStr.toULongLong(NULL,16));
                }
                // 2."10+-"进制转换,先从16进制的字符串转成10进制的数字，再转回10进制的字符串，兼容负数
                else if(argType.toLower()=="10+-")
                {
                    // 获取数字
                    long num = argStr.toLongLong(NULL,16);
                    // 取出最高位（4个位），数据大于8 ，是个负数
                    // 因为toUInt 总是把数据转为正数
                    char a = argStr.toLatin1().back();
                    if(QString(a).toUInt() >= 8)
                    {
                      num = ~num;
                      num++;
                    }
                    strResult += QString::number(num);
                }
                // 3."16"进制转换,原本就是16进制
                else if(argType.toLower()=="16")
                {
                    strResult += ("0x" + argStr);
                }
                // 4."100" 子对象匹配
                else if(argType.toLower()=="100")
                {
                    treeW = findKeyTopTree(treeOrdArg->child(i), 0, argStr);
                    if(treeW!=NULL)
                    {
                        strResult += treeW->text(1);
                    }
                    else
                    {
                        strResult += "NULL";
                    }
                }
                strResult += " ";
            }

        }
        else
        {   // 没有参数的情况
            strResult += "NULL";
        }
    }
    // 7.3.翻译“回复码参数”
    QTreeWidgetItem* treeRepArg;    // REP附带参数的Tree地址
    if(strList.at(3).toLower() == "c0")
    {
        strResult += "Arg::";
        // 没有附带参数的话，该excel文件中的命令码下就没有"rep"的子项目
        treeRepArg = findKeyTopTree(treeCtlOrder, 0, "rep");

        if(treeRepArg != NULL)
        {   // 要把所有子对象都遍历一次
            int curArgIndex = 7;    // 当前的子参数的偏移个数
            for(int i=0;i<treeRepArg->childCount();i++)
            {
                // 获取需要的参数个数
                int argSize = treeRepArg->child(i)->text(0).toInt();
                // 获取该参数的注释
                strResult += (treeRepArg->child(i)->text(1) + "=");
                // 防止访问溢出
                if((curArgIndex+argSize) >= (strList.size()-2))
                {
                    strResult += " ARG IS TOO MANY!";
                    break;
                }
                // 合并参数字符串
                QString argStr;
                argStr.clear();
                for(int i2=0;i2<argSize;i2++)
                {
                    curArgIndex++;
                    argStr += strList.at(curArgIndex);
                }
                // 获取参数类型
                QString argType=treeRepArg->child(i)->text(2);
                // 1."10"进制转换,先从16进制的字符串转成10进制的数字，再转回10进制的字符串，不兼容负数
                if(argType.toLower()=="10")
                {
                    // 获取数字
                    strResult += QString::number(argStr.toULongLong(NULL,16));
                }
                // 2."10+-"进制转换,先从16进制的字符串转成10进制的数字，再转回10进制的字符串，兼容负数
                else if(argType.toLower()=="10+-")
                {
                    // 获取数字
                    long num = argStr.toLongLong(NULL,16);
                    // 取出最高位（4个位），数据大于8 ，是个负数
                    // 因为toUInt 总是把数据转为正数
                    char a = argStr.toLatin1().back();
                    if(QString(a).toUInt() >= 8)
                    {
                      num = ~num;
                      num++;
                    }
                    strResult += QString::number(num);
                }
                // 3."16"进制转换,原本就是16进制
                else if(argType.toLower()=="16")
                {
                    strResult += ("0x" + argStr);
                }
                // 4."100" 子对象匹配
                else if(argType.toLower()=="100")
                {
                    treeW = findKeyTopTree(treeRepArg->child(i), 0, argStr);
                    if(treeW!=NULL)
                    {
                        strResult += treeW->text(1);
                    }
                    else
                    {
                        strResult += "NULL";
                    }
                }
                strResult += " ";
            }

        }
        else
        {   // 没有参数的情况
            strResult += "NULL";
        }
    }
    // 10.显示内容
    QDateTime curTime = QDateTime::currentDateTime();   //
    QString   str = curTime.toString("hh:mm:ss ");      //显示时间
    for(int i=0;i<strList.size();i++)
    {
        str += strList.at(i)+" ";
    }
    str = str.simplified();
    // 显示源码内容
    myShow->setTextStyle(str      ,Qt::white,strColor,8);
    // 显示注释内容
    myShow->setTextStyle(strResult,Qt::white,strColor,8);
}

// 输入一行can帧数据，如：<0x00800000> [8] aa d4 03 01 00 00 d8 55
// 转出解析完成并被校验好的数据，前两位是源和目的 的ID
bool canExplain::explain(QString str)
{
  // 重发判断发送 收到 read: Network is down 就要重发,把信息重发出去
  if(str.trimmed() == "read: Network is down")
  {
    emit candumpIsDown();
    myShow->setTextStyle(QString::fromLocal8Bit("candump is close"),Qt::red,Qt::white,16);   // can挂了
    return true;
  }

  //myShow->setText(str);
  //1.判断数据有效性，第0个是‘<’,第11个是‘>’,第13是‘[’，第15个是‘]’
  if(str.size()<16)  return false;
  if(str.at(0)!='<') return false;
  if(str.at(11)!='>')return false;
  if(str.at(13)!='[')return false;
  if(str.at(15)!=']')return false;
  //2.抽出数据，按空格划分
  QStringList list=str.simplified().split(' ');
  uint  id      ;   // * ID号
  uint  len     ;    // * 附带数据长度
  QStringList da ;  // * 数据
  QString id_str = list.at(0);
  QString len_qby = list.at(1);

  id_str.remove(11,1);  // 去掉‘>’
  id_str.remove(0,3);   // 去掉‘<0x’
  len_qby.remove(2,1);   // 去掉‘]’
  len_qby.remove(0,1);   // 去掉‘[’
  id = id_str.toUInt(NULL,16);  // id号
  len = len_qby.toUInt(); // 数据长度
  if(len != (list.size()-2))return false;//判断数据长度正确
  for(uint i=0;i<len;i++)
  {
    da.append(list.at(i+2));
  }
  //3.处理数据
//  qDebug("%x",id);            // 调试
//  qDebug()<<len;              // 调试
//  qDebug()<<da;               // 调试
  // 3.0.长度为0的代表是请求帧
  if(len == 0)
  {
      myShow->setText("Request Frame!");
      return true;
  }
  // 3.1.之前没有接收数据
  if(canSign == 0)
  {
    // 头错误
    if(da.at(0).toLower() != "aa")
    {
      emit canRevErr(1);
      myShow->setTextStyle(QString::fromLocal8Bit("头错误"),Qt::red,Qt::white,16);   // 出错
      return false;
    }

    canDate.clear();
    canDate.append(da);
    canCurLen   = len;
    canDestID   = (id >> 16) & 0x1f;
    canSrcID    = (id >> 22) & 0x1f;
    canSign     = 1;  //进入接收状态
    canNeedLen  = da.at(2).toUInt()+5;// 这个参数在试剂封闭板卡中有变动

  }
  // 3.2.已经在接收数据中
  else
  {
    // 3.2.1.目的ID不一样
    if(canDestID != (char)((id >> 16) & 0x1f))
    {
      emit canRevErr(1);
      myShow->setTextStyle(QString::fromLocal8Bit("目的ID不一样"),Qt::red,Qt::white,16);   // 出错
      myShow->setText(str);
      qDebug()<<"err: "<<canDate;

      canSign = 0;//接收清空
      return false;
    }
    // 3.2.2.源ID不一样
    if(canSrcID  != (char)((id >> 22) & 0x1f))
    {
      emit canRevErr(2);
      myShow->setTextStyle(QString::fromLocal8Bit("源ID不一样"),Qt::red,Qt::white,16);   // 出错
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
    myShow->setTextStyle(QString::fromLocal8Bit("接收长度出错"),Qt::red,Qt::white,16);   // 出错
    canSign = 0;//接收清空
    return false;
  }
  // 3.3.2.接收长度正确->校验数据
  if(canNeedLen == canCurLen)
  {
    // 头错误
    if(canDate.at(0).toLower() != "aa")
    {
      emit canRevErr(1);
      myShow->setTextStyle(QString::fromLocal8Bit("头错误2"),Qt::red,Qt::white,16);   // 出错
      return false;
    }
    // 尾错误
    if(canDate.at(canDate.size()-1).toLower() != "55")
    {
      emit canRevErr(1);
      myShow->setTextStyle(QString::fromLocal8Bit("尾错误"),Qt::red,Qt::white,16);   // 出错
      return false;
    }
    uchar c = 0;
    uint  i ;
    for(i=1;i<(canCurLen-2);i++)
    {
        c += canDate.at(i).toUInt(NULL,16);
    }
    // 3.3.3.校验出错
    if(c != canDate.at(i).toUInt(NULL,16))
    {
      emit canRevErr(4);
      myShow->setTextStyle(QString::fromLocal8Bit("校验出错"),Qt::red,Qt::white,16);   // 出错
      canSign = 0;//接收清空
      return false;
    }
    // 3.3.4.接收正确,数据转发出去
//    qDebug()<<"canSrcID="<<(uchar)canSrcID;        // 调试
//    qDebug()<<"canDestID="<<(uchar)canDestID;      // 调试
//    qDebug()<<"canDate="<<canDate;     // 调试
    canSign = 0;//接收清空
    // 翻译内容
    translate(canDestID, canSrcID, canDate);




    return true;
  }

  return true;
}

// 查找树类下的


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

