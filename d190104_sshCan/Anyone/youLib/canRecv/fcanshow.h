#ifndef FCANSHOW_H
#define FCANSHOW_H

#include <QWidget>
namespace Ui {class FcanShow;}

class FcanShow : public QWidget
{
    Q_OBJECT

public:
    explicit FcanShow(QWidget *parent = 0);
    ~FcanShow();
    // �������
    QList< QStringList > canDateList;// ��Ϣ���ַ�������
    uint                 canNum;
public slots:
    // ���⺯��
    void setFilterEnable(bool enable);              // ���ع�����
    bool filter_show(const QStringList canDate);    // ������ʾ����
    void append(const QStringList canDate);         // ����can����
    void clear();                                   // �������

signals:
    void clearMyShow();                             // ���������Ļ
    void needTranslate(const QStringList strList);  // ��Ҫ������ź�
private slots:
    void filter_reload(void);                       // ��������

private:
    Ui::FcanShow *ui;
    void filter_init(void);
};

#endif // FCANSHOW_H
