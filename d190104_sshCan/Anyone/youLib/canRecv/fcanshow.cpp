/* ����ļ��Ĺ����Ǹ���CAN����Ϣ��ʾ��ʽ��can�Ľ�����canExplain.c���ļ�������
 * �����ʾ��ʽ�й���ģʽ�ͷǹ���ģʽ����������˰������ؾͻ��Զ�����ǹ���ģʽ
*/

#include "fcanshow.h"
#include "ui_fcanshow.h"
FcanShow::FcanShow(QWidget *parent) :QWidget(parent),ui(new Ui::FcanShow)
{
    ui->setupUi(this);
    // ��ʼ������
    filter_init();
}

FcanShow::~FcanShow()
{
    delete ui;
}

// ���ع�������ͬʱ�����������
void FcanShow::setFilterEnable(bool enable)
{
    ui->frame_filter->setHidden(!enable);
    if(ui->frame_filter->isHidden())
    {
        clear();
    }
}
// �������
void FcanShow::clear()
{
    canNum=0;
    ui->label_recNum->setText(QString("%1").arg(canNum));   // ��ʾ����
    canDateList.clear();
    emit clearMyShow();     // �ط�������Ϣ
}
// ���������ݺ���                          **************************************************** begin
// ���˲�����ʼ��
void FcanShow::filter_init(void)
{
    canNum=0;
    ui->label_recNum->setText(QString("%1").arg(canNum));// ��ʾ����

    canDateList.clear();
    connect(ui->c_filterSource ,SIGNAL(clicked(bool)),ui->spinBox_filterSource ,SLOT(setDisabled(bool)));
    connect(ui->c_filterObject ,SIGNAL(clicked(bool)),ui->spinBox_filterObject ,SLOT(setDisabled(bool)));
    connect(ui->c_filterType   ,SIGNAL(clicked(bool)),ui->spinBox_filterType   ,SLOT(setDisabled(bool)));
    connect(ui->c_filterNumber ,SIGNAL(clicked(bool)),ui->spinBox_filterNumber ,SLOT(setDisabled(bool)));
    connect(ui->c_filterContent,SIGNAL(clicked(bool)),ui->spinBox_filterContent,SLOT(setDisabled(bool)));
    connect(ui->b_filterReload ,SIGNAL(clicked()),this,SLOT(filter_reload()));  // ���ذ���
}
// ���¹���CAN֡��Ϣ
void FcanShow::filter_reload(void)
{
    int i;
    emit clearMyShow();                         // ��������
    for(i=0;i<canDateList.size();i++)
    {
        emit needTranslate(canDateList.at(i));  // ���ͷ�������
    }
}
// ���can����
void FcanShow::append(const QStringList canDate)
{
    // ��can�����ղ�
    canDateList.append(canDate);
    canNum++;
    ui->label_recNum->setText(QString("%1").arg(canNum));// ��ʾ����
}
// ����ѡ��������������ж�������ַ����Ƿ�������ʾ
bool FcanShow::filter_show(const QStringList canDate)
{
    // 1.ֻ�п����������Ż��������,�����������ͻ���ǰ�˳�
    if(false == ui->frame_filter->isHidden())
    {
        // 2.���˿�����
        // 2.1.������
        if((canDate.at(3).toLower()=="00")||(canDate.at(3).toLower()=="40")||(canDate.at(3).toLower()=="41")||(canDate.at(3).toLower()=="42")||(canDate.at(3).toLower()=="43"))
        {
            if(ui->c_filterOredr->isChecked() == false)return false;
        }
        // 2.2.REP��
        else if(canDate.at(3).toLower()=="c0")
        {
            if(ui->c_filterRep->isChecked() == false)return false;
        }
        // 2.3.ACK��
        else if(canDate.at(3).toLower()=="d4")
        {
            if(ui->c_filterAck->isChecked() == false)return false;
        }
        // 2.4.evt��
        else if(canDate.at(3).toLower()=="f8")
        {
            if(ui->c_filterEvt->isChecked() == false)return false;
        }
        // 2.5.upload��
        else if(canDate.at(3).toLower()=="d8")
        {
            if(ui->c_filterUpload->isChecked() == false)return false;
        }
        // 2.6.���� ��
        else if(ui->c_filterUpload->isChecked() == false)return false;

        // 3.����ԴID
        if(ui->c_filterSource->isChecked())
        {
            if(canDate.at(0).toInt(nullptr,16) != ui->spinBox_filterSource->value()) return false;
        }
        // 3.����Ŀ��ID
        if(ui->c_filterObject->isChecked())
        {
            if(canDate.at(1).toInt(nullptr,16) != ui->spinBox_filterObject->value()) return false;
        }
        // 4.��������
        if(ui->c_filterType->isChecked())
        {
            if(canDate.at(5).toInt(nullptr,16) != ui->spinBox_filterType->value())   return false;
        }
        // 5.���˶���
        if(ui->c_filterNumber->isChecked())
        {
            if(canDate.at(6).toInt(nullptr,16) != ui->spinBox_filterNumber->value()) return false;
        }
        // 6.��������
        if(ui->c_filterContent->isChecked())
        {
            if(canDate.at(7).toInt(nullptr,16) != ui->spinBox_filterContent->value())return false;
        }
    }
    // ������ʾ
    return true;
}
// ���������ݺ���                          **************************************************** end
