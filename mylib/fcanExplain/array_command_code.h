/*
 * 放着命令类型的编码
 */
#ifndef ARRAY_COMMAND_CODE
#define ARRAY_COMMAND_CODE

#include "command.h"
//小分类->命令类型中，每个类型具体命令的个数
#define CONTENT_CODE_NUM_SLAVE               sizeof(content_code_addr_slave				)   //"从站"
#define CONTENT_CODE_NUM_SMARTCARD           sizeof(content_code_addr_smartcard         )   //"智能卡"
#define CONTENT_CODE_NUM_TIMESEQ             sizeof(content_code_addr_timeseq           )   //"时序"
#define CONTENT_CODE_NUM_AUTOSAMPLE          sizeof(content_code_addr_autosample        )   //"自动进样"
#define CONTENT_CODE_NUM_VALVE               sizeof(content_code_addr_valve             )   //"阀"
#define CONTENT_CODE_NUM_PUMP                sizeof(content_code_addr_pump              )   //"泵"
#define CONTENT_CODE_NUM_MOTOR               sizeof(content_code_addr_motor             )   //"电机"
#define CONTENT_CODE_NUM_BARCODESCANER       sizeof(content_code_addr_barcodescaner     )   //"条码扫描器"
#define CONTENT_CODE_NUM_SYRING              sizeof(content_code_addr_syring            )   //"注射器"
#define CONTENT_CODE_NUM_SAMPLE              sizeof(content_code_addr_sample            )   //"采样组件"
#define CONTENT_CODE_NUM_TEMPERATURE         sizeof(content_code_addr_temperature       )   //"温度控制"
#define CONTENT_CODE_NUM_PRESSURE            sizeof(content_code_addr_pressure          )   //"压力控制"
#define CONTENT_CODE_NUM_REAGENT             sizeof(content_code_addr_reagent           )   //"试剂检测板"
#define CONTENT_CODE_NUM_LOADER              sizeof(content_code_addr_loader            )   //"装载组件"
#define CONTENT_CODE_NUM_FEEDER              sizeof(content_code_addr_feeder            )   //"进给组件"
#define CONTENT_CODE_NUM_UNLOADER            sizeof(content_code_addr_unloader          )   //"卸载组件"
#define CONTENT_CODE_NUM_MIXER               sizeof(content_code_addr_mixer             )   //"混匀组件"
#define CONTENT_CODE_NUM_OTHER               sizeof(content_code_addr_other             )   //"其他"
#define CONTENT_CODE_NUM_POWER               sizeof(content_code_addr_power             )   //"电压监控"
#define CONTENT_CODE_NUM_PERFUSION           sizeof(content_code_addr_perfusion         )   //"灌注"
#define CONTENT_CODE_NUM_EVACUATION          sizeof(content_code_addr_evacuation        )   //"排空"
#define CONTENT_CODE_NUM_SAMPLE_3D           sizeof(content_code_addr_sample_3d         )   //"三维采样组件"
#define CONTENT_CODE_NUM_SAMPLES_REAGENTS    sizeof(content_code_addr_samples_reagents  )   //"样本试剂运动组件"
#define CONTENT_CODE_NUM_REAGENT_ROOM        sizeof(content_code_addr_reagent_room      )   //"试剂池混匀组件"
#define CONTENT_CODE_NUM_CODE_WHEEL          sizeof(content_code_addr_code_wheel        )   //"码盘控制组件"
#define CONTENT_CODE_NUM_CODER_MOTOR         sizeof(content_code_addr_coder_motor       )   //"编码器电机控制"
#define CONTENT_CODE_NUM_SAMPLE_CODER_MOTOR  sizeof(content_code_addr_sample_coder_motor)   //"编码器电机采样组件"
#define CONTENT_CODE_NUM_SUCK_MIX            sizeof(content_code_addr_suck_mix          )   //"吸样混匀组件"
#define CONTENT_CODE_NUM_THROW_CUP           sizeof(content_code_addr_throw_cup         )   //"抛杯组件"
#define CONTENT_CODE_NUM_ADD_CUP             sizeof(content_code_addr_add_cup           )   //"加杯组件"
#define CONTENT_CODE_NUM_DEBUG               sizeof(content_code_addr_debug             )   //"调试"
//命令码的类型
command_code_str command_code_type[COMMAND_CODE_NUM] =
{
  {  CMD_TYPE_SLAVE              ,   QString::fromLocal8Bit("从站 ")                ,CONTENT_CODE_NUM_SLAVE              , content_code_addr_slave               },
  {  CMD_TYPE_SMARTCARD          ,   QString::fromLocal8Bit("智能卡 ")              ,CONTENT_CODE_NUM_SMARTCARD          , content_code_addr_smartcard           },
  {  CMD_TYPE_TIMESEQ            ,   QString::fromLocal8Bit("时序 ")                ,CONTENT_CODE_NUM_TIMESEQ            , content_code_addr_timeseq             },
  {  CMD_TYPE_AUTOSAMPLE         ,   QString::fromLocal8Bit("自动进样 ")            ,CONTENT_CODE_NUM_AUTOSAMPLE         , content_code_addr_autosample          },
  {  CMD_TYPE_VALVE              ,   QString::fromLocal8Bit("阀 ")                  ,CONTENT_CODE_NUM_VALVE              , content_code_addr_valve               },
  {  CMD_TYPE_PUMP               ,   QString::fromLocal8Bit("泵 ")                  ,CONTENT_CODE_NUM_PUMP               , content_code_addr_pump                },
  {  CMD_TYPE_MOTOR              ,   QString::fromLocal8Bit("电机 ")                ,CONTENT_CODE_NUM_MOTOR              , content_code_addr_motor               },
  {  CMD_TYPE_BARCODESCANER      ,   QString::fromLocal8Bit("条码扫描器 ")          ,CONTENT_CODE_NUM_BARCODESCANER      , content_code_addr_barcodescaner       },
  {  CMD_TYPE_SYRING             ,   QString::fromLocal8Bit("注射器 ")              ,CONTENT_CODE_NUM_SYRING             , content_code_addr_syring              },
  {  CMD_TYPE_SAMPLE             ,   QString::fromLocal8Bit("采样组件 ")            ,CONTENT_CODE_NUM_SAMPLE             , content_code_addr_sample              },
  {  CMD_TYPE_TEMPERATURE        ,   QString::fromLocal8Bit("温度控制 ")            ,CONTENT_CODE_NUM_TEMPERATURE        , content_code_addr_temperature         },
  {  CMD_TYPE_PRESSURE           ,   QString::fromLocal8Bit("压力控制 ")            ,CONTENT_CODE_NUM_PRESSURE           , content_code_addr_pressure            },
  {  CMD_TYPE_REAGENT            ,   QString::fromLocal8Bit("试剂检测板 ")          ,CONTENT_CODE_NUM_REAGENT            , content_code_addr_reagent             },
  {  CMD_TYPE_LOADER             ,   QString::fromLocal8Bit("装载组件 ")            ,CONTENT_CODE_NUM_LOADER             , content_code_addr_loader              },
  {  CMD_TYPE_FEEDER             ,   QString::fromLocal8Bit("进给组件 ")            ,CONTENT_CODE_NUM_FEEDER             , content_code_addr_feeder              },
  {  CMD_TYPE_UNLOADER           ,   QString::fromLocal8Bit("卸载组件 ")            ,CONTENT_CODE_NUM_UNLOADER           , content_code_addr_unloader            },
  {  CMD_TYPE_MIXER              ,   QString::fromLocal8Bit("混匀组件 ")            ,CONTENT_CODE_NUM_MIXER              , content_code_addr_mixer               },
  {  CMD_TYPE_OTHER              ,   QString::fromLocal8Bit("其他 ")                ,CONTENT_CODE_NUM_OTHER              , content_code_addr_other               },
  {  CMD_TYPE_POWER              ,   QString::fromLocal8Bit("电压监控 ")            ,CONTENT_CODE_NUM_POWER              , content_code_addr_power               },
  {  CMD_TYPE_PERFUSION          ,   QString::fromLocal8Bit("灌注 ")                ,CONTENT_CODE_NUM_PERFUSION          , content_code_addr_perfusion           },
  {  CMD_TYPE_EVACUATION         ,   QString::fromLocal8Bit("排空 ")                ,CONTENT_CODE_NUM_EVACUATION         , content_code_addr_evacuation          },
  {  CMD_TYPE_SAMPLE_3D          ,   QString::fromLocal8Bit("三维采样组件 ")        ,CONTENT_CODE_NUM_SAMPLE_3D          , content_code_addr_sample_3d           },
  {  CMD_TYPE_SAMPLES_REAGENTS   ,   QString::fromLocal8Bit("样本试剂运动组件 ")    ,CONTENT_CODE_NUM_SAMPLES_REAGENTS   , content_code_addr_samples_reagents    },
  {  CMD_TYPE_REAGENT_ROOM       ,   QString::fromLocal8Bit("试剂池混匀组件 ")      ,CONTENT_CODE_NUM_REAGENT_ROOM       , content_code_addr_reagent_room        },
  {  CMD_TYPE_CODE_WHEEL         ,   QString::fromLocal8Bit("码盘控制组件 ")        ,CONTENT_CODE_NUM_CODE_WHEEL         , content_code_addr_code_wheel          },
  {  CMD_TYPE_CODER_MOTOR        ,   QString::fromLocal8Bit("编码器电机控制 ")      ,CONTENT_CODE_NUM_CODER_MOTOR        , content_code_addr_coder_motor         },
  {  CMD_TYPE_SAMPLE_CODER_MOTOR ,   QString::fromLocal8Bit("编码器电机采样组件 ")  ,CONTENT_CODE_NUM_SAMPLE_CODER_MOTOR , content_code_addr_sample_coder_motor  },
  {  CMD_TYPE_SUCK_MIX           ,   QString::fromLocal8Bit("吸样混匀组件 ")        ,CONTENT_CODE_NUM_SUCK_MIX           , content_code_addr_suck_mix            },
  {  CMD_TYPE_THROW_CUP          ,   QString::fromLocal8Bit("抛杯组件 ")            ,CONTENT_CODE_NUM_THROW_CUP          , content_code_addr_throw_cup           },
  {  CMD_TYPE_ADD_CUP            ,   QString::fromLocal8Bit("加杯组件 ")            ,CONTENT_CODE_NUM_ADD_CUP            , content_code_addr_add_cup             },
  {  CMD_TYPE_DEBUG              ,   QString::fromLocal8Bit("调试 ")                ,CONTENT_CODE_NUM_DEBUG              , content_code_addr_debug               },
  {  CMD_CMD_CONTENT_INVALID     ,   QString::fromLocal8Bit("无定义 ")              ,0                                   , NULL                                  }
};

#endif // ARRAY_COMMAND_CODE

