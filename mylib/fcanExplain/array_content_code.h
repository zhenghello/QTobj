/*
 * 放着命令内容的编码
 */
#ifndef ARRAY_CONTENT_CODE
#define ARRAY_CONTENT_CODE

#include "command.h"
#include "array_arg_ord_code.h"     // 附带参数的数组
#include "array_arg_rep_code.h"     // 附带参数的数组

//命令类型->"从站"
cCmd content_code_addr_slave             [] =
{
  { CMD_QUERY_SLAVE_VERSION                          , QString::fromLocal8Bit("查询从站指定版本信息 ")                            , 1 , cmd_query_slave_version_ord_arg                   , 3 , cmd_query_slave_version_rep_arg                   },
  { CMD_QUERY_SLAVE_ALL_VERSION                      , QString::fromLocal8Bit("查询从站版本信息 ")                                , 0 , cmd_query_slave_all_version_ord_arg               , 9 , cmd_query_slave_all_version_rep_arg               },
  { CMD_QUERY_SLAVE_TIME                             , QString::fromLocal8Bit("获取时间 ")                                        , 0 , cmd_query_slave_time_ord_arg                      , 6 , cmd_query_slave_time_rep_arg                      },
  { CMD_SET_SLAVE_TIME                               , QString::fromLocal8Bit("设置时间 ")                                        , 6 , cmd_set_slave_time_ord_arg                        , 0 , cmd_set_slave_time_rep_arg                        },
  { CMD_SLAVE_PARSE_FRAME_FORMAT_ERR                 , QString::fromLocal8Bit("从站解析帧格式错误 ")                              , 0 , cmd_slave_parse_frame_format_err_ord_arg          , 0 , cmd_slave_parse_frame_format_err_rep_arg          },
  { CMD_SLAVE_COMM_SELF_CHECK_OK                     , QString::fromLocal8Bit("从站上报通信自检成功命令 ")                        , 0 , cmd_slave_comm_self_check_ok_ord_arg              , 0 , cmd_slave_comm_self_check_ok_rep_arg              },
  { CMD_UPGRADE_RESET                                , QString::fromLocal8Bit("复位命令 ")                                        , 0 , cmd_upgrade_reset_ord_arg                         , 0 , cmd_upgrade_reset_rep_arg                         },
  { CMD_ENTER_UPGRADE_MODE                           , QString::fromLocal8Bit("进入升级模式 ")                                    , 0 , cmd_enter_upgrade_mode_ord_arg                    , 0 , cmd_enter_upgrade_mode_rep_arg                    },
  { CMD_START_UPGRADE                                , QString::fromLocal8Bit("开始升级 ")                                        , 0 , cmd_start_upgrade_ord_arg                         , 0 , cmd_start_upgrade_rep_arg                         },
  { CMD_UPGRADE_DATA                                 , QString::fromLocal8Bit("升级数据命令 ")                                    , 0 , cmd_upgrade_data_ord_arg                          , 0 , cmd_upgrade_data_rep_arg                          },
  { CMD_UPGRADE_FINISH                               , QString::fromLocal8Bit("升级结束 ")                                        , 0 , cmd_upgrade_finish_ord_arg                        , 0 , cmd_upgrade_finish_rep_arg                        },
  { CMD_FPGA_START_UPGRADE                           , QString::fromLocal8Bit("开始升级FPGA ")                                    , 0 , cmd_fpga_start_upgrade_ord_arg                    , 0 , cmd_fpga_start_upgrade_rep_arg                    },
  { CMD_FPGA_UPGRADE_DATA                            , QString::fromLocal8Bit("FPGA升级数据命令 ")                                , 0 , cmd_fpga_upgrade_data_ord_arg                     , 0 , cmd_fpga_upgrade_data_rep_arg                     },
  { CMD_FPGA_UPGRADE_FINISH                          , QString::fromLocal8Bit("FPGA升级结束 ")                                    , 0 , cmd_fpga_upgrade_finish_ord_arg                   , 0 , cmd_fpga_upgrade_finish_rep_arg                   },
};
//命令类型->"智能卡"
cCmd content_code_addr_smartcard         [] =
{
//  { CMD_SCR_RESET_PCD                                , QString::fromLocal8Bit("复位PCD ")                                       , 0 , cmd_scr_reset_pcd_ord_arg                         , 0 , cmd_scr_reset_pcd_rep_arg                         },
//  { CMD_SCR_CLOSE_RF                                 , QString::fromLocal8Bit("关闭射频 ")                                      , 0 , cmd_scr_close_rf_ord_arg                          , 0 , cmd_scr_close_rf_rep_arg                          },
//  { CMD_SCR_TEST                                     , QString::fromLocal8Bit("测试 ")                                          , 0 , cmd_scr_test_ord_arg                              , 0 , cmd_scr_test_rep_arg                              },
//  { CMD_SCR_BEEP                                     , QString::fromLocal8Bit("蜂鸣器控制 ")                                    , 0 , cmd_scr_beep_ord_arg                              , 0 , cmd_scr_beep_rep_arg                              },
//  { CMD_SCR_REQUEST                                  , QString::fromLocal8Bit("寻卡请求 ")                                      , 0 , cmd_scr_request_ord_arg                           , 0 , cmd_scr_request_rep_arg                           },
//  { CMD_SCR_ANTICOLL                                 , QString::fromLocal8Bit("防卡冲突 ")                                      , 0 , cmd_scr_anticoll_ord_arg                          , 0 , cmd_scr_anticoll_rep_arg                          },
//  { CMD_SCR_SELECT                                   , QString::fromLocal8Bit("选卡 ")                                          , 0 , cmd_scr_select_ord_arg                            , 0 , cmd_scr_select_rep_arg                            },
//  { CMD_SCR_RATS                                     , QString::fromLocal8Bit("选中应答请求 ")                                  , 0 , cmd_scr_rats_ord_arg                              , 0 , cmd_scr_rats_rep_arg                              },
//  { CMD_SCR_COMMAND                                  , QString::fromLocal8Bit("传输命令 ")                                      , 0 , cmd_scr_command_ord_arg                           , 0 , cmd_scr_command_rep_arg                           },
  { CMD_CLOSE_SMARTCARD                              , QString::fromLocal8Bit("关闭读卡器 ")                                      , 0 , cmd_close_smartcard_ord_arg                       , 0 , cmd_close_smartcard_rep_arg                       },
  { CMD_OPEN_SMARTCARD                               , QString::fromLocal8Bit("打开读卡器 ")                                      , 0 , cmd_open_smartcard_ord_arg                        , 0 , cmd_open_smartcard_rep_arg                        },
  { CMD_WRITE_SMARTCARD                              , QString::fromLocal8Bit("写卡 ")                                            , 0 , cmd_write_smartcard_ord_arg                       , 0 , cmd_write_smartcard_rep_arg                       },
  { CMD_READ_SMARTCARD                               , QString::fromLocal8Bit("读卡 ")                                            , 0 , cmd_read_smartcard_ord_arg                        , 0 , cmd_read_smartcard_rep_arg                        },
  { CMD_CREATE_SMARTCARD                             , QString::fromLocal8Bit("创建卡 ")                                          , 0 , cmd_create_smartcard_ord_arg                      , 0 , cmd_create_smartcard_rep_arg                      },
  { CMD_SETEXAUTHKEY_SMARTCARD                       , QString::fromLocal8Bit("设置外部认证密钥 ")                                , 0 , cmd_setexauthkey_smartcard_ord_arg                , 0 , cmd_setexauthkey_smartcard_rep_arg                },
  { CMD_SETFILELINEKEY_SMARTCARD                     , QString::fromLocal8Bit("设置文件线路保护密钥 ")                            , 0 , cmd_setfilelinekey_smartcard_ord_arg              , 0 , cmd_setfilelinekey_smartcard_rep_arg              },
  { CMD_SET_STORE_DIR                                , QString::fromLocal8Bit("设置信息存放目录 ")                                , 0 , cmd_set_store_dir_ord_arg                         , 0 , cmd_set_store_dir_rep_arg                         },
  { CMD_QUIRE_CARD_VER                               , QString::fromLocal8Bit("查询卡版本信息 ")                                  , 0 , cmd_quire_card_ver_ord_arg                        , 0 , cmd_quire_card_ver_rep_arg                        },
  { CMD_SMARTCARD_OPEN                               , QString::fromLocal8Bit("打开读卡器设备，开始读卡 ")                        , 0 , cmd_smartcard_open_ord_arg                        , 0 , cmd_smartcard_open_rep_arg                        },
  { CMD_SMARTCARD_CLOSE                              , QString::fromLocal8Bit("关闭读卡器设备，停止读卡 ")                        , 0 , cmd_smartcard_close_ord_arg                       , 0 , cmd_smartcard_close_rep_arg                       },
  { CMD_SMARTCARD_WRITE                              , QString::fromLocal8Bit("写读卡器设备，将信息写入卡中 ")                    , 0 , cmd_smartcard_write_ord_arg                       , 0 , cmd_smartcard_write_rep_arg                       },
  { CMD_GET_SMARTCARD_NO                             , QString::fromLocal8Bit("读卡号 ")                                          , 0 , cmd_get_smartcard_no_ord_arg                      , 0 , cmd_get_smartcard_no_rep_arg                      },
  { CMD_SET_OEM_NUM                                  , QString::fromLocal8Bit("设定OEM代号 ")                                     , 0 , cmd_set_oem_num_ord_arg                           , 0 , cmd_set_oem_num_rep_arg                           },
};
//命令类型->"时序"
cCmd content_code_addr_timeseq           [] =
{
  { CMD_TIMESEQ_FRAME_HEAD                           , QString::fromLocal8Bit("时序包包头命令 ")                                  , 1 , cmd_timeseq_frame_head_ord_arg                    , 0 , cmd_timeseq_frame_head_rep_arg                    },
  { CMD_TIMESEQ_FRAME_TAIL                           , QString::fromLocal8Bit("时序包包尾命令 ")                                  , 1 , cmd_timeseq_frame_tail_ord_arg                    , 0 , cmd_timeseq_frame_tail_rep_arg                    },
  { CMD_TIMESEQ_FINISH                               , QString::fromLocal8Bit("时序结束命令 ")                                    , 0 , cmd_timeseq_finish_ord_arg                        , 0 , cmd_timeseq_finish_rep_arg                        },
  { CMD_START_TIMESEQ                                , QString::fromLocal8Bit("时序启动命令 ")                                    , 1 , cmd_start_timeseq_ord_arg                         , 0 , cmd_start_timeseq_rep_arg                         },
  { CMD_STOP_TIMESEQ                                 , QString::fromLocal8Bit("停止所有运行中的时序命令 ")                        , 0 , cmd_stop_timeseq_ord_arg                          , 0 , cmd_stop_timeseq_rep_arg                          },
  { CMD_TIMESEQ_OVERLAP_CONTROL                      , QString::fromLocal8Bit("时序重叠命令 ")                                    , 0 , cmd_timeseq_overlap_control_ord_arg               , 0 , cmd_timeseq_overlap_control_rep_arg               },
};
//命令类型->"自动进样"
cCmd content_code_addr_autosample        [] =
{
  { CMD_START_AUTOSAMPLE                             , QString::fromLocal8Bit("启动自动进样 ")                                    , 0 , cmd_start_autosample_ord_arg                      , 0 , cmd_start_autosample_rep_arg                      },
  { CMD_START_AUTOSAMPLE_RACK_MOVING                 , QString::fromLocal8Bit("自动进样时启动试管架移动 ")                        , 0 , cmd_start_autosample_rack_moving_ord_arg          , 0 , cmd_start_autosample_rack_moving_rep_arg          },
  { CMD_START_AUTOSAMPLE_TUBE_MIXING                 , QString::fromLocal8Bit("自动进样时启动试管的混匀 ")                        , 0 , cmd_start_autosample_tube_mixing_ord_arg          , 0 , cmd_start_autosample_tube_mixing_rep_arg          },
  { CMD_STOP_AUTOSAMPLE                              , QString::fromLocal8Bit("停止自动进样 ")                                    , 0 , cmd_stop_autosample_ord_arg                       , 0 , cmd_stop_autosample_rep_arg                       },
  { CMD_ABORT_AUTOSAMPLE                             , QString::fromLocal8Bit("终止自动进样 ")                                    , 0 , cmd_abort_autosample_ord_arg                      , 0 , cmd_abort_autosample_rep_arg                      },
  { CMD_EMERGENCY_STOP_AUTOSAMPLE                    , QString::fromLocal8Bit("紧急停止自动进样 ")                                , 0 , cmd_emergency_stop_autosample_ord_arg             , 0 , cmd_emergency_stop_autosample_rep_arg             },
  { CMD_AUTOSAMPLE_SKIP_CUR_RACK                     , QString::fromLocal8Bit("跳过当前试管架 ")                                  , 0 , cmd_autosample_skip_cur_rack_ord_arg              , 0 , cmd_autosample_skip_cur_rack_rep_arg              },
  { CMD_RECOVER_AUTOSAMPLE                           , QString::fromLocal8Bit("恢复自动进样 ")                                    , 0 , cmd_recover_autosample_ord_arg                    , 0 , cmd_recover_autosample_rep_arg                    },
  { CMD_UPLOAD_RACK_NUMBER                           , QString::fromLocal8Bit("主动上传试管架号 ")                                , 0 , cmd_upload_rack_number_ord_arg                    , 0 , cmd_upload_rack_number_rep_arg                    },
  { CMD_UPLOAD_MIXPOS_INFO                           , QString::fromLocal8Bit("主动上传混匀位信息 ")                              , 0 , cmd_upload_mixpos_info_ord_arg                    , 0 , cmd_upload_mixpos_info_rep_arg                    },
  { CMD_UPLOAD_SAMPLEPOS_INFO                        , QString::fromLocal8Bit("主动上传采样位信息 ")                              , 0 , cmd_upload_samplepos_info_ord_arg                 , 0 , cmd_upload_samplepos_info_rep_arg                 },
  { CMD_UPLOAD_AUTOSAMPLE_FINISH                     , QString::fromLocal8Bit("自动进样结束命令 ")                                , 0 , cmd_upload_autosample_finish_ord_arg              , 0 , cmd_upload_autosample_finish_rep_arg              },
  { CMD_UPLOAD_AUTOSAMPLE_MIX_FINISH                 , QString::fromLocal8Bit("自动进样混匀结束命令 ")                            , 0 , cmd_upload_autosample_mix_finish_ord_arg          , 0 , cmd_upload_autosample_mix_finish_rep_arg          },
  { CMD_QUIRE_AUTOSAMPLER_STATE                      , QString::fromLocal8Bit("查询自动进样器状态 ")                              , 0 , cmd_quire_autosampler_state_ord_arg               , 0 , cmd_quire_autosampler_state_rep_arg               },
  { CMD_AUTOSAMPLER_INIT                             , QString::fromLocal8Bit("初始化自动进样器 ")                                , 0 , cmd_autosampler_init_ord_arg                      , 0 , cmd_autosampler_init_rep_arg                      },
  { CMD_EMPTY_AUTOSAMPLER                            , QString::fromLocal8Bit("清空自动进样器 ")                                  , 0 , cmd_empty_autosampler_ord_arg                     , 0 , cmd_empty_autosampler_rep_arg                     },
};
//命令类型->"阀"
cCmd content_code_addr_valve             [] =
{
  { CMD_CONTROL_VALVE                                , QString::fromLocal8Bit("阀控制 ")                                          , 0 , cmd_control_valve_ord_arg                         , 0 , cmd_control_valve_rep_arg                         },
  { CMD_QUERY_ALL_VALVE_STATE                        , QString::fromLocal8Bit("查询所有阀状态 ")                                  , 0 , cmd_query_all_valve_state_ord_arg                 , 0 , cmd_query_all_valve_state_rep_arg                 },
  { CMD_QUIRE_VALVE_GROUP_STATE                      , QString::fromLocal8Bit("查询阀组状态 ")                                    , 0 , cmd_quire_valve_group_state_ord_arg               , 0 , cmd_quire_valve_group_state_rep_arg               },
  { CMD_QUIRE_VALVE_CH_STATE                         , QString::fromLocal8Bit("查询指定阀状态 ")                                  , 0 , cmd_quire_valve_ch_state_ord_arg                  , 0 , cmd_quire_valve_ch_state_rep_arg                  },
};
//命令类型->"泵"
cCmd content_code_addr_pump              [] =
{
  { CMD_CONTROL_PUMP                                 , QString::fromLocal8Bit("泵控制 ")                                          , 0 , cmd_control_pump_ord_arg                          , 0 , cmd_control_pump_rep_arg                          },
  { CMD_QUERY_ALL_PUMP_STATE                         , QString::fromLocal8Bit("查询所有泵状态 ")                                  , 0 , cmd_query_all_pump_state_ord_arg                  , 0 , cmd_query_all_pump_state_rep_arg                  },
};
//命令类型->"电机"
cCmd content_code_addr_motor             [] =
{
  { CMD_MOTOR_CONFIG_ATTRIBUTE                       , QString::fromLocal8Bit("电机属性配置 ")                                    , 3 , cmd_motor_config_attribute_ord_arg                , 0 , cmd_motor_config_attribute_rep_arg                },
  { CMD_MOTOR_CONFIG_SPEED                           , QString::fromLocal8Bit("电机挡速配置 ")                                    , 2 , cmd_motor_config_speed_ord_arg                    , 0 , cmd_motor_config_speed_rep_arg                    },
  { CMD_MOTOR_CONFIG_INIT                            , QString::fromLocal8Bit("电机初始配置 ")                                    , 4 , cmd_motor_config_init_ord_arg                     , 0 , cmd_motor_config_init_rep_arg                     },
  { CMD_MOTOR_CONFIG_POS                             , QString::fromLocal8Bit("电机位置状态配置 ")                                , 3 , cmd_motor_config_pos_ord_arg                      , 0 , cmd_motor_config_pos_rep_arg                      },
  { CMD_QUERY_MOTOR_CONFIG_ATTRIBUTE                 , QString::fromLocal8Bit("查询电机属性配置 ")                                , 0 , nullptr                                           , 0 , cmd_query_motor_config_attribute_rep_arg          },
  { CMD_QUERY_MOTOR_CONFIG_SPEED                     , QString::fromLocal8Bit("查询电机挡速配置 ")                                , 1 , cmd_query_motor_config_speed_ord_arg              , 0 , cmd_query_motor_config_speed_rep_arg              },
  { CMD_QUERY_MOTOR_CONFIG_INIT                      , QString::fromLocal8Bit("查询电机初始配置 ")                                , 0 , nullptr                                           , 0 , cmd_query_motor_config_init_rep_arg               },
  { CMD_QUERY_MOTOR_CONFIG_POS                       , QString::fromLocal8Bit("查询电机位置状态配置 ")                            , 1 , cmd_query_motor_config_pos_ord_arg                , 0 , cmd_query_motor_config_pos_rep_arg                },
  { CMD_MOTOR_INIT                                   , QString::fromLocal8Bit("以指定挡速初始化 ")                                , 4 , cmd_motor_init_ord_arg                            , 0 , cmd_motor_init_rep_arg                            },
  { CMD_MOTOR_MOVE_POS                               , QString::fromLocal8Bit("电机以指定挡速运动到指定位置 ")                    , 4 , cmd_motor_move_pos_ord_arg                        , 0 , cmd_motor_move_pos_rep_arg                        },
  { CMD_MOTOR_MOVE_STEP                              , QString::fromLocal8Bit("电机以指定挡速走指定步数 ")                        , 4 , cmd_motor_move_step_ord_arg                       , 0 , cmd_motor_move_step_rep_arg                       },
};
//命令类型->"条码扫描器"
cCmd content_code_addr_barcodescaner     [] =
{
  { CMD_QUIRE_BARCODE_SCANNER_STATE                  , QString::fromLocal8Bit("查询条码扫描器状态 ")                              , 0 , cmd_quire_barcode_scanner_state_ord_arg           , 0 , cmd_quire_barcode_scanner_state_rep_arg           },
  { CMD_START_BARCODE_SCANNING                       , QString::fromLocal8Bit("启动读取条码扫描器 ")                              , 0 , cmd_start_barcode_scanning_ord_arg                , 0 , cmd_start_barcode_scanning_rep_arg                },
  { CMD_BARCODE_TYPE_CHECK_STATUS_SET                , QString::fromLocal8Bit("设置条码扫描仪支持的码制以及校验 ")                , 0 , cmd_barcode_type_check_status_set_ord_arg         , 0 , cmd_barcode_type_check_status_set_rep_arg         },
  { CMD_BARCODE_LEN_SET                              , QString::fromLocal8Bit("设置条码扫描仪支持的长度 ")                        , 0 , cmd_barcode_len_set_ord_arg                       , 0 , cmd_barcode_len_set_rep_arg                       },
  { CMD_BARCODE_SCANNER_TYPE_SET                     , QString::fromLocal8Bit("条码扫描仪类型设定 ")                              , 0 , cmd_barcode_scanner_type_set_ord_arg              , 0 , cmd_barcode_scanner_type_set_rep_arg              },
  { CMD_BARCODE_SCANNER_CLOSE                        , QString::fromLocal8Bit("关闭激光器 ")                                      , 0 , cmd_barcode_scanner_close_ord_arg                 , 0 , cmd_barcode_scanner_close_rep_arg                 },
  { CMD_BARCODE_SCANNER_OPEN                         , QString::fromLocal8Bit("打开激光器 ")                                      , 0 , cmd_barcode_scanner_open_ord_arg                  , 0 , cmd_barcode_scanner_open_rep_arg                  },
};
//命令类型->"注射器"
cCmd content_code_addr_syring            [] =
{
  {             0,                                    QString::fromLocal8Bit(" 无 ")                                              ,0 , nullptr                                           , 0 , nullptr                                           },
};
//命令类型->"采样组件"
cCmd content_code_addr_sample            [] =
{
  { CMD_SAMPLE_CONFIG                                , QString::fromLocal8Bit("配置采样组件 ")                                    , 2 , cmd_sample_config_ord_arg                         , 0 , cmd_sample_config_rep_arg                         },
  { CMD_SAMPLE_HSWING                                , QString::fromLocal8Bit("采样组件水平摆动 ")                                , 6 , cmd_sample_hswing_ord_arg                         , 0 , cmd_sample_hswing_rep_arg                         },
  { CMD_H_INIT_SAMPLE                                , QString::fromLocal8Bit("以指定挡速水平初始化采样组件 ")                    , 3 , cmd_h_init_sample_ord_arg                         , 0 , cmd_h_init_sample_rep_arg                         },
  { CMD_V_INIT_SAMPLE                                , QString::fromLocal8Bit("以指定挡速垂直初始化采样组件 ")                    , 3 , cmd_v_init_sample_ord_arg                         , 0 , cmd_v_init_sample_rep_arg                         },
  { CMD_SAMPLE_H_MOVE_POS                            , QString::fromLocal8Bit("以指定挡速水平运动到指定位置 ")                    , 4 , cmd_sample_h_move_pos_ord_arg                     , 0 , cmd_sample_h_move_pos_rep_arg                     },
  { CMD_SAMPLE_V_MOVE_POS                            , QString::fromLocal8Bit("以指定挡速垂直运动到指定位置 ")                    , 4 , cmd_sample_v_move_pos_ord_arg                     , 0 , cmd_sample_v_move_pos_rep_arg                     },
};
//命令类型->"温度控制"
cCmd content_code_addr_temperature       [] =
{
  { CMD_TEMPERATURE_RANGE_JUDGE                      , QString::fromLocal8Bit("温度范围判断 ")                                    , 1 , cmd_temperature_range_judge_ord_arg               , 0 , nullptr                                           },
  { CMD_TEMPERATURE_CONTROL                          , QString::fromLocal8Bit("温度控制 ")                                        , 1 , cmd_temperature_control_ord_arg                   , 0 , nullptr                                           },
  { CMD_QUIRE_CUR_TEMPERATURE                        , QString::fromLocal8Bit("查询指定通道实测温度值 ")                          , 0 , nullptr                                           , 1 , cmd_quire_cur_temperature_rep_arg                 },
  { CMD_QUIRE_CUR_TEMPERATURE_COMPENSATION           , QString::fromLocal8Bit("查询指定通道补偿后的温度值 ")                      , 0 , nullptr                                           , 1 , cmd_quire_cur_temperature_compensation_rep_arg    },
  { CMD_SET_TARGET_TEMPERATURE                       , QString::fromLocal8Bit("下发目标温度 ")                                    , 1 , cmd_set_target_temperature_ord_arg                , 0 , nullptr                                           },
  { CMD_TEMPERATURE_COMPENSATION_CONFIG              , QString::fromLocal8Bit("下发温度补偿值 ")                                  , 1 , cmd_temperature_compensation_config_ord_arg       , 0 , nullptr                                           },
  { CMD_CONFIG_WORK_RUN_TEMPERATURE                  , QString::fromLocal8Bit("配置工作温度和运行温度 ")                          , 4 , cmd_config_work_run_temperature_ord_arg           , 0 , nullptr                                           },
  { CMD_SET_TEMPERATURE_CH_PID_PARAM                 , QString::fromLocal8Bit("设置PID参数 ")                                     , 3 , cmd_set_temperature_ch_pid_param_ord_arg          , 0 , nullptr                                           },
  { CMD_QUIRE_TEMPERATURE_CH_PID_PARAM               , QString::fromLocal8Bit("获取PID参数 ")                                     , 0 , nullptr                                           , 3 , cmd_quire_temperature_ch_pid_param_rep_arg        },
};
//命令类型->"压力控制"
cCmd content_code_addr_pressure          [] =
{
  { CMD_PRESSURE_CONFIG                              , QString::fromLocal8Bit("压力配置 ")                                        , 4 , cmd_pressure_config_ord_arg                       , 0 , nullptr                       					  },
  { CMD_QUERY_PRESSURE_AD_VALUE                      , QString::fromLocal8Bit("查询指定压力通道压力AD值 ")                        , 0 , nullptr               							  , 1 , cmd_query_pressure_ad_value_rep_arg               },
  { CMD_CHECK_PRESSURE                               , QString::fromLocal8Bit("查询指定通道压力是否在指定压力范围 ")              , 2 , cmd_check_pressure_ord_arg                        , 1 , cmd_check_pressure_rep_arg                        },
  { CMD_QUERY_PRESSURE_VALUE                         , QString::fromLocal8Bit("查询指定压力通道压力值 ")                          , 0 , nullptr                  						  , 1 , cmd_query_pressure_value_rep_arg                  },
  { CMD_BUILD_PRESSURE                               , QString::fromLocal8Bit("建压 ")                                            , 3 , cmd_build_pressure_ord_arg                        , 0 , nullptr                        				},
  { CMD_CALIBRATION_PRESSURE                         , QString::fromLocal8Bit("压力标定 ")                                        , 0 , nullptr                  						  , 0 , nullptr                        				},
  { CMD_QUERY_PRESSURE_KB                            , QString::fromLocal8Bit("查询指定通道压力的K值和B值 ")                      , 0 , nullptr                     					  , 2 , cmd_query_pressure_kb_rep_arg                     },
  { CMD_SET_PRESSURE_KB                              , QString::fromLocal8Bit("设置指定通道压力的K值和B值 ")                      , 2 , cmd_set_pressure_kb_ord_arg                       , 0 , nullptr                       				},
  { CMD_AUTO_CALC_PRESSURE_KB                        , QString::fromLocal8Bit("自动计算指定通道压力的K值和B值 ")                  , 0 , nullptr                                           , 0 , nullptr                 					},
  { CMD_SET_PRESSURE_DEFAULT_KB                      , QString::fromLocal8Bit("设置默认压力通道的K值和B值 ")                      , 0 , nullptr                                           , 0 , nullptr               						},
  { CMD_MONITOR_PRESSURE                             , QString::fromLocal8Bit("压力监控 ")                                        , 4 , cmd_monitor_pressure_ord_arg                      , 0 , nullptr                      				},
  { CMD_QUIRE_PRESSURE_CH_VALUE                      , QString::fromLocal8Bit("查询指定通道压力值 ")                              , 0 , nullptr                                           , 1 , cmd_quire_pressure_ch_value_rep_arg               },
  { CMD_QUIRE_PRESSURE_CH_KB_VALUE                   , QString::fromLocal8Bit("查询指定通道的KB值 ")                              , 0 , nullptr                                           , 2 , cmd_quire_pressure_ch_kb_value_rep_arg            },
  { CMD_SET_PRESSURE_CH_KB_VALUE                     , QString::fromLocal8Bit("设定指定通道的KB值 ")                              , 2 , cmd_set_pressure_ch_kb_value_ord_arg              , 0 , nullptr              						},
  { CMD_SET_PRESSURE_MONITOR_STATE                   , QString::fromLocal8Bit("启动指定通道压力监测 ")                            , 3 , cmd_set_pressure_monitor_state_ord_arg            , 0 , nullptr            							},
  { CMD_CHECK_PRESSURE_STATE                         , QString::fromLocal8Bit("结束指定通道压力监测 ")                            , 2 , cmd_check_pressure_state_ord_arg                  , 1 , cmd_check_pressure_state_rep_arg                  },
  { CMD_SET_AUTO_BUILD_PRESSURE                      , QString::fromLocal8Bit("自动建压 ")                                        , 1 , cmd_set_auto_build_pressure_ord_arg               , 0 , nullptr               						},
};
//命令类型->"试剂检测板"
cCmd content_code_addr_reagent           [] =
{
  { CMD_REAGENT_CONFIG                               , QString::fromLocal8Bit("试剂通道配置 ")                                    , 0 , cmd_reagent_config_ord_arg                        , 0 , cmd_reagent_config_rep_arg                        },
  { CMD_QUIRE_REAGENT_CH_STATE                       , QString::fromLocal8Bit("查询指定通道试剂状态 ")                            , 0 , cmd_quire_reagent_ch_state_ord_arg                , 0 , cmd_quire_reagent_ch_state_rep_arg                },
  { CMD_DETEC_REAGENT_CH                             , QString::fromLocal8Bit("试剂有无查询 ")                                    , 0 , cmd_detec_reagent_ch_ord_arg                      , 0 , cmd_detec_reagent_ch_rep_arg                      },
  { CMD_QUIRE_NONE_REAGENT_TIME                      , QString::fromLocal8Bit("查询无试剂时间 ")                                  , 0 , cmd_quire_none_reagent_time_ord_arg               , 0 , cmd_quire_none_reagent_time_rep_arg               },
  { CMD_SET_NONE_REAGENT_THRESHOLD                   , QString::fromLocal8Bit("设置无试剂阈值 ")                                  , 0 , cmd_set_none_reagent_threshold_ord_arg            , 0 , cmd_set_none_reagent_threshold_rep_arg            },
};
//命令类型->"装载组件"
cCmd content_code_addr_loader            [] =
{
  { CMD_CONFIG_LOADER                                , QString::fromLocal8Bit("配置装载组件 ")                                    , 0 , cmd_config_loader_ord_arg                         , 0 , cmd_config_loader_rep_arg                         },
  { CMD_LOADER_INIT                                  , QString::fromLocal8Bit("初始化装载组件 ")                                  , 0 , cmd_loader_init_ord_arg                           , 0 , cmd_loader_init_rep_arg                           },
  { CMD_LOAD_RACK                                    , QString::fromLocal8Bit("装载试管架 ")                                      , 0 , cmd_load_rack_ord_arg                             , 0 , cmd_load_rack_rep_arg                             },
};
//命令类型->"进给组件"
cCmd content_code_addr_feeder            [] =
{
  { CMD_CONFIG_FEEDER                                , QString::fromLocal8Bit("配置进给组件 ")                                    , 0 , cmd_config_feeder_ord_arg                         , 0 , cmd_config_feeder_rep_arg                         },
  { CMD_FEEDER_INIT                                  , QString::fromLocal8Bit("初始化进给组件 ")                                  , 0 , cmd_feeder_init_ord_arg                           , 0 , cmd_feeder_init_rep_arg                           },
  { CMD_FEED_RACK                                    , QString::fromLocal8Bit("试管架移动一个试管位 ")                            , 0 , cmd_feed_rack_ord_arg                             , 0 , cmd_feed_rack_rep_arg                             },
};
//命令类型->"卸载组件"
cCmd content_code_addr_unloader          [] =
{
  { CMD_CONFIG_UNLOADER                              , QString::fromLocal8Bit("配置卸载组件 ")                                    , 0 , cmd_config_unloader_ord_arg                       , 0 , cmd_config_unloader_rep_arg                       },
  { CMD_UNLOADER_INIT                                , QString::fromLocal8Bit("初始化卸载组件 ")                                  , 0 , cmd_unloader_init_ord_arg                         , 0 , cmd_unloader_init_rep_arg                         },
  { CMD_UNLOAD_RACK                                  , QString::fromLocal8Bit("卸载试管架 ")                                      , 0 , cmd_unload_rack_ord_arg                           , 0 , cmd_unload_rack_rep_arg                           },
};
//命令类型->"混匀组件"
cCmd content_code_addr_mixer             [] =
{
  { CMD_CONFIG_MIXER                                 , QString::fromLocal8Bit("配置混匀组件 ")                                    , 0 , cmd_config_mixer_ord_arg                          , 0 , cmd_config_mixer_rep_arg                          },
  { CMD_MIXER_INIT                                   , QString::fromLocal8Bit("初始化混匀组件 ")                                  , 0 , cmd_mixer_init_ord_arg                            , 0 , cmd_mixer_init_rep_arg                            },
  { CMD_TUBE_MIX                                     , QString::fromLocal8Bit("启动试管混匀 ")                                    , 0 , cmd_tube_mix_ord_arg                              , 0 , cmd_tube_mix_rep_arg                              },
  { CMD_MIXER_RESET                                  , QString::fromLocal8Bit("混匀组件复位 ")                                    , 0 , cmd_mixer_reset_ord_arg                           , 0 , cmd_mixer_reset_rep_arg                           },
  { CMD_QUIRE_MIXER_STATE                            , QString::fromLocal8Bit("查询混匀组件是否在初始位 ")                        , 0 , cmd_quire_mixer_state_ord_arg                     , 0 , cmd_quire_mixer_state_rep_arg                     },
  { CMD_GRAB_MECHANISM_INIT                          , QString::fromLocal8Bit("启动初始化抓取结构 ")                              , 0 , cmd_grab_mechanism_init_ord_arg                   , 0 , cmd_grab_mechanism_init_rep_arg                   },
  { CMD_GRAB_TUBE                                    , QString::fromLocal8Bit("抓取试管 ")                                        , 0 , cmd_grab_tube_ord_arg                             , 0 , cmd_grab_tube_rep_arg                             },
  { CMD_RAISE_MECHANISM_INIT                         , QString::fromLocal8Bit("启动初始化升降结构 ")                              , 0 , cmd_raise_mechanism_init_ord_arg                  , 0 , cmd_raise_mechanism_init_rep_arg                  },
  { CMD_RAISE_TUBE                                   , QString::fromLocal8Bit("举起试管 ")                                        , 0 , cmd_raise_tube_ord_arg                            , 0 , cmd_raise_tube_rep_arg                            },
  { CMD_SWING_MECHANISM_INIT                         , QString::fromLocal8Bit("启动速度初始化摆动结构 ")                          , 0 , cmd_swing_mechanism_init_ord_arg                  , 0 , cmd_swing_mechanism_init_rep_arg                  },
  { CMD_SWING_TUBE                                   , QString::fromLocal8Bit("摆动试管 ")                                        , 0 , cmd_swing_tube_ord_arg                            , 0 , cmd_swing_tube_rep_arg                            },
  { CMD_GRAB_TUBE_FROM_RELAY                         , QString::fromLocal8Bit("抓取电机从中继仓取试管 ")                          , 0 , cmd_grab_tube_from_relay_ord_arg                  , 0 , cmd_grab_tube_from_relay_rep_arg                  },
  { CMD_RAISE_TUBE_TO_RELAY                          , QString::fromLocal8Bit("升降电机将试管放到中继仓 ")                        , 0 , cmd_raise_tube_to_relay_ord_arg                   , 0 , cmd_raise_tube_to_relay_rep_arg                   },
  { CMD_RELAY_MECHANISM_INIT                         , QString::fromLocal8Bit("启动初始化中继仓组件 ")                            , 0 , cmd_relay_mechanism_init_ord_arg                  , 0 , cmd_relay_mechanism_init_rep_arg                  },
  { CMD_RELAY_TUBE                                   , QString::fromLocal8Bit("中继仓接试管 ")                                    , 0 , cmd_relay_tube_ord_arg                            , 0 , cmd_relay_tube_rep_arg                            },
};
//命令类型->"其他"
cCmd content_code_addr_other             [] =
{
  { CMD_QUIRE_MOTOR_OPT_STATE                        , QString::fromLocal8Bit("查询电机光耦状态 ")                                , 0 , cmd_quire_motor_opt_state_ord_arg                 , 0 , cmd_quire_motor_opt_state_rep_arg                 },
  { CMD_QUIRE_REAGENT_OPT_STATE                      , QString::fromLocal8Bit("查询试剂光耦状态 ")                                , 0 , cmd_quire_reagent_opt_state_ord_arg               , 0 , cmd_quire_reagent_opt_state_rep_arg               },
  { CMD_QUIRE_SWITCH_STATE                           , QString::fromLocal8Bit("查询开关状态 ")                                    , 0 , cmd_quire_switch_state_ord_arg                    , 0 , cmd_quire_switch_state_rep_arg                    },
  { CMD_SET_SW_CHECK_STATE                           , QString::fromLocal8Bit("设置是否进行开关检测 ")                            , 0 , cmd_set_sw_check_state_ord_arg                    , 0 , cmd_set_sw_check_state_rep_arg                    },
  { CMD_UPLOAD_OPEN_ERR                              , QString::fromLocal8Bit("上报右侧门或者激光器盒子打开故障 ")                , 0 , cmd_upload_open_err_ord_arg                       , 0 , cmd_upload_open_err_rep_arg                       },
  { CMD_CRP_LASER_CTL_CMD                            , QString::fromLocal8Bit("CRP激光器控制命令 ")                               , 0 , cmd_crp_laser_ctl_cmd_ord_arg                     , 0 , cmd_crp_laser_ctl_cmd_rep_arg                     },
  { CMD_QUIRE_MOTOR_OPT_GROUP_STATE                  , QString::fromLocal8Bit("查询电机光耦组状态 ")                              , 0 , cmd_quire_motor_opt_group_state_ord_arg           , 0 , cmd_quire_motor_opt_group_state_rep_arg           },
  { CMD_QUIRE_MOTOR_OPT_CH_STATE                     , QString::fromLocal8Bit("查询指定电机光耦状态 ")                            , 0 , cmd_quire_motor_opt_ch_state_ord_arg              , 0 , cmd_quire_motor_opt_ch_state_rep_arg              },
  { CMD_QUIRE_REAGENT_GROUP_STATE                    , QString::fromLocal8Bit("查询试剂通道组的状态 ")                            , 0 , cmd_quire_reagent_group_state_ord_arg             , 0 , cmd_quire_reagent_group_state_rep_arg             },
  { CMD_QUIRE_REAGENT_CHANEL_STATE                   , QString::fromLocal8Bit("查询指定的试剂通道试剂有无的状态 ")                , 0 , cmd_quire_reagent_chanel_state_ord_arg            , 0 , cmd_quire_reagent_chanel_state_rep_arg            },
  { CMD_QUIRE_SWITCH_GROUP_STATE                     , QString::fromLocal8Bit("查询开关通道组的状态 ")                            , 0 , cmd_quire_switch_group_state_ord_arg              , 0 , cmd_quire_switch_group_state_rep_arg              },
  { CMD_QUIRE_SWITCH_CH_STATE                        , QString::fromLocal8Bit("查询指定的开关通道的状态 ")                        , 0 , cmd_quire_switch_ch_state_ord_arg                 , 0 , cmd_quire_switch_ch_state_rep_arg                 },
  { CMD_SET_SWITCH_ALL_MONITOR_STATE                 , QString::fromLocal8Bit("设定所有开关通道是否进行实时检查 ")                , 0 , cmd_set_switch_all_monitor_state_ord_arg          , 0 , cmd_set_switch_all_monitor_state_rep_arg          },
  { CMD_SET_SWITCH_CH_MONITOR_STATE                  , QString::fromLocal8Bit("设定指定开关通道是否进行实时检查 ")                , 0 , cmd_set_switch_ch_monitor_state_ord_arg           , 0 , cmd_set_switch_ch_monitor_state_rep_arg           },
};
//命令类型->"电压监控"
cCmd content_code_addr_power             [] =
{
  { CMD_QUIRE_POWER_VALUE                            , QString::fromLocal8Bit("查询通道电压 ")                                    , 0 , cmd_quire_power_value_ord_arg                     , 0 , cmd_quire_power_value_rep_arg                     },
  { CMD_SET_POWER_MONITOR_STATE                      , QString::fromLocal8Bit("启动通道电压监测 ")                                , 0 , cmd_set_power_monitor_state_ord_arg               , 0 , cmd_set_power_monitor_state_rep_arg               },
  { CMD_CLEAR_POWER_MONITOR_STATE                    , QString::fromLocal8Bit("关闭通道电压监测 ")                                , 0 , cmd_clear_power_monitor_state_ord_arg             , 0 , cmd_clear_power_monitor_state_rep_arg             },
};
//命令类型->"灌注"
cCmd content_code_addr_perfusion         [] =
{
  { CMD_START_PERFUSION                              , QString::fromLocal8Bit("启动灌注 ")                                        , 0 , cmd_start_perfusion_ord_arg                       , 0 , cmd_start_perfusion_rep_arg                       },
};
//命令类型->"排空"
cCmd content_code_addr_evacuation        [] =
{
  { CMD_START_EVACUATION                             , QString::fromLocal8Bit("启动排空 ")                                        , 0 , cmd_start_evacuation_ord_arg                      , 0 , cmd_start_evacuation_rep_arg                      },
};
//命令类型->"三维采样组件"
cCmd content_code_addr_sample_3d         [] =
{
  { CMD_SAMPLE_3D_LRSWING                            , QString::fromLocal8Bit("三维采样组件左右摆动 ")                            , 0 , cmd_sample_3d_lrswing_ord_arg                     , 0 , cmd_sample_3d_lrswing_rep_arg                     },
  { CMD_SAMPLE_3D_HSWING                             , QString::fromLocal8Bit("三维采样组件水平摆动 ")                            , 0 , cmd_sample_3d_hswing_ord_arg                      , 0 , cmd_sample_3d_hswing_rep_arg                      },
  { CMD_SAMPLE_3D_HMOTOR_INIT                        , QString::fromLocal8Bit("三维采样组件水平电机初始化 ")                      , 0 , cmd_sample_3d_hmotor_init_ord_arg                 , 0 , cmd_sample_3d_hmotor_init_rep_arg                 },
  { CMD_SAMPLE_3D_VMOTOR_INIT                        , QString::fromLocal8Bit("三维采样组件垂直电机初始化 ")                      , 0 , cmd_sample_3d_vmotor_init_ord_arg                 , 0 , cmd_sample_3d_vmotor_init_rep_arg                 },
  { CMD_SAMPLE_3D_LRMOTOR_INIT                       , QString::fromLocal8Bit("三维采样组件左右电机初始化 ")                      , 0 , cmd_sample_3d_lrmotor_init_ord_arg                , 0 , cmd_sample_3d_lrmotor_init_rep_arg                },
  { CMD_SAMPLE_3D_HMOTOR_POS                         , QString::fromLocal8Bit("三维采样组件水平电机走位置 ")                      , 0 , cmd_sample_3d_hmotor_pos_ord_arg                  , 0 , cmd_sample_3d_hmotor_pos_rep_arg                  },
  { CMD_SAMPLE_3D_VMOTOR_POS                         , QString::fromLocal8Bit("三维采样组件垂直电机走位置 ")                      , 0 , cmd_sample_3d_vmotor_pos_ord_arg                  , 0 , cmd_sample_3d_vmotor_pos_rep_arg                  },
  { CMD_SAMPLE_3D_LRMOTOR_POS                        , QString::fromLocal8Bit("三维采样组件左右电机走位置 ")                      , 0 , cmd_sample_3d_lrmotor_pos_ord_arg                 , 0 , cmd_sample_3d_lrmotor_pos_rep_arg                 },
};
//命令类型->"样本试剂运动组件"
cCmd content_code_addr_samples_reagents  [] =
{
  { CMD_SAMPLES_REAGENTS_SAMPLE_HMOTOR_INIT          , QString::fromLocal8Bit("样本试剂运动组件中的样本采样组件水平电机初始化 ")  , 0 , cmd_samples_reagents_sample_hmotor_init_ord_arg   , 0 , cmd_samples_reagents_sample_hmotor_init_rep_arg   },
  { CMD_SAMPLES_REAGENTS_SAMPLE_VMOTOR_INIT          , QString::fromLocal8Bit("样本试剂运动组件中的样本采样组件垂直电机初始化 ")  , 0 , cmd_samples_reagents_sample_vmotor_init_ord_arg   , 0 , cmd_samples_reagents_sample_vmotor_init_rep_arg   },
  { CMD_SAMPLES_REAGENTS_SAMPLE_LRMOTOR_INIT         , QString::fromLocal8Bit("样本试剂运动组件中的样本采样组件左右电机初始化 ")  , 0 , cmd_samples_reagents_sample_lrmotor_init_ord_arg  , 0 , cmd_samples_reagents_sample_lrmotor_init_rep_arg  },
  { CMD_SAMPLES_REAGENTS_REAGENT_HMOTOR_INIT         , QString::fromLocal8Bit("样本试剂运动组件中的试剂采样组件水平电机初始化 ")  , 0 , cmd_samples_reagents_reagent_hmotor_init_ord_arg  , 0 , cmd_samples_reagents_reagent_hmotor_init_rep_arg  },
  { CMD_SAMPLES_REAGENTS_REAGENT_VMOTOR_INIT         , QString::fromLocal8Bit("样本试剂运动组件中的试剂采样组件垂直电机初始化 ")  , 0 , cmd_samples_reagents_reagent_vmotor_init_ord_arg  , 0 , cmd_samples_reagents_reagent_vmotor_init_rep_arg  },
  { CMD_SAMPLES_REAGENTS_REAGENT_LRMOTOR_INIT        , QString::fromLocal8Bit("样本试剂运动组件中的试剂采样组件左右电机初始化 ")  , 0 , cmd_samples_reagents_reagent_lrmotor_init_ord_arg , 0 , cmd_samples_reagents_reagent_lrmotor_init_rep_arg },
  { CMD_SAMPLES_REAGENTS_HATCHERY_MOTOR_INIT         , QString::fromLocal8Bit("样本试剂运动组件中的孵育池混匀电机初始化 ")        , 0 , cmd_samples_reagents_hatchery_motor_init_ord_arg  , 0 , cmd_samples_reagents_hatchery_motor_init_rep_arg  },
  { CMD_SAMPLES_REAGENTS_SAMPLE_HMOTOR_POS           , QString::fromLocal8Bit("样本试剂运动组件中的样本采样组件水平电机走位置 ")  , 0 , cmd_samples_reagents_sample_hmotor_pos_ord_arg    , 0 , cmd_samples_reagents_sample_hmotor_pos_rep_arg    },
  { CMD_SAMPLES_REAGENTS_SAMPLE_VMOTOR_POS           , QString::fromLocal8Bit("样本试剂运动组件中的样本采样组件垂直电机走位置 ")  , 0 , cmd_samples_reagents_sample_vmotor_pos_ord_arg    , 0 , cmd_samples_reagents_sample_vmotor_pos_rep_arg    },
  { CMD_SAMPLES_REAGENTS_SAMPLE_LRMOTOR_POS          , QString::fromLocal8Bit("样本试剂运动组件中的样本采样组件左右电机走位置 ")  , 0 , cmd_samples_reagents_sample_lrmotor_pos_ord_arg   , 0 , cmd_samples_reagents_sample_lrmotor_pos_rep_arg   },
  { CMD_SAMPLES_REAGENTS_REAGENT_HMOTOR_POS          , QString::fromLocal8Bit("样本试剂运动组件中的试剂采样组件水平电机走位置 ")  , 0 , cmd_samples_reagents_reagent_hmotor_pos_ord_arg   , 0 , cmd_samples_reagents_reagent_hmotor_pos_rep_arg   },
  { CMD_SAMPLES_REAGENTS_REAGENT_VMOTOR_POS          , QString::fromLocal8Bit("样本试剂运动组件中的试剂采样组件垂直电机走位置 ")  , 0 , cmd_samples_reagents_reagent_vmotor_pos_ord_arg   , 0 , cmd_samples_reagents_reagent_vmotor_pos_rep_arg   },
  { CMD_SAMPLES_REAGENTS_REAGENT_LRMOTOR_POS         , QString::fromLocal8Bit("样本试剂运动组件中的试剂采样组件左右电机走位置 ")  , 0 , cmd_samples_reagents_reagent_lrmotor_pos_ord_arg  , 0 , cmd_samples_reagents_reagent_lrmotor_pos_rep_arg  },
  { CMD_SAMPLES_REAGENTS_HATCHERY_MOTOR_POS          , QString::fromLocal8Bit("样本试剂运动组件中的孵育池混匀电机走位置 ")        , 0 , cmd_samples_reagents_hatchery_motor_pos_ord_arg   , 0 , cmd_samples_reagents_hatchery_motor_pos_rep_arg   },
  { CMD_SAMPLES_REAGENTS_HATCHERY_MIX                , QString::fromLocal8Bit("样本试剂运动组件中的孵育池混匀 ")                  , 0 , cmd_samples_reagents_hatchery_mix_ord_arg         , 0 , cmd_samples_reagents_hatchery_mix_rep_arg         },
};
//命令类型->"试剂池混匀组件"
cCmd content_code_addr_reagent_room      [] =
{
  { CMD_REAGENT_ROOM_MOTOR_INIT                      , QString::fromLocal8Bit("试剂池混匀电机初始化 ")                            , 0 , cmd_reagent_room_motor_init_ord_arg               , 0 , cmd_reagent_room_motor_init_rep_arg               },
  { CMD_REAGENT_ROOM_MOTOR_POS                       , QString::fromLocal8Bit("试剂池混匀电机走位置 ")                            , 0 , cmd_reagent_room_motor_pos_ord_arg                , 0 , cmd_reagent_room_motor_pos_rep_arg                },
  { CMD_REAGENT_ROOM_MIX                             , QString::fromLocal8Bit("试剂池混匀 ")                                      , 0 , cmd_reagent_room_mix_ord_arg                      , 0 , cmd_reagent_room_mix_rep_arg                      },
};
//命令类型->"码盘控制组件"
cCmd content_code_addr_code_wheel        [] =
{
  { CMD_CODE_WHEEL_INIT                              , QString::fromLocal8Bit("初始化码盘 ")                                      , 0 , cmd_code_wheel_init_ord_arg                       , 0 , cmd_code_wheel_init_rep_arg                       },
  { CMD_CODE_WHEEL_POS                               , QString::fromLocal8Bit("码盘走位置 ")                                      , 0 , cmd_code_wheel_pos_ord_arg                        , 0 , cmd_code_wheel_pos_rep_arg                        },
  { CMD_CODE_WHEEL_STOP                              , QString::fromLocal8Bit("停止码盘 ")                                        , 0 , cmd_code_wheel_stop_ord_arg                       , 0 , cmd_code_wheel_stop_rep_arg                       },
};
//命令类型->"编码器电机控制"
cCmd content_code_addr_coder_motor       [] =
{
  { CMD_CODER_MOTOR_CFG_ATTR                         , QString::fromLocal8Bit("编码器电机属性配置 ")                              , 0 , cmd_coder_motor_cfg_attr_ord_arg                  , 0 , cmd_coder_motor_cfg_attr_rep_arg                  },
  { CMD_CODER_MOTOR_CFG_SPEED                        , QString::fromLocal8Bit("编码器电机速度配置 ")                              , 0 , cmd_coder_motor_cfg_speed_ord_arg                 , 0 , cmd_coder_motor_cfg_speed_rep_arg                 },
  { CMD_CODER_MOTOR_CFG_INIT                         , QString::fromLocal8Bit("编码器电机初始化配置 ")                            , 0 , cmd_coder_motor_cfg_init_ord_arg                  , 0 , cmd_coder_motor_cfg_init_rep_arg                  },
  { CMD_CODER_MOTOR_INIT                             , QString::fromLocal8Bit("编码器电机初始化 ")                                , 0 , cmd_coder_motor_init_ord_arg                      , 0 , cmd_coder_motor_init_rep_arg                      },
  { CMD_CODER_MOTOR_POS                              , QString::fromLocal8Bit("编码器电机走位置 ")                                , 0 , cmd_coder_motor_pos_ord_arg                       , 0 , cmd_coder_motor_pos_rep_arg                       },
  { CMD_CODER_MOTOR_STEPS                            , QString::fromLocal8Bit("编码器电机走步数 ")                                , 0 , cmd_coder_motor_steps_ord_arg                     , 0 , cmd_coder_motor_steps_rep_arg                     },
};
//命令类型->"试剂采样组件"
cCmd content_code_addr_sample_coder_motor[] =
{
  { CMD_SAMPLE_CODER_MOTOR_HINIT                     , QString::fromLocal8Bit("试剂采样组件水平初始化 ")                          , 0 , cmd_sample_coder_motor_hinit_ord_arg              , 0 , cmd_sample_coder_motor_hinit_rep_arg              },
  { CMD_SAMPLE_CODER_MOTOR_VINIT                     , QString::fromLocal8Bit("试剂采样组件垂直初始化 ")                          , 0 , cmd_sample_coder_motor_vinit_ord_arg              , 0 , cmd_sample_coder_motor_vinit_rep_arg              },
  { CMD_SAMPLE_CODER_MOTOR_HPOS                      , QString::fromLocal8Bit("试剂采样组件水平走位置 ")                          , 0 , cmd_sample_coder_motor_hpos_ord_arg               , 0 , cmd_sample_coder_motor_hpos_rep_arg               },
  { CMD_SAMPLE_CODER_MOTOR_VPOS                      , QString::fromLocal8Bit("试剂采样组件垂直走位置 ")                          , 0 , cmd_sample_coder_motor_vpos_ord_arg               , 0 , cmd_sample_coder_motor_vpos_rep_arg               },
  { CMD_SAMPLE_CODER_MOTOR_VSUCK                     , QString::fromLocal8Bit("试剂采样组件垂直吸样 ")                            , 0 , cmd_sample_coder_motor_vsuck_ord_arg              , 0 , cmd_sample_coder_motor_vsuck_rep_arg              },
};
//命令类型->"吸样混匀组件"
cCmd content_code_addr_suck_mix          [] =
{
  { CMD_SUCK_MIX_INIT                                , QString::fromLocal8Bit("吸样混匀组件初始化 ")                              , 0 , cmd_suck_mix_init_ord_arg                         , 0 , cmd_suck_mix_init_rep_arg                         },
  { CMD_SUCK_MIX_SUCK                                , QString::fromLocal8Bit("吸样混匀组件吸样 ")                                , 0 , cmd_suck_mix_suck_ord_arg                         , 0 , cmd_suck_mix_suck_rep_arg                         },
  { CMD_SUCK_MIX_SUCK_END                            , QString::fromLocal8Bit("吸样混匀组件吸样结束 ")                            , 0 , cmd_suck_mix_suck_end_ord_arg                     , 0 , cmd_suck_mix_suck_end_rep_arg                     },
  { CMD_SUCK_MIX_MIX                                 , QString::fromLocal8Bit("吸样混匀组件混匀 ")                                , 0 , cmd_suck_mix_mix_ord_arg                          , 0 , cmd_suck_mix_mix_rep_arg                          },
  { CMD_SUCK_MIX_MIX_END                             , QString::fromLocal8Bit("吸样混匀组件混匀结束 ")                            , 0 , cmd_suck_mix_mix_end_ord_arg                      , 0 , cmd_suck_mix_mix_end_rep_arg                      },
};
//命令类型->"抛杯组件"
cCmd content_code_addr_throw_cup         [] =
{
  { CMD_THROW_CUP_INIT                               , QString::fromLocal8Bit("初始化抛杯组件 ")                                  , 0 , cmd_throw_cup_init_ord_arg                        , 0 , cmd_throw_cup_init_rep_arg                        },
  { CMD_THROW_CUP_THROW                              , QString::fromLocal8Bit("抛杯组件抛杯 ")                                    , 0 , cmd_throw_cup_throw_ord_arg                       , 0 , cmd_throw_cup_throw_rep_arg                       },
};
//命令类型->"加杯组件"
cCmd content_code_addr_add_cup           [] =
{
  { CMD_ADD_CUP_INIT                                 , QString::fromLocal8Bit("初始化加杯组件 ")                                  , 0 , cmd_add_cup_init_ord_arg                          , 0 , cmd_add_cup_init_rep_arg                          },
  { CMD_ADD_CUP_ADD                                  , QString::fromLocal8Bit("加杯组件加杯 ")                                    , 0 , cmd_add_cup_add_ord_arg                           , 0 , cmd_add_cup_add_rep_arg                           },
};
//命令类型->"调试"
cCmd content_code_addr_debug             [] =
{
  { CMD_UPLOAD_DEBUG_MSG                             , QString::fromLocal8Bit("MCU上传调试信息 ")                                 , 0 , cmd_upload_debug_msg_ord_arg                      , 0 , cmd_upload_debug_msg_rep_arg                      },
  { CMD_ERROR_DEBUG                                  , QString::fromLocal8Bit("错误调试命令 ")                                    , 0 , cmd_error_debug_ord_arg                           , 0 , cmd_error_debug_rep_arg                           },
  { CMD_5101_INIT                                    , QString::fromLocal8Bit("初始化5101运动组件 ")                              , 0 , cmd_5101_init_ord_arg                             , 0 , cmd_5101_init_rep_arg                             },
};

#endif // ARRAY_CONTENT_CODE
