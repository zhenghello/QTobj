#ifndef USBGRAM_H
#define USBGRAM_H

#include "usbPack.h"

class usbGram : public usbPack
{
    Q_OBJECT
public:
    usbGram(int VID, int PID);
    void gramTx(QVector<char> pack);
    void gram2pack(QVector<char> gram);
protected slots:
    void pack2gram(QVector<char> pack);
signals:
    void gramRx(QVector<char>);
private:

};
int pack_checksum(char *pack,uint pack_size);
#endif // USERHID_H
