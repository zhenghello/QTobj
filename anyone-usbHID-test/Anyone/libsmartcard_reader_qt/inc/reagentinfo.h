#pragma once

#include <QObject>
#include <QString>
#include <QtCore/qglobal.h>

#ifdef LIBREAGENTPUBLIC_LIB
    #define REAGENTPUBLIC_EXPORT Q_DECL_EXPORT
#else
    #define REAGENTPUBLIC_EXPORT Q_DECL_IMPORT
#endif

namespace reagentpublic
{
    // �Լ���Ϣ
    class REAGENTPUBLIC_EXPORT ReagentInfo
    {
        public:
            ReagentInfo();
            ~ReagentInfo();

        public:

            // RF���汾,��ʽ��1,2,3,4...��ѡ��
            QString VER;

            // OEM-ID(���磺DM��A��B��K�ȣ�,��������������AB��BK֮�����λ����Ϊ����ĸ�Ĳ������ˣ�
            QString OEMID;

            //-----------��������õ���ֵ- �Լ���Ϣ----------------------------------------------
            // �Լ�����V1��֮ǰ��type��
            QString reagentId_v1;

            // OEM����V1����λ��֮ǰagent��ǰ��λ��
            QString oem_v1;

            // ��������ϢV1����λ��֮ǰagent�ĺ���λ��
            QString agent_v1;

            // �Լ�����V4 - 3Bytes��V4֮����´��ţ�
            QString reagentId_v4;

            // OEM����V4 - 2Bytes��V4֮����´��ţ�
            QString oem_v4;

            // ��������ϢV4 - 1.5Bytes��3*4bit����V4֮����´��ţ�
            QString agent_v4;

            // �Լ�����(mL)
            int package;

            // ��������
            QString productDate;

            // δ��ƿ��Ч��
            QString expDays;

            // ��ƿ��Ч��
            QString openExpDays;

            // ��Ӧ���루�������գ�
            QString barcode_v1;

            // ���ô�����ֻ�е���parseRF������MF����EF02���������ݲ��ܹ������õ���
            int timesUsed;

            //-----------��������õ���ֵ- ��������----------------------------------------------

            // �������Ƿ��Զ���
            int agentUserDefined_v4;

            // ����ʹ�ô���
            int allowableTimes_v4;

            // ����
            QString lotNo;

            //-----------��������õ���ֵ- ��������Ϣ----------------------------------------------

            // �Ƿ����ô�������Ϣ
            int agentEnabled_v4;

            // �Ƿ��д������Զ��������
            int hasAgentUserDefined_v4;

            //-----------��������õ���ֵ- ��������----------------------------------------------

            // ʹ��ʱ��  yyyy/MM/dd HH:mm:ss
            QString DatetimeUsed_v4;

            // ����ʱ��  yyyy/MM/dd HH:mm:ss
            QString DatetimeChecked_v4;


            //-----------���������ֵ(���ݽ�����ʱ����㣩----------------------------------------------
            // �Լ�����
            QString name;

            // �Լ�����(mL)
            int volume;

            // δ��ƿ��Ч��
            int expDate;

            // ��ƿ��Ч��
            int openDate;
            int openExpDate;

            // ������Ч�ڣ�qMin(δ��ƿ��Ч�ڣ���ƿ��Ч�ڣ���
            int finalExpDate;

			//CRP�����ϴʹ��
			QString CRPVersion;
    };

    // EF �ļ��������ƣ�
    class REAGENTPUBLIC_EXPORT EF: public QObject
    {
        public:
            EF();
            ~EF();

            // �ļ��̱�ʶ
            QString P2;

            // �ļ�����
            int dataLen;

            // �ļ����ݣ������ƣ�
            unsigned char * Data;
    };

    // DF �ļ�
    class REAGENTPUBLIC_EXPORT DF: public QObject
    {
        public:
            DF();
            ~DF();

            // �ļ��̱�ʶ
            QString P2;

            // EF�ļ��б�
            QList<EF *> EFList;
    };

    const QString MF_Declaration_P2 = "02";

    // MF �ļ�
    class REAGENTPUBLIC_EXPORT MF: public QObject
    {
        public:
            // ver:����RF���İ汾,��ʽ��1,2,3,4...
            MF(QString ver);
            ~MF();

            // RF���汾,��ʽ��1,2,3,4...
            QString VER;

            // OEM-ID(���磺DM��A��B��K�ȣ�,��������������AB��BK֮�����λ����Ϊ����ĸ�Ĳ������ˣ�
            QString OEMID;

            // MF�����EF�ļ��б�������DF�µ��ļ���
            QList<EF *> EFList;

            // DF�ļ��б�
            QList<DF *> DFList;
    };
}
