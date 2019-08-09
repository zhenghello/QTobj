#ifndef __COMMONRES_H
#define __COMMONRES_H

//定义EVT帧最大长度
#define EVT_FRAME_MAX_SIZE_USB                     (10u)

//协议帧起始码
#define PROTOCOL_FRAME_START_CODE_USB               (0xAA)
//协议帧停止码
#define PROTOCOL_FRAME_STOP_CODE_USB                (0x55)

//协议帧格式下标
#define FRAME_START_INDEX_USB                       (0u)  //起始
#define FRAME_CONTROL_INDEX_USB                     (1u)  //控制
#define FRAME_DATALEN_INDEX_USB                     (2u)  //数据长度
#define FRAME_COMMAND_INDEX_USB                     (4u)  //命令码
#define FRAME_COMMAND_TYPE_INDEX_USB                (4u)  //命令类型
#define FRAME_COMMAND_NUM_INDEX_USB                 (5u)  //命令对象
#define FRAME_COMMAND_CONTENT_INDEX_USB             (6u)  //命令内容
#define FRAME_COMMAND_PARAM_INDEX_USB               (7u)  //命令参数

//控制码编码
#define FRAME_CONTROL_CODE_COMMAND_REP_USB          (0x00) //主站下传命令帧(需回REP)
#define FRAME_CONTROL_CODE_COMMAND_NO_REP_USB       (0x40) //主站下传命令帧(不需回REP)
#define FRAME_CONTROL_CODE_TS_HEAD_USB              (0x41) //时序包包头
#define FRAME_CONTROL_CODE_TS_BODY_USB              (0x42) //时序包包体
#define FRAME_CONTROL_CODE_TS_TAIL_USB              (0x43) //时序包包尾
#define FRAME_CONTROL_CODE_REP_USB                  (0xC0) //从站响应帧REP
#define FRAME_CONTROL_CODE_ACK_USB                  (0xD4) //从站应答帧ACK
#define FRAME_CONTROL_CODE_EVT_USB                  (0xF8) //从站异常帧EVT
#define FRAME_CONTROL_CODE_UPLOAD_USB               (0xD8) //从站主动上传帧
#define FRAME_CONTROL_CODE_UPLOAD_INF               (0xC4) //主动上传信息帧

//控制码mask
#define CONTROL_CODE_RETURNFLAG_MASK_USB            (0x40)
#define CONTROL_CODE_IDENT_MASK_USB                 (0x03)

//控制码识别编码
#define CONTROL_CODE_IDENT_CMD_USB                  (0x00) //命令
#define CONTROL_CODE_IDENT_TS_HEAD_USB              (0x01) //时序包头
#define CONTROL_CODE_IDENT_TS_BODY_USB              (0x02) //时序包体
#define CONTROL_CODE_IDENT_TS_TAIL_USB              (0x03) //时序包尾

//帧需要返回REP
#define FRAME_RETURN_REP_USB(x)     (CONTROL_CODE_RETURNFLAG_MASK_USB != ((x) & CONTROL_CODE_RETURNFLAG_MASK_USB))

#define EXIT_FAILURE_LOCOAL  -272
#define EXIT_SUCCESS_LOCOAL  0

//返回帧转态
typedef enum
{
	NONE_RETURN_USB = 0x00, //不需要返回
	NEED_ACK_USB,           //应答
	NEED_REP_USB,           //响应
	NEED_EVT_USB,           //异常
	NEED_UPLOAD_USB,        //主动上传
} return_frame_state_e_usb;

//帧格式检查状态定义
typedef enum
{
	FRAME_CHECK_START_USB = 0x00u, //开始码
	FRAME_CHECK_CONTROL_USB,       //控制码
	FRAME_CHECK_DATALENH,       //数据长度
	FRAME_CHECK_DATALENL,
	FRAME_CHECK_DATA_USB,          //数据
	FRAME_CHECK_CHECKSUM_USB,      //校验和
	FRAME_CHECK_STOP_USB          //停止码
} check_state_e_usb;

//帧返回结构体定义
typedef struct _return_frame_buf_usb
{
    UINT8 flag;                 //返回帧类型
    UINT8 ctl_code;             //控制码
    UINT8 cmd_type;             //命令类型
    UINT8 cmd_num;              //命令对象
    UINT8 cmd_content;          //命令内容
    UINT8 node_num;             //节点号
    UINT8 reserve;             //保留
    UINT8 err_code;            //错误码
    UINT8 state_len;            //查询命令的返回数据长度
    UINT8 *pstate_buff;         //查询命令的返回数据缓冲区 //命令执行完后申请，rep后释放
    //timeseq_cmd_t *ptimeseq_cmd;//指向时序命令缓冲区
} return_buf_t;

//帧格式检查结构体定义
typedef struct _check_frame_usb
{
	volatile UINT8 check_state; //帧检查状态
	volatile UINT16 frame_data_len; //帧数据区长度
	volatile UINT8 check_sum; //帧数据区校验和
	volatile UINT8 timeseq_cur_save_index; //当前时序包存放位置
	volatile UINT8 timeseq_save_index; //时序包存放位置
	volatile UINT8 buff_index; //缓冲区下标
	volatile UINT8 pre_frame_data; //上一次数据
	//uint8 buff[PROTOCOL_FRAME_MAX_SIZE]; //帧缓冲区
	//uint8 state_buff[QUERY_CMD_STATE_DATA_MAX_SIZE]; //状态数据返回缓冲区
	UINT8 *pbuff; //帧缓冲区，判断帧数据区长度后申请，命令执行完后释放
	//	  uint8 *pstate_buff; //状态数据返回缓冲区，命令执行完后申请，rep后释放//没有必要将rep返回值存于此处
	return_buf_t return_buff; //帧返回缓冲区
} frame_check_t_usb;

#endif //commonres.h