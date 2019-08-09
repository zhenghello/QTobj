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
	bool hidSend(int len, UINT8 *pbuff);// 发送usb数据
	bool hidRead(int len,UINT8 *pbuff, int timeout); // 读取usb数据,直接调用，有超时时间
	bool hidParse(UINT8 *pdata_out, int& len_data_out, UINT& cmd_type, int timeout); 
//signals:
//	void data_parse(QString x);
	HANDLE phid;    // 定义的用于HID的handle
protected:
	int vid;
	int pid;
	char port;
private:
	UINT8 read_pack_data_buff[READ_PACK_LEN]; //包数据缓冲区
	UINT8 index_read_pack_data_buff;          //包数据缓冲区索引
	UINT8 read_pack_data_count;               //包数据计数

	typedef enum _segmentation_flag
	{
		SEGMENTATION_NONE = 0x00,   //报文不分帧
		SEGMENTATION_FIRST = 0x40,  //分帧报文的第一帧
		SEGMENTATION_OTHER = 0x80,  //分帧报文的其它帧
		SEGMENTATION_LAST = 0xC0    //分帧报文的最后一帧
	}segmentation_flag;

	#define HID_USB_MAX_PACKET_USER    62  //HID设备用户包数据

	typedef struct _pack_struct
	{
		UINT8 state;                 //记录封包最后的检查状态
		UINT8 check_sum;             //记录封包最后的报文校验和
		UINT16 command_data_len;  //记录报文数据区长度
		segmentation_flag pack_flag; //记录上一封包的封包标志
		UINT8 pack_num;              //记录上一封包的封包号
		UINT8 valid_len; //记录有效封包长度
	}pack_struct;

	typedef struct _unpack_struct
	{
		segmentation_flag pack_flag;//记录上一封包的封包标志
		UINT8 pack_num;              //记录上一封包的封包号
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
