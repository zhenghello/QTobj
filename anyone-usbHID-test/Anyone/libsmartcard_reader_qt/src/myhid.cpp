#include "myhid.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern "C"
{
	// This file is in the Windows DDK available from Microsoft.
#include "hidsdi.h"
#include <setupapi.h>
}

// **************************************************************************************************************************************

/* 功能：打开USB设备，并且返回HANDLE
 * 返回参数：成功\失败
 * 备注：这里会同时设置buff的缓存区为512
*/
bool open_hid(HANDLE *hDevice, USHORT vid, USHORT pid)
{
    static GUID HidGuid;						/* HID全局唯一ID：Windows为我们提供这个值 */
    HDEVINFO HidDevInfo;						/* 包含所有附加的HID设备信息的结构句柄 */
    SP_DEVICE_INTERFACE_DATA devInfoData;		/* HID设备的信息结构 */
    BOOLEAN Result;								/* 获取下一个设备信息结构的结果 */
    DWORD Index;								/* HidDevInfo 数组的内部偏移值 */
    DWORD DataSize;								/* DeviceInterfaceDetail 结构体的大小 */
    BOOLEAN GotRequiredSize;					/* 获得的设备信息数据结构大小标志 */
    PSP_DEVICE_INTERFACE_DETAIL_DATA detailData;/* 设备信息数据 */
    DWORD RequiredSize;							/* 设备信息数据结构的大小 */
    HIDD_ATTRIBUTES HIDAttrib;					/* HID device 属性 */

    // 初始化变量，获得的设备信息个数 = 0;
    GotRequiredSize = FALSE;

    // 1)从操作系统中获取HID全局唯一ID
    HidD_GetHidGuid(&HidGuid);
    // 2) 获取所有HID设备的枚举信息
     HidDevInfo = SetupDiGetClassDevs(&HidGuid,NULL, NULL,DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
     // 3) 根据1)和2)检测所有设备，如果返回空，就停止函数。
     // 1)中拿ID,2)拿设备信息，但这只是信息索引，具体数据还要再调用函数读取
    Index = 0;							       //3.1. 初始偏移=0
    devInfoData.cbSize = sizeof(devInfoData);  //3.2. 设置要读取的设备信息数据的结构大小
    do{
        // 3.3.通过索引Index获取一个HID设备的信息
        Result = SetupDiEnumDeviceInterfaces(   HidDevInfo,
                                                0,
                                                &HidGuid,
                                                Index,
                                                &devInfoData);
        if(Result == FALSE)//这里代表后续没有数据了
        {
            //释放HID设备信息列表内存
             if(detailData != NULL)free(detailData);
             SetupDiDestroyDeviceInfoList(HidDevInfo);
             cout << "no find hid!"<<endl;
             return FALSE;
        }
        // 3.4 获取设备接口详细数据的结构体和大小，如果第一次调用会有错误，但是可以获取到结构体的大小
        if(GotRequiredSize == FALSE)
        {   // 3.4.1.第一次获取，得到设备个数
            SetupDiGetDeviceInterfaceDetail( HidDevInfo,
                                                    &devInfoData,
                                                    NULL,
                                                    0,
                                                    &DataSize,
                                                    NULL);
            GotRequiredSize = TRUE;
            // 3.4.2.根据设备个数分配内存
            detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(DataSize);
            // 3.4.2.设置设备接口描述的大小
            detailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
        }
        // 4.读取设备信息，读取的个数在DataSize中，信息返回在devInfoData中，然后就可以挑选特定的HID设备(VID,PID)了
                SetupDiGetDeviceInterfaceDetail(  HidDevInfo,
                                                    &devInfoData,
                                                    detailData,
                                                    DataSize,
                                                    &RequiredSize,
                                                    NULL);
        // 5.获取一个设备的HANDLE,确保事务可以阻塞传输
        *hDevice = CreateFile( detailData->DevicePath,
                                    GENERIC_READ | GENERIC_WRITE,
                                    //NULL,                           //以独占的方式打开
                                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                                    (LPSECURITY_ATTRIBUTES)NULL,
                                    OPEN_EXISTING,
                                    FILE_FLAG_OVERLAPPED,
                                    NULL);
         // 6. 获取HID设备的 VID & PID,判断是否是我们想要的
         if(*hDevice != INVALID_HANDLE_VALUE)
         {
             HIDAttrib.Size = sizeof(HIDAttrib);
             // 6.1.获取属性，放在HIDAttrib中
             HidD_GetAttributes(*hDevice, &HIDAttrib);
             // 6.2.拿到匹配的vid和pid
             if((HIDAttrib.VendorID == vid) && (HIDAttrib.ProductID == pid))
             {
                // 6.3.设置读取缓存区的最大长度,这里注意，最大只能512！
                HidD_SetNumInputBuffers(*hDevice,INPUT_PACK_MAX);
                //释放HID设备信息列表内存
                 if(detailData != NULL)free(detailData);
                 SetupDiDestroyDeviceInfoList(HidDevInfo);
                return TRUE;	// 找到 HID device
             }
             //关闭不是我们想要的设备
             CloseHandle(*hDevice);
         }
         Index++;	/* 增加数组索引以搜索下一个设备 */
    } while(Result == TRUE);

    //释放HID设备信息列表内存
     if(detailData != NULL)free(detailData);
     SetupDiDestroyDeviceInfoList(HidDevInfo);
     cout << "here"<<endl;

     return FALSE;
}

/* 功能：根据HID的HANDLE,读取USB上传的数据
 * 输入参数：HID的HANDLE，
 * 输入参数：缓存区
 * 输入参数：最大读取(以包的长度+1为单位)
 * 输出参数：实际读取
 * 返回：读取成功/失败
 */
bool read_hid(HANDLE hDevice,char *buff,ULONG max_len,ULONG *real_len, int timeout)
{
    BOOL                    bResult;
    OVERLAPPED              HidOverlapped;  // 阻塞事件
    HANDLE                  ReportEvent;    // 阻塞读取的延时事件HANDLE
    // 1.判断输入
    if((hDevice == NULL) || (buff == NULL) ||(max_len<(READ_PACK_LEN+1)) || (NULL == real_len))
	{
		return FALSE;
	}
    // 2.为捕获数据创建一个新的事件
    ReportEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
    // 3.填充HID重叠结构，以便Windows知道设备发送一个IN报告时引发的事件。
    HidOverlapped.hEvent = ReportEvent;
    HidOverlapped.Offset = 0;
    HidOverlapped.OffsetHigh = 0;
    // 4.从HID设备获得报告。注意，对Read文件的调用只会启动对缓存区的读取。
    // 如果输入缓冲区已满，则此例程将导致事件发生，并且数据将立即呈现。
    // 如果不是，当HID决定在IN端点上提供HID报告时，将发生该事件。
    bResult = ReadFile(	hDevice,							/* 已经被打开的HID的HANDLE */
                        buff,                               /* IN事务数据待填充 */
                        max_len,                            // 最大读取范围
                        (LPDWORD)real_len,                           /* 实际接收的数据 */
                        (LPOVERLAPPED) &HidOverlapped );	/* 等待结构体事件HANDLE */
    // 5.这里在等待IN事件，如果不设置时间（ms）的话，会立即返回错误并且不接收HID数据
    //   如果返回true,那么那么可以从指定的缓存区读数据了。
    /*bResult = WaitForSingleObject(ReportEvent, READ_WAITING_TIME);*/
	bResult = WaitForSingleObject(ReportEvent, timeout);
	if((bResult == WAIT_TIMEOUT) || (bResult == WAIT_ABANDONED))
	{
		CancelIo(&hDevice);
	}
    // 5.1.如果传输超时，就要手动复位它
    ResetEvent(ReportEvent);
	//调试时发现real_len这一个地址会被置为NULL，原因不知道，这儿增加处理异常情况
	/*if((NULL == real_len) || (hDevice == NULL))
	{
		return false;
	}*/
    // 5.2.这里代表收到正确数据，每个report的第一个参数是HID的接口ID号，可以忽略掉
    if(bResult == WAIT_OBJECT_0)
    {   //这里代表读取到有效数据，如果读取的长度=0；代表实际是读到一包数据。
        if(*real_len == 0){*real_len = (READ_PACK_LEN+1);}
        return TRUE;
    }
    else
    {
		int error = GetLastError();
		cout << "read fail!error_code="<<error<<endl;
		if((error == 997) && (*real_len == 0))
		{
			//没有读到内容
			return TRUE;
		}
        return FALSE;
    }
}

/**********************************************************
* 功能: 写数据到HID设备
* 输入参数：hDevice: 打开的HID的HANDLE
* 输入参数：buff :   待写入的参数，buff的数据长度固定为WRITE_PACK_LEN+1，其中第一个为REPORT ID
* 输出参数：写入成功/失败
**********************************************************/
bool write_hid(HANDLE hDevice,UINT8* pbuff)
{
	unsigned long	numBytesReturned;
	BOOL			bResult;
	OVERLAPPED		HidOverlapped;
	HANDLE			ReportEvent;
	UINT8 buff[WRITE_PACK_LEN + 1] = {0};

	// 1.判断输入
	if((hDevice == NULL) || (buff == NULL))return FALSE;
	// 2.为捕获数据创建一个新的事件
	ReportEvent = CreateEventA(NULL, TRUE, TRUE, "");
	// 3.填充HID重叠结构，以便Windows知道设备发送一个报告时引发的事件。
	HidOverlapped.hEvent = ReportEvent;
	HidOverlapped.Offset = 0;
	HidOverlapped.OffsetHigh = 0;

	/* 使用 WriteFile 向HID设备发送输出报告。首先我们应该填满缓冲区*/
	buff[0]=0;//这个是report id,没什么必要就别改动
	memcpy(&buff[1], pbuff, 64);
	bResult = WriteFile( hDevice,
		buff,                   // 要传送的数据地址
		WRITE_PACK_LEN+1,                // 传送个数
		&numBytesReturned,               // 返回字节个数
		(LPOVERLAPPED) &HidOverlapped);  // 阻塞事件
	// 阻塞等待写事件完成
	bResult = WaitForSingleObject(ReportEvent, WRITE_WAITING_TIME);
	ResetEvent(ReportEvent);

	// 5.2.这里代表正常发送数据
	if(bResult == WAIT_OBJECT_0)
	{
		return TRUE;
	}
	else
	{
		cout << "write fail!error_code="<<GetLastError()<<endl;
		return FALSE;
	}
}

// 在hid.lib中 HidD_GetNumInputBuffers 用于读取缓存区长度
// HidD_SetNumInputBuffers 用于设置缓存区的大小，最大只能设置 512
// WaitForSingleObject 用于读取的阻塞等待，第二个参数是等待时间，单位：ms
// 每次重新打开HID时，原缓存区中的数据就丢失了。
// 有时候读取成功了，但是读取到的个数=0；实际上这个时候读取到的数据是一个数据包65个
// 如果在某个情况下读取失败了，一般是读取太快，缓存区没数据，这时就要立刻重新打开HID,获得一个新的HANDLE,否则会导致接下来的数据也一直读取失败，
// 不管是主机还是设备，每次写操作都要以一个包为单位传送数据，这里在设备中设置IN/OUT包长度是64，则所有数据都必须以64的单位发送和接收