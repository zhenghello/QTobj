#ifndef ANYONE_H
#define ANYONE_H

#include <QMainWindow>
#include "fdebug.h"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
QT_CHARTS_USE_NAMESPACE

namespace Ui {class AnyOne;}

class AnyOne : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnyOne(QWidget *parent = 0);
    ~AnyOne();

private slots:
    void on_pushButton_end_clicked();
    void on_b1_clicked();
    void on_b2_clicked();
    void on_b3_clicked();
    void on_b4_clicked();
    void on_b5_clicked();
    void on_b6_clicked();

    void on_b101_clicked();
    void on_b102_clicked();
    void on_b103_clicked();

    void timeOutA();

private:
    Ui::AnyOne *ui;

    void dat_config_save(void);
    void dat_config_load(void);
};
QJsonObject treeWidgetItem2jsonObj(QTreeWidgetItem *itemp);

#endif // ANYONE_H
