#ifndef MESSAGEBOARD_H
#define MESSAGEBOARD_H

#include <QWidget>

namespace Ui {class messageBoard;}

class messageBoard : public QWidget
{
    Q_OBJECT

public:
    explicit messageBoard(QWidget *parent = 0, QString titleName="messageBoard_noTitle");
    ~messageBoard();

private slots:
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::messageBoard *ui;
    void dat_config_save(void);
    void dat_config_load(void);
};

#endif // MESSAGEBOARD_H
