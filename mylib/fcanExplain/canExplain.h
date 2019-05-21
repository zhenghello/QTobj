#ifndef CANEXPLAIN_H
#define CANEXPLAIN_H

#include<QVector>
#include<QString>
#include<QColor>
#include "command.h"
#include "errtable.h"
#include "commonres.h"

#define ARG_SIZE_MAX 20
#define CMP_SIZE_MAX 20
//代码对应的字符串输出
typedef struct _code_str
{
    uint    code; //代码
    QString str; //执行命令
}code_str;

//代码对应的字符串和颜色输出
typedef struct _ctl_code_str
{
    uint     code; //代码
    QString  str;  //中文命令
    QColor   col;  //命令码对应 的颜色
}ctl_code_str;

// 附带参数结构体
typedef struct _cArg
{
    int      flag;    // 数据类型，只有整数=0，有负数=-1，hex显示=-2,有特殊匹配数>0,这时flag为匹配的最大对象个数，最多为10个
    uint     size;    // 占用长度>0
    QString  str;     // 附带参数的名称
    code_str cmp[CMP_SIZE_MAX]; // 最多十个
}cArg;
// 命令结构体
typedef struct _cCmd
{
    uint         code;
    QString      str;
    uint         ordArgSize;
    cArg         *ordArg;//命令的附带参数
    uint         repArgSize;
    cArg         *repArg;//应答的附带参数
}cCmd;
// 类型结构体
typedef struct _command_code_str
{
   uint         code;       //代码
   QString      str;        //执行命令
   uint         cstr_len;   //执行的详细命令的长度
   cCmd         *concest_list; //执行的详细命令列表
}command_code_str;
// 错误类型编码
typedef struct _err_code_str
{
    uint         code; //代码
    QString      str;  //执行命令
}err_code_str;

// 解释can的命令
bool canStr2explainStr(QString strIN, QVector<uint> *arrayOUT, QString *strOUT, QColor *colorOUT);


#endif // CARG_H
