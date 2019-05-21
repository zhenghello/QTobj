/******************************************************************************/
#ifndef __TIMESEQRES_H
#define __TIMESEQRES_H
/******************************************************************************/
#include "deftype.h"
/******************************************************************************/
//时序命令帧格式下标
#define TS_FRAME_CONTROL_INDEX                  (0u)
#define TS_FRAME_DATALEN_INDEX                  (1u)
#define TS_FRAME_COMMAND_INDEX                  (2u)
#define TS_FRAME_COMMAND_TYPE_INDEX             (2u)
#define TS_FRAME_COMMAND_NUM_INDEX              (3u)
#define TS_FRAME_COMMAND_CONTENT_INDEX          (4u)
#define TS_FRAME_COMMAND_PARAM_INDEX            (5u)
//时序帧控制码
#define TS_FRAME_CONTROL_CODE_HEAD              (0x41)
#define TS_FRAME_CONTROL_CODE_BODY              (0x42)
#define TS_FRAME_CONTROL_CODE_TAIL              (0x43)
//时序包最大命令数
//#define TIMESEQ_MAX_CMD_NUM                     (600u)
#define TIMESEQ_MAX_CMD_NUM                     (1000u)
//时序包命令存放长度(通常为：控制码1+数据长度1+命令码3+参数长度12)
//#define TIMESEQ_CMD_FRAME_SIZE                  (18u)
#define TIMESEQ_CMD_FRAME_SIZE                  (12u)
//时序包缓冲区大小
#define TIMESEQ_BUF_SIZE                        (TIMESEQ_MAX_CMD_NUM*TIMESEQ_CMD_FRAME_SIZE)
//最大缓存时序包数
#define TIMESEQ_SAVE_MAX_NUM                    (2u)
//最大运行时序包数
#define TIMESEQ_RUN_MAX_NUM                     (4u)
//最大时序号定义
//#define MAX_TIMESEQ_NUM                         (200u)
#define MAX_TIMESEQ_NUM                         (1022u)

//时序包缓冲区状态
typedef enum
{
    NONE_TIMESEQ = 0x00,     //没有时序
    HAVE_TIMESEQ,            //有时序
    RECEIVING_TIMESEQ_FRAME, //正在接收时序
    TIMESEQ_RUNNING,         //时序正在运行
} timeseq_buf_state_e;
//时序包运行状态
typedef enum
{
    TIMESEQ_NO_RUNNING = 0x00, //时序包不运行
    TIMESEQ_NEED_RUNNING,      //时序包运行
} timeseq_running_state_e;

//时序命令缓存
typedef struct _timeseq_cmd
{
    uint8 ctl_code;     //控制码
    uint8 cmd_type;     //命令类型
    uint8 cmd_num;      //命令对象
    uint8 cmd_content;  //命令内容
    uint16 reserve;     //保留（时序号）
} timeseq_cmd_t;
//时序包缓冲区结构体定义
typedef struct _timeseq_buf
{
    uint8 state;             //时序包状态
    uint8 run_cnt;           //时序包重复运行次数
    uint16 num;              //时序号
    uint16 cmd_size;         //时序包命令总数（时序包包体数）
    uint16 *pcmd_start_time; //命令启动时间
    uint8 *pcmd_buff;        //时序包命令缓冲区
    uint16 *pcmd_num;        //时序命令号
} timeseq_buf_t;
//时序包运行控制结构体定义
typedef struct _timeseq_ctl
{
    uint8 state;              //时序包运行状态
    uint8 run_timeseq_num;    //当前运行的时序包号
    uint8 cur_run_index;      //当前运行的时序在缓冲区中的位置
    uint16 run_time;          //当前时序运行时间
    uint16 exec_cmd_cnt;      //对执行的命令计数
    timeseq_cmd_t timeseq_cmd;//时序命令缓存
} timeseq_ctl_t;
/******************************************************************************/
#endif
/******************************************************************************/
