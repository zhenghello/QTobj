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
    // titleName �����ݿ�ͱ�������֣�������־������Լ��ĵ����ļ�����
    explicit FtreeDabeBase(QWidget *parent = 0, QString titleName = "FtreeDabeBaseNoTitleName");
    ~FtreeDabeBase();
    QTreeWidgetItem* findKey(int column,QString key);                // ����ȫ��ƥ��
    QTreeWidgetItem* findKey(int column,QString key,int chileCount); // ����ָ�����Ӷ��������ƥ��
    QTreeWidget *mainTree(void);                                     // �������ĵ�ַ
public slots:
    void hideFrame(bool hide);  // ���ؿ�
private slots:
    void on_bExcelFileName_clicked();
    void on_bDatFileName_clicked();
    void on_bOpenExcel_clicked();
    void on_bOpenDat_clicked();

    void on_bLoadExcel_clicked();
    void on_bSaveExcel_clicked();
    void on_bLoadDAt_clicked();
    void on_bSaveDat_clicked();

    void pressTree(QTreeWidgetItem *item, int column);    // tree��������
    void fixWidth(bool fix);                              // �̶����

    void on_bDbFileName_clicked();
    void on_bFindKey_clicked();



signals:
    void sendMsgTree(QTreeWidgetItem *tree,int column); // tree���·�����Ϣ��column�Ƕ�Ӧ���У�tree�����item��ָ��
    void reloadExcelFinish();                           // ��������Excel���
private:
    Ui::FtreeDabeBase *ui;
//    QString configName;      // �����ļ���
    QString treeDatName;         // tree�ı����ļ���

    void treeWidgetInit(void);
    void treeDecChose(void);
    void treeAddChose(void);
    void treeAddChildChose(void);

    void dat_config_save(void);
    void dat_config_load(void);
};

#endif // FTREEDABEBASE_H
