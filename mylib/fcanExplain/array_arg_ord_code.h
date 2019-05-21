/*
 * 放着命令内容的编码
 */
#ifndef ARRAY_ORD_ARG_CODE_H
#define ARRAY_ORD_ARG_CODE_H

//命令类型->"从站"
cArg cmd_query_slave_version_ord_arg                   [] = {{0,1,QString::fromLocal8Bit("对象"),{{0x01,QString::fromLocal8Bit("PCB版本")},{0x02,QString::fromLocal8Bit("MCU版本")},{0x03,QString::fromLocal8Bit("FPGA版本")}}}};
cArg cmd_query_slave_all_version_ord_arg               [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_query_slave_time_ord_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_set_slave_time_ord_arg                        [] = {{0,1,QString::fromLocal8Bit("年"),{}},{0,1,QString::fromLocal8Bit("月"),{}},{0,1,QString::fromLocal8Bit("日"),{}},{0,1,QString::fromLocal8Bit("时"),{}},{0,1,QString::fromLocal8Bit("分"),{}},{0,1,QString::fromLocal8Bit("秒"),{}}};
cArg cmd_slave_parse_frame_format_err_ord_arg          [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_slave_comm_self_check_ok_ord_arg              [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upgrade_reset_ord_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_enter_upgrade_mode_ord_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_start_upgrade_ord_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upgrade_data_ord_arg                          [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upgrade_finish_ord_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_fpga_start_upgrade_ord_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_fpga_upgrade_data_ord_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_fpga_upgrade_finish_ord_arg                   [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"智能卡"
//cArg cmd_scr_reset_pcd_ord_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_close_rf_ord_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_test_ord_arg                            [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_beep_ord_arg                            [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_request_ord_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_anticoll_ord_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_select_ord_arg                          [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_rats_ord_arg                            [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_command_ord_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_close_smartcard_ord_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_open_smartcard_ord_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_write_smartcard_ord_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_read_smartcard_ord_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_create_smartcard_ord_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_setexauthkey_smartcard_ord_arg                [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_setfilelinekey_smartcard_ord_arg              [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_set_store_dir_ord_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_card_ver_ord_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_smartcard_open_ord_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_smartcard_close_ord_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_smartcard_write_ord_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_get_smartcard_no_ord_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_set_oem_num_ord_arg                           [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"时序"
cArg cmd_timeseq_frame_head_ord_arg                    [] = {{0,2,QString::fromLocal8Bit("时序号")}};
cArg cmd_timeseq_frame_tail_ord_arg                    [] = {{0,2,QString::fromLocal8Bit("帧数")}};
cArg cmd_timeseq_finish_ord_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_start_timeseq_ord_arg                         [] = {{0,2,QString::fromLocal8Bit("时序号")}};
cArg cmd_stop_timeseq_ord_arg                          [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_timeseq_overlap_control_ord_arg               [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"自动进样"
cArg cmd_start_autosample_ord_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_start_autosample_rack_moving_ord_arg          [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_start_autosample_tube_mixing_ord_arg          [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_stop_autosample_ord_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_abort_autosample_ord_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_emergency_stop_autosample_ord_arg             [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_autosample_skip_cur_rack_ord_arg              [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_recover_autosample_ord_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upload_rack_number_ord_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upload_mixpos_info_ord_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upload_samplepos_info_ord_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upload_autosample_finish_ord_arg              [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upload_autosample_mix_finish_ord_arg          [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_autosampler_state_ord_arg               [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_autosampler_init_ord_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_empty_autosampler_ord_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"阀"
cArg cmd_control_valve_ord_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_query_all_valve_state_ord_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_valve_group_state_ord_arg               [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_valve_ch_state_ord_arg                  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"泵"
cArg cmd_control_pump_ord_arg                          [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_query_all_pump_state_ord_arg                  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"电机"
cArg cmd_motor_config_attribute_ord_arg                [] = {{0,1,QString::fromLocal8Bit("最大电流")},{2,1,QString::fromLocal8Bit("锁定"),{{0x00,QString::fromLocal8Bit("锁定")},{0x01,QString::fromLocal8Bit("不锁")}}},{2,1,QString::fromLocal8Bit("方向"),{{0x00,QString::fromLocal8Bit("正向")},{0x01,QString::fromLocal8Bit("反向")}}}};
cArg cmd_motor_config_speed_ord_arg                    [] = {{0,1,QString::fromLocal8Bit("电机档速")},{0,1,QString::fromLocal8Bit("细分数")}};
cArg cmd_motor_config_init_ord_arg                     [] = {{0,2,QString::fromLocal8Bit("最大步数")},{0,2,QString::fromLocal8Bit("初始化步数")},{0,2,QString::fromLocal8Bit("补偿步数")},{0,2,QString::fromLocal8Bit("阻尼步数")}};
cArg cmd_motor_config_pos_ord_arg                      [] = {{0,1,QString::fromLocal8Bit("位置号")},{0,2,QString::fromLocal8Bit("离初始位步数")},{0,1,QString::fromLocal8Bit("位置光耦号")}};
cArg cmd_query_motor_config_attribute_ord_arg          [] = {{}};
cArg cmd_query_motor_config_speed_ord_arg              [] = {{0,1,QString::fromLocal8Bit("电机档速")}};
cArg cmd_query_motor_config_init_ord_arg               [] = {{}};
cArg cmd_query_motor_config_pos_ord_arg                [] = {{0,1,QString::fromLocal8Bit("位置号")}};
cArg cmd_motor_init_ord_arg                            [] = {{0,1,QString::fromLocal8Bit("档速")},{0,2,QString::fromLocal8Bit("最大时间")},{2,1,QString::fromLocal8Bit("锁定"),{{0x00,QString::fromLocal8Bit("锁定")},{0x01,QString::fromLocal8Bit("不锁")}}},{0,1,QString::fromLocal8Bit("阻尼")}};
cArg cmd_motor_move_pos_ord_arg                        [] = {{0,1,QString::fromLocal8Bit("位置")},{0,1,QString::fromLocal8Bit("档速")},{0,2,QString::fromLocal8Bit("时间")},{2,1,QString::fromLocal8Bit("锁定"),{{0x00,QString::fromLocal8Bit("锁定")},{0x01,QString::fromLocal8Bit("不锁")}}}};
cArg cmd_motor_move_step_ord_arg                       [] = {{-1,2,QString::fromLocal8Bit("步数")},{0,1,QString::fromLocal8Bit("档速")},{0,2,QString::fromLocal8Bit("时间")},{2,1,QString::fromLocal8Bit("锁定"),{{0x00,QString::fromLocal8Bit("锁定")},{0x01,QString::fromLocal8Bit("不锁")}}}};
//命令类型->"条码扫描器"
cArg cmd_quire_barcode_scanner_state_ord_arg           [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_start_barcode_scanning_ord_arg                [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_barcode_type_check_status_set_ord_arg         [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_barcode_len_set_ord_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_barcode_scanner_type_set_ord_arg              [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_barcode_scanner_close_ord_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_barcode_scanner_open_ord_arg                  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"注射器"
//命令类型->"采样组件"
cArg cmd_sample_config_ord_arg                         [] = {{0,1,QString::fromLocal8Bit("水平电机号")},{0,1,QString::fromLocal8Bit("垂直电机号")}};
cArg cmd_sample_hswing_ord_arg                         [] = {{0,1,QString::fromLocal8Bit("次数")},{0,1,QString::fromLocal8Bit("向前幅度")},{0,1,QString::fromLocal8Bit("向后幅度")},{0,1,QString::fromLocal8Bit("档速")},{0,2,QString::fromLocal8Bit("最大时间")},{2,1,QString::fromLocal8Bit("锁定"),{{0x00,QString::fromLocal8Bit("锁定")},{0x01,QString::fromLocal8Bit("不锁")}}}};
cArg cmd_h_init_sample_ord_arg                         [] = {{0,1,QString::fromLocal8Bit("档速")},{0,2,QString::fromLocal8Bit("最大时间")},{2,1,QString::fromLocal8Bit("锁定"),{{0x00,QString::fromLocal8Bit("锁定")},{0x01,QString::fromLocal8Bit("不锁")}}}};
cArg cmd_v_init_sample_ord_arg                         [] = {{0,1,QString::fromLocal8Bit("档速")},{0,2,QString::fromLocal8Bit("最大时间")},{2,1,QString::fromLocal8Bit("锁定"),{{0x00,QString::fromLocal8Bit("锁定")},{0x01,QString::fromLocal8Bit("不锁")}}}};
cArg cmd_sample_h_move_pos_ord_arg                     [] = {{0,1,QString::fromLocal8Bit("位置")},{0,1,QString::fromLocal8Bit("档速")},{0,2,QString::fromLocal8Bit("最大时间")},{2,1,QString::fromLocal8Bit("锁定"),{{0x00,QString::fromLocal8Bit("锁定")},{0x01,QString::fromLocal8Bit("不锁")}}}};
cArg cmd_sample_v_move_pos_ord_arg                     [] = {{0,1,QString::fromLocal8Bit("位置")},{0,1,QString::fromLocal8Bit("档速")},{0,2,QString::fromLocal8Bit("最大时间")},{2,1,QString::fromLocal8Bit("锁定"),{{0x00,QString::fromLocal8Bit("锁定")},{0x01,QString::fromLocal8Bit("不锁")}}}};
//命令类型->"温度控制"
cArg cmd_temperature_range_judge_ord_arg               [] = {{2,1,QString::fromLocal8Bit("判断"),{{0x00,QString::fromLocal8Bit("关闭")},{0x01,QString::fromLocal8Bit("打开")}}}};
cArg cmd_temperature_control_ord_arg                   [] = {{2,1,QString::fromLocal8Bit("控制"),{{0x00,QString::fromLocal8Bit("关闭")},{0x01,QString::fromLocal8Bit("打开")}}}};
cArg cmd_quire_cur_temperature_ord_arg                 [] = {{}};
cArg cmd_quire_cur_temperature_compensation_ord_arg    [] = {{}};
cArg cmd_set_target_temperature_ord_arg                [] = {{0,2,QString::fromLocal8Bit("目标温度")}};
cArg cmd_temperature_compensation_config_ord_arg       [] = {{0,2,QString::fromLocal8Bit("温度补偿")}};
cArg cmd_config_work_run_temperature_ord_arg           [] = {{0,2,QString::fromLocal8Bit("工作温度下限")},{0,2,QString::fromLocal8Bit("工作温度上限")},{0,2,QString::fromLocal8Bit("运行温度下限")},{0,2,QString::fromLocal8Bit("运行温度上限")}};
cArg cmd_set_temperature_ch_pid_param_ord_arg          [] = {{0,4,QString::fromLocal8Bit("Kp")},{0,4,QString::fromLocal8Bit("Ki")},{0,4,QString::fromLocal8Bit("Kd")}};
cArg cmd_quire_temperature_ch_pid_param_ord_arg        [] = {{}};
//命令类型->"压力控制"
cArg cmd_pressure_config_ord_arg                       [] = {{2,1,QString::fromLocal8Bit("状态"),{{0x00,QString::fromLocal8Bit("压力控制")},{0x00,QString::fromLocal8Bit("不控制")}}},{0,1,QString::fromLocal8Bit("AD通道")},{0,1,QString::fromLocal8Bit("泵号")},{0,1,QString::fromLocal8Bit("阀号")}};      // 压力配置
cArg cmd_query_pressure_ad_value_ord_arg               [] = {{}};                                                                                                                                              // 查询指定压力通道压力AD值         
cArg cmd_check_pressure_ord_arg                        [] = {{0,2,QString::fromLocal8Bit("高压")},{0,2,QString::fromLocal8Bit("低压")}};      																   // 查询指定通道压力是否在指定压力范围
cArg cmd_query_pressure_value_ord_arg                  [] = {{}};                                                                                                                                              // 查询指定压力通道压力值           
cArg cmd_build_pressure_ord_arg                        [] = {{-1,2,QString::fromLocal8Bit("重启压力")},{-1,2,QString::fromLocal8Bit("目标压力")},{0,2,QString::fromLocal8Bit("建压时间")}};                        // 建压
cArg cmd_calibration_pressure_ord_arg                  [] = {{}};                                                                                                                                              // 压力标定
cArg cmd_query_pressure_kb_ord_arg                     [] = {{}};                                                                                                                                              // 查询指定通道压力的K值和B值
cArg cmd_set_pressure_kb_ord_arg                       [] = {{-1,4,QString::fromLocal8Bit("K")},{-1,4,QString::fromLocal8Bit("B")}};                                                                           // 设置指定通道压力的K值和B值
cArg cmd_auto_calc_pressure_kb_ord_arg                 [] = {{}};                                                                                                                                              // 自动计算指定通道压力的K值和B值
cArg cmd_set_pressure_default_kb_ord_arg               [] = {{}};                                                                                                                                              // 设置默认压力通道的K值和B值
cArg cmd_monitor_pressure_ord_arg                      [] = {{3,1,QString::fromLocal8Bit("类型"),{{0,QString::fromLocal8Bit("正压")},{1,QString::fromLocal8Bit("负压")},{2,QString::fromLocal8Bit("鞘流")}}},{-1,2,QString::fromLocal8Bit("最小压")},{-1,2,QString::fromLocal8Bit("最大压")},{0,2,QString::fromLocal8Bit("监控时间")}};         // 启动指定通道压力监测
cArg cmd_quire_pressure_ch_value_ord_arg               [] = {{}};                                                                                                                                              // 查询指定通道压力值
cArg cmd_quire_pressure_ch_kb_value_ord_arg            [] = {{}};                                                                                                                                              // 查询指定通道的KB值
cArg cmd_set_pressure_ch_kb_value_ord_arg              [] = {{-1,4,QString::fromLocal8Bit("K")},{-1,4,QString::fromLocal8Bit("B")}};                                                                           // 设定指定通道的KB值
cArg cmd_set_pressure_monitor_state_ord_arg            [] = {{3,1,QString::fromLocal8Bit("类型"),{{0,QString::fromLocal8Bit("正压")},{1,QString::fromLocal8Bit("负压")},{2,QString::fromLocal8Bit("鞘流")}}},{-1,2,QString::fromLocal8Bit("最小压")},{-1,2,QString::fromLocal8Bit("最大压")},{0,2,QString::fromLocal8Bit("监控时间")}};         // 启动指定通道压力监测            
cArg cmd_check_pressure_state_ord_arg                  [] = {{-1,2,QString::fromLocal8Bit("高压")},{-1,2,QString::fromLocal8Bit("低压")}};                                                                      // 查询指定通道压力是否在指定压力范围
cArg cmd_set_auto_build_pressure_ord_arg               [] = {3,1,QString::fromLocal8Bit("类型"),{{0,QString::fromLocal8Bit("关机")},{1,QString::fromLocal8Bit("待机")},{2,QString::fromLocal8Bit("开机")}}};      // 自动建压
//命令类型->"试剂检测板"
cArg cmd_reagent_config_ord_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_reagent_ch_state_ord_arg                [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_detec_reagent_ch_ord_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_none_reagent_time_ord_arg               [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_set_none_reagent_threshold_ord_arg            [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"装载组件"
cArg cmd_config_loader_ord_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_loader_init_ord_arg                           [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_load_rack_ord_arg                            []  = {0,0,QString::fromLocal8Bit(""),{}};
//命令类型->"进给组件"
cArg cmd_config_feeder_ord_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_feeder_init_ord_arg                           [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_feed_rack_ord_arg                            []  = {0,0,QString::fromLocal8Bit(""),{}};
//命令类型->"卸载组件"
cArg cmd_config_unloader_ord_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_unloader_init_ord_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_unload_rack_ord_arg                           [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"混匀组件"
cArg cmd_config_mixer_ord_arg                          [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_mixer_init_ord_arg                            [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_tube_mix_ord_arg                            []   = {0,0,QString::fromLocal8Bit(""),{}};
cArg cmd_mixer_reset_ord_arg                           [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_mixer_state_ord_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_grab_mechanism_init_ord_arg                   [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_grab_tube_ord_arg                            []  = {0,0,QString::fromLocal8Bit(""),{}};
cArg cmd_raise_mechanism_init_ord_arg                  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_raise_tube_ord_arg                            [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_swing_mechanism_init_ord_arg                  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_swing_tube_ord_arg                            [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_grab_tube_from_relay_ord_arg                  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_raise_tube_to_relay_ord_arg                   [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_relay_mechanism_init_ord_arg                  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_relay_tube_ord_arg                            [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"其他"
cArg cmd_quire_motor_opt_state_ord_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_reagent_opt_state_ord_arg               [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_switch_state_ord_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_set_sw_check_state_ord_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upload_open_err_ord_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_crp_laser_ctl_cmd_ord_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_motor_opt_group_state_ord_arg           [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_motor_opt_ch_state_ord_arg              [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_reagent_group_state_ord_arg             [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_reagent_chanel_state_ord_arg            [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_switch_group_state_ord_arg              [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_switch_ch_state_ord_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_set_switch_all_monitor_state_ord_arg          [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_set_switch_ch_monitor_state_ord_arg           [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"电压监控"
cArg cmd_quire_power_value_ord_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_set_power_monitor_state_ord_arg               [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_clear_power_monitor_state_ord_arg             [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"灌注"
cArg cmd_start_perfusion_ord_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"排空"
cArg cmd_start_evacuation_ord_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"三维采样组件"
cArg cmd_sample_3d_lrswing_ord_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_3d_hswing_ord_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_3d_hmotor_init_ord_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_3d_vmotor_init_ord_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_3d_lrmotor_init_ord_arg                [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_3d_hmotor_pos_ord_arg                  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_3d_vmotor_pos_ord_arg                  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_3d_lrmotor_pos_ord_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"样本试剂运动组件"
cArg cmd_samples_reagents_sample_hmotor_init_ord_arg   [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_sample_vmotor_init_ord_arg   [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_sample_lrmotor_init_ord_arg  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_reagent_hmotor_init_ord_arg  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_reagent_vmotor_init_ord_arg  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_reagent_lrmotor_init_ord_arg [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_hatchery_motor_init_ord_arg  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_sample_hmotor_pos_ord_arg    [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_sample_vmotor_pos_ord_arg    [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_sample_lrmotor_pos_ord_arg   [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_reagent_hmotor_pos_ord_arg   [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_reagent_vmotor_pos_ord_arg   [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_reagent_lrmotor_pos_ord_arg  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_hatchery_motor_pos_ord_arg   [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_hatchery_mix_ord_arg         [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"试剂池混匀组件"
cArg cmd_reagent_room_motor_init_ord_arg               [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_reagent_room_motor_pos_ord_arg                [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_reagent_room_mix_ord_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"码盘控制组件"
cArg cmd_code_wheel_init_ord_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_code_wheel_pos_ord_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_code_wheel_stop_ord_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"编码器电机控制"
cArg cmd_coder_motor_cfg_attr_ord_arg                  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_coder_motor_cfg_speed_ord_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_coder_motor_cfg_init_ord_arg                  [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_coder_motor_init_ord_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_coder_motor_pos_ord_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_coder_motor_steps_ord_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"试剂采样组件"
cArg cmd_sample_coder_motor_hinit_ord_arg              [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_coder_motor_vinit_ord_arg              [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_coder_motor_hpos_ord_arg               [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_coder_motor_vpos_ord_arg               [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_coder_motor_vsuck_ord_arg              [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"吸样混匀组件"
cArg cmd_suck_mix_init_ord_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_suck_mix_suck_ord_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_suck_mix_suck_end_ord_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_suck_mix_mix_ord_arg                          [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_suck_mix_mix_end_ord_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"抛杯组件"
cArg cmd_throw_cup_init_ord_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_throw_cup_throw_ord_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"加杯组件"
cArg cmd_add_cup_init_ord_arg                          [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_add_cup_add_ord_arg                           [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"调试"
cArg cmd_upload_debug_msg_ord_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_error_debug_ord_arg                           [] = {{0,0,QString::fromLocal8Bit(""),{{0x00,QString::fromLocal8Bit("")},{0x00,QString::fromLocal8Bit("")}}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_5101_init_ord_arg                            []  = {0,0,QString::fromLocal8Bit(""),{}};


#endif // ARRAY_ARG_CODE_H

