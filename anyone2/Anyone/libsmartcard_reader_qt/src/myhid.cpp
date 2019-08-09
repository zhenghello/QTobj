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

/* ���ܣ���USB�豸�����ҷ���HANDLE
 * ���ز������ɹ�\ʧ��
 * ��ע�������ͬʱ����buff�Ļ�����Ϊ512
*/
bool open_hid(HANDLE *hDevice, USHORT vid, USHORT pid)
{
    static GUID HidGuid;						/* HIDȫ��ΨһID��WindowsΪ�����ṩ���ֵ */
    HDEVINFO HidDevInfo;						/* �������и��ӵ�HID�豸��Ϣ�Ľṹ��� */
    SP_DEVICE_INTERFACE_DATA devInfoData;		/* HID�豸����Ϣ�ṹ */
    BOOLEAN Result;								/* ��ȡ��һ���豸��Ϣ�ṹ�Ľ�� */
    DWORD Index;								/* HidDevInfo ������ڲ�ƫ��ֵ */
    DWORD DataSize;								/* DeviceInterfaceDetail �ṹ��Ĵ�С */
    BOOLEAN GotRequiredSize;					/* ��õ��豸��Ϣ���ݽṹ��С��־ */
    PSP_DEVICE_INTERFACE_DETAIL_DATA detailData;/* �豸��Ϣ���� */
    DWORD RequiredSize;							/* �豸��Ϣ���ݽṹ�Ĵ�С */
    HIDD_ATTRIBUTES HIDAttrib;					/* HID device ���� */

    // ��ʼ����������õ��豸��Ϣ���� = 0;
    GotRequiredSize = FALSE;

    // 1)�Ӳ���ϵͳ�л�ȡHIDȫ��ΨһID
    HidD_GetHidGuid(&HidGuid);
    // 2) ��ȡ����HID�豸��ö����Ϣ
     HidDevInfo = SetupDiGetClassDevs(&HidGuid,NULL, NULL,DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
     // 3) ����1)��2)��������豸��������ؿգ���ֹͣ������
     // 1)����ID,2)���豸��Ϣ������ֻ����Ϣ�������������ݻ�Ҫ�ٵ��ú�����ȡ
    Index = 0;							       //3.1. ��ʼƫ��=0
    devInfoData.cbSize = sizeof(devInfoData);  //3.2. ����Ҫ��ȡ���豸��Ϣ���ݵĽṹ��С
    do{
        // 3.3.ͨ������Index��ȡһ��HID�豸����Ϣ
        Result = SetupDiEnumDeviceInterfaces(   HidDevInfo,
                                                0,
                                                &HidGuid,
                                                Index,
                                                &devInfoData);
        if(Result == FALSE)//����������û��������
        {
            //�ͷ�HID�豸��Ϣ�б��ڴ�
             if(detailData != NULL)free(detailData);
             SetupDiDestroyDeviceInfoList(HidDevInfo);
             cout << "no find hid!"<<endl;
             return FALSE;
        }
        // 3.4 ��ȡ�豸�ӿ���ϸ���ݵĽṹ��ʹ�С�������һ�ε��û��д��󣬵��ǿ��Ի�ȡ���ṹ��Ĵ�С
        if(GotRequiredSize == FALSE)
        {   // 3.4.1.��һ�λ�ȡ���õ��豸����
            SetupDiGetDeviceInterfaceDetail( HidDevInfo,
                                                    &devInfoData,
                                                    NULL,
                                                    0,
                                                    &DataSize,
                                                    NULL);
            GotRequiredSize = TRUE;
            // 3.4.2.�����豸���������ڴ�
            detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(DataSize);
            // 3.4.2.�����豸�ӿ������Ĵ�С
            detailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
        }
        // 4.��ȡ�豸��Ϣ����ȡ�ĸ�����DataSize�У���Ϣ������devInfoData�У�Ȼ��Ϳ�����ѡ�ض���HID�豸(VID,PID)��
                SetupDiGetDeviceInterfaceDetail(  HidDevInfo,
                                                    &devInfoData,
                                                    detailData,
                                                    DataSize,
                                                    &RequiredSize,
                                                    NULL);
        // 5.��ȡһ���豸��HANDLE,ȷ�����������������
        *hDevice = CreateFile( detailData->DevicePath,
                                    GENERIC_READ | GENERIC_WRITE,
                                    //NULL,                           //�Զ�ռ�ķ�ʽ��
                                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                                    (LPSECURITY_ATTRIBUTES)NULL,
                                    OPEN_EXISTING,
                                    FILE_FLAG_OVERLAPPED,
                                    NULL);
         // 6. ��ȡHID�豸�� VID & PID,�ж��Ƿ���������Ҫ��
         if(*hDevice != INVALID_HANDLE_VALUE)
         {
             HIDAttrib.Size = sizeof(HIDAttrib);
             // 6.1.��ȡ���ԣ�����HIDAttrib��
             HidD_GetAttributes(*hDevice, &HIDAttrib);
             // 6.2.�õ�ƥ���vid��pid
             if((HIDAttrib.VendorID == vid) && (HIDAttrib.ProductID == pid))
             {
                // 6.3.���ö�ȡ����������󳤶�,����ע�⣬���ֻ��512��
                HidD_SetNumInputBuffers(*hDevice,INPUT_PACK_MAX);
                //�ͷ�HID�豸��Ϣ�б��ڴ�
                 if(detailData != NULL)free(detailData);
                 SetupDiDestroyDeviceInfoList(HidDevInfo);
                return TRUE;	// �ҵ� HID device
             }
             //�رղ���������Ҫ���豸
             CloseHandle(*hDevice);
         }
         Index++;	/* ��������������������һ���豸 */
    } while(Result == TRUE);

    //�ͷ�HID�豸��Ϣ�б��ڴ�
     if(detailData != NULL)free(detailData);
     SetupDiDestroyDeviceInfoList(HidDevInfo);
     cout << "here"<<endl;

     return FALSE;
}

/* ���ܣ�����HID��HANDLE,��ȡUSB�ϴ�������
 * ���������HID��HANDLE��
 * ���������������
 * �������������ȡ(�԰��ĳ���+1Ϊ��λ)
 * ���������ʵ�ʶ�ȡ
 * ���أ���ȡ�ɹ�/ʧ��
 */
bool read_hid(HANDLE hDevice,char *buff,ULONG max_len,ULONG *real_len, int timeout)
{
    BOOL                    bResult;
    OVERLAPPED              HidOverlapped;  // �����¼�
    HANDLE                  ReportEvent;    // ������ȡ����ʱ�¼�HANDLE
    // 1.�ж�����
    if((hDevice == NULL) || (buff == NULL) ||(max_len<(READ_PACK_LEN+1)) || (NULL == real_len))
	{
		return FALSE;
	}
    // 2.Ϊ�������ݴ���һ���µ��¼�
    ReportEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
    // 3.���HID�ص��ṹ���Ա�Windows֪���豸����һ��IN����ʱ�������¼���
    HidOverlapped.hEvent = ReportEvent;
    HidOverlapped.Offset = 0;
    HidOverlapped.OffsetHigh = 0;
    // 4.��HID�豸��ñ��档ע�⣬��Read�ļ��ĵ���ֻ�������Ի������Ķ�ȡ��
    // ������뻺����������������̽������¼��������������ݽ��������֡�
    // ������ǣ���HID������IN�˵����ṩHID����ʱ�����������¼���
    bResult = ReadFile(	hDevice,							/* �Ѿ����򿪵�HID��HANDLE */
                        buff,                               /* IN�������ݴ���� */
                        max_len,                            // ����ȡ��Χ
                        (LPDWORD)real_len,                           /* ʵ�ʽ��յ����� */
                        (LPOVERLAPPED) &HidOverlapped );	/* �ȴ��ṹ���¼�HANDLE */
    // 5.�����ڵȴ�IN�¼������������ʱ�䣨ms���Ļ������������ش����Ҳ�����HID����
    //   �������true,��ô��ô���Դ�ָ���Ļ������������ˡ�
    /*bResult = WaitForSingleObject(ReportEvent, READ_WAITING_TIME);*/
	bResult = WaitForSingleObject(ReportEvent, timeout);
	if((bResult == WAIT_TIMEOUT) || (bResult == WAIT_ABANDONED))
	{
		CancelIo(&hDevice);
	}
    // 5.1.������䳬ʱ����Ҫ�ֶ���λ��
    ResetEvent(ReportEvent);
	//����ʱ����real_len��һ����ַ�ᱻ��ΪNULL��ԭ��֪����������Ӵ����쳣���
	/*if((NULL == real_len) || (hDevice == NULL))
	{
		return false;
	}*/
    // 5.2.��������յ���ȷ���ݣ�ÿ��report�ĵ�һ��������HID�Ľӿ�ID�ţ����Ժ��Ե�
    if(bResult == WAIT_OBJECT_0)
    {   //��������ȡ����Ч���ݣ������ȡ�ĳ���=0������ʵ���Ƕ���һ�����ݡ�
        if(*real_len == 0){*real_len = (READ_PACK_LEN+1);}
        return TRUE;
    }
    else
    {
		int error = GetLastError();
		cout << "read fail!error_code="<<error<<endl;
		if((error == 997) && (*real_len == 0))
		{
			//û�ж�������
			return TRUE;
		}
        return FALSE;
    }
}

/**********************************************************
* ����: д���ݵ�HID�豸
* ���������hDevice: �򿪵�HID��HANDLE
* ���������buff :   ��д��Ĳ�����buff�����ݳ��ȹ̶�ΪWRITE_PACK_LEN+1�����е�һ��ΪREPORT ID
* ���������д��ɹ�/ʧ��
**********************************************************/
bool write_hid(HANDLE hDevice,UINT8* pbuff)
{
	unsigned long	numBytesReturned;
	BOOL			bResult;
	OVERLAPPED		HidOverlapped;
	HANDLE			ReportEvent;
	UINT8 buff[WRITE_PACK_LEN + 1] = {0};

	// 1.�ж�����
	if((hDevice == NULL) || (buff == NULL))return FALSE;
	// 2.Ϊ�������ݴ���һ���µ��¼�
	ReportEvent = CreateEventA(NULL, TRUE, TRUE, "");
	// 3.���HID�ص��ṹ���Ա�Windows֪���豸����һ������ʱ�������¼���
	HidOverlapped.hEvent = ReportEvent;
	HidOverlapped.Offset = 0;
	HidOverlapped.OffsetHigh = 0;

	/* ʹ�� WriteFile ��HID�豸����������档��������Ӧ������������*/
	buff[0]=0;//�����report id,ûʲô��Ҫ�ͱ�Ķ�
	memcpy(&buff[1], pbuff, 64);
	bResult = WriteFile( hDevice,
		buff,                   // Ҫ���͵����ݵ�ַ
		WRITE_PACK_LEN+1,                // ���͸���
		&numBytesReturned,               // �����ֽڸ���
		(LPOVERLAPPED) &HidOverlapped);  // �����¼�
	// �����ȴ�д�¼����
	bResult = WaitForSingleObject(ReportEvent, WRITE_WAITING_TIME);
	ResetEvent(ReportEvent);

	// 5.2.�������������������
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

// ��hid.lib�� HidD_GetNumInputBuffers ���ڶ�ȡ����������
// HidD_SetNumInputBuffers �������û������Ĵ�С�����ֻ������ 512
// WaitForSingleObject ���ڶ�ȡ�������ȴ����ڶ��������ǵȴ�ʱ�䣬��λ��ms
// ÿ�����´�HIDʱ��ԭ�������е����ݾͶ�ʧ�ˡ�
// ��ʱ���ȡ�ɹ��ˣ����Ƕ�ȡ���ĸ���=0��ʵ�������ʱ���ȡ����������һ�����ݰ�65��
// �����ĳ������¶�ȡʧ���ˣ�һ���Ƕ�ȡ̫�죬������û���ݣ���ʱ��Ҫ�������´�HID,���һ���µ�HANDLE,����ᵼ�½�����������Ҳһֱ��ȡʧ�ܣ�
// ���������������豸��ÿ��д������Ҫ��һ����Ϊ��λ�������ݣ��������豸������IN/OUT��������64�����������ݶ�������64�ĵ�λ���ͺͽ���