/******************************************************************************/
#ifndef __COMMONRES_H
#define __COMMONRES_H
/******************************************************************************/
#include "deftype.h"
//#include "timeseqres.h"
/******************************************************************************/
//Э��֡��󳤶ȶ���
#define PROTOCOL_FRAME_MAX_SIZE                (250u)
//����ACK֡��󳤶�
#define ACK_FRAME_MAX_SIZE                     (10u)
//����REP֡��󳤶�
#define REP_FRAME_MAX_SIZE                     (80u)
//����EVT֡��󳤶�
#define EVT_FRAME_MAX_SIZE                     (10u)
//��ѯ��������ݵ���󳤶�
#define QUERY_CMD_STATE_DATA_MAX_SIZE          (72)

//Э��֡��ʼ��
#define PROTOCOL_FRAME_START_CODE               (0xAA)
//Э��ֹ֡ͣ��
#define PROTOCOL_FRAME_STOP_CODE                (0x55)

//Э��֡��ʽ�±�
#define FRAME_START_INDEX                       (0u)  //��ʼ
#define FRAME_CONTROL_INDEX                     (1u)  //����
#define FRAME_DATALEN_INDEX                     (2u)  //���ݳ���
#define FRAME_COMMAND_INDEX                     (3u)  //������
#define FRAME_COMMAND_TYPE_INDEX                (3u)  //��������
#define FRAME_COMMAND_NUM_INDEX                 (4u)  //�������
#define FRAME_COMMAND_CONTENT_INDEX             (5u)  //��������
#define FRAME_COMMAND_PARAM_INDEX               (6u)  //�������

//���������
#define FRAME_CONTROL_CODE_COMMAND_REP          (0x00) //��վ�´�����֡(���REP)
#define FRAME_CONTROL_CODE_COMMAND_NO_REP       (0x40) //��վ�´�����֡(�����REP)
#define FRAME_CONTROL_CODE_TS_HEAD              (0x41) //ʱ�����ͷ
#define FRAME_CONTROL_CODE_TS_BODY              (0x42) //ʱ�������
#define FRAME_CONTROL_CODE_TS_TAIL              (0x43) //ʱ�����β
#define FRAME_CONTROL_CODE_REP                  (0xC0) //��վ��Ӧ֡REP
#define FRAME_CONTROL_CODE_ACK                  (0xD4) //��վӦ��֡ACK
#define FRAME_CONTROL_CODE_EVT                  (0xF8) //��վ�쳣֡EVT
#define FRAME_CONTROL_CODE_UPLOAD               (0xD8) //��վ�����ϴ�֡
#define UPLOAD_INF_FRAME_CONTROL_CODE          (0xC4) //֡������,��������������2�ֽڵĳ����ַ���

//������mask
#define CONTROL_CODE_TRANSDIR_MASK              (0x80)
#define CONTROL_CODE_RETURNFLAG_MASK            (0x40)
#define CONTROL_CODE_ABNORMALFLAG_MASK          (0x20)
#define CONTROL_CODE_FUNCTION_MASK              (0x1C)
#define CONTROL_CODE_IDENT_MASK                 (0x03)
//�����빦�ܱ���
#define CONTROL_CODE_FUNCTION_CMD               (0x00) //����
#define CONTROL_CODE_FUNCTION_ACK               (0x14) //Ӧ��
#define CONTROL_CODE_FUNCTION_UPLOAD            (0x18) //�����ϴ�
//������ʶ�����
#define CONTROL_CODE_IDENT_CMD                  (0x00) //����
#define CONTROL_CODE_IDENT_TS_HEAD              (0x01) //ʱ���ͷ
#define CONTROL_CODE_IDENT_TS_BODY              (0x02) //ʱ�����
#define CONTROL_CODE_IDENT_TS_TAIL              (0x03) //ʱ���β

//֡����Ҫ����REP
#define FRAME_NOT_RETURN_REP(x) (CONTROL_CODE_RETURNFLAG_MASK == ((x) & CONTROL_CODE_RETURNFLAG_MASK))
//֡��Ҫ����REP
#define FRAME_RETURN_REP(x)     (CONTROL_CODE_RETURNFLAG_MASK != ((x) & CONTROL_CODE_RETURNFLAG_MASK))

//����֡ת̬
typedef enum
{
    NONE_RETURN = 0x00, //����Ҫ����
    NEED_ACK,           //Ӧ��
    NEED_REP,           //��Ӧ
    NEED_EVT,           //�쳣
    NEED_UPLOAD,        //�����ϴ�
} return_frame_state_e;
//֡��ʽ���״̬����
typedef enum
{
    FRAME_CHECK_START = 0x00u, //��ʼ��
    FRAME_CHECK_CONTROL,       //������
    FRAME_CHECK_DATALEN,       //���ݳ���
    FRAME_CHECK_DATA,          //����
    FRAME_CHECK_CHECKSUM,      //У���
    FRAME_CHECK_STOP,          //ֹͣ��
    FRAME_CHECK_ERROR          //����
} check_state_e;


//֡���ؽṹ�嶨��
typedef struct _return_frame_buf
{
    uint8 flag       ;          //����֡����
    uint8 ctl_code   ;           //������
    uint8 cmd_type   ;           //��������
    uint8 cmd_num    ;           //�������
    uint8 cmd_content;           //��������
    uint8 node_num   ;           //�ڵ��
    uint16 reserve   ;          //����
    uint16 err_code  ;          //������
    uint8 state_len  ;          //��ѯ����ķ������ݳ���
    uint8 *pstate_buff;         //��ѯ����ķ������ݻ�����
//    timeseq_cmd_t *ptimeseq_cmd;//ָ��ʱ���������
} return_buf_t;
//���庯��ָ������
typedef int32 (*pfncmdproc)(cuint8 *ppara_buff, uint8 para_len, \
                            return_buf_t *preturn_buff);
//�����ṹ�嶨��
typedef struct
{
    uint8 cmd_code;       //������
    pfncmdproc fncmdproc; //ִ������
} cmd_proc_t;
//֡��ʽ���ṹ�嶨��
typedef struct _check_frame
{
    volatile uint8 check_state; //֡���״̬
    volatile uint8 frame_data_len; //֡����������
    volatile uint8 check_sum; //֡������У���
    volatile uint8 timeseq_cur_save_index; //��ǰʱ������λ��
    volatile uint8 timeseq_save_index; //ʱ������λ��
    volatile uint8 buff_index; //�������±�
    volatile uint8 pre_frame_data; //��һ������
    uint8 buff[PROTOCOL_FRAME_MAX_SIZE]; //֡������
    uint8 state_buff[QUERY_CMD_STATE_DATA_MAX_SIZE]; //״̬���ݷ��ػ�����
    return_buf_t return_buff; //֡���ػ�����
} frame_check_t;
/******************************************************************************/
#endif
/******************************************************************************/
