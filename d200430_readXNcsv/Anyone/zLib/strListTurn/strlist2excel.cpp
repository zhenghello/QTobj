#include "strlist2excel.h"
#include <QAxObject> // QT       += axcontainer      # use excel function
#include <QFile>
#include <QDebug>
// ����excel�ļ������ԭ�����ڣ��ͻᱻѯ��
void creatExcel(QString excelName)
{
    excelName.replace("/","\\");                // Ϊ������ļ���
    QAxObject *excelApp         = NULL;         // �����У�excelApp�趨Ϊexcel�ļ��Ĳ�������
    QAxObject *excelWorkBookS   = NULL;         // �� QAxObject �Ĺ���
    QAxObject *excelWorkBook    = NULL;        // ���Excel��������
    excelApp = new QAxObject("Excel.Application");
    excelApp->dynamicCall("SetVisible(bool)", false); //true ��ʾ�����ļ�ʱ�ɼ���false��ʾΪ���ɼ�
    excelWorkBookS = excelApp->querySubObject("WorkBooks");
    excelWorkBookS->dynamicCall("Add");
    //�������������������������������� ���ļ�·�����ļ� ����������������������������������������
    excelWorkBook = excelApp->querySubObject("ActiveWorkBook");
    excelWorkBook->dynamicCall("SaveAs(const QString&, int,QString,QString,bool,bool,int,int)",excelName);
    // ��ȡ�򿪵�excel�ļ������еĹ���sheet
    //QAxObject *excelSheets = excelWorkBook->querySubObject("WorkSheets");
    // һ��Ҫ�ǵ�close����Ȼϵͳ����������n��EXCEL.EXE����
    excelWorkBook->dynamicCall("Close(Boolean)",false);
    excelApp->dynamicCall("Quit(void)");
    if (excelApp)
    {
        delete excelApp;
        excelApp = NULL;
    }
}
// ��excel�ļ�תΪlist,���ݻᱣ�浽 listAll��
bool excel2ListAll(QString excelName,QList<QStringList> *listAll)
{
    excelName.replace("/","\\");                // Ϊ������ļ���
    // 1.�ж�excel�ļ����ڣ�û��excel��ֱ���˳�
    if(!QFile::exists(excelName))return false ;
    // 2.��ȡexcel
    QAxObject *excelApp         = NULL;         // �����У�excelApp�趨Ϊexcel�ļ��Ĳ�������
    QAxObject *excelWorkBookS   = NULL;         // �� QAxObject �Ĺ���
    QAxObject *excelWorkBook    = NULL;         // ���Excel��������
    excelApp = new QAxObject("Excel.Application");
    excelApp->dynamicCall("SetVisible(bool)", false);                           // true ��ʾ�����ļ�ʱ�ɼ���false��ʾΪ���ɼ�
    excelWorkBookS = excelApp->querySubObject("WorkBooks");                     // ��������
    excelWorkBook = excelWorkBookS->querySubObject("Open(QString&)", excelName);    // ���ļ�·�����ļ�
    QAxObject *excelSheets = excelWorkBook->querySubObject("WorkSheets");    // ��ȡ�򿪵�excel�ļ������еĹ���sheet
//  int excelSheetSize = excelSheets->property("Count").toInt();     // Excel�ļ��б�ĸ���
    //if(excelSheetSize<1);
    QAxObject *excelSheet = excelSheets->querySubObject("Item(int)",1);// ��ȡ��1��������
    // 3.�������������������������������������� ��ȡȫ������ ����������������������������������������ȡһ�������ڵ����ݣ�תΪ�б��ٰ�ÿ���б�תΪ�ַ���
    listAll->clear();   // 2020��5��3�գ��޸��˶�ȡ��ʽ�����ӿ�ݣ���û����֤��
    QAxObject * usedRange = excelSheet->querySubObject("UsedRange");    // ��ȡ��sheet�����ݷ�Χ���������Ϊ�����ݵľ�������
    if (NULL == usedRange || usedRange->isNull())return false ;         // excel ��������
    QVariant uesdData = usedRange->dynamicCall("Value");                // һ���Ի�ȡsheet�е���������
    QVariantList rowDataList = uesdData.toList();                       // ת��Ϊlist
    QAxObject * rowObj = usedRange->querySubObject("Rows");             // ��ȡ����
    int rowNum = rowObj->property("Count").toInt();
//    QAxObject * columnObj = usedRange->querySubObject("Columns");       // ��ȡ����
//    int columnNum = columnObj->property("Count").toInt();
    for(int i=0; i<rowNum; i++)
    {
        QStringList columnData =  rowDataList[i].toStringList();        // ��i�е�����
        listAll->append(columnData);
    }

    // һ��Ҫ�ǵ�close����Ȼϵͳ����������n��EXCEL.EXE����
    excelWorkBook->dynamicCall("Close()");
    excelApp->dynamicCall("Quit()");
    if (excelApp)
    {
        delete excelApp;
        excelApp = NULL;
    }
    // ������ͻ����excel���������ݣ���listAll��-------------------------------------
    return true;
}
// ��ListAllתΪ excel ,���ݻᱣ�浽 excel��
bool ListAll2excel(QString excelName,QList<QStringList> *listAll)
{
    // ������������ݶ���listAll����-------------------------------------
    // 3.�ж�excel�ļ����ڣ�û��excel�ʹ���
    if(!QFile::exists(excelName))
    {
        creatExcel( excelName);
    }
    // 4.���ݱ���
    QAxObject *excelApp         = NULL;         // �����У�excelApp�趨Ϊexcel�ļ��Ĳ�������
    QAxObject *excelWorkBookS   = NULL;         // �� QAxObject �Ĺ���
    QAxObject *excelWorkBook    = NULL;         // ���Excel��������
    excelApp = new QAxObject("Excel.Application");
    excelApp->dynamicCall("SetVisible(bool)", false); //true ��ʾ�����ļ�ʱ�ɼ��� false ��ʾΪ���ɼ�
    excelWorkBookS = excelApp->querySubObject("WorkBooks");

    excelWorkBook = excelWorkBookS->querySubObject("Open(QString&)", excelName);// ���ļ�·�����ļ�
    // ��ȡ�򿪵�excel�ļ������еĹ���sheet
    QAxObject *excelSheets = excelWorkBook->querySubObject("WorkSheets");

 //   int excelSheetSize = excelSheets->property("Count").toInt();// Excel�ļ��б�ĸ���:
    QAxObject *excelSheet = excelSheets->querySubObject("Item(int)", 1);// ��ȡ��1��������
    QAxObject *usedRange  = excelSheet->querySubObject("UsedRange");
    usedRange->dynamicCall("ClearContents()");
    // �������������������������� д������ ��������������������������
    for(int row=0; row<listAll->size();row++ )
    {
        for(int column=0; column<listAll->at(row).size();column++ )
        {
            QAxObject *cell = excelSheet->querySubObject("Cells(int,int)",row+1,column+1);// ��ȡ���е�λ��
            cell->setProperty("Value", listAll->at(row).at(column));        // д������, ��row�У���column��
        }
    }
    // һ��Ҫ�ǵ�close����Ȼϵͳ����������n��EXCEL.EXE����
    excelWorkBook->dynamicCall("Save()");   // ���excel���򿪣��ͻ�ѯ��
    excelWorkBook->dynamicCall("Close()");
    excelApp->dynamicCall("Quit()");
    if (excelApp)
    {
        delete excelApp;
        excelApp = NULL;
    }
    return true;
}


