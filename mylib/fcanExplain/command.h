/******************************************************************************/
#ifndef __COMMAND_H
#define __COMMAND_H
/******************************************************************************/
//命令类型定义
//从站相关命令
#define CMD_TYPE_SLAVE                              (0x01)
//智能卡相关命令
#define CMD_TYPE_SMARTCARD                          (0x02)
//时序相关命令
#define CMD_TYPE_TIMESEQ                            (0x10)
//自动进样相关命令
#define CMD_TYPE_AUTOSAMPLE                         (0x11)
//阀命令
#define CMD_TYPE_VALVE                              (0x21)
//泵命令
#define CMD_TYPE_PUMP                               (0x22)
//电机命令
#define CMD_TYPE_MOTOR                              (0x23)
//条码扫描器命令
#define CMD_TYPE_BARCODESCANER                      (0x24)
//注射器命令
#define CMD_TYPE_SYRING                             (0x60)
//采样组件命令
#define CMD_TYPE_SAMPLE                             (0x61)
//温度控制命令
#define CMD_TYPE_TEMPERATURE                        (0x62)
//压力控制命令
#define CMD_TYPE_PRESSURE                           (0x63)
//试剂检测板命令
#define CMD_TYPE_REAGENT                            (0x64)
//装载组件命令
#define CMD_TYPE_LOADER                             (0x70)
//进给组件命令
#define CMD_TYPE_FEEDER                             (0x71)
//卸载组件命令
#define CMD_TYPE_UNLOADER                           (0x72)
//混匀组件命令
#define CMD_TYPE_MIXER                              (0x73)
//其他命令
#define CMD_TYPE_OTHER                              (0xE0)
//电压监控命令
#define CMD_TYPE_POWER                              (0xE1)
//灌注命令
#define CMD_TYPE_PERFUSION                          (0xE2)
//排空命令
#define CMD_TYPE_EVACUATION                         (0xE3)
//三维采样组件命令
#define CMD_TYPE_SAMPLE_3D                          (0xE4)
//样本试剂运动组件命令
#define CMD_TYPE_SAMPLES_REAGENTS                   (0xE5)
//试剂池混匀组件命令
#define CMD_TYPE_REAGENT_ROOM                       (0xE6)
//码盘控制组件命令
#define CMD_TYPE_CODE_WHEEL                         (0xE7)
//编码器电机控制命令
#define CMD_TYPE_CODER_MOTOR                        (0xE8)
//编码器电机采样组件
#define CMD_TYPE_SAMPLE_CODER_MOTOR                 (0xE9)
//吸样混匀组件命令
#define CMD_TYPE_SUCK_MIX                           (0xEA)
//抛杯组件命令
#define CMD_TYPE_THROW_CUP                          (0xEB)
//加杯组件命令
#define CMD_TYPE_ADD_CUP                            (0xEC)
//调试命令
#define CMD_TYPE_DEBUG                              (0xF0)
//无效命令
#define CMD_CMD_CONTENT_INVALID                     (0xFF)

/*****************************从站命令*****************************************/
//查询从站指定版本信息
#define CMD_QUERY_SLAVE_VERSION                     (0x00)
//查询从站版本信息
#define CMD_QUERY_SLAVE_ALL_VERSION                 (0x01)
//获取时间
#define CMD_QUERY_SLAVE_TIME                        (0x02)
//设置时间
#define CMD_SET_SLAVE_TIME                          (0x03)
//从站解析帧格式错误
#define CMD_SLAVE_PARSE_FRAME_FORMAT_ERR            (0x10)
//从站上报通信自检成功命令
#define CMD_SLAVE_COMM_SELF_CHECK_OK                (0x11)
//复位命令
#define CMD_UPGRADE_RESET                           (0x20)
//进入升级模式
#define CMD_ENTER_UPGRADE_MODE                      (0x21)
//开始升级
#define CMD_START_UPGRADE                           (0x22)
//升级数据命令
#define CMD_UPGRADE_DATA                            (0x23)
//升级结束
#define CMD_UPGRADE_FINISH                          (0x24)
//开始升级FPGA
#define CMD_FPGA_START_UPGRADE                      (0x25)
//FPGA升级数据命令
#define CMD_FPGA_UPGRADE_DATA                       (0x26)
//FPGA升级结束
#define CMD_FPGA_UPGRADE_FINISH                     (0x27)




/*****************************智能卡命令***************************************/
//复位PCD
#define CMD_SCR_RESET_PCD                           (0x00)
//关闭射频
#define CMD_SCR_CLOSE_RF                            (0x01)
//测试
#define CMD_SCR_TEST                                (0x02)
//蜂鸣器控制
#define CMD_SCR_BEEP                                (0x03)
//寻卡请求
#define CMD_SCR_REQUEST                             (0x10)
//防卡冲突
#define CMD_SCR_ANTICOLL                            (0x11)
//选卡
#define CMD_SCR_SELECT                              (0x12)
//选中应答请求
#define CMD_SCR_RATS                                (0x13)
//传输命令
#define CMD_SCR_COMMAND                             (0x14)
//关闭读卡器
#define CMD_CLOSE_SMARTCARD                         (0x00)
//打开读卡器
#define CMD_OPEN_SMARTCARD                          (0x01)
//写卡
#define CMD_WRITE_SMARTCARD                         (0x02)
//读卡
#define CMD_READ_SMARTCARD                          (0x03)
//创建卡
#define CMD_CREATE_SMARTCARD                        (0x04)
//设置外部认证密钥
#define CMD_SETEXAUTHKEY_SMARTCARD                  (0x05)
//设置文件线路保护密钥
#define CMD_SETFILELINEKEY_SMARTCARD                (0x06)
//设置信息存放目录
#define CMD_SET_STORE_DIR                           (0x07)
//查询卡版本信息
#define CMD_QUIRE_CARD_VER                          (0x08)

//打开读卡器设备，开始读卡
#define CMD_SMARTCARD_OPEN                          (0x09)
//关闭读卡器设备，停止读卡
#define CMD_SMARTCARD_CLOSE                         (0x0A)
//写读卡器设备，将信息写入卡中
#define CMD_SMARTCARD_WRITE                         (0x0B)
//读卡号
#define CMD_GET_SMARTCARD_NO                        (0x0C)
//设定OEM代号
#define CMD_SET_OEM_NUM                             (0x0D)
#define CMD_SET_CHANNEL                             (0x0E)
/************************************时序命令**********************************/
//时序包包头命令
#define CMD_TIMESEQ_FRAME_HEAD                      (0x00)
//时序包包尾命令
#define CMD_TIMESEQ_FRAME_TAIL                      (0x01)
//时序结束命令
#define CMD_TIMESEQ_FINISH                          (0x02)
//时序启动命令
#define CMD_START_TIMESEQ                           (0x10)
//停止所有运行中的时序命令
#define CMD_STOP_TIMESEQ                            (0x11)
//时序重叠命令
#define CMD_TIMESEQ_OVERLAP_CONTROL                 (0x12)

/**********************************自动进样命令********************************/
//启动自动进样
#define CMD_START_AUTOSAMPLE                        (0x00)
//自动进样时启动试管架移动
#define CMD_START_AUTOSAMPLE_RACK_MOVING            (0x01)
//自动进样时启动试管的混匀
#define CMD_START_AUTOSAMPLE_TUBE_MIXING            (0x02)
//停止自动进样
#define CMD_STOP_AUTOSAMPLE                         (0x03)
//终止自动进样
#define CMD_ABORT_AUTOSAMPLE                        (0x0A)
//紧急停止自动进样
#define CMD_EMERGENCY_STOP_AUTOSAMPLE               (0x04)
//跳过当前试管架
#define CMD_AUTOSAMPLE_SKIP_CUR_RACK                (0x05)
//恢复自动进样
#define CMD_RECOVER_AUTOSAMPLE                      (0x06)
//主动上传试管架号
#define CMD_UPLOAD_RACK_NUMBER                      (0x10)
//主动上传混匀位信息
#define CMD_UPLOAD_MIXPOS_INFO                      (0x11)
//主动上传采样位信息
#define CMD_UPLOAD_SAMPLEPOS_INFO                   (0x12)
//自动进样结束命令
#define CMD_UPLOAD_AUTOSAMPLE_FINISH                (0x13)
//自动进样混匀结束命令
#define CMD_UPLOAD_AUTOSAMPLE_MIX_FINISH            (0x14)
//查询自动进样器状态
#define CMD_QUIRE_AUTOSAMPLER_STATE                 (0x20)
//初始化自动进样器
#define CMD_AUTOSAMPLER_INIT                        (0x21)
//清空自动进样器
#define CMD_EMPTY_AUTOSAMPLER                       (0x22)

//自动进样中请求混匀位信息     //2018年1月22日-zkp添加
#define CMD_QUIRE_AUTOSAMPLE_MIX_POS_MSG            (0x30)
//主动试管到位信息            //2018年1月22日-zkp添加
#define CMD_UPLOAD_IN_POS_INFO                      (0x31)

//// 初始化旋转扫码组件         //2018年3月26日-zkp添加
//#define CMD_INIT_TURN_SCAN_MOTOR                    (0x32)
//// 启动旋转扫码组件           //2018年3月26日-zkp添加
//#define CMD_START_TURN_SCAN_MOTOR                   (0x33)
// 配置自动进样配件           //2018年3月31日-zkp添加
#define CMD_CONFIG_AUTO_SAMPLE_PARTS                (0x34)
// 消除装载不到位故障(使能自动装载)   //2018年3月31日-zkp添加
#define CMD_ENABLE_AUTO_LOAD                        (0x35)
// 启动末梢混匀                      //2018年3月31日-zkp添加
#define CMD_START_PERIPHERAL_MIX                    (0x36)
// 启动末梢清空                      //2018年5月31日-zkp添加
#define CMD_START_PERIPHERAL_EMPTY                  (0x37)

// 测试旋转扫描组件                  //2018年3月31日-zkp添加
#define CMD_TEST_TURN_SCAN_ASSEMBLY                 (0x40)
// 测试末梢混匀组件                  //2018年3月31日-zkp添加
#define CMD_TEST_PERIPHERAL_ASSEMBLY                (0x41)

/************************************阀命令************************************/
//阀控制
#define CMD_CONTROL_VALVE                           (0x00)
//查询所有阀状态
#define CMD_QUERY_ALL_VALVE_STATE                   (0x01)

//查询阀组状态
#define CMD_QUIRE_VALVE_GROUP_STATE                 (0x01)
//查询指定阀状态
#define CMD_QUIRE_VALVE_CH_STATE                    (0x02)

/************************************泵命令************************************/
//泵控制
#define CMD_CONTROL_PUMP                            (0x00)
//查询所有泵状态
#define CMD_QUERY_ALL_PUMP_STATE                    (0x01)

/**********************************电机命令************************************/
//电机属性配置
#define CMD_MOTOR_CONFIG_ATTRIBUTE                  (0x00)
//电机挡速配置
#define CMD_MOTOR_CONFIG_SPEED                      (0x01)
//电机初始配置
#define CMD_MOTOR_CONFIG_INIT                       (0x02)
//电机位置状态配置
#define CMD_MOTOR_CONFIG_POS                        (0x03)
//查询电机属性配置
#define CMD_QUERY_MOTOR_CONFIG_ATTRIBUTE            (0x08)
//查询电机挡速配置
#define CMD_QUERY_MOTOR_CONFIG_SPEED                (0x09)
//查询电机初始配置
#define CMD_QUERY_MOTOR_CONFIG_INIT                 (0x0a)
//查询电机位置状态配置
#define CMD_QUERY_MOTOR_CONFIG_POS                  (0x0b)
//以指定挡速初始化
#define CMD_MOTOR_INIT                              (0x10)
//电机以指定挡速运动到指定位置
#define CMD_MOTOR_MOVE_POS                          (0x11)
//电机以指定挡速走指定步数
#define CMD_MOTOR_MOVE_STEP                         (0x12)

/***********************************条码扫描器*********************************/
//查询条码扫描器状态
#define CMD_QUIRE_BARCODE_SCANNER_STATE             (0x00)
//启动读取条码扫描器
#define CMD_START_BARCODE_SCANNING                  (0x01)
//设置条码扫描仪支持的码制以及校验
#define CMD_BARCODE_TYPE_CHECK_STATUS_SET           (0x20)
//设置条码扫描仪支持的长度
#define CMD_BARCODE_LEN_SET                         (0x21)
//条码扫描仪类型设定
#define CMD_BARCODE_SCANNER_TYPE_SET                (0x12)
//关闭激光器
#define CMD_BARCODE_SCANNER_CLOSE                   (0x10)
//打开激光器
#define CMD_BARCODE_SCANNER_OPEN                    (0x11)

/***********************************注射器命令*********************************/
//无

/**********************************采样组件命令********************************/
//配置采样组件
#define CMD_SAMPLE_CONFIG                           (0x00)
//采样组件水平摆动
#define CMD_SAMPLE_HSWING                           (0x11)
//以指定挡速水平初始化采样组件
#define CMD_H_INIT_SAMPLE                           (0x12)
//以指定挡速垂直初始化采样组件
#define CMD_V_INIT_SAMPLE                           (0x13)
//以指定挡速水平运动到指定位置
#define CMD_SAMPLE_H_MOVE_POS                       (0x14)
//以指定挡速垂直运动到指定位置
#define CMD_SAMPLE_V_MOVE_POS                       (0x15)

/************************************压力控制命令******************************/
//压力配置
#define CMD_PRESSURE_CONFIG                         (0x00)
//查询指定压力通道压力AD值
#define CMD_QUERY_PRESSURE_AD_VALUE                 (0x10)
//查询指定通道压力是否在指定压力范围
#define CMD_CHECK_PRESSURE                          (0x11)
//查询指定压力通道压力值
#define CMD_QUERY_PRESSURE_VALUE                    (0x12)
//建压
#define CMD_BUILD_PRESSURE                          (0x20)
//压力标定
#define CMD_CALIBRATION_PRESSURE                    (0x21)
//查询指定通道压力的K值和B值
#define CMD_QUERY_PRESSURE_KB                       (0x30)
//设置指定通道压力的K值和B值
#define CMD_SET_PRESSURE_KB                         (0x31)
//自动计算指定通道压力的K值和B值
#define CMD_AUTO_CALC_PRESSURE_KB                   (0x32)
//设置默认压力通道的K值和B值
#define CMD_SET_PRESSURE_DEFAULT_KB                 (0x33)
// 设置自动建压状态     -2018年8月8日 由zkp添加，用于DM1114 两个大气泵的自动建压
#define CMD_SET_AUTO_BUILD_PRESSURE                 (0x34)
//压力监控
#define CMD_MONITOR_PRESSURE                        (0x40)

//查询指定通道压力值
#define CMD_QUIRE_PRESSURE_CH_VALUE                 (0x12)
//查询指定通道的KB值
#define CMD_QUIRE_PRESSURE_CH_KB_VALUE              (0x30)
//设定指定通道的KB值
#define CMD_SET_PRESSURE_CH_KB_VALUE                (0x31)
//启动指定通道压力监测
#define CMD_SET_PRESSURE_MONITOR_STATE              (0x40)
//结束指定通道压力监测
#define CMD_CHECK_PRESSURE_STATE                    (0x11)   

/************************************试剂检测命令******************************/
//试剂通道配置
#define CMD_REAGENT_CONFIG                          (0x00)
//查询指定通道试剂状态
#define CMD_QUIRE_REAGENT_CH_STATE                  (0x10)
//试剂有无查询
#define CMD_DETEC_REAGENT_CH                        (0x11)
//查询无试剂时间
#define CMD_QUIRE_NONE_REAGENT_TIME                 (0x12)
//设置无试剂阈值
#define CMD_SET_NONE_REAGENT_THRESHOLD              (0x13)

/****************************************温度控制命令**************************/
//温度范围判断
#define CMD_TEMPERATURE_RANGE_JUDGE                 (0x00)
//温度控制
#define CMD_TEMPERATURE_CONTROL                     (0x01)
//查询指定通道实测温度值
#define CMD_QUIRE_CUR_TEMPERATURE                   (0x10)
//查询指定通道补偿后的温度值
#define CMD_QUIRE_CUR_TEMPERATURE_COMPENSATION      (0x11)
//下发目标温度
#define CMD_SET_TARGET_TEMPERATURE                  (0x20)
//下发温度补偿值
#define CMD_TEMPERATURE_COMPENSATION_CONFIG         (0x21)
//配置工作温度和运行温度
#define CMD_CONFIG_WORK_RUN_TEMPERATURE             (0x22)
//设置PID参数
#define CMD_SET_TEMPERATURE_CH_PID_PARAM            (0x40)
//获取PID参数
#define CMD_QUIRE_TEMPERATURE_CH_PID_PARAM          (0x41)

/***************************************装载组件命令***************************/
//配置装载组件
#define CMD_CONFIG_LOADER                           (0x00)
//初始化装载组件
#define CMD_LOADER_INIT                             (0x10)
//装载试管架
#define CMD_LOAD_RACK                               (0x11)

/**********************************进给组件命令********************************/
//配置进给组件
#define CMD_CONFIG_FEEDER                           (0x00)
//初始化进给组件
#define CMD_FEEDER_INIT                             (0x10)
//试管架移动一个试管位
#define CMD_FEED_RACK                               (0x11)

/*********************************卸载组件命令*********************************/
//配置卸载组件
#define CMD_CONFIG_UNLOADER                         (0x00)
//初始化卸载组件
#define CMD_UNLOADER_INIT                           (0x10)
//卸载试管架
#define CMD_UNLOAD_RACK                             (0x11)

/*********************************混匀组件命令*********************************/
//配置混匀组件
#define CMD_CONFIG_MIXER                            (0x00)
//初始化混匀组件
#define CMD_MIXER_INIT                              (0x10)
//启动试管混匀
#define CMD_TUBE_MIX                                (0x11)
//混匀组件复位
#define CMD_MIXER_RESET                             (0x12)
//查询混匀组件是否在初始位
#define CMD_QUIRE_MIXER_STATE                       (0x13)
//启动初始化抓取结构
#define CMD_GRAB_MECHANISM_INIT                     (0x20)
//抓取试管
#define CMD_GRAB_TUBE                               (0x21)
//启动初始化升降结构
#define CMD_RAISE_MECHANISM_INIT                    (0x22)
//举起试管
#define CMD_RAISE_TUBE                              (0x23)
//启动速度初始化摆动结构
#define CMD_SWING_MECHANISM_INIT                    (0x24)
//摆动试管
#define CMD_SWING_TUBE                              (0x25)

//抓取电机从中继仓取试管
#define CMD_GRAB_TUBE_FROM_RELAY                    (0x26)
//升降电机将试管放到中继仓
#define CMD_RAISE_TUBE_TO_RELAY                     (0x27)
//启动初始化中继仓组件
#define CMD_RELAY_MECHANISM_INIT                    (0x28)
//中继仓接试管
#define CMD_RELAY_TUBE                              (0x29)

/******************************从站其他命令************************************/
//查询电机光耦状态
#define CMD_QUIRE_MOTOR_OPT_STATE                   (0x00)
//查询试剂光耦状态
#define CMD_QUIRE_REAGENT_OPT_STATE                 (0x01)
//查询开关状态
#define CMD_QUIRE_SWITCH_STATE                      (0x02)
//设置是否进行开关检测
#define CMD_SET_SW_CHECK_STATE                      (0x10)
//上报右侧门或者激光器盒子打开故障
#define CMD_UPLOAD_OPEN_ERR                         (0x11)
//CRP激光器控制命令
#define CMD_CRP_LASER_CTL_CMD                       (0x20)

//查询电机光耦组状态
#define CMD_QUIRE_MOTOR_OPT_GROUP_STATE             (0x00)
//查询指定电机光耦状态
#define CMD_QUIRE_MOTOR_OPT_CH_STATE                (0x01)
//查询试剂通道组的状态
#define CMD_QUIRE_REAGENT_GROUP_STATE               (0x10)
//查询指定的试剂通道试剂有无的状态
#define CMD_QUIRE_REAGENT_CHANEL_STATE              (0x11)
//查询开关通道组的状态
#define CMD_QUIRE_SWITCH_GROUP_STATE                (0x20)
//查询指定的开关通道的状态
#define CMD_QUIRE_SWITCH_CH_STATE                   (0x21)
//设定所有开关通道是否进行实时检查
#define CMD_SET_SWITCH_ALL_MONITOR_STATE            (0x22)
//设定指定开关通道是否进行实时检查
#define CMD_SET_SWITCH_CH_MONITOR_STATE             (0x23)

//LED设备控制 -- 2018年7月20日 zkp新增
#define CMD_LED_CONTROL                             (0x30)
//启动直流减速电机 -- 2018年8月27日 zkp新增
#define CMD_START_DC_GEAR_MOTOR                     (0x40)
//停止直流减速电机 -- 2018年8月27 zkp新增
#define CMD_STOP_DC_GEAR_MOTOR                      (0x41)

//无刷电机启动 -- 2018年8月22日 zkp新增
#define CMD_START_BRUSHLESS_MOTOR                   (0x50)
//无刷电机摆动 -- 2018年8月22日 zkp新增
#define CMD_START_BRUSHLESS_SWING                   (0x51)
//无刷电机停止 -- 2018年8月22日 zkp新增
#define CMD_STOP_BRUSHLESS_MOTOR                    (0x52)
/********************************电压监控命令**********************************/
//查询通道电压
#define CMD_QUIRE_POWER_VALUE                       (0x00)
//启动通道电压监测
#define CMD_SET_POWER_MONITOR_STATE                 (0x10)
//关闭通道电压监测
#define CMD_CLEAR_POWER_MONITOR_STATE               (0x20)
/*********************************灌注命令*************************************/
//启动灌注
#define CMD_START_PERFUSION                         (0x00)
/*********************************排空命令*************************************/
//启动排空
#define CMD_START_EVACUATION                        (0x00)
/*********************************三维采样组件命令*****************************/
//三维采样组件左右摆动
#define CMD_SAMPLE_3D_LRSWING                       (0x01)
//三维采样组件水平摆动
#define CMD_SAMPLE_3D_HSWING                        (0x11)
//三维采样组件水平电机初始化
#define CMD_SAMPLE_3D_HMOTOR_INIT                   (0x12)
//三维采样组件垂直电机初始化
#define CMD_SAMPLE_3D_VMOTOR_INIT                   (0x13)
//三维采样组件左右电机初始化
#define CMD_SAMPLE_3D_LRMOTOR_INIT                  (0x16)
//三维采样组件水平电机走位置
#define CMD_SAMPLE_3D_HMOTOR_POS                    (0x14)
//三维采样组件垂直电机走位置
#define CMD_SAMPLE_3D_VMOTOR_POS                    (0x15)
//三维采样组件左右电机走位置
#define CMD_SAMPLE_3D_LRMOTOR_POS                   (0x17)
/*********************************样本试剂运动组件命令*************************/
//样本试剂运动组件中的样本采样组件水平电机初始化
#define CMD_SAMPLES_REAGENTS_SAMPLE_HMOTOR_INIT     (0x00)
//样本试剂运动组件中的样本采样组件垂直电机初始化
#define CMD_SAMPLES_REAGENTS_SAMPLE_VMOTOR_INIT     (0x01)
//样本试剂运动组件中的样本采样组件左右电机初始化
#define CMD_SAMPLES_REAGENTS_SAMPLE_LRMOTOR_INIT    (0x02)
//样本试剂运动组件中的试剂采样组件水平电机初始化
#define CMD_SAMPLES_REAGENTS_REAGENT_HMOTOR_INIT    (0x03)
//样本试剂运动组件中的试剂采样组件垂直电机初始化
#define CMD_SAMPLES_REAGENTS_REAGENT_VMOTOR_INIT    (0x04)
//样本试剂运动组件中的试剂采样组件左右电机初始化
#define CMD_SAMPLES_REAGENTS_REAGENT_LRMOTOR_INIT   (0x05)
//样本试剂运动组件中的孵育池混匀电机初始化
#define CMD_SAMPLES_REAGENTS_HATCHERY_MOTOR_INIT    (0x06)

//样本试剂运动组件中的样本采样组件水平电机走位置
#define CMD_SAMPLES_REAGENTS_SAMPLE_HMOTOR_POS      (0x10)
//样本试剂运动组件中的样本采样组件垂直电机走位置
#define CMD_SAMPLES_REAGENTS_SAMPLE_VMOTOR_POS      (0x11)
//样本试剂运动组件中的样本采样组件左右电机走位置
#define CMD_SAMPLES_REAGENTS_SAMPLE_LRMOTOR_POS     (0x12)
//样本试剂运动组件中的试剂采样组件水平电机走位置
#define CMD_SAMPLES_REAGENTS_REAGENT_HMOTOR_POS     (0x13)
//样本试剂运动组件中的试剂采样组件垂直电机走位置
#define CMD_SAMPLES_REAGENTS_REAGENT_VMOTOR_POS     (0x14)
//样本试剂运动组件中的试剂采样组件左右电机走位置
#define CMD_SAMPLES_REAGENTS_REAGENT_LRMOTOR_POS    (0x15)
//样本试剂运动组件中的孵育池混匀电机走位置
#define CMD_SAMPLES_REAGENTS_HATCHERY_MOTOR_POS     (0x16)
//样本试剂运动组件中的孵育池混匀
#define CMD_SAMPLES_REAGENTS_HATCHERY_MIX           (0x20)
/********************************试剂池混匀组件命令****************************/
//试剂池混匀电机初始化
#define CMD_REAGENT_ROOM_MOTOR_INIT                 (0x00)
//试剂池混匀电机走位置
#define CMD_REAGENT_ROOM_MOTOR_POS                  (0x10)
//试剂池混匀
#define CMD_REAGENT_ROOM_MIX                        (0x20)
/*********************************码盘控制组件*********************************/
//初始化码盘
#define CMD_CODE_WHEEL_INIT                         (0x10)
//码盘走位置
#define CMD_CODE_WHEEL_POS                          (0x11)
//停止码盘
#define CMD_CODE_WHEEL_STOP                         (0x12)
/******************************编码器电机控制组件******************************/
//编码器电机属性配置
#define CMD_CODER_MOTOR_CFG_ATTR                    (0x00)
//编码器电机速度配置
#define CMD_CODER_MOTOR_CFG_SPEED                   (0x01)
//编码器电机初始化配置
#define CMD_CODER_MOTOR_CFG_INIT                    (0x02)
//编码器电机初始化
#define CMD_CODER_MOTOR_INIT                        (0x10)
//编码器电机走位置
#define CMD_CODER_MOTOR_POS                         (0x11)
//编码器电机走步数
#define CMD_CODER_MOTOR_STEPS                       (0x12)
/******************************试剂采样组件控制*****************************/
//试剂采样组件水平初始化
#define CMD_SAMPLE_CODER_MOTOR_HINIT                (0x12)
//试剂采样组件垂直初始化
#define CMD_SAMPLE_CODER_MOTOR_VINIT                (0x13)
//试剂采样组件水平走位置
#define CMD_SAMPLE_CODER_MOTOR_HPOS                 (0x14)
//试剂采样组件垂直走位置
#define CMD_SAMPLE_CODER_MOTOR_VPOS                 (0x15)
//试剂采样组件垂直吸样
#define CMD_SAMPLE_CODER_MOTOR_VSUCK                (0x16)
/*******************************吸样混匀组件控制*******************************/
//吸样混匀组件初始化
#define CMD_SUCK_MIX_INIT                           (0x00)
//吸样混匀组件吸样
#define CMD_SUCK_MIX_SUCK                           (0x01)
//吸样混匀组件吸样结束
#define CMD_SUCK_MIX_SUCK_END                       (0x02)
//吸样混匀组件混匀
#define CMD_SUCK_MIX_MIX                            (0x03)
//吸样混匀组件混匀结束
#define CMD_SUCK_MIX_MIX_END                        (0x04)
/********************************抛杯组件控制**********************************/
//初始化抛杯组件
#define CMD_THROW_CUP_INIT                          (0x00)
//抛杯组件抛杯
#define CMD_THROW_CUP_THROW                         (0x01)
/********************************加杯组件控制**********************************/
//初始化加杯组件
#define CMD_ADD_CUP_INIT                            (0x00)
//加杯组件加杯
#define CMD_ADD_CUP_ADD                             (0x01)
/********************************从站调试命令**********************************/
//触发引脚控制
#define CMD_TRIGGER_PIN_CONTROL                     (0x00)
//错误调试命令
#define CMD_ERROR_DEBUG                             (0x01)
//初始化5101运动组件
#define CMD_5101_INIT                               (0x02)
// 上传调试信息 -- 2018年9月12日，zkp增加，用于debug_msg的附带上传调试信息
#define CMD_UPLOAD_DEBUG_MSG                        (0x00)

/******************************************************************************/
#endif
/******************************************************************************/
