#ifndef ANYONE_H
#define ANYONE_H

#include <QMainWindow>
#include<QSettings>
#include "fdebug.h"
#include "excel2mat.h"

namespace Ui {class AnyOne;}

class AnyOne : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnyOne(QWidget *parent = 0);
    ~AnyOne();

private slots:

    // 结束按键
    void on_pushButton_end_clicked();

    void on_b101_clicked();
    void on_b103_clicked();

    void tableWidgetInit(void);
    void tableWidgetItemPressed(QTableWidgetItem *item);
    void tableWidgetAddOne(QTableWidget *table, int row, QString str="");

    void on_lineEditFind_textChanged(const QString &arg1);

private:
    QString mstr_new;
    QString mstr_del;
    QString mstr_up;
    QString mstr_dowm;
    QString mstr_uup;

    Excel2Mat *emd;
    Fdebug *mydebug;
    QString exePath;                // 可执行文件的路径,即使在其他位置启动，也可以正常找到配置文件

    void dat_config_save(void);
    void dat_config_load(void);
    Ui::AnyOne *ui;
};

#endif // ANYONE_H
