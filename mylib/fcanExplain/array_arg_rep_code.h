#ifndef ARRAY_ARG_REP_CODE_H
#define ARRAY_ARG_REP_CODE_H

//命令类型->"从站"
cArg cmd_query_slave_version_rep_arg                  [] = {{0,1,QString::fromLocal8Bit("版本")},{0,1,QString::fromLocal8Bit("")},{0,2,QString::fromLocal8Bit("")}};
cArg cmd_query_slave_all_version_rep_arg              [] = {{0,1,QString::fromLocal8Bit("PCB版本")},{0,1,QString::fromLocal8Bit("")},{0,2,QString::fromLocal8Bit("")},{0,1,QString::fromLocal8Bit("MCU版本")},{0,1,QString::fromLocal8Bit("")},{0,2,QString::fromLocal8Bit("")},{0,1,QString::fromLocal8Bit("FPGA版本")},{0,1,QString::fromLocal8Bit("")},{0,2,QString::fromLocal8Bit("")},};
cArg cmd_query_slave_time_rep_arg                     [] = {{0,1,QString::fromLocal8Bit("年"),{}},{0,1,QString::fromLocal8Bit("月"),{}},{0,1,QString::fromLocal8Bit("日"),{}},{0,1,QString::fromLocal8Bit("时"),{}},{0,1,QString::fromLocal8Bit("分"),{}},{0,1,QString::fromLocal8Bit("秒"),{}}};
cArg cmd_set_slave_time_rep_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_slave_parse_frame_format_err_rep_arg         [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_slave_comm_self_check_ok_rep_arg             [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upgrade_reset_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_enter_upgrade_mode_rep_arg                   [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_start_upgrade_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upgrade_data_rep_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upgrade_finish_rep_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_fpga_start_upgrade_rep_arg                   [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_fpga_upgrade_data_rep_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_fpga_upgrade_finish_rep_arg                  [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"智能卡"
//cArg cmd_scr_reset_pcd_rep_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_close_rf_rep_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_test_rep_arg                           [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_beep_rep_arg                           [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_request_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_anticoll_rep_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_select_rep_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_rats_rep_arg                           [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//cArg cmd_scr_command_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_close_smartcard_rep_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_open_smartcard_rep_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_write_smartcard_rep_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_read_smartcard_rep_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_create_smartcard_rep_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_setexauthkey_smartcard_rep_arg               [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_setfilelinekey_smartcard_rep_arg             [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_set_store_dir_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_card_ver_rep_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_smartcard_open_rep_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_smartcard_close_rep_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_smartcard_write_rep_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_get_smartcard_no_rep_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_set_oem_num_rep_arg                          [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"时序"
cArg cmd_timeseq_frame_head_rep_arg                   [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_timeseq_frame_tail_rep_arg                   [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_timeseq_finish_rep_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_start_timeseq_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_stop_timeseq_rep_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_timeseq_overlap_control_rep_arg              [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"自动进样"
cArg cmd_start_autosample_rep_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_start_autosample_rack_moving_rep_arg         [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_start_autosample_tube_mixing_rep_arg         [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_stop_autosample_rep_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_abort_autosample_rep_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_emergency_stop_autosample_rep_arg            [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_autosample_skip_cur_rack_rep_arg             [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_recover_autosample_rep_arg                   [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upload_rack_number_rep_arg                   [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upload_mixpos_info_rep_arg                   [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upload_samplepos_info_rep_arg                [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upload_autosample_finish_rep_arg             [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upload_autosample_mix_finish_rep_arg         [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_autosampler_state_rep_arg              [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_autosampler_init_rep_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_empty_autosampler_rep_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"阀"
cArg cmd_control_valve_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_query_all_valve_state_rep_arg                [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_valve_group_state_rep_arg              [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_valve_ch_state_rep_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"泵"
cArg cmd_control_pump_rep_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_query_all_pump_state_rep_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"电机"
cArg cmd_motor_config_attribute_rep_arg               [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_motor_config_speed_rep_arg                   [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_motor_config_init_rep_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_motor_config_pos_rep_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_query_motor_config_attribute_rep_arg         [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_query_motor_config_speed_rep_arg             [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_query_motor_config_init_rep_arg              [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_query_motor_config_pos_rep_arg               [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_motor_init_rep_arg                           [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_motor_move_pos_rep_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_motor_move_step_rep_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"条码扫描器"
cArg cmd_quire_barcode_scanner_state_rep_arg          [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_start_barcode_scanning_rep_arg               [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_barcode_type_check_status_set_rep_arg        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_barcode_len_set_rep_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_barcode_scanner_type_set_rep_arg             [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_barcode_scanner_close_rep_arg                [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_barcode_scanner_open_rep_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"注射器"
//命令类型->"采样组件"
cArg cmd_sample_config_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_hswing_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_h_init_sample_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_v_init_sample_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_h_move_pos_rep_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_v_move_pos_rep_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"温度控制"
cArg cmd_temperature_range_judge_rep_arg              [] = {{}};
cArg cmd_temperature_control_rep_arg                  [] = {{}};
cArg cmd_quire_cur_temperature_rep_arg                [] = {{0,2,QString::fromLocal8Bit("温度")}};
cArg cmd_quire_cur_temperature_compensation_rep_arg   [] = {{0,2,QString::fromLocal8Bit("温度补偿")}};
cArg cmd_set_target_temperature_rep_arg               [] = {{}};
cArg cmd_temperature_compensation_config_rep_arg      [] = {{}};
cArg cmd_config_work_run_temperature_rep_arg          [] = {{}};
cArg cmd_set_temperature_ch_pid_param_rep_arg         [] = {{}};
cArg cmd_quire_temperature_ch_pid_param_rep_arg       [] = {{0,4,QString::fromLocal8Bit("Kp")},{0,4,QString::fromLocal8Bit("Ki")},{0,4,QString::fromLocal8Bit("Kd")}};
//命令类型->"压力控制"
cArg cmd_pressure_config_rep_arg                      [] = {{}};																													                           // 压力配置                  
cArg cmd_query_pressure_ad_value_rep_arg              [] = {{0,2,QString::fromLocal8Bit("AD")}};                                                                                                               // 查询指定压力通道压力AD值         
cArg cmd_check_pressure_rep_arg                       [] = {{2,1,QString::fromLocal8Bit("状态"),{{0,QString::fromLocal8Bit("范围内")},{1,QString::fromLocal8Bit("范围外")}}}};                                 // 查询指定通道压力是否在指定压力范围     
cArg cmd_query_pressure_value_rep_arg                 [] = {{-1,2,QString::fromLocal8Bit("压力值")}};                                                                                                          // 查询指定压力通道压力值           
cArg cmd_build_pressure_rep_arg                       [] = {{}};                                                                                                                                               // 建压                    
cArg cmd_calibration_pressure_rep_arg                 [] = {{}};                                                                          																	   // 压力标定                  
cArg cmd_query_pressure_kb_rep_arg                    [] = {{-1,4,QString::fromLocal8Bit("K")},{-1,4,QString::fromLocal8Bit("B")}};                                                                            // 查询指定通道压力的K值和B值        
cArg cmd_set_pressure_kb_rep_arg                      [] = {{}};                                                                                                                                               // 设置指定通道压力的K值和B值        
cArg cmd_auto_calc_pressure_kb_rep_arg                [] = {{}};                                                                                                                                               // 自动计算指定通道压力的K值和B值      
cArg cmd_set_pressure_default_kb_rep_arg              [] = {{}};                                                                                                                                               // 设置默认压力通道的K值和B值        
cArg cmd_monitor_pressure_rep_arg                     [] = {{}};                                                                                                                                               // 压力监控                  
cArg cmd_quire_pressure_ch_value_rep_arg              [] = {{-1,2,QString::fromLocal8Bit("压力值")}};                                                                                                          // 查询指定通道压力值             
cArg cmd_quire_pressure_ch_kb_value_rep_arg           [] = {{-1,4,QString::fromLocal8Bit("K")},{-1,4,QString::fromLocal8Bit("B")}};                                                                            // 查询指定通道的KB值            
cArg cmd_set_pressure_ch_kb_value_rep_arg             [] = {{}};                                                                                                                                               // 设定指定通道的KB值            
cArg cmd_set_pressure_monitor_state_rep_arg           [] = {{}};                                                                                                                                               // 启动指定通道压力监测            
cArg cmd_check_pressure_state_rep_arg                 [] = {{2,1,QString::fromLocal8Bit("状态"),{{0,QString::fromLocal8Bit("范围内")},{1,QString::fromLocal8Bit("范围外")}}}};                                 // 启动通道压力监测
cArg cmd_set_auto_build_pressure_rep_arg              [] = {{}};                                                         																			           // 自动建压                  
//命令类型->"试剂检测板"
cArg cmd_reagent_config_rep_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_reagent_ch_state_rep_arg               [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_detec_reagent_ch_rep_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_none_reagent_time_rep_arg              [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_set_none_reagent_threshold_rep_arg           [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"装载组件"
cArg cmd_config_loader_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_loader_init_rep_arg                          [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_load_rack_rep_arg                            [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"进给组件"
cArg cmd_config_feeder_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_feeder_init_rep_arg                          [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_feed_rack_rep_arg                            [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"卸载组件"
cArg cmd_config_unloader_rep_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_unloader_init_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_unload_rack_rep_arg                          [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"混匀组件"
cArg cmd_config_mixer_rep_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_mixer_init_rep_arg                           [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_tube_mix_rep_arg                             [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_mixer_reset_rep_arg                          [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_mixer_state_rep_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_grab_mechanism_init_rep_arg                  [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_grab_tube_rep_arg                            [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_raise_mechanism_init_rep_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_raise_tube_rep_arg                           [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_swing_mechanism_init_rep_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_swing_tube_rep_arg                           [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_grab_tube_from_relay_rep_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_raise_tube_to_relay_rep_arg                  [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_relay_mechanism_init_rep_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_relay_tube_rep_arg                           [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"其他"
cArg cmd_quire_motor_opt_state_rep_arg                [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_reagent_opt_state_rep_arg              [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_switch_state_rep_arg                   [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_set_sw_check_state_rep_arg                   [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_upload_open_err_rep_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_crp_laser_ctl_cmd_rep_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_motor_opt_group_state_rep_arg          [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_motor_opt_ch_state_rep_arg             [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_reagent_group_state_rep_arg            [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_reagent_chanel_state_rep_arg           [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_switch_group_state_rep_arg             [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_quire_switch_ch_state_rep_arg                [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_set_switch_all_monitor_state_rep_arg         [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_set_switch_ch_monitor_state_rep_arg          [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"电压监控"
cArg cmd_quire_power_value_rep_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_set_power_monitor_state_rep_arg              [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_clear_power_monitor_state_rep_arg            [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"灌注"
cArg cmd_start_perfusion_rep_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"排空"
cArg cmd_start_evacuation_rep_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"三维采样组件"
cArg cmd_sample_3d_lrswing_rep_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_3d_hswing_rep_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_3d_hmotor_init_rep_arg                [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_3d_vmotor_init_rep_arg                [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_3d_lrmotor_init_rep_arg               [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_3d_hmotor_pos_rep_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_3d_vmotor_pos_rep_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_3d_lrmotor_pos_rep_arg                [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"样本试剂运动组件"
cArg cmd_samples_reagents_sample_hmotor_init_rep_arg  [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_sample_vmotor_init_rep_arg  [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_sample_lrmotor_init_rep_arg [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_reagent_hmotor_init_rep_arg [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_reagent_vmotor_init_rep_arg [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_reagent_lrmotor_init_rep_arg[] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_hatchery_motor_init_rep_arg [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_sample_hmotor_pos_rep_arg   [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_sample_vmotor_pos_rep_arg   [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_sample_lrmotor_pos_rep_arg  [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_reagent_hmotor_pos_rep_arg  [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_reagent_vmotor_pos_rep_arg  [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_reagent_lrmotor_pos_rep_arg [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_hatchery_motor_pos_rep_arg  [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_samples_reagents_hatchery_mix_rep_arg        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"试剂池混匀组件"
cArg cmd_reagent_room_motor_init_rep_arg              [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_reagent_room_motor_pos_rep_arg               [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_reagent_room_mix_rep_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"码盘控制组件"
cArg cmd_code_wheel_init_rep_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_code_wheel_pos_rep_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_code_wheel_stop_rep_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"编码器电机控制"
cArg cmd_coder_motor_cfg_attr_rep_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_coder_motor_cfg_speed_rep_arg                [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_coder_motor_cfg_init_rep_arg                 [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_coder_motor_init_rep_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_coder_motor_pos_rep_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_coder_motor_steps_rep_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"试剂采样组件"
cArg cmd_sample_coder_motor_hinit_rep_arg             [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_coder_motor_vinit_rep_arg             [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_coder_motor_hpos_rep_arg              [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_coder_motor_vpos_rep_arg              [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_sample_coder_motor_vsuck_rep_arg             [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"吸样混匀组件"
cArg cmd_suck_mix_init_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_suck_mix_suck_rep_arg                        [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_suck_mix_suck_end_rep_arg                    [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_suck_mix_mix_rep_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_suck_mix_mix_end_rep_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"抛杯组件"
cArg cmd_throw_cup_init_rep_arg                       [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_throw_cup_throw_rep_arg                      [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"加杯组件"
cArg cmd_add_cup_init_rep_arg                         [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_add_cup_add_rep_arg                          [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
//命令类型->"调试"
cArg cmd_upload_debug_msg_rep_arg                     [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_error_debug_rep_arg                          [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};
cArg cmd_5101_init_rep_arg                            [] = {{0,0,QString::fromLocal8Bit(""),{}},{0,0,QString::fromLocal8Bit(""),{}}};


#endif // ARRAY_ARG_CODE_H

