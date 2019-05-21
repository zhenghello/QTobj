
/******************************************************************************/
#ifndef __USB_USER_COMMONRES_H
#define __USB_USER_COMMONRES_H
/******************************************************************************/
//#include "deftype.h"
#include "commonres.h"
//#include "usb.h"
/******************************************************************************/

#define U_FRAME_PARA_LEN 63   // usb֡���ݵĲ�������
#define U_FRAME_SEG_MAX   PROTOCOL_FRAME_MAX_SIZE/U_FRAME_PARA_LEN // usb֡��������

// USB�Զ���Э��֡��ʽ�±�
#define U_START_INDEX                       (0u)  //��ʼ
#define U_CONTROL_INDEX                     (1u)  //����
#define U_LEN_H_INDEX                       (2u)  //���ݳ���
#define U_LEN_L_INDEX                       (3u)  //���ݳ���
#define U_COMMAND_TYPE_INDEX                (4u)  //��������
#define U_COMMAND_NUM_INDEX                 (5u)  //�������
#define U_COMMAND_CONTENT_INDEX             (6u)  //��������
#define U_COMMAND_PARAM_INDEX               (7u)  //�������
// ���������ϴ�֡�����ֵ
#define UPLOAD_FRAME_MAX_SIZE               (250) //

//can�ֶα�־����
#define U_FRAME_NONE_SEG          0x00  //���ֶ�
#define U_FRAME_FIRST_SEG         0x01  //��һ���ֶ�
#define U_FRAME_MIDDLE_SEG        0x10  //�м�ֶ�
#define U_FRAME_END_SEG           0x11  //���ֶ�

#define    USB_FRAME_SIZE     (char)0x40  // usb��֡����
/******************************************************************************/
#endif
/******************************************************************************/
