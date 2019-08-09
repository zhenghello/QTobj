#ifndef TIMESEQEXPLAIN_H
#define TIMESEQEXPLAIN_H

#include "ftreeDabeBase.h"

class timeSeqExplain : public FtreeDabeBase
{
public:
    timeSeqExplain(QWidget *parent = 0);

    bool protocolExplain(const QByteArray *qbyPack,QByteArray *qbyExplain,QByteArray *qbyAll);
    bool txtExplain(QString timeSeqName);
    QStringList getExplainFailKey();
private:
    QStringList explainFailKey; //解析失败的数据记录
};

#endif // TIMESEQEXPLAIN_H
