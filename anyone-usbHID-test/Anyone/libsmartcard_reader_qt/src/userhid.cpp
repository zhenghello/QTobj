#include "userhid.h"
#include "commonres.h"
#include <QDateTime>
#include <QElapsedTimer>
#include <QDebug>
#include <iostream>

userHid::userHid(int VID, int PID, char PORT) : QObject(NULL)
{
	phid = 0;
	vid = VID;
	pid = PID;
	port = PORT;
	index_read_pack_data_buff = 0;
	read_pack_data_count = 0;
	pack.check_sum = 0;
	pack.command_data_len = 0;
	pack.pack_flag = SEGMENTATION_NONE;
	pack.pack_num = 0;
	pack.state = FRAME_CHECK_START_USB;
	pack.valid_len = 0;
	unpack.pack_flag = SEGMENTATION_NONE;
	unpack.pack_num = 0;
}

bool userHid::hidOpen()
{
	bool b;

	if(phid)
	{
		CloseHandle(phid);
		phid = 0;
	}

	b = open_hid(&phid, vid, pid);
	if(false == b)
	{
		phid = 0;
	}

	return b;
}

bool userHid::hidClose()
{
	if(phid)
	{
		CloseHandle(phid);
		phid = 0;
	}

	return true;
}

bool userHid::hidSend(int len, UINT8 *pbuff)
{
	bool b = false;
	UINT8 *psendBuff = NULL;
	UINT16 index_psendBuff = 0;
	int len_sendBuff = 0;
	int lret = EXIT_FAILURE_LOCOAL;
	UINT8 send_pack_data_buff[64] = {0};

	if((NULL == pbuff) || (len <= 0))
	{
		return false;
	}

	psendBuff = new UINT8[len];//���뻺���������ڴ洢����������
	memcpy(psendBuff, pbuff, len);
	len_sendBuff = len;

	if(0 == phid) //�豸�Ƿ��Ѿ��򿪣����û������豸
	{
		b = hidOpen();
		if(false == b)
		{
			delete []psendBuff;
			psendBuff = NULL;
			return false;
		}
	}

	while(1) //ѭ���з��ͣ�ֱ�����ݷ�����
	{
		lret = data_pack(psendBuff, &index_psendBuff, send_pack_data_buff, len_sendBuff, &pack); //����ʵ��ȡ���ֽ������˳�����Чָ��
		if(0 > lret)
		{
			//���ʧ�ܣ�û�пɷ��͵İ�
			delete []psendBuff;
			psendBuff = NULL;
			b = true;
			break;
		}
		//����ɹ�
		len_sendBuff -= lret;//����ʣ����������ݳ���
		b = write_hid(phid, send_pack_data_buff);//���ͷ��
		if(false == b)
		{ 
			delete []psendBuff;//���ͷ��ʧ��
			psendBuff = NULL;
			b = false;
			break;
		}
	}

	qint64 current_time = QDateTime::currentMSecsSinceEpoch() + 100; //�ر�Ҫע�������ڰ忨�ϲ�����Ӵ˶���ʱ�����������ݣ�ò�ư忨�ϵĻ������ᱻ���
	while(current_time > QDateTime::currentMSecsSinceEpoch()) //��ʱһ��ʱ�䣬��������ڳ�ʱʱ����û�ж������ݣ����ͺ����϶�����ɳ���Ī���ҵ�������Ϊԭ����Ч�ĵ�ַ������ȫ�����0��
	{
		;
	}
	return b;
}

//hid.lib���л�����豸��������ʱ���豸���������ڲ��ռ䣬����Ķ�ֻ�Ǵ��ڲ��ռ��
bool userHid::hidRead(int len, UINT8 *pbuff, int timeout)
{
	bool b = false;
	int lret = EXIT_FAILURE_LOCOAL;
	UINT16 p_out;
	UINT8 temp_pack_buff[READ_PACK_LEN] = {0};
	int temp_index_pbuff = 0;
	int ok_count = 0;
	int fail_count = 0;

	if(NULL == pbuff || (0 >= len))
	{
		return false;
	}

	if(read_pack_data_count >= len)
	{
		//�����ݻ��������е������ܹ������ȡ
		memcpy(pbuff, &read_pack_data_buff[index_read_pack_data_buff], len);
		read_pack_data_count -= len;
		index_read_pack_data_buff += len;
		b = true;
	}
	else
	{
		//�����ݻ������е����ݲ���
		//����ʣ������
		if(0 < read_pack_data_count)
		{
			memcpy(pbuff, &read_pack_data_buff[index_read_pack_data_buff], read_pack_data_count);
			temp_index_pbuff = read_pack_data_count;
			index_read_pack_data_buff = 0;
			read_pack_data_count = 0;
		}

		//������
		if(0 == phid) //�豸�Ƿ��Ѿ��򿪣����û������豸
		{
			b = hidOpen();
			if(false == b)
			{
				return false;
			}
		}

		qint64 current_time = QDateTime::currentMSecsSinceEpoch() + timeout;
		/*QElapsedTimer t;*/
		while(1) 
		{
			if (current_time < QDateTime::currentMSecsSinceEpoch())//��ʱ�ж�
			{
				b = false;
				break;
			}
			/*t.start();
			while(!t.hasExpired(50));*/
			b = hid_read_pack(temp_pack_buff, READ_PACK_LEN, timeout);
			if(b)
			{
				//�����ɹ�
				p_out = 0;
				lret = data_unpack(temp_pack_buff, read_pack_data_buff, &p_out, READ_PACK_LEN, &unpack);
				if(0 > lret)
				{
					//���ʧ��
					return false;
				}
				else
				{
					//����ɹ�
					read_pack_data_count = lret;//���ð����ݻ������е����ݳ���
					index_read_pack_data_buff = 0;

					if((len - temp_index_pbuff) > read_pack_data_count) //�ж�һ���Ƿ�����������������ѭ�������
					{
						memcpy(&pbuff[temp_index_pbuff], read_pack_data_buff, read_pack_data_count);
						temp_index_pbuff += read_pack_data_count;
						read_pack_data_count = 0;
						index_read_pack_data_buff = 0;
					}
					else
					{
						memcpy(&pbuff[temp_index_pbuff], read_pack_data_buff, len - temp_index_pbuff);
						read_pack_data_count -= (len - temp_index_pbuff);
						index_read_pack_data_buff += (len - temp_index_pbuff);
						temp_index_pbuff = len;
						break;
					}
				}
			}
		}
	}

	return b;
}

//bool userHid::hidRead(int len, UINT8 *pbuff)
//{
//	bool b = false;
//	int lret = EXIT_FAILURE_LOCOAL;
//	UINT16 p_out = 0;
//	UINT8 temp_pack_buff[READ_PACK_LEN] = {0};
//	int temp_index_pbuff = 0;
//
//	if(NULL == pbuff || (0 >= len))
//	{
//		return false;
//	}
//
//	if(read_pack_data_count >= len)
//	{
//		//�����ݻ��������е������ܹ������ȡ
//		memcpy(pbuff, &read_pack_data_buff[index_read_pack_data_buff], len);
//		read_pack_data_count -= len;
//		index_read_pack_data_buff += len;
//	}
//	else
//	{
//		//�����ݻ������е����ݲ���
//		//����ʣ������
//		if(0 < read_pack_data_count)
//		{
//			memcpy(pbuff, &read_pack_data_buff[index_read_pack_data_buff], read_pack_data_count);
//			temp_index_pbuff = read_pack_data_count;
//			index_read_pack_data_buff = 0;
//			read_pack_data_count = 0;
//		}
//
//		//������
//		if(0 == phid) //�豸�Ƿ��Ѿ��򿪣����û������豸
//		{
//			b = hidOpen();
//			if(false == b)
//			{
//				return false;
//			}
//		}
//
//		while(1)//һֱ�ȵ�������
//		{
//			b = hid_read_pack(temp_pack_buff, READ_PACK_LEN);
//			if(b)
//			{
//				//�����ɹ�
//				p_out = 0;
//				lret = data_unpack(temp_pack_buff, read_pack_data_buff, &p_out, READ_PACK_LEN, &unpack);
//				if(0 > lret)
//				{
//					//���ʧ��
//					return false;
//				}
//				else
//				{
//					//����ɹ�
//					read_pack_data_count = lret;//���ð����ݻ������е����ݳ���
//					index_read_pack_data_buff = 0;
//					//
//					if((len - temp_index_pbuff) > read_pack_data_count) //�ж�һ���Ƿ�����������������ѭ�������
//					{
//						memcpy(&pbuff[temp_index_pbuff], read_pack_data_buff, read_pack_data_count);
//						temp_index_pbuff += read_pack_data_count;
//						read_pack_data_count = 0;
//						index_read_pack_data_buff = 0;
//					}
//					else
//					{
//						memcpy(&pbuff[temp_index_pbuff], read_pack_data_buff, len - temp_index_pbuff);
//						read_pack_data_count -= (len - temp_index_pbuff);
//						index_read_pack_data_buff += (len - temp_index_pbuff);
//						temp_index_pbuff = len;
//						break;
//					}
//				}
//			}
//		}
//
//	}
//
//	return true;
//}

bool userHid::hidParse(UINT8 *pdata_out, int& len_data_out, UINT& cmd_type, int timeout)
{
	bool b = false;
	UINT8 data_read = 0x00;
	UINT8 state = 0x00;
	UINT8 check_sum = 0x00;
	UINT16 data_len = 0x0000;
	UINT8 data_local[2048];
	UINT16 data_index = 0x0000;
	int lret = EXIT_FAILURE_LOCOAL;

	if(NULL == pdata_out)
	{
		return false;
	}

	while(hidRead(1, &data_read, timeout))
	{
		switch(state)
		{
		case FRAME_CHECK_START_USB:
			lret = check_start(&data_read, &data_local[data_index], &state);
			break;
		case FRAME_CHECK_CONTROL_USB:
			lret = check_control(&data_read, &data_local[data_index], &state, &check_sum);
			break;
		case FRAME_CHECK_DATALENH:
			lret = check_datalen_h(&data_read, &data_local[data_index], &state, &check_sum, &data_len);
			break;
		case FRAME_CHECK_DATALENL:
			lret = check_datalen_l(&data_read, &data_local[data_index], &state, &check_sum, &data_len);
			break;
		case FRAME_CHECK_DATA_USB:
			lret = check_data(&data_read, &data_local[data_index], &state, &check_sum, &data_len);
			break;
		case FRAME_CHECK_CHECKSUM_USB:
			lret = check_checksum(&data_read, &data_local[data_index], &state, &check_sum);
			break;
		case FRAME_CHECK_STOP_USB:
			if(EXIT_SUCCESS_LOCOAL == check_stop(&data_read, &data_local[data_index], &state))
			{
				if((FRAME_CONTROL_CODE_REP_USB != data_local[FRAME_CONTROL_INDEX_USB]) &&    //��REP
				   (FRAME_CONTROL_CODE_UPLOAD_INF != data_local[FRAME_CONTROL_INDEX_USB]))   //�������ϴ���Ϣ֡
				{
					lret = EXIT_FAILURE_LOCOAL;
					break; //������
				}
				//һ�����ݽ������
				cmd_type = 0;
				for(int i = 0;i < 3;i++)
				{
					cmd_type |= data_local[FRAME_COMMAND_INDEX_USB + i] << 8 *(2 - i);
				}

				len_data_out = 0;
				for(int i = 0;i < 2;i++)
				{
					len_data_out |= data_local[FRAME_DATALEN_INDEX_USB + i] << 8 * (1 - i);
				}
				len_data_out -= 3;

				if(0 != len_data_out)
				{
					for(int i = 0;i < len_data_out;i++)
					{
						pdata_out[i] = data_local[FRAME_COMMAND_PARAM_INDEX_USB + i];
					}
				}

				return true;
			}
			break;
		default:break;
		}
		if(EXIT_SUCCESS_LOCOAL == lret)
		{
			data_index++;
		}
		else
		{
			data_index = 0;
		}
	}
	return false;
}

int userHid::check_start(UINT8* pdata_in, UINT8* pdata_out, UINT8* pstate)
{
	if(PROTOCOL_FRAME_START_CODE_USB != *pdata_in)
	{
		//������ʼ�ֽڲ���
		*pstate = FRAME_CHECK_START_USB;
		return EXIT_FAILURE_LOCOAL;
	}
	else
	{
		*pdata_out = *pdata_in;
		*pstate = FRAME_CHECK_CONTROL_USB;
		return EXIT_SUCCESS_LOCOAL;
	}
}

int userHid::check_control(UINT8* pdata_in, UINT8* pdata_out, UINT8* pstate, UINT8* pcheck_sum)
{
	int lret = EXIT_FAILURE_LOCOAL;

	switch(*pdata_in)
	{
	case FRAME_CONTROL_CODE_COMMAND_REP_USB:
	case FRAME_CONTROL_CODE_COMMAND_NO_REP_USB:
	case FRAME_CONTROL_CODE_TS_HEAD_USB:
	case FRAME_CONTROL_CODE_TS_BODY_USB:
	case FRAME_CONTROL_CODE_TS_TAIL_USB:
	case FRAME_CONTROL_CODE_REP_USB:
	case FRAME_CONTROL_CODE_ACK_USB:
	case FRAME_CONTROL_CODE_EVT_USB:
	case FRAME_CONTROL_CODE_UPLOAD_USB:
	case FRAME_CONTROL_CODE_UPLOAD_INF:
		*pdata_out = *pdata_in;
		*pcheck_sum = *pdata_in;
		*pstate = FRAME_CHECK_DATALENH;
		lret = EXIT_SUCCESS_LOCOAL;
		break;
	default:
		*pstate = FRAME_CHECK_START_USB;
		break;
	}

	return lret;
}

int userHid::check_datalen_h(UINT8* pdata_in, UINT8* pdata_out, UINT8* pstate, UINT8* pcheck_sum, UINT16* pdata_len)
{
	*pdata_out = *pdata_in;
	*pcheck_sum += *pdata_in;
	*pstate = FRAME_CHECK_DATALENL;
	*pdata_len = (*pdata_in) << 8;

	return EXIT_SUCCESS_LOCOAL;
}

int userHid::check_datalen_l(UINT8* pdata_in, UINT8* pdata_out, UINT8* pstate, UINT8* pcheck_sum, UINT16* pdata_len)
{
	*pdata_len |=  *pdata_in;

	if(3 > *pdata_len)
	{
		*pstate = FRAME_CHECK_START_USB;
		return EXIT_FAILURE_LOCOAL;
	}
	else
	{
		*pdata_out = *pdata_in;
		*pcheck_sum += *pdata_in;
		*pstate = FRAME_CHECK_DATA_USB;
		return EXIT_SUCCESS_LOCOAL;
	}
}

int userHid::check_data(UINT8* pdata_in, UINT8* pdata_out, UINT8* pstate, UINT8* pcheck_sum, UINT16* pdata_len)
{
	if(0 < *pdata_len)
	{
		(*pdata_len)--;
		*pdata_out = *pdata_in;
		*pcheck_sum += *pdata_in;
	}
	if(0 == *pdata_len)
	{
		*pstate = FRAME_CHECK_CHECKSUM_USB;
	}

	return EXIT_SUCCESS_LOCOAL;
}

int userHid::check_checksum(UINT8* pdata_in, UINT8* pdata_out, UINT8* pstate, UINT8* pcheck_sum)
{
	if((*pcheck_sum) == (*pdata_in))
	{
		*pdata_out = *pdata_in;
		*pstate = FRAME_CHECK_STOP_USB;
		return EXIT_SUCCESS_LOCOAL;
	}
	else
	{
		*pstate = FRAME_CHECK_START_USB;
		return EXIT_FAILURE_LOCOAL;
	}
}

int userHid::check_stop(UINT8* pdata_in, UINT8* pdata_out, UINT8* pstate)
{
	if(PROTOCOL_FRAME_STOP_CODE_USB == (*pdata_in))
	{
		*pdata_out = *pdata_in;
		*pstate = FRAME_CHECK_START_USB;
		return EXIT_SUCCESS_LOCOAL;
	}
	else
	{
		*pstate = FRAME_CHECK_START_USB;
		return EXIT_FAILURE_LOCOAL;
	}
}

//����ķ����־ֻ�Ӵ�������ݻ�������ȡһ����Ч�ı��Ľ��з��
//�˺�����������������ȡ��62�ֽڵ���Ч���� || ��ȡ��һ�������ı��� || ��������ݻ��������Ѿ�û��������
//����p_out == 64 || check_stop == EXIT_SUCCESS_LOCOAL || data_len == 0
int userHid::data_check(UINT8* pdata_in, UINT16* pp_in, UINT8* pdata_out, UINT data_len, pack_struct* ppack)
{
	int lret = EXIT_FAILURE_LOCOAL;
	UINT8 p_out = 0x02;
	UINT8 count = 0x00;
	UINT8 p_count = 0x00;

	while(data_len)
	{
		switch(ppack->state)
		{
		case FRAME_CHECK_START_USB:
			{
				lret = check_start(&pdata_in[*pp_in], &pdata_out[p_out], &(ppack->state));
				if(EXIT_SUCCESS_LOCOAL == lret)
				{
					p_out++;
					count++;
					ppack->pack_flag = SEGMENTATION_NONE;
					ppack->pack_num = 0;
				}
			}
			break;
		case FRAME_CHECK_CONTROL_USB:
			{
				lret = check_control(&pdata_in[*pp_in], &pdata_out[p_out], &(ppack->state), &(ppack->check_sum));
				if(EXIT_SUCCESS_LOCOAL == lret)
				{
					p_out++;
					count++;
				}
				else
				{
					//���ʧ��ʱ�޳�֮ǰ��ͬһ�����е���Ч����
					p_out -= count;//���жϷְ���־��ԭ����ÿ���ְ���ֻ��һ�����ģ�����Ҫ�ְ��ı��ģ�������ֿ���������һ���ְ���
				}
			}
			break;
		case FRAME_CHECK_DATALENH:
			{
				lret = check_datalen_h(&pdata_in[*pp_in], &pdata_out[p_out], &(ppack->state), &(ppack->check_sum), &(ppack->command_data_len));
				if(EXIT_SUCCESS_LOCOAL == lret)
				{
					p_out++;
					count++;
				}
				else
				{
					p_out -= count;
				}
			}
			break;
		case FRAME_CHECK_DATALENL:
			{
				lret = check_datalen_l(&pdata_in[*pp_in], &pdata_out[p_out], &(ppack->state), &(ppack->check_sum), &(ppack->command_data_len));
				if(EXIT_SUCCESS_LOCOAL == lret)
				{
					p_out++;
					count++;
				}
				else
				{
					p_out -= count;
				}
			}
			break;
		case FRAME_CHECK_DATA_USB:
			{
				lret = check_data(&pdata_in[*pp_in], &pdata_out[p_out], &(ppack->state), &(ppack->check_sum), &(ppack->command_data_len));
				if(EXIT_SUCCESS_LOCOAL == lret)
				{
					p_out++;
					count++;
				}
				else
				{
					;//�����ܷ���
				}
			}
			break;
		case FRAME_CHECK_CHECKSUM_USB:
			{
				lret = check_checksum(&pdata_in[*pp_in], &pdata_out[p_out], &(ppack->state), &((ppack->check_sum)));
				if(EXIT_SUCCESS_LOCOAL == lret)
				{
					p_out++;
					count++;
				}
				else
				{
					if(ppack->pack_flag == SEGMENTATION_NONE)
					{
						p_out -= count;
					}
					else   //ǰ��ķְ��Ѿ�����ȥ�ˣ�����ְ�Ҳû�б�Ҫ�˳���
					{
						ppack->state = FRAME_CHECK_STOP_USB;
						pdata_out[p_out] = pdata_in[*pp_in];
						p_out++;
					}
				}
			}
			break;
		case FRAME_CHECK_STOP_USB:
			{
				lret = check_stop(&pdata_in[*pp_in], &pdata_out[p_out], &(ppack->state));
				if(EXIT_SUCCESS_LOCOAL == lret)
				{
					p_out++;
					count = 0;//һ�����ĵ������Ѿ���ɼ��
					ppack->valid_len = p_out - 0x02;
					if(ppack->pack_flag != SEGMENTATION_NONE)
					{
						ppack->pack_flag = SEGMENTATION_LAST;
						ppack->pack_num += 1;
					}

					(*pp_in)++;
					p_count++;
					return p_count;  //����ʵ��ȡ�˶����ֽ�
				}
				else
				{
					if(ppack->pack_flag == SEGMENTATION_NONE)
					{
						p_out -= count;
					}
					else
					{
						ppack->state = FRAME_CHECK_START_USB;
						pdata_out[p_out] = pdata_in[*pp_in];
						p_out++;
						ppack->pack_flag = SEGMENTATION_LAST;
						ppack->pack_num += 1;
						ppack->valid_len = p_out - 0x02;

						(*pp_in)++;
						p_count++;
						return p_count;
					}
				}
			}
			break;
		default:break;
		}

		(*pp_in)++;
		data_len--;
		p_count++;

		if((HID_USB_MAX_PACKET_USER + 2) == p_out)
		{
			if(ppack->pack_flag == SEGMENTATION_NONE)
			{
				ppack->pack_flag = SEGMENTATION_FIRST;
				ppack->pack_num = 0;
			}
			else
			{
				ppack->pack_flag = SEGMENTATION_OTHER;
				ppack->pack_num += 1;
			}
			ppack->valid_len = p_out - 0x02;

			return p_count;
		}
	}

	//�������Ѿ�Ϊ�գ����ǻ���û�еõ���Ч�ķ��
	//��¼��Ч�������
	ppack->valid_len = p_out - 0x02;

	return EXIT_FAILURE_LOCOAL; //���ط������
}

int userHid::data_pack(UINT8* pdata_in, UINT16* pp_in, UINT8* pdata_out, UINT data_len, pack_struct* ppack)
{
	int lret = EXIT_FAILURE_LOCOAL;
	UINT8 i = 0;

	if((NULL == pdata_in) || (NULL == pdata_out) || (NULL == ppack) || (0 == data_len))
	{
		return EXIT_FAILURE_LOCOAL;
	}

	lret = data_check(pdata_in, pp_in, pdata_out, data_len, ppack);
	if(0 < lret)
	{
		pdata_out[0] = ppack->pack_flag | ppack->pack_num;
		pdata_out[1] = ppack->valid_len;
		if(ppack->valid_len < HID_USB_MAX_PACKET_USER)//���������Ȳ��ֲ�0
		{
			for(i = ppack->valid_len + 2;i < HID_USB_MAX_PACKET_USER + 2;i++)
			{
				pdata_out[i] = 0x00;
			}
		}
	}

	return lret;
}

int userHid::data_unpack(UINT8* pdata_in, UINT8* pdata_out, UINT16* pp_out, UINT8 data_len, unpack_struct* punpack)
{
	UINT8 p_in = 0x00;
	UINT8 pack_flag = 0x00;
	UINT8 pack_num = 0x00;
	UINT8 valid_len = 0x00;
	UINT8 i = 0;

	if(WRITE_PACK_LEN != data_len)
	{
		return EXIT_FAILURE_LOCOAL;
	}

	pack_flag = pdata_in[p_in] & 0xC0; //�ְ���־
	pack_num = pdata_in[p_in] & 0x3F;  //�ְ���
	p_in++;

	if((pack_flag != SEGMENTATION_NONE) && (pack_flag != SEGMENTATION_FIRST) &&  \
		(pack_flag != SEGMENTATION_OTHER) && (pack_flag != SEGMENTATION_LAST))
	{
		//��Ч���ݰ�
		return EXIT_FAILURE_LOCOAL;
	}

	//�ְ���Ч���ж�
	if(punpack->pack_flag == SEGMENTATION_NONE) //��һ���Ĳ��ְ�
	{
		if(((pack_flag != SEGMENTATION_NONE) && (pack_flag != SEGMENTATION_FIRST)) || (0 != pack_num))
		{
			//�������Ƕ������ұ������Ƿְ����ĵ��װ������߱����ְ��Ų���ȷ
			return EXIT_FAILURE_LOCOAL;
		}
	}
	if(punpack->pack_flag == SEGMENTATION_FIRST) //��һ��Ϊ���ĵ�һ�ְ�
	{
		if(((pack_flag != SEGMENTATION_OTHER) && (pack_flag != SEGMENTATION_LAST)) || (pack_num != 0x01))
		{
			//���������м�ְ��ұ����������ְ������߱����ְ��Ų�����1
			return EXIT_FAILURE_LOCOAL;
		}
	}
	if(punpack->pack_flag == SEGMENTATION_OTHER) //��һ��Ϊ�����м�ְ�
	{
		if(((pack_flag != SEGMENTATION_OTHER) && (pack_flag != SEGMENTATION_LAST)) || (punpack->pack_num != pack_num - 1))
		{
			//���������м�ְ��ұ����������ְ������߱����ְ��Ų�����
			return EXIT_FAILURE_LOCOAL;
		}
	}
	if(punpack->pack_flag == SEGMENTATION_LAST) //��һ��Ϊ�������ְ�
	{
		if(((pack_flag != SEGMENTATION_NONE) && (pack_flag != SEGMENTATION_FIRST)) || (0 != pack_num))
		{
			//�������Ƕ������ұ������Ƿְ����ĵ��װ������߱����ְ��Ų���ȷ
			return EXIT_FAILURE_LOCOAL;
		}
	}

	//�������
	punpack->pack_flag = (segmentation_flag)pack_flag;
	punpack->pack_num = pack_num;

	valid_len = pdata_in[p_in];//���ݰ���Ч���ݳ���
	p_in++;

	for(i = 0;i < valid_len;i++)
	{
		pdata_out[*pp_out] = pdata_in[p_in];
		(*pp_out)++;
		p_in++;
	}

	return valid_len;
}

bool userHid::hid_read_pack(UINT8* ppack_buff, UINT8 pack_len, int timeout)
{
	char rbuff[READ_PACK_LEN + 1];
	bool b = false;
	ULONG real_len = 0;
	UINT8 len_count = 0;

	if((0 == phid) || (READ_PACK_LEN != pack_len))
	{
		return false;
	}

	b = read_hid(phid, rbuff, 65, &real_len, timeout);
	if(b)
	{
		UINT8 index = 0;
		while(index < real_len)
		{
			if(0 == (index % (READ_PACK_LEN + 1)))
			{
				index++;
				continue;
			}
			if(len_count < READ_PACK_LEN)
			{
				ppack_buff[len_count] = rbuff[index];
				len_count++;
				index++;
			}
			else
			{
				index++;
			}
		}
	}
	else
	{
		this->hidOpen();//��ȡʧ�ܾ�Ҫ���´�hid
	}

	if(READ_PACK_LEN != len_count)
	{
		b = false;
	}

	return b;
}
