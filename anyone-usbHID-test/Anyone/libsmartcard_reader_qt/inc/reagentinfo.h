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
    // 试剂信息
    class REAGENTPUBLIC_EXPORT ReagentInfo
    {
        public:
            ReagentInfo();
            ~ReagentInfo();

        public:

            // RF卡版本,格式：1,2,3,4...，选用
            QString VER;

            // OEM-ID(例如：DM、A、B、K等）,后续可能是类似AB，BK之类的两位（因为单字母的不够用了）
            QString OEMID;

            //-----------解析条码得到的值- 试剂信息----------------------------------------------
            // 试剂类型V1（之前的type）
            QString reagentId_v1;

            // OEM代号V1（两位，之前agent的前两位）
            QString oem_v1;

            // 代理商信息V1（两位，之前agent的后两位）
            QString agent_v1;

            // 试剂类型V4 - 3Bytes（V4之后的新代号）
            QString reagentId_v4;

            // OEM代号V4 - 2Bytes（V4之后的新代号）
            QString oem_v4;

            // 代理商信息V4 - 1.5Bytes（3*4bit）（V4之后的新代号）
            QString agent_v4;

            // 试剂总量(mL)
            int package;

            // 生产日期
            QString productDate;

            // 未开瓶有效期
            QString expDays;

            // 开瓶有效期
            QString openExpDays;

            // 对应条码（仅条码封闭）
            QString barcode_v1;

            // 已用次数（只有调用parseRF，按照MF传递EF02及其他内容才能够解析得到）
            int timesUsed;

            //-----------解析条码得到的值- 生产批号----------------------------------------------

            // 代理商是否自定义
            int agentUserDefined_v4;

            // 允许使用次数
            int allowableTimes_v4;

            // 批号
            QString lotNo;

            //-----------解析条码得到的值- 代理商信息----------------------------------------------

            // 是否启用代理商信息
            int agentEnabled_v4;

            // 是否有代理商自定义的内容
            int hasAgentUserDefined_v4;

            //-----------解析条码得到的值- 过程数据----------------------------------------------

            // 使用时间  yyyy/MM/dd HH:mm:ss
            QString DatetimeUsed_v4;

            // 检验时间  yyyy/MM/dd HH:mm:ss
            QString DatetimeChecked_v4;


            //-----------解析后换算的值(根据解析的时间计算）----------------------------------------------
            // 试剂名称
            QString name;

            // 试剂余量(mL)
            int volume;

            // 未开瓶有效期
            int expDate;

            // 开瓶有效期
            int openDate;
            int openExpDate;

            // 最终有效期（qMin(未开瓶有效期，开瓶有效期））
            int finalExpDate;

			//CRP深度清洗使用
			QString CRPVersion;
    };

    // EF 文件（二进制）
    class REAGENTPUBLIC_EXPORT EF: public QObject
    {
        public:
            EF();
            ~EF();

            // 文件短标识
            QString P2;

            // 文件长度
            int dataLen;

            // 文件内容（二进制）
            unsigned char * Data;
    };

    // DF 文件
    class REAGENTPUBLIC_EXPORT DF: public QObject
    {
        public:
            DF();
            ~DF();

            // 文件短标识
            QString P2;

            // EF文件列表
            QList<EF *> EFList;
    };

    const QString MF_Declaration_P2 = "02";

    // MF 文件
    class REAGENTPUBLIC_EXPORT MF: public QObject
    {
        public:
            // ver:传递RF卡的版本,格式：1,2,3,4...
            MF(QString ver);
            ~MF();

            // RF卡版本,格式：1,2,3,4...
            QString VER;

            // OEM-ID(例如：DM、A、B、K等）,后续可能是类似AB，BK之类的两位（因为单字母的不够用了）
            QString OEMID;

            // MF下面的EF文件列表（不包括DF下的文件）
            QList<EF *> EFList;

            // DF文件列表
            QList<DF *> DFList;
    };
}
