/* 这个文件的结构为：
 * 宏定义
 * 开放函数
 * 命令内容编码
 * 命令类型编码
 * 错误类型编码
 * 这个文件的功能就是尽可能完整得解释一个can命令，所以所有CAN的解释都要在这个文件中处理。
*/
#include "canExplain.h"

//#include <QDebug>   //后期删除
// ---------------------------------------------------- 宏定义
//大分类->个数定义
#define ID_CODE_NUM       7     //ID码的个数
#define CONTROL_CODE_NUM  9     //控制码个数
#define COMMAND_CODE_NUM  32    //命令类型个数
#define ERROR_CODE_NUM    216   //错误码个数
#define NO_RECORD         QString::fromLocal8Bit("NO_record")
// ---------------------------------------------------- 变量声明
extern  code_str          id_code          [ID_CODE_NUM];     // ID码
extern  ctl_code_str      control_code     [CONTROL_CODE_NUM];// 控制码
extern  command_code_str  command_code_type[COMMAND_CODE_NUM];// 命令类型
extern  err_code_str      error_code       [ERROR_CODE_NUM];  // 错误类型
// 内部函数
bool find_ctl_code(uint ctl,QString *str,QColor *color);            // 找控制码
bool find_id_code(uint16 id,QString *str);                          // 找ID码
bool find_type_code(uint cmd,QString *cmd_str);                     // 找命令类型码
bool find_concest_code(uint cmd,uint concest,QString *concest_str); // 找命令内容
bool find_arg_code(QVector<uint> argIN, QString *strOUT);           // 找参数内容
bool find_err_code(uint err_code,QString *str);                     // 找错误码
bool find_debug_code(QVector<uint>arrayIN,QString *strOUT);         // 找打印信息码

// ---------------------------------------------------- 函数区域

//函数功能：将下位机传送上来的字符串转换成固定的协议，这和传送的协议有关
           //当前的传输协议为："(00 01 aa 00 03 01 00 01 05 55)"
//输入参数： strIN    要转换的字符串
//输入参数： strOUT   要解释的内容
//输入参数： array    输出的参数
// ：colorOUT    显示的颜色
//备注    ： 输出的协议参数为：输出，输入，头，控制码，参数长度，命令码，命令对象，命令内容，附带参数，校验码，尾
bool canStr2explainStr(QString strIN,QVector<uint> *uintArrayOUT,QString *strOUT,QColor *colorOUT)
{
    // 1.取出括号的内容，这是郑凯鹏和转接板定义好的
    int index1,index2;
    index1=strIN.indexOf("("); // 头
    index2=strIN.indexOf(")"); // 尾
    if(index1==-1||index2==-1)return false;     // 出错跳出
    strIN=strIN.mid(index1+1,index2-index1-1);  // 取出括号内容
    if(strIN.isEmpty())return false;            //出错跳出
    // 2.将字符串翻译为数组
    QStringList strlist;
    int i;
    // 2.1.去掉首尾空白 + 去掉多空格为1空格，去掉非识别字符
    strIN = strIN.simplified();
    // 2.2.分割字符段
    strlist = strIN.split(" ");
    // 2.3.转为十进制
    uintArrayOUT->clear();
    for(i=0;i<strlist.length();i++)
    {
        uintArrayOUT->append(strlist.at(i).toInt(nullptr,16));    //转换进制
    }
    if(uintArrayOUT->size()<10)return false;//出错跳出
    strOUT->clear();
    // 3.解释内容
    QString str;
    //  翻译ID源
    find_id_code(uintArrayOUT->at(0),&str);
    *strOUT+=str;
    *strOUT+=">";
    find_id_code(uintArrayOUT->at(1),&str);
    *strOUT+=str;
    *strOUT+=" ";
    //  翻译控制码+颜色
    find_ctl_code(uintArrayOUT->at(3),&str,colorOUT);
    *strOUT+=str;
    *strOUT+="->";
    //  翻译命令类型
    find_type_code(uintArrayOUT->at(5),&str);
    *strOUT+=&str;
    *strOUT+="->";
    //  插入对象
    *strOUT+=QString::fromLocal8Bit("对象=")+QString::number(uintArrayOUT->at(6),10);
    *strOUT+="->";
    // 翻译内容
    find_concest_code(uintArrayOUT->at(5),uintArrayOUT->at(7),&str);
    *strOUT+=&str;
    // 翻译特殊的的can打印信息命令
    QVector<uint> arrayIN = *uintArrayOUT;
    if(true == find_debug_code(arrayIN,&str))
    {
        *strOUT+="::";
        *strOUT+=&str;
    }
    //  翻译参数
    find_arg_code(arrayIN,&str);
    *strOUT+=&str;
    //  翻译错误码
    if(uintArrayOUT->at(3) == (uchar)0xF8)
    {
        QString err_str;
        int err_code = (uchar)uintArrayOUT->at(8)*256 + (uchar)uintArrayOUT->at(9);
        find_err_code(err_code,&err_str);
        *strOUT+="==";
        *strOUT+=err_str;
    }
    return true;
}
// 查找控制码的名字和对应的颜色
bool find_ctl_code(uint ctl,QString *str,QColor *color)
{
    int i;
    //控制码
    for(i=0;i<CONTROL_CODE_NUM;i++)
    {
        if( ctl == control_code[i].code )
        {
            *str    = control_code[i].str;
            *color  = control_code[i].col;
            break;
        }
    }
    if( i == CONTROL_CODE_NUM )
    {
        *str    = NO_RECORD;
        *color  = QColor(250,150,250);
        return false;
    }
    return true;
}
// 查找ID码的名字
bool find_id_code(uint16 id,QString *str)
{
    int i;
    //码
    for(i=0;i<ID_CODE_NUM;i++)
    {
        if( id == id_code[i].code )
        {
            *str = id_code[i].str;
            break;
        }
    }
    if( i == ID_CODE_NUM )
    {
        *str = NO_RECORD;
        return false;
    }
    return true;
}
// 查找命令码的中文名字
bool find_type_code(uint cmd,QString *cmd_str)
{
    int i;
    //码
    for(i=0;i<COMMAND_CODE_NUM;i++)
    {
        if( cmd == command_code_type[i].code )
        {
            *cmd_str = command_code_type[i].str;
            break;
        }
    }
    if( i == COMMAND_CODE_NUM )
    {
        *cmd_str = NO_RECORD;
        return false;
    }
    return true;
}
// 查找命令码对应的命令内容的中文名字
bool find_concest_code(uint cmd,uint concest,QString *concest_str)
{
    uint i,j;
    //命令注释
    for(i=0;i<COMMAND_CODE_NUM;i++)
    {
      if( cmd == command_code_type[i].code )//查询命令类型
      {
        for( j=0;j< command_code_type[i].cstr_len;j++)
        {
            if( concest == command_code_type[i].concest_list[j].code )//查询命令内容
            {
                *concest_str=command_code_type[i].concest_list[j].str;
                break;
            }
        }
        if(j==command_code_type[i].cstr_len)
        {
            *concest_str = NO_RECORD;
            return false;
        }
        break;
      }
    }
    if(i==COMMAND_CODE_NUM)
    {
        *concest_str = NO_RECORD;
        return false;
    }
    return true;
}
// 查找正常命令码对应的命令内容的附带参数
bool find_arg_code(QVector<uint>arrayIN,QString *strOUT)
{
    uint cmd_index;
    uint content_index;
    uint ctl_code = arrayIN.at(3);  // 控制码
    uint cmd_code = arrayIN.at(5);  // 命令码
    uint content_code = arrayIN.at(7);  // 命令内容

    *strOUT = " ";
    // 1.非命令，REP类的，不关注参数
    if(  (ctl_code!=FRAME_CONTROL_CODE_COMMAND_REP)\
       &&(ctl_code!=FRAME_CONTROL_CODE_COMMAND_NO_REP)\
       &&(ctl_code!=FRAME_CONTROL_CODE_TS_HEAD)\
       &&(ctl_code!=FRAME_CONTROL_CODE_TS_BODY)\
       &&(ctl_code!=FRAME_CONTROL_CODE_TS_TAIL)\
       &&(ctl_code!=FRAME_CONTROL_CODE_REP)
       )
    {return false;}
    // 2.没有数据不翻译
    if(10 >= arrayIN.size()){return false;}
    // 3.找命令和内容的位置
    for(cmd_index=0;cmd_index<COMMAND_CODE_NUM;cmd_index++)
    {
      if( cmd_code == command_code_type[cmd_index].code )//查询命令类型
      {
        for( content_index=0;content_index< command_code_type[cmd_index].cstr_len;content_index++)
        {
          if( content_code == command_code_type[cmd_index].concest_list[content_index].code )//查询命令内容
          {
            break;
          }
        }
        break;
      }
    }
    // 3.1.没有匹配的情况
    if((cmd_index==COMMAND_CODE_NUM)||(content_index==command_code_type[cmd_index].cstr_len))
    {
        return false;
    }
    // 3.2.到这里，匹配的命令和命令内容的偏移就放在cmd_index和content_index中了
    // 4.选定匹配的参数个数和指针，这里先把要命令内容中的命令参数个数，和参数的内容都放到变量和指针中
    uint  argSize; // 参数个数
    cArg  *argP;   // 参数内容
    if(ctl_code==FRAME_CONTROL_CODE_REP)
    {
        argSize = command_code_type[cmd_index].concest_list[content_index].repArgSize;
        argP    = command_code_type[cmd_index].concest_list[content_index].repArg;
    }
    else
    {
        argSize = command_code_type[cmd_index].concest_list[content_index].ordArgSize;
        argP    = command_code_type[cmd_index].concest_list[content_index].ordArg;
    }
    // 4.1.去除非法数据
    if( 0 == argSize || argSize>10 )
    {
        return false;
    }
    // 5.开始寻找参数
    uint array_index=8;   //读取参数过程中的偏移
    uint arg_index;
    uint value_index;
    // 这里开始翻译参数内容了，参数个数由1~10，每个参数都要遍历
    // 有4种参数的情况：-2=hex打印，-1 = 有符号数，0 = 只有正值，>1 = 有特殊匹配
    *strOUT=QString::fromLocal8Bit("::");
    for(arg_index=0;arg_index<argSize;arg_index++)
    {
        // 获取参数名
        *strOUT += argP[arg_index].str;
        *strOUT += "=";
        // 有符号数字
        if(argP[arg_index].flag == -1)
        {
            int value=0;
            for(value_index=0;value_index<argP[arg_index].size;value_index++)
            {
                //qDebug()<<"size="<<argP[arg_index].size <<"not nag"<<arrayIN.at(array_index);
                value*=256;
                value+=(char)(arrayIN.at(array_index++));
            }
            //qDebug()<<"nag date"<<value;
            // 获取参数值
            *strOUT += QString::number(value);
        }
        else
        // 正数、hex和匹配
        {
            uint value=0;   // 先抽出数据
            for(value_index=0;value_index<argP[arg_index].size;value_index++)
            {   //
                //qDebug()<<"not pos"<<arrayIN.at(array_index);
                value<<=8;
                value|=arrayIN.at(array_index++);
            }
            //qDebug()<<"all date"<<value;

            if(argP[arg_index].flag == 0)
            {   // 获取参数值->整数
                *strOUT += QString::number(value);
            }
            else if(argP[arg_index].flag == -2)
            {   // 获取参数值->hex
                *strOUT += QString::number(value,16);
            }
            else if((argP[arg_index].flag<=10)&&(argP[arg_index].flag>=1))
            {   // 获取参数值->匹配
                int cmp_index;
                for(cmp_index=0;cmp_index<argP[arg_index].flag;cmp_index++)
                {
                    if(value == argP[arg_index].cmp[cmp_index].code)
                    {
                        *strOUT += argP[arg_index].cmp[cmp_index].str;
                        break;
                    }
                }
                // 没有匹配的情况
                if(cmp_index==argP[arg_index].flag)
                {*strOUT += NO_RECORD;}
            }
        }
        *strOUT += " ";
    }
    return true;
}
// 查找主动上次信息帧
bool find_debug_code(QVector<uint>arrayIN,QString *strOUT)
{
    uint ctl_code = arrayIN.at(3);  // 控制码
    uint cmd_code = arrayIN.at(5);  // 命令码
    uint content_code = arrayIN.at(7);  // 命令内容
    uint arg_len  = arrayIN.at(4) - 3;
    // 符合打印故障的条件
    if((ctl_code == FRAME_CONTROL_CODE_UPLOAD)&&(cmd_code == CMD_TYPE_DEBUG)&&(content_code == CMD_UPLOAD_DEBUG_MSG))
    {
        QByteArray qba;
        *strOUT = "\r\n";
        for(uint i=0;i<arg_len;i++)
        {
            qba.append(arrayIN.at(i+8));//参数转为字符串
        }
        *strOUT += qba;
        return true;
    }
    return false;
}
// 查找err码，从err_table中找
bool find_err_code(uint err_code,QString *str)
{
    int i;
    const char error_str[] = "NoRecord";
    //错误事件
    for(i=0;i<ERROR_CODE_NUM;i++)
    {
        if( err_code == error_code[i].code )
        {
            *str = error_code[i].str;
        }
    }
    if( i == error_code[i].code )
    {
        *str = QString::fromLocal8Bit(error_str);
        return false;
    }
    return true;
}

/**全局变量   声明区********************************************************************/

//从机对象编码
code_str id_code[ID_CODE_NUM] =
{
  {0x00,   QString::fromLocal8Bit("主控")},
  {0x01,   QString::fromLocal8Bit("驱动")},
  {0x02,   QString::fromLocal8Bit("自动")},
  {0x03,   QString::fromLocal8Bit("温控")},
  {0x04,   QString::fromLocal8Bit("封闭")},
  {0x05,   QString::fromLocal8Bit("免疫")},
  {0x06,   QString::fromLocal8Bit("其他")},
};
//控制码编码
ctl_code_str control_code[CONTROL_CODE_NUM] =
{
  {FRAME_CONTROL_CODE_COMMAND_REP   ,  QString::fromLocal8Bit("命令帧")      , QColor(0  ,0  ,0  ),     },
  {FRAME_CONTROL_CODE_COMMAND_NO_REP,  QString::fromLocal8Bit("无应答命令帧"), QColor(10 ,10 ,10 ),     },
  {FRAME_CONTROL_CODE_TS_HEAD       ,  QString::fromLocal8Bit("时序包头")    , QColor(50,50,50),        },
  {FRAME_CONTROL_CODE_TS_BODY       ,  QString::fromLocal8Bit("时序包体")    , QColor(100,100,100),     },
  {FRAME_CONTROL_CODE_TS_TAIL       ,  QString::fromLocal8Bit("时序包尾")    , QColor(150,150,150),     },
  {FRAME_CONTROL_CODE_REP           ,  QString::fromLocal8Bit("REP")  , QColor(  0,  0,200),     },
  {FRAME_CONTROL_CODE_ACK           ,  QString::fromLocal8Bit("ACK")  , QColor(  0,200,  0),     },
  {FRAME_CONTROL_CODE_EVT           ,  QString::fromLocal8Bit("EVT")  , QColor(255,  0,  0),     },
  {FRAME_CONTROL_CODE_UPLOAD        ,  QString::fromLocal8Bit("UPLOAD") , QColor(  0,200,200),     }
};


// 下面这些数组的顺序不能改变


#include "array_content_code.h" // 命令内容的数组
#include "array_command_code.h" // 命令类型的数组
#include "array_error_code.h"   // 错误码的数组
