#ifndef FHID_H
#define FHID_H

#include <QWidget>
#include "usbPack.h"
#include "fdebug.h"
#include "charStr.h"

namespace Ui {class Fhid;}

class Fhid : public QWidget
{
    Q_OBJECT

public:
    explicit Fhid(QWidget *parent = 0);
    ~Fhid();
    bool openUsb(void);
    void closeUsb();
    void writeUsb();

private slots:
    void readUsb(QVector<char> R);
    void hideMyTable(void);
    void update_count(void);
    void table_init(void);
    void table_pressed(const QModelIndex &index);

    void on_b_open_clicked();
    void on_b_hid_send_clicked();
    void on_b_hid_clear_clicked();
    void on_check_minWidth_clicked(bool checked);
    void on_check_hide_clicked(bool checked);



private:
    Ui::Fhid *ui;
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void dat_config_save(QString filename);
    void dat_config_load(QString filename);
    QString         config_filename;       //  保存文件名
    QTimer          updateCount1s;
    QTimer          hideFrame;
    uint            rxCount;              // 接收次数
    uint            txCount;
};

#endif // FHID_H
