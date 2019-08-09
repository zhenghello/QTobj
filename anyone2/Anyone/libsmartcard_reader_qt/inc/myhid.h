#ifndef __MYHID_H
#define __MYHID_H

#include "Windows.h"
#include <dbt.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 定义读和写的包长度，这个由USB设备决定
#define    READ_PACK_LEN        64
#define    WRITE_PACK_LEN       64

// 接收缓存区的最大长度
#define    INPUT_PACK_MAX       512  // 缓存包最大个数
#define    INPUT_MAX_LEN        (INPUT_PACK_MAX*(READ_PACK_LEN+1)) // 缓存区的最大长度

// 定义读和写的最长等待时间，在该时间内没有收到消息或者回应就会出错,单位：ms
#define    READ_WAITING_TIME    100
#define    WRITE_WAITING_TIME   10

bool open_hid(HANDLE *hDevice, USHORT vid, USHORT pid);                // 打开设备
bool read_hid(HANDLE hDevice,char *buff,ULONG max_len,ULONG *real_len, int timeout);  // 读设备
bool write_hid(HANDLE hDevice,UINT8 buff[WRITE_PACK_LEN+1]);                 // 写设备
//CloseHandle(hDevice);//关设备

#endif