#ifndef STRLIST2DAT_H
#define STRLIST2DAT_H

#include <QString>

#define DAT_CELL_MINIWIDTH 60   // ����dat�У�%%�Ĺ̶����
// ����ת��Ԫ��
bool ListAll2dat(QString datName,QList<QStringList> *listAll);
bool dat2ListAll(QString datName,QList<QStringList> *listAll);

#endif // STRLIST2DAT_H
