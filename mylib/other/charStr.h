#ifndef CHARSTR
#define CHARSTR

#include <QList>
#include <QVector>

void lineStr2charList(QString str, QList<char> *list);
void lineStr2charVector(QString str, QVector<char> *vector);
void lineStr2charArray(QString str, QByteArray *array);

#endif // CHARSTR

