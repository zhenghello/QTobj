
/******************************************************************************/
#ifndef __USB_USER_COMMONRES_H
#define __USB_USER_COMMONRES_H
/******************************************************************************/
//#include "deftype.h"
#include "commonres.h"
//#include "usb.h"
/******************************************************************************/

#define U_FRAME_PARA_LEN 63   // usb帧数据的参数长度
#define U_FRAME_SEG_MAX   PROTOCOL_FRAME_MAX_SIZE/U_FRAME_PARA_LEN // usb帧的最多个数

// USB自定义协议帧格式下标
#define U_START_INDEX                       (0u)  //起始
#define U_CONTROL_INDEX                     (1u)  //控制
#define U_LEN_H_INDEX                       (2u)  //数据长度
#define U_LEN_L_INDEX                       (3u)  //数据长度
#define U_COMMAND_TYPE_INDEX                (4u)  //命令类型
#define U_COMMAND_NUM_INDEX                 (5u)  //命令对象
#define U_COMMAND_CONTENT_INDEX             (6u)  //命令内容
#define U_COMMAND_PARAM_INDEX               (7u)  //命令参数
// 定义主动上传帧的最大值
#define UPLOAD_FRAME_MAX_SIZE               (250) //

//can分段标志定义
#define U_FRAME_NONE_SEG          0x00  //不分段
#define U_FRAME_FIRST_SEG         0x01  //第一个分段
#define U_FRAME_MIDDLE_SEG        0x10  //中间分段
#define U_FRAME_END_SEG           0x11  //最后分段

#define    USB_FRAME_SIZE     (char)0x40  // usb的帧长度
/******************************************************************************/
#endif
/******************************************************************************/
