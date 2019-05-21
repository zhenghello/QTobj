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
    void autoAckSting(QString str); // �ظ����Զ�Ӧ���ź�
private slots:
    void dealRecMsg(QString str);       // ������յ�����Ϣ
    void sendAckMsg(void);              // �ظ���Ϣ

private:
    Ui::FsshGuiAutoAck *ui;
    QTimer delayTimer;
    void dat_config_save(void);
    void dat_config_load(void);
};

#endif // FSSHGUIAUTOACK_H
