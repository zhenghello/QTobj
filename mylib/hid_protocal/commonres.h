/******************************************************************************/
#ifndef __COMMONRES_H
#define __COMMONRES_H
/******************************************************************************/
#include "deftype.h"
//#include "timeseqres.h"
/******************************************************************************/
//协议帧最大长度定义
#define PROTOCOL_FRAME_MAX_SIZE                (250u)
//定义ACK帧最大长度
#define ACK_FRAME_MAX_SIZE                     (10u)
//定义REP帧最大长度
#define REP_FRAME_MAX_SIZE                     (80u)
//定义EVT帧最大长度
#define EVT_FRAME_MAX_SIZE                     (10u)
//查询命令返回数据的最大长度
#define QUERY_CMD_STATE_DATA_MAX_SIZE          (72)

//协议帧起始码
#define PROTOCOL_FRAME_START_CODE               (0xAA)
//协议帧停止码
#define PROTOCOL_FRAME_STOP_CODE                (0x55)

//协议帧格式下标
#define FRAME_START_INDEX                       (0u)  //起始
#define FRAME_CONTROL_INDEX                     (1u)  //控制
#define FRAME_DATALEN_INDEX                     (2u)  //数据长度
#define FRAME_COMMAND_INDEX                     (3u)  //命令码
#define FRAME_COMMAND_TYPE_INDEX                (3u)  //命令类型
#define FRAME_COMMAND_NUM_INDEX                 (4u)  //命令对象
#define FRAME_COMMAND_CONTENT_INDEX             (5u)  //命令内容
#define FRAME_COMMAND_PARAM_INDEX               (6u)  //命令参数

//控制码编码
#define FRAME_CONTROL_CODE_COMMAND_REP          (0x00) //主站下传命令帧(需回REP)
#define FRAME_CONTROL_CODE_COMMAND_NO_REP       (0x40) //主站下传命令帧(不需回REP)
#define FRAME_CONTROL_CODE_TS_HEAD              (0x41) //时序包包头
#define FRAME_CONTROL_CODE_TS_BODY              (0x42) //时序包包体
#define FRAME_CONTROL_CODE_TS_TAIL              (0x43) //时序包包尾
#define FRAME_CONTROL_CODE_REP                  (0xC0) //从站响应帧REP
#define FRAME_CONTROL_CODE_ACK                  (0xD4) //从站应答帧ACK
#define FRAME_CONTROL_CODE_EVT                  (0xF8) //从站异常帧EVT
#define FRAME_CONTROL_CODE_UPLOAD               (0xD8) //从站主动上传帧
#define UPLOAD_INF_FRAME_CONTROL_CODE          (0xC4) //帧控制码,这个代表后续会有2字节的长度字符串

//控制码mask
#define CONTROL_CODE_TRANSDIR_MASK              (0x80)
#define CONTROL_CODE_RETURNFLAG_MASK            (0x40)
#define CONTROL_CODE_ABNORMALFLAG_MASK          (0x20)
#define CONTROL_CODE_FUNCTION_MASK              (0x1C)
#define CONTROL_CODE_IDENT_MASK                 (0x03)
//控制码功能编码
#define CONTROL_CODE_FUNCTION_CMD               (0x00) //命令
#define CONTROL_CODE_FUNCTION_ACK               (0x14) //应答
#define CONTROL_CODE_FUNCTION_UPLOAD            (0x18) //主动上传
//控制码识别编码
#define CONTROL_CODE_IDENT_CMD                  (0x00) //命令
#define CONTROL_CODE_IDENT_TS_HEAD              (0x01) //时序包头
#define CONTROL_CODE_IDENT_TS_BODY              (0x02) //时序包体
#define CONTROL_CODE_IDENT_TS_TAIL              (0x03) //时序包尾

//帧不需要返回REP
#define FRAME_NOT_RETURN_REP(x) (CONTROL_CODE_RETURNFLAG_MASK == ((x) & CONTROL_CODE_RETURNFLAG_MASK))
//帧需要返回REP
#define FRAME_RETURN_REP(x)     (CONTROL_CODE_RETURNFLAG_MASK != ((x) & CONTROL_CODE_RETURNFLAG_MASK))

//返回帧转态
typedef enum
{
    NONE_RETURN = 0x00, //不需要返回
    NEED_ACK,           //应答
    NEED_REP,           //响应
    NEED_EVT,           //异常
    NEED_UPLOAD,        //主动上传
} return_frame_state_e;
//帧格式检查状态定义
typedef enum
{
    FRAME_CHECK_START = 0x00u, //开始码
    FRAME_CHECK_CONTROL,       //控制码
    FRAME_CHECK_DATALEN,       //数据长度
    FRAME_CHECK_DATA,          //数据
    FRAME_CHECK_CHECKSUM,      //校验和
    FRAME_CHECK_STOP,          //停止码
    FRAME_CHECK_ERROR          //错误
} check_state_e;


//帧返回结构体定义
typedef struct _return_frame_buf
{
    uint8 flag       ;          //返回帧类型
    uint8 ctl_code   ;           //控制码
    uint8 cmd_type   ;           //命令类型
    uint8 cmd_num    ;           //命令对象
    uint8 cmd_content;           //命令内容
    uint8 node_num   ;           //节点号
    uint16 reserve   ;          //保留
    uint16 err_code  ;          //错误码
    uint8 state_len  ;          //查询命令的返回数据长度
    uint8 *pstate_buff;         //查询命令的返回数据缓冲区
//    timeseq_cmd_t *ptimeseq_cmd;//指向时序命令缓冲区
} return_buf_t;
//定义函数指针类型
typedef int32 (*pfncmdproc)(cuint8 *ppara_buff, uint8 para_len, \
                            return_buf_t *preturn_buff);
//命令处理结构体定义
typedef struct
{
    uint8 cmd_code;       //命令码
    pfncmdproc fncmdproc; //执行命令
} cmd_proc_t;
//帧格式检查结构体定义
typedef struct _check_frame
{
    volatile uint8 check_state; //帧检查状态
    volatile uint8 frame_data_len; //帧数据区长度
    volatile uint8 check_sum; //帧数据区校验和
    volatile uint8 timeseq_cur_save_index; //当前时序包存放位置
    volatile uint8 timeseq_save_index; //时序包存放位置
    volatile uint8 buff_index; //缓冲区下标
    volatile uint8 pre_frame_data; //上一次数据
    uint8 buff[PROTOCOL_FRAME_MAX_SIZE]; //帧缓冲区
    uint8 state_buff[QUERY_CMD_STATE_DATA_MAX_SIZE]; //状态数据返回缓冲区
    return_buf_t return_buff; //帧返回缓冲区
} frame_check_t;
/******************************************************************************/
#endif
/******************************************************************************/
