#ifndef FTREEDABEBASE_H
#define FTREEDABEBASE_H

#include <QWidget>
#include <QTreeWidget>

#include <excel2treeWidget.h>
#include <dat2treeWidget.h>
#include <strlist2treeWidget.h>

namespace Ui {class FtreeDabeBase;}

class FtreeDabeBase : public QWidget
{
    Q_OBJECT

public:
    // titleName 是数据库和标题的名字，这个名字决定它自己的导入文件名字
    explicit FtreeDabeBase(QWidget *parent = 0, QString titleName = "FtreeDabeBaseNoTitleName");
    ~FtreeDabeBase();
    QTreeWidgetItem* findKey(int column,QString key);                // 查找全部匹配
    QTreeWidgetItem* findKey(int column,QString key,int chileCount); // 查找指定列子对象个数的匹配
    QTreeWidget *mainTree(void);                                     // 返回树的地址
public slots:
    void hideFrame(bool hide);  // 隐藏框
private slots:
    void on_bExcelFileName_clicked();
    void on_bDatFileName_clicked();
    void on_bOpenExcel_clicked();
    void on_bOpenDat_clicked();

    void on_bLoadExcel_clicked();
    void on_bSaveExcel_clicked();
    void on_bLoadDAt_clicked();
    void on_bSaveDat_clicked();

    void pressTree(QTreeWidgetItem *item, int column);    // tree按键触发
    void fixWidth(bool fix);                              // 固定宽度

    void on_bDbFileName_clicked();
    void on_bFindKey_clicked();



signals:
    void sendMsgTree(QTreeWidgetItem *tree,int column); // tree按下发送消息，column是对应的列，tree是这个item的指针
    void reloadExcelFinish();                           // 重新载入Excel完成
private:
    Ui::FtreeDabeBase *ui;
//    QString configName;      // 配置文件名
    QString treeDatName;         // tree的保存文件名

    void treeWidgetInit(void);
    void treeDecChose(void);
    void treeAddChose(void);
    void treeAddChildChose(void);

    void dat_config_save(void);
    void dat_config_load(void);
};

#endif // FTREEDABEBASE_H
