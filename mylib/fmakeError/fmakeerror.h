#ifndef FMAKEERROR_H
#define FMAKEERROR_H

#include <QWidget>
#include "canpack.h"
namespace Ui {class FmakeError;}

class FmakeError : public QWidget
{
    Q_OBJECT

public:
    explicit FmakeError(QWidget *parent = 0);
    ~FmakeError();

private slots:
    void errCodeChange(void);
    void idCodeChange(void);

    void on_pushButton_send_clicked();

private:
    Ui::FmakeError *ui;
    canPack *idPack;
    canPack *errPack;

};

#endif // FMAKEERROR_H
