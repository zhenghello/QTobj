#ifndef FTREE2EXCEL_H
#define FTREE2EXCEL_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

#include <QTextBrowser>
#include <QLineEdit>
#include <QDateTime>
#include <QTreeWidget>
#include <QHeaderView>

#include <QDebug>
#include <QLabel>
#include <QFileDialog>
#include <QProcess>

#include <QApplication>
#include <tree2excel.h>
class FtreeExcel : public QWidget
{
    Q_OBJECT
public:
    explicit FtreeExcel(QString jsonName = ".\\config\\test.json" , bool hideKey = true , QWidget *parent = 0);
    ~FtreeExcel();
    void    hide_key(bool hide);
    QString getJsonName();
    const QTreeWidgetItem* findKeyWord(int column, QString key);

private:
    QTreeWidget      *tree;

    QVBoxLayout     *verticalLayout;
    QFrame          *frame_hide;
    QGridLayout     *gridLayout;
    QLineEdit       *lineEdit;

    QPushButton     *button[12];
    void dat_config_save(QString filename);
    void dat_config_load(QString filename);
    void treeDecChose();
    void treeAddChose();
    void treeAddChild();

private slots:
    void click_button00();
    void click_button01();
    void click_button02();
    void click_button03();
    void click_button04();
    void click_button05();
    void click_button06();
    void click_button07();
    void click_button08();
    void click_button09();
    void click_button10();
    void click_button11();
    void press_tree(QModelIndex index);
};

#endif // FtreeExcel_H
