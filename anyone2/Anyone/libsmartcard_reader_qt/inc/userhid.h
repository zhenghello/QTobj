#ifndef __USERHID_H
#define __USERHID_H

#include "myhid.h"
#include <QObject>
#include <QString>

class userHid : public QObject
{
	Q_OBJECT
public:
	userHid(int VID, int PID, char PORT=0);
	bool hidOpen();
	bool hidClose();
	bool hidSend(int len, UINT8 *pbuff);// ����usb����
	bool hidRead(int len,UINT8 *pbuff, int timeout); // ��ȡusb����,ֱ�ӵ��ã��г�ʱʱ��
	bool hidParse(UINT8 *pdata_out, int& len_data_out, UINT& cmd_type, int timeout); 
//signals:
//	void data_parse(QString x);
	HANDLE phid;    // ���������HID��handle
protected:
	int vid;
	int pid;
	char port;
private:
	UINT8 read_pack_data_buff[READ_PACK_LEN]; //�����ݻ�����
	UINT8 index_read_pack_data_buff;          //�����ݻ���������
	UINT8 read_pack_data_count;               //�����ݼ���

	typedef enum _segmentation_flag
	{
		SEGMENTATION_NONE = 0x00,   //���Ĳ���֡
		SEGMENTATION_FIRST = 0x40,  //��֡���ĵĵ�һ֡
		SEGMENTATION_OTHER = 0x80,  //��֡���ĵ�����֡
		SEGMENTATION_LAST = 0xC0    //��֡���ĵ����һ֡
	}segmentation_flag;

	#define HID_USB_MAX_PACKET_USER    62  //HID�豸�û�������

	typedef struct _pack_struct
	{
		UINT8 state;                 //��¼������ļ��״̬
		UINT8 check_sum;             //��¼������ı���У���
		UINT16 command_data_len;  //��¼��������������
		segmentation_flag pack_flag; //��¼��һ����ķ����־
		UINT8 pack_num;              //��¼��һ����ķ����
		UINT8 valid_len; //��¼��Ч�������
	}pack_struct;

	typedef struct _unpack_struct
	{
		segmentation_flag pack_flag;//��¼��һ����ķ����־
		UINT8 pack_num;              //��¼��һ����ķ����
	}unpack_struct;

	pack_struct pack;
	unpack_struct unpack;

	int check_start(UINT8* pdata_in, UINT8* pdata_out, UINT8* pstate);
	int check_control(UINT8* pdata_in, UINT8* pdata_out, UINT8* pstate, UINT8* pcheck_sum);
	int check_datalen_h(UINT8* pdata_in, UINT8* pdata_out, UINT8* pstate, UINT8* pcheck_sum, UINT16* pdata_len);
	int check_datalen_l(UINT8* pdata_in, UINT8* pdata_out, UINT8* pstate, UINT8* pcheck_sum, UINT16* pdata_len);
	int check_data(UINT8* pdata_in, UINT8* pdata_out, UINT8* pstate, UINT8* pcheck_sum, UINT16* pdata_len);
	int check_checksum(UINT8* pdata_in, UINT8* pdata_out, UINT8* pstate, UINT8* pcheck_sum);
	int check_stop(UINT8* pdata_in, UINT8* pdata_out, UINT8* pstate);
	int data_check(UINT8* pdata_in, UINT16* pp_in, UINT8* pdata_out, UINT data_len, pack_struct* ppack);
	int data_pack(UINT8* pdata_in, UINT16* pp_in, UINT8* pdata_out, UINT data_len, pack_struct* ppack);
	int data_unpack(UINT8* pdata_in, UINT8* pdata_out, UINT16* pp_out, UINT8 data_len, unpack_struct* punpack);
	bool hid_read_pack(UINT8* ppack_buff, UINT8 pack_len, int timeout);
	/*bool hidRead(int len,UINT8 *pbuff); */
};

#endif
