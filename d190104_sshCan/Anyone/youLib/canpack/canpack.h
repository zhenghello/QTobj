#ifndef CANPACK_H
#define CANPACK_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>


class canPack : public QTableWidget
{
    Q_OBJECT
public:
    canPack(int argNum=0);
    void setCanPack_OrderArg(QStringList qsl);       // ���õ�Ԫ��_����Ͳ���
    void setCanPack_ctlCode(QString str);            // ���õ�Ԫ��_������
    void sendCanPack(void);                          // ���͵�Ԫ��
private:
    void table_init(int argNum);
    void composeStr(void);                          // �ϳɲ���

private slots:
    void table_pressed(const QModelIndex &index);   // ���²���
    void table_cellChanged(int row, int column);    // ��Ԫ��ı����

signals:
    void send_can_pack(QString);
};

#endif // CANPACK_H
