#ifndef __COMMONRES_H
#define __COMMONRES_H

//����EVT֡��󳤶�
#define EVT_FRAME_MAX_SIZE_USB                     (10u)

//Э��֡��ʼ��
#define PROTOCOL_FRAME_START_CODE_USB               (0xAA)
//Э��ֹ֡ͣ��
#define PROTOCOL_FRAME_STOP_CODE_USB                (0x55)

//Э��֡��ʽ�±�
#define FRAME_START_INDEX_USB                       (0u)  //��ʼ
#define FRAME_CONTROL_INDEX_USB                     (1u)  //����
#define FRAME_DATALEN_INDEX_USB                     (2u)  //���ݳ���
#define FRAME_COMMAND_INDEX_USB                     (4u)  //������
#define FRAME_COMMAND_TYPE_INDEX_USB                (4u)  //��������
#define FRAME_COMMAND_NUM_INDEX_USB                 (5u)  //�������
#define FRAME_COMMAND_CONTENT_INDEX_USB             (6u)  //��������
#define FRAME_COMMAND_PARAM_INDEX_USB               (7u)  //�������

//���������
#define FRAME_CONTROL_CODE_COMMAND_REP_USB          (0x00) //��վ�´�����֡(���REP)
#define FRAME_CONTROL_CODE_COMMAND_NO_REP_USB       (0x40) //��վ�´�����֡(�����REP)
#define FRAME_CONTROL_CODE_TS_HEAD_USB              (0x41) //ʱ�����ͷ
#define FRAME_CONTROL_CODE_TS_BODY_USB              (0x42) //ʱ�������
#define FRAME_CONTROL_CODE_TS_TAIL_USB              (0x43) //ʱ�����β
#define FRAME_CONTROL_CODE_REP_USB                  (0xC0) //��վ��Ӧ֡REP
#define FRAME_CONTROL_CODE_ACK_USB                  (0xD4) //��վӦ��֡ACK
#define FRAME_CONTROL_CODE_EVT_USB                  (0xF8) //��վ�쳣֡EVT
#define FRAME_CONTROL_CODE_UPLOAD_USB               (0xD8) //��վ�����ϴ�֡
#define FRAME_CONTROL_CODE_UPLOAD_INF               (0xC4) //�����ϴ���Ϣ֡

//������mask
#define CONTROL_CODE_RETURNFLAG_MASK_USB            (0x40)
#define CONTROL_CODE_IDENT_MASK_USB                 (0x03)

//������ʶ�����
#define CONTROL_CODE_IDENT_CMD_USB                  (0x00) //����
#define CONTROL_CODE_IDENT_TS_HEAD_USB              (0x01) //ʱ���ͷ
#define CONTROL_CODE_IDENT_TS_BODY_USB              (0x02) //ʱ�����
#define CONTROL_CODE_IDENT_TS_TAIL_USB              (0x03) //ʱ���β

//֡��Ҫ����REP
#define FRAME_RETURN_REP_USB(x)     (CONTROL_CODE_RETURNFLAG_MASK_USB != ((x) & CONTROL_CODE_RETURNFLAG_MASK_USB))

#define EXIT_FAILURE_LOCOAL  -272
#define EXIT_SUCCESS_LOCOAL  0

//����֡ת̬
typedef enum
{
	NONE_RETURN_USB = 0x00, //����Ҫ����
	NEED_ACK_USB,           //Ӧ��
	NEED_REP_USB,           //��Ӧ
	NEED_EVT_USB,           //�쳣
	NEED_UPLOAD_USB,        //�����ϴ�
} return_frame_state_e_usb;

//֡��ʽ���״̬����
typedef enum
{
	FRAME_CHECK_START_USB = 0x00u, //��ʼ��
	FRAME_CHECK_CONTROL_USB,       //������
	FRAME_CHECK_DATALENH,       //���ݳ���
	FRAME_CHECK_DATALENL,
	FRAME_CHECK_DATA_USB,          //����
	FRAME_CHECK_CHECKSUM_USB,      //У���
	FRAME_CHECK_STOP_USB          //ֹͣ��
} check_state_e_usb;

//֡���ؽṹ�嶨��
typedef struct _return_frame_buf_usb
{
    UINT8 flag;                 //����֡����
    UINT8 ctl_code;             //������
    UINT8 cmd_type;             //��������
    UINT8 cmd_num;              //�������
    UINT8 cmd_content;          //��������
    UINT8 node_num;             //�ڵ��
    UINT8 reserve;             //����
    UINT8 err_code;            //������
    UINT8 state_len;            //��ѯ����ķ������ݳ���
    UINT8 *pstate_buff;         //��ѯ����ķ������ݻ����� //����ִ��������룬rep���ͷ�
    //timeseq_cmd_t *ptimeseq_cmd;//ָ��ʱ���������
} return_buf_t;

//֡��ʽ���ṹ�嶨��
typedef struct _check_frame_usb
{
	volatile UINT8 check_state; //֡���״̬
	volatile UINT16 frame_data_len; //֡����������
	volatile UINT8 check_sum; //֡������У���
	volatile UINT8 timeseq_cur_save_index; //��ǰʱ������λ��
	volatile UINT8 timeseq_save_index; //ʱ������λ��
	volatile UINT8 buff_index; //�������±�
	volatile UINT8 pre_frame_data; //��һ������
	//uint8 buff[PROTOCOL_FRAME_MAX_SIZE]; //֡������
	//uint8 state_buff[QUERY_CMD_STATE_DATA_MAX_SIZE]; //״̬���ݷ��ػ�����
	UINT8 *pbuff; //֡���������ж�֡���������Ⱥ����룬����ִ������ͷ�
	//	  uint8 *pstate_buff; //״̬���ݷ��ػ�����������ִ��������룬rep���ͷ�//û�б�Ҫ��rep����ֵ���ڴ˴�
	return_buf_t return_buff; //֡���ػ�����
} frame_check_t_usb;

#endif //commonres.h