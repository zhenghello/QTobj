#ifndef FOPTMOTOR_H
#define FOPTMOTOR_H

#include <QWidget>

#include "messageBoard.h"
#include "canpack.h"

namespace Ui {class FOptMotor;}

class FOptMotor : public QWidget
{
    Q_OBJECT

public:
    explicit FOptMotor(QWidget *parent = 0);
    ~FOptMotor();

private slots:
    void on_pushButton_init_clicked();
    void on_pushButton_p1_clicked();

    void on_pushButton_p2_clicked();

    void on_pushButton_s1_clicked();

    void on_pushButton_s2_clicked();

    void on_pushButtons3_clicked();

    void on_pushButton_s4_clicked();

    void on_pushButton_sample_vinit_clicked();

    void on_pushButton_sample_hinit_clicked();

    void on_pushButton_sample_vpos_clicked();

    void on_pushButton_sample_hpos_clicked();

signals:
    void send_can_pack(QString);    // ·¢ËÍcan°ü
private:
    Ui::FOptMotor *ui;
    canPack *cp = NULL;
};

#endif // FOPTMOTOR_H
