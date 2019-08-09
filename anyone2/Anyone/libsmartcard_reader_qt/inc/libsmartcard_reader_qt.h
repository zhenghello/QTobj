#ifndef LIBSMARTCARD_READER_QT_H
#define LIBSMARTCARD_READER_QT_H

//#include "libsmartcard_reader_qt_global.h"

#include "userhid.h"
#include "reagentinfo.h"
#include <QObject>
#include <QString>
#include <QTimer>

#define SMARTCARDVID     0x6666
#define SMARRCARDPID     0x6666
#define SMARTCARTPORT    0x00

//读卡器命令定义
#define SMARTCARDMASK                0xFF00FF
#define SMARTCARDUPLAODINFO          0x020009
#define SMARTCARDUPLOADBEGIN         0x000001
#define SMARTCARDUPLOADEND           0x000000
#define SMARTCARDUPLOADINVALIDCARD   0x000002  
#define SMARTCARDUPLOADCARDINFO      0x000003
#define SMARTCARDUPLOADCARDERRORCODE 0x000004

#define SMARTCARDOEMSET              0x02000D

#define MFDIR     0x3F00

//自制usb读卡器驱动，Windows端使用。要求支持qt
//提供读卡、写卡、制卡、删除卡片结构功能
using namespace reagentpublic;

//class LIBSMARTCARD_READER_QT_EXPORT libsmartcard_reader_qt:public QObject //
class libsmartcard_reader_qt:public QObject
{
	Q_OBJECT
public:
	libsmartcard_reader_qt(int VID = SMARTCARDVID, int PID = SMARRCARDPID, char PORT = SMARTCARTPORT);
	~libsmartcard_reader_qt();

    bool smartcard_read(MF &pmf, UINT8 &invalid_card_info, UINT16 &cpu_card_error_code, bool &timeout_flag, bool & usb_open_flag, UINT8* pcard_version_id, UINT8 which_channel = 0x00, int timeout = 20000, UINT8 oem = 'D');
	bool smartcard_write(unsigned char df_p2, unsigned char ef_p2, unsigned short offset, unsigned short len, char* pbuff, int timeout = 1000, UINT8 which_channel = 0x00, UINT8 oem = 'D');
    bool smartcard_create(MF &pmf, UINT8 which_channel = 0x00, UINT8 oem = 'D');
	bool smartcard_delete(int timeout =20000, UINT8 which_channel = 0x00, UINT8 oem = 'D');
	bool smartcard_get_cardid(UINT8 *pcar_id, int timeout = 1000, UINT8 which_channel = 0x00, UINT8 oem = 'D');

private:
	userHid* puserhid;
	bool action_over;

	bool cmd_open(UINT8 which_channel, int timeout = 1000);
	bool cmd_close(UINT8 which_channel, int timeout = 1000);
	bool cmd_write(unsigned char df_p2, unsigned char ef_p2, unsigned short offset, unsigned short len, char* pbuff, int timeout, UINT8 which_channel = 0x00);
	bool cmd_create(unsigned char df_p2, unsigned char ef_p2, unsigned short len, unsigned char* pbuff, int timeout = 2000, UINT8 which_channel = 0x00);
	bool cmd_delete(int timeout = 20000, UINT8 which_channel = 0x00);
	bool cmd_oemset(UINT8 which_channel, UINT8 oem, int timeout = 1000);
	bool cmd_get_cardid(UINT8 *pcar_id, UINT8 which_channel, int timeout);
};

#endif // LIBSMARTCARD_READER_QT_H
