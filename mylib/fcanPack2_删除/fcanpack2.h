#ifndef FCANPACK2_H
#define FCANPACK2_H

#include <QWidget>
#include <QDebug>
#include <QList>
#include <QLineEdit>

namespace Ui {class FcanPack2;}

class FcanPack2 : public QWidget
{
    Q_OBJECT
public:
    explicit FcanPack2(int num=5, int table_max_hight=42, QWidget *parent = 0);
    ~FcanPack2();

public:
    void setCanPack(QStringList qsl);
    void sendCanPack(void);
    void getCanPack(QString *str, QVector<char> *qvr);
private slots:
    void table_pressed(const QModelIndex &index);
    void table_cellChanged(int row, int column);
signals:
    void send_can_pack(QString qstr);
private:
    Ui::FcanPack2 *ui;

    void composeStr(void);
    void table_init(int argNum);


};

#endif // FCANPACK2_H
