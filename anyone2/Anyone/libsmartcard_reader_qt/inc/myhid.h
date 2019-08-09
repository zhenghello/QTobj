#ifndef __MYHID_H
#define __MYHID_H

#include "Windows.h"
#include <dbt.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// �������д�İ����ȣ������USB�豸����
#define    READ_PACK_LEN        64
#define    WRITE_PACK_LEN       64

// ���ջ���������󳤶�
#define    INPUT_PACK_MAX       512  // �����������
#define    INPUT_MAX_LEN        (INPUT_PACK_MAX*(READ_PACK_LEN+1)) // ����������󳤶�

// �������д����ȴ�ʱ�䣬�ڸ�ʱ����û���յ���Ϣ���߻�Ӧ�ͻ����,��λ��ms
#define    READ_WAITING_TIME    100
#define    WRITE_WAITING_TIME   10

bool open_hid(HANDLE *hDevice, USHORT vid, USHORT pid);                // ���豸
bool read_hid(HANDLE hDevice,char *buff,ULONG max_len,ULONG *real_len, int timeout);  // ���豸
bool write_hid(HANDLE hDevice,UINT8 buff[WRITE_PACK_LEN+1]);                 // д�豸
//CloseHandle(hDevice);//���豸

#endif