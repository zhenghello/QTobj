#ifndef FSSHGUIAUTOACK_H
#define FSSHGUIAUTOACK_H

#include <QWidget>
#include <QSettings>
#include <QTimer>
namespace Ui {class FsshGuiAutoAck;}

class FsshGuiAutoAck : public QWidget
{
    Q_OBJECT

public:
    explicit FsshGuiAutoAck(QWidget *parent = 0,QString title = "noName");
    ~FsshGuiAutoAck();
signals:
    void autoAckSting(QString str); // 回复的自动应答信号
private slots:
    void dealRecMsg(QString str);       // 处理接收到的信息
    void sendAckMsg(void);              // 回复信息

private:
    Ui::FsshGuiAutoAck *ui;
    QTimer delayTimer;
    void dat_config_save(void);
    void dat_config_load(void);
};

#endif // FSSHGUIAUTOACK_H
