/**********************************************************************/
#ifndef __ERRTABLE_H
#define __ERRTABLE_H
/**********************************************************************/
//错误码定义
typedef enum _err_id
{
  NO_ERR = 0x0000,//无错
/******************************板卡错误********************************/
  ERR_DB_BUG = 0x0100,//驱动板bug
  ERR_DB_INPUT_PARAM = 0x0110,//输入参数错误
  ERR_DB_READ_FPGA = 0x0200,//读FPGA错误
  ERR_DB_WRITE_FPGA = 0x0210,//写FPGA错误
/******************************协议帧错误******************************/
  ERR_DB_CMD_FORMAT_START = 0x1000,//帧起始码错误
  ERR_DB_CMD_FORMAT_CONTROL = 0x1010,//帧控制码错误
  ERR_DB_CMD_FORMAT_DATALEN = 0x1020,//帧长度错误
  ERR_DB_CMD_FORMAT_CHECKSUM = 0x1030,//帧校验和错误
  ERR_DB_CMD_FORMAT_STOP = 0x1040,//帧停止码错误
  ERR_DB_CMD_INVALID = 0x1050,//无效命令
  ERR_DB_CMD_PARAM_LEN = 0x1060,//帧命令参数的长度错误
/*****************************升级*************************************/
  ERR_DB_IS_BOOT_MODE = 0x1100,//当前已在BOOT模式下
  ERR_DB_IS_NOT_BOOT_MODE = 0x1110,//当前不在BOOT模式下
  ERR_DB_UPGRADE_START_ADDR = 0x1120,//升级起始地址错误
  ERR_DB_ERASE_FLASH_SECTOR = 0x1130,//擦除扇区错误
  ERR_DB_WRITE_FLASH = 0x1140,//写flash错误
  ERR_DB_UPGRADE_DATA = 0x1150,//数据升级错误
  ERR_DB_UPGRADE_STATE = 0x1160,//升级状态错误
  ERR_DB_FPGA_EPCS = 0x1170,//EPCS类型错误
  ERR_DB_FPGA_UPGRADE_START_ADDR = 0x1180,//FPGA升级起始地址错误
  ERR_DB_FPGA_READ_EPCS_ID = 0x1190,//读取EPCS id错误
  ERR_DB_FPGA_ERASE_EPCS = 0x11a0,//擦除EPCS错误
  ERR_DB_FPGA_WRITE_EPCS = 0x11b0,//写EPCS错误
  ERR_DB_FPGA_READ_EPCS = 0x11c0,//读EPCS错误
  ERR_DB_FPGA_IS_NOT_UPGRADE_MODE = 0x11d0,//不是FPGA升级模式
  
  ERR_FPGA_UPGRADE = 0x11e0,//fpga升级错误
/*****************************时序*************************************/
  ERR_DB_TIMESEQ_HEAD_FRAME = 0x1400,//时序包包头帧错误
  ERR_DB_TIMESEQ_BODY_FRAME = 0x1410,//时序包包体帧错误
  ERR_DB_TIMESEQ_TAIL_FRAME = 0x1420,//时序包包尾帧错误
  ERR_DB_TIMESEQ_NUMBER = 0x1430,//时序号错误
  ERR_DB_TIMESEQ_RECEIVING_OR_RUNNING = 0x1440,//时序正在接收或运行中
  ERR_DB_TIMESEQ_FRAME_SIZE = 0x1450,//时序包帧错误
  ERR_DB_TIMESEQ_CONTROL_BUSY = 0x1460,//时序控制忙
  ERR_DB_TIMESEQ_NUMBER_NONE = 0x1470,//驱动板时序缓冲区中无此时序
  ERR_DB_TIMESEQ_STOP = 0x1480,//停止时序错误
/******************************阀**************************************/
  ERR_DB_CONTROL_VALVE = 0x2000,//控制阀错误
  ERR_DB_VALVE_STATE = 0x2100,//查询阀状态错误
  ERR_DB_VALVE_NUM = 0x2200,//阀号错误
/******************************泵**************************************/
  ERR_DB_CONTROL_PUMP = 0x3000,//泵控制错误
  ERR_DB_PUMP_STATE = 0x3100,//查询泵状态错误
  ERR_DB_PUMP_NUM = 0x3200,//泵号错误
/******************************电机************************************/
  ERR_DB_CONFIG_MOTOR = 0x4000,//配置电机错误
  ERR_DB_GET_MOTOR_CONFIG = 0x4010,//获取电机配置错误
  ERR_DB_MOTOR_NUM = 0x4100,//电机号错误
  ERR_DB_MOTOR_SPEED = 0x4110,//电机挡速错误
  ERR_DB_MOTOR_MAXTIME = 0x4120,//电机动作命令中执行时间参数太小
  ERR_DB_MOTOR_STEPS_ZERO = 0x4130,//电机步数为0
  ERR_DB_MOTOR_POS = 0x4140,//启动电机走位置时位置错误
  ERR_DB_MOTOR_BUSY = 0x4150,//电机忙
  ERR_DB_MOTOR_START_ACTION_RSTEP_GTR0 = 0x4160,//动作启动前电机剩余步数大于0
  ERR_DB_MOTOR_BACK_TO_INITPOS_STEPS_TOO_LARGE = 0x4170,//电机回初始位步数太大
  ERR_DB_MOTOR_LEAVE_INITPOS_STEPS_TOO_LARGE = 0x4180,//电机离开初始位步数太大
  ERR_DB_MOTOR_OPT_ERR_POS = 0x4190, //电机光耦错误
  ERR_DB_MOTOR_WRITE_PARAM = 0x41a0, //写电机参数错误
  ERR_DB_MOTOR_READ_RSTEP = 0x41b0,//读取电机剩余步数错误
  ERR_DB_MOTOR_NOT_LEAVE_INIT_POS = 0x41c0,//电机未离开初始位
  ERR_DB_MOTOR_NOT_BACK_INIT_POS = 0x41d0,//电机未回到初始位
  ERR_DB_MOTOR_LOST_STEPS = 0x41e0,//电机丢步
  ERR_DB_MOTOR_NOT_MOVE_TO_POS = 0x41f0,//电机未走到目标位置
  ERR_DB_MOTOR_EXEC_TIME_OUT = 0x4200,//电机执行超时
/********************************采样组件******************************/
  ERR_DB_CONFIG_SAMPLE = 0x5000,//配置采样组件错误
  ERR_DB_SAMPLE_BUSY = 0x5100,//采样组件忙
  ERR_DB_SAMPLE_EXEC_TIME_OUT = 0x5110,//采样组件执行超时
  ERR_DB_SAMPLE_H_POS = 0x5120,//采样组件水平位置错误
  ERR_DB_SAMPLE_V_POS = 0x5130,//采样组件垂直位置错误
  ERR_DB_SAMPLE_SWING_TIMES = 0x5140,//采样组件摆动次数错误
  ERR_DB_SAMPLE_SWING_HPOS1 = 0x5150,//采样组件摆动前水平位置错误
  ERR_DB_SAMPLE_SWING_HPOS2 = 0x5160,//采样组件摆动后水平位置错误
  ERR_DB_SAMPLE_SWING_VPOS = 0x5170,//采样组件摆动前垂直位置错误
/*********************************压力*********************************/
  ERR_DB_CONFIG_PRESSURE = 0x6000,//配置压力错误
  ERR_DB_READ_PRESSURE_AD = 0x6010,//读取压力AD错误
  ERR_DB_PRESSURE_NOT_WHIHIN_THE_RANGE = 0x6020,//检查压力时当前压力不在范围内
  ERR_DB_PRESSURE_TOO_LOW = 0x6030,//检查通道压力时，当前压力低于指定压力
  ERR_DB_PRESSURE_TOO_HIGH = 0x6040,//检查通道压力时，当前压力高于指定压力
  ERR_DB_BUILD_PRESSURE_CMD_PARAM = 0x6100,//建压参数错误
  ERR_DB_BUILD_PRESSURE_BUSY = 0x6110,//建压忙
  ERR_DB_BUILD_PRESSURE_FAILURE = 0x6120,//建压失败
  ERR_DB_BUILD_PRESSURE_TOO_HIGH = 0x6130,//压力绝对值太高
  ERR_DB_BULID_PRESSURE_OPEN_PUMP_TOO_LONG = 0x6140,//建压时开泵时间太长
  ERR_DB_MPRESSURE_CMD_PARAM = 0x6200,//压力监控时命令参数错误
  ERR_DB_MPRESSURE_BUSY = 0x6210,//此通道正在监控压力
  ERR_DB_MPRESSURE_NOT_WHIHIN_THE_RANGE = 0x6220,//压力监控时当前压力不在指定范围内
/**********************************试剂********************************/
  ERR_DB_CONFIG_REAGENT = 0x7000,//配置试剂错误
  ERR_DB_READ_REAGENT_STATE = 0x7010,//读试剂状态错误
  ERR_DB_REAGENT_DETEC_CMD_PARAM = 0x7020,//试剂检测命令参数错误
  ERR_DB_REAGENT_DETEC_BUSY = 0x7030,//试剂检测忙
  ERR_DB_NO_REAGENT = 0x7040,//无试剂
  ERR_DB_REAGENT_CONTROL = 0x7050,//试剂控制错误
  ERR_DB_GET_NONE_REAGENT = 0x7060,//获取无试剂时间出错
  ERR_DB_SET_NONE_REAGENT_THRESHOLD = 0x7070,//设置无试剂阈值时间出错
  ERR_DB_WASTE_REAGENT_FULL = 0x7080,//机外废液满
  
  ERR_WASTE_REAGENT_EXTERN_FULL = 0x7081,//机内废液满
  ERR_SCI_SWITCH_REAGENT_EMPTY = 0x7090,//SCI浮子传感器异常
  ERR_FCM_SWITCH_REAGENT_EMPTY = 0x7091,//FCM浮子传感器异常
  ERR_DIL_SWITCH_REAGENT_EMPTY = 0x7092,//DIL浮子传感器异常
  ERR_WC1_SWITCH_REAGENT_EMPTY = 0x7093,//WC1浮子传感器异常
  ERR_WC2_SWITCH_REAGENT_EMPTY = 0x7094,//WC2浮子传感器异常
	
	ERR_REAGENTS_ROOM_PUT_REAGENT = 0x7095, //试剂盘放入了试剂
	
/**********************************温度********************************/
  ERR_DB_CONFIG_TEMP = 0x8000,//温度配置错误
  ERR_DB_READ_TEMP = 0x8010,//读取温度错误
  ERR_DB_CONTROL_TEMP = 0x8020,//温度控制出错
  ERR_DB_TEMP_OUT_OF_WORK_RANGE = 0x8030,//温度超出工作范围
  ERR_DB_TEMP_OUT_OF_RUN_RANGE = 0x8040,//温度超出运行范围
  ERR_DB_FAN_SPEED_IS_TOO_LOW = 0x8100,//风扇转速太低
/*********************************其他*********************************/
  ERR_DB_RIGHT_FRONT_DOOR_OPEN = 0x9000,//右侧门打开
  ERR_DB_LASER_COVER_OPEN = 0x9010,//激光器盒子打开
  ERR_CRP_CRPDOOR_OPEN = 0x9020,//CRP试剂门打开
  
  ERR_LASER_DOOR_OPEN = 0x9011,//光学门打开
  ERR_SHEATH_DOOR_OPEN = 0x9012,//鞘流阻抗门打开
  ERR_FRONT_SAVE_DOOR_OPEN = 0x9013,//前面板安全门打开
	
	ERR_REAGENTS_ROOM_DOOR_OPEN = 0x9014, //试剂盘仓门打开
	ERR_CUP_ROMM_DOOR_OPEN = 0x9015, //反应杯仓门打开
	
	ERR_CUP_ROOM_CUP_EMPTY = 0x9016, //反应杯仓反应杯空
  
/*********************************电源电压监控*************************/
  ERR_POWER_OUT_OF_RANGE_5V = 0x9030,//5V电源电压异常
  ERR_POWER_OUT_OF_RANGE_12V = 0x9031,//12V电源电压异常
  ERR_POWER_OUT_OF_RANGE_24V = 0x9032,//24V电源电压异常
/**********************************************************************/
/**********************************灌注********************************/
  ERR_PERFUSION_VALVE_CTL = 0x9040,//灌注时阀控制错误
  ERR_PERFUSION_SWITCH_CTL = 0x9041,//灌注时浮子传感器控制错误
  ERR_PERFUSION_TIME_TOO_LONG = 0x9042,//灌注时间太长
/**********************************排空********************************/
  ERR_EVACUATION_VALVE_CTL = 0x9050,//排空时阀控制错误
  ERR_EVACUATION_SWITCH_CTL = 0x9051,//排空时浮子传感器控制错误
  ERR_EVACUATION_TIME_TOO_LONG = 0x9052,//排空时间太长
/**********************************样本试剂运动组件********************/
  ERR_SAMPLES_REAGENTS_EXEC_TIME_OUT = 0x9060, //样本试剂运动组件执行超时
  ERR_SAMPLES_REAGENTS_BUSY = 0x9061, //样本试剂运动组件忙
  ERR_SAMPLES_REAGENTS_VPOS = 0x9062, //样本试剂运动组件垂直位置错误
  ERR_SAMPLES_REAGENTS_HATCHERY_MOTOR_POS = 0x9063, //样本试剂运动组件孵育池混匀电机位置错误
  ERR_SAMPLES_REAGENTS_LRPOS = 0x9064, //样本试剂运动组件左右电机位置错误
/**********************************试剂池混匀组件**********************/
  ERR_REAGENT_ROOM_MIX_EXEC_TIME_OUT = 0x9070,//试剂池混匀组件执行超时
  ERR_REAGENT_ROOM_MIX_BUSY = 0x9071, //试剂池混匀组件忙
  ERR_REAGENT_ROOM_MOTOR_POS = 0x9072, //试剂池混匀电机位置错误
/**********************************************************************/
//保留0xa000~0xafff
/********************************条码扫描器****************************/
  ERR_DB_BARCODE_CMD_PARAM = 0xa000,//命令参数错误
  ERR_DB_BARCODE_IS_SCANNNING = 0xa010,//正在扫描
  ERR_DB_BARCODE_SCAN_TIMEOUT = 0xa020,//扫描超时
/******************************智能卡读卡器****************************/
  ERR_DB_SMARTCARD_RESET = 0xa030,//读卡器复位错误
  ERR_DB_SMARTCARD_INIT  = 0xa031,//智能卡初始化错误
  ERR_DB_SMARTCARD_RETURN = 0xa032,//智能卡指令执行错误
	
	ERR_DB_SMARTCARD_VERSION = 0xa033,//智能卡版本错误
	ERR_DB_SMARTCARD_CMD_TRAS = 0xa034,//读卡器与智能卡之间指令传输错误
	ERR_DB_SMARTCARD_KEY_EXAUTH = 0xa035,//外部认证密钥错误
	ERR_DB_SMARTCARD_KEY_FILE_LINE = 0xa036,//文件线路密钥错误
	
/********************************码盘控*************************/
  ERR_INIT_OPT  = 0xb000, //初始化时初始位光耦故障
	ERR_CODE_WHEEL_ACTION_POS_OPT_OR_MOTOR = 0xb001, //码盘初始化时位置光耦故障或者电机故障
	ERR_CODE_WHEEL_EXEC_TIME_OUT = 0xb002,    //码盘动作超时
	ERR_CODE_WHEEL_BUSY = 0xb003,             //码盘忙
	ERR_CODE_WHEEL_POS = 0xb004,              //码盘走位置失败
	ERR_MOTOR_OR_INIT_OPT_AND_POS_OPT = 0xb005, //初始化时电机不动或者初始位光耦和位置光耦同时无效
	ERR_POS_OPT = 0xb006,                       //初始化时位置光耦故障
	ERR_CODER_MOTOR_EXEC_TIME_OUT = 0xb007,     //编码器电机动作超时
	ERR_CODER_MOTOR_BUSY = 0xb008,              //编码器电机忙
	ERR_REAGENTS_NEEDLE_COLLISION = 0xb009,     //试剂采样针撞针
	ERR_REAGENTS_NEEDLE_SUCK_NO_REAGENT = 0xb00a,  //试剂针吸取试剂失败，表明没有试剂
	ERR_SAMPLE_REAGENTS_BUSY = 0xb00b,          //试剂采样组件忙
	ERR_SAMPLE_REAGENTS_V_POS = 0xb00c,         //试剂采样组件水平走位置时，垂直电机不在初始位
	
	ERR_SUCK_MIX_INIT = 0xb00d,  //吸样混匀组件初始化错误
	ERR_SUCK_MIX_SUCK = 0xb00e,  //吸样混匀组件吸样错误
	ERR_SUCK_MIX_SUCK_END = 0xb00f, //吸样混匀组件吸样结束错误
	ERR_SUCK_MIX_MIX = 0xb010,   //吸样混匀组件混匀错误
	ERR_SUCK_MIX_MIX_END = 0xb011, //吸样混匀组件混匀结束错误
	ERR_SUCK_MIX_EXEC_TIME_OUT = 0xb012, //吸样混匀组件执行超时
	ERR_SUCK_MIX_BUSY = 0xb013,  //吸样混匀组件忙
	
	ERR_THROW_CUP_INIT = 0xb014,   //抛杯组件初始化错误
	ERR_THROW_CUP_THROW = 0xb015,  //抛杯组件抛杯时出错
	ERR_THROW_CUP_EXEC_TIME_OUT = 0xb016, //抛杯组件执行超时
	ERR_THROW_CUP_BUSY = 0xb017,  //抛杯组件忙
	
	ERR_ADD_CUP = 0xb018,   //加杯故障，反应杯没有成功加到孵育盘中
	
	ERR_FEED_CUP_INIT = 0xb019,  //进杯组件初始化错误
	ERR_FEED_CUP_FEED = 0xb01a,  //进杯组件进杯错误
	ERR_FEED_CUP_NO_CUP = 0xb01b, //进杯组件判定反应杯仓没有反应杯了
	ERR_FEED_CUP_LITTLE_CUP = 0xb01c, //进杯组件判定反应杯仓反应杯不足
	ERR_FEED_CUP_FEED_COM = 0xb01d,  //进杯组件进杯部分故障，进不了杯
	ERR_FEED_CUP_BUSY = 0xb01e, //进杯组件忙
	
	ERR_ADD_CUP_EXEC_TIME_OUT = 0xb01f, //加杯组件执行超时
	ERR_ADD_CUP_BUSY = 0xb020,  //加杯组件忙
	ERR_ADD_CUP_POS_HAVE_CUP = 0xb021,  //当前位置有反应杯
	
	ERR_REAGENTS_ROOM_BUSY = 0xb022,  //试剂池组将忙
	ERR_HATCHERY_ROOM_BUSY = 0xb023,  //孵育池组件忙
	
	ERR_SLAVE_DEBUG_EXEC_TIME_OUT = 0xb024,  //从站调试执行超时
	ERR_SLAVE_DEBUG_BUSY = 0xb025,           //从站调试组件忙

/******************************装载组件********************************/
  ERR_DB_CONFIG_LOADER = 0xc000,//配置装载组件错误
  ERR_DB_LOADER_BUSY = 0xc100,//装载组件忙
  ERR_DB_LOADER_IS_NOT_INIT_POS = 0xc110,//装载试管架时机构不在初始位
  ERR_DB_LOADER_SENSOR = 0xc120,//装载组件传感器异常或电机故障
  ERR_DB_LOADER_EXEC_TIME_OUT = 0xc130,//装载组件执行时间太长
/*********************************进给组件*****************************/
  ERR_DB_CONFIG_FEEDER = 0xc200,//配置进给组件错误
  ERR_DB_FEEDER_BUSY = 0xc300,//进给组件忙
  ERR_DB_FEEDER_IS_NOT_INIT_POS = 0xc310,//进给时机构不在初始位
  ERR_DB_FEEDER_SENSOR = 0xc320,//进给组件传感器异常或电机故障
  ERR_DB_FEEDER_EXEC_TIME_OUT = 0xc330,//进给组件执行时间太长
/********************************卸载组件******************************/
  ERR_DB_CONFIG_UNLOADER = 0xc400,//配置卸载组件错误
  ERR_DB_UNLOADER_BUSY = 0xc500,//卸载组件忙
  ERR_DB_UNLOADER_IS_NOT_INIT_POS = 0xc510,//卸载试管时机构不在初始位
  ERR_DB_UNLOADER_SENSOR = 0xc520,//卸载组件传感器异常或电机故障
  ERR_DB_UNLOADER_EXEC_TIME_OUT = 0xc530,//卸载组件执行时间太长
  ERR_DB_UNLOADER_IS_FULL = 0xc540,//卸载平台满
/**********************************混匀组件****************************/
  ERR_DB_CONFIG_MIXER = 0xc600,//配置混匀组件错误
  ERR_DB_MIXER_BUSY = 0xc700,//混匀组件忙
  ERR_DB_MIXER_IS_NOT_INIT_POS = 0xc710,//混匀机构不在初始位
  ERR_DB_MIXER_SENSOR = 0xc720,//混匀组件传感器异常或电机故障
  ERR_DB_MIXER_EXEC_TIME_OUT = 0xc730,//混匀组件执行时间太长
/*********************************自动进样*****************************/
  ERR_DB_AUTO_SAMPLE_BUSY = 0xd000,//自动进样忙
  ERR_DB_AUTO_SAMPLE_START_PARAM = 0xd010,//启动自动进样参数错误
  ERR_DB_AUTO_SAMPLE_UNLOADER_FULL = 0xd020,//卸载平台满
  ERR_DB_AUTO_SAMPLE_LOADER_IS_NOT_INITPOS = 0xd030,//装载机构不在初始位
  ERR_DB_AUTO_SAMPLE_FEEDER_IS_NOT_INITPOS = 0xd040,//进给机构不在初始位
  ERR_DB_AUTO_SAMPLE_UNLOADER_IS_NOT_INITPOS = 0xd050,//卸载机构不在初始位
  ERR_DB_AUTO_SAMPLE_MIXER_IS_NOT_INITPOS = 0xd060,//混匀机构不在初始位
  ERR_DB_AUTO_SAMPLE_COUNTER_ABNORMAL = 0xd070,//计数器状态异常
  ERR_DB_AUTO_SAMPLE_IS_NOT_WORKING = 0xd100,//自动进样未工作
  ERR_DB_AUTO_SAMPLE_IS_MIXING = 0xd110,//正在混匀中
  ERR_DB_AUTO_SAMPLE_IS_FEEDING = 0xd120,//正在进给中
  ERR_DB_AUTO_SAMPLE_IS_UNLOADING = 0xd130,//正在卸载中
  ERR_DB_AUTO_SAMPLE_MIXCMD_INVALID = 0xd140,//混匀命令无效
  ERR_DB_AUTO_SAMPLE_EXEC_TIMEOUT = 0xd150,//自动进样动作超时
  ERR_DB_AUTO_SAMPLE_COUNTER_IS_TRIGGERED = 0xd200,//计数器被触发
  ERR_DB_AUTO_SAMPLE_COUNTER_TRIGGER_ABNORMAL = 0xd210,//计数器触发异常
  
}err_id_e;

//蜂鸣器报警音定义
typedef enum 
{
    NO_BEEP = 0x0000, //无响声
    BEEP_5S = 0x0155, //5短
    BEEP_4S = 0x0055, //4短
    BEEP_3S = 0x0015, //3短
    BEEP_2S = 0x0005, //2短
    BEEP_1S = 0x0001, //1短
    BEEP_1L = 0x000f, //1长
    BEEP_1L1S = 0x002f, //1长1短
    BEEP_1L2S = 0x00af, //1长2短
    BEEP_1L3S = 0x002af, //1长3短
} beep_type_e;

//蜂鸣器警告定义
typedef enum
{
    //BEEP_5S BEEP_4S BEEP_3S BEEP_2S BEEP_1S BEEP_1L BEEP_1L1S BEEP_1L2S BEEP_1L3S
    ERR_BEEP_DS18B20 = BEEP_5S, //DS18B20错误
    ERR_BEEP_FAN = BEEP_4S, //风扇错误
    ERR_BEEP_PARAM = BEEP_3S, //EEROM参数错误
    ERR_BEEP_INIT_TEMP_STRUCT = BEEP_2S, //初始化温度控制结构体错误(EEROM)
    
    ERR_BEEP_TEMP_OUT_OF_RANGE = BEEP_1L1S, //温度超过范围错误
    ERR_BEEP_TEMP_CTL = BEEP_1L2S, //温度控制错误
    ERR_BEEP_SWITCH = BEEP_1L3S,//制冷门打开
} err_beep_id_e;
/**********************************************************************/
#endif
/**********************************************************************/
