/*
    ���������������һ��CAN������
    ���can�����ݿ����Զ��ϳɡ�
    �����ⲿ���ò���
*/
#include "canpack.h"

#define CELL_HEIGHT 20 //��Ԫ��߶�
#define CELL_WIDTH  25 //��Ԫ����

canPack::canPack(QWidget *parent, int argNum):QTableWidget(parent)
{
    // �б��ʼ��
    setParent(parent);
    table_init(argNum);
}
#include"QDebug"
// table���ʼ��
void canPack::table_init(int argNum)
{
    int columnNum = 10 + argNum; // ���� canͷ+ͷβ��ʶ��+У��λ+3���̶�������
    int i;
    // ����ȫ���ĸ߶ȺͿ��
    setMaximumHeight(CELL_HEIGHT * 3+2);
    setMaximumWidth(CELL_WIDTH*(argNum+10+2)+2);

    clear ();
    //��������
    setRowCount(2);               // ����
    setColumnCount(columnNum);    // ����
    //�����б�ͷ���б�ͷ����
    horizontalHeader()->hide();
    verticalHeader()->hide();
    horizontalHeader()->setDefaultSectionSize(CELL_WIDTH);   //����Ĭ���п�
    verticalHeader()->setDefaultSectionSize(CELL_HEIGHT);    //����Ĭ���и�
    //��������->����һ�ѵ�Ԫ��
    QTableWidgetItem *qtab;
    for(i=0;i<8;i++)
    {
        //  �������
        qtab = new QTableWidgetItem();
        qtab->setText("00");
        setItem(0,i,qtab);
    }
    for(;i<columnNum;i++)
    {
        //  �������
        qtab = new QTableWidgetItem();
        qtab->setText("");
        setItem(0,i,qtab);
    }
    // ����ͷ����IDѡ��Ĭ��Ϊ��
    qtab = item(0,0);
    qtab->setBackgroundColor(QColor(255, 50, 255));//��ɫ
    qtab->setText("");
    qtab = item(0,1);
    qtab->setBackgroundColor(QColor(255, 50, 255));//��ɫ
    qtab->setText("");
    // ����ǰ���п��
    setColumnWidth(0,CELL_WIDTH*2);
    setColumnWidth(1,CELL_WIDTH*2);

    // ����ͷβ�ͳ��Ȳ��ɱ༭
    qtab = item(0,2);
    qtab->setBackgroundColor(QColor(200, 200, 100));//��ɫ
    qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//���ɱ༭
    qtab->setText("aa");

    qtab = item(0,columnNum-1);
    qtab->setBackgroundColor(QColor(200, 200, 100));//��ɫ
    qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//���ɱ༭
    qtab->setText("55");

    qtab = item(0,columnNum-2);// У��
    qtab->setBackgroundColor(QColor(100, 200, 200));//��ɫ
    qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//���ɱ༭

    qtab = item(0,4);   // ����
    qtab->setBackgroundColor(QColor(200, 200, 200));//��ɫ
    //qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//���ɱ༭
    qtab->setText(QString::number(argNum+3));
    //setItem(0,2,qtab);

    // ����������ɫ
    qtab = item(0,5);
    qtab->setBackgroundColor(QColor(255, 85, 127));//��ɫ
    qtab = item(0,6);
    qtab->setBackgroundColor(QColor(255, 85, 127));//��ɫ
    qtab = item(0,7);
    qtab->setBackgroundColor(QColor(255, 85, 127));//��ɫ

    //�ϲ��ڶ���
    setSpan(1,0,1,columnCount());
    qtab = new QTableWidgetItem();
    qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//���ɱ༭
    qtab->setText(" ");
    qtab->setTextAlignment(Qt::AlignCenter);    //����
    qtab->setBackgroundColor(QColor(85,255,255));//��ɫ
    setItem(1,0,qtab);
    //������������
    QObject::connect(this,SIGNAL(pressed(QModelIndex)),this,SLOT(table_pressed(QModelIndex)));
    QObject::connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(table_cellChanged(int,int)));
    composeStr(); //�ϳ�
}
#include <QtWidgets/QApplication>
//��갴��,excel�Ķ�������Ѻϳɺ�����ݷ����źų���
void canPack::table_pressed(const QModelIndex &index)
{
    int cur_row     =index.row();    //��ǰ��
    int cur_column  =index.column(); //��ǰ��
    QTableWidgetItem *qtab;
    // 0.ֻ���һ���������

    if( qApp->mouseButtons() != Qt::RightButton)return ;
    if(1!=cur_row || 0!=cur_column)return;//ֻ�еڶ��в�����

    //����ǰ�Ⱥϳ�
    composeStr();
    //��ȡ��Ԫ��
    qtab=item(cur_row,cur_column);
    if ( qtab == NULL || (qtab->text() == "") )return; //�հ��˳�
    QString str = qtab->text();

    emit send_can_pack( str);//��������
}
// �ϳ��ַ��������ݵ�һ�У�����������ȣ��ϳɵڶ������ݣ��հ׸�ᱻ���ԣ�
void canPack::composeStr(void)
{
    QObject::disconnect(this,SIGNAL(cellChanged(int,int)),this,SLOT(table_cellChanged(int,int)));
    int i;
    QTableWidgetItem *qtab;
    // �������
    int count=0;
    for(i=3+2;i<columnCount()-2;i++)
    {
        qtab = item(0,i);
        if ( qtab == NULL || (qtab->text().trimmed() == "") )continue;
        else count++;
    }
    qtab = item(0,2+2);
    qtab->setText(QString("%1").arg(count,2,16,QChar('0')));
    // ����У���
    int sumcheck=0;
    for(i=1+2;i<columnCount()-2;i++)
    {
        qtab = item(0,i);
        if ( qtab == NULL || (qtab->text() == "") )continue;
        else sumcheck += qtab->text().toInt(nullptr,16);
    }
    qtab = item(0,columnCount()-2);
    qtab->setText(QString("%1").arg(sumcheck%256,2,16,QChar('0')));
    // �ϳ��ַ���
    QString str;
    for(i=0;i<columnCount();i++)
    {
        qtab = item(0,i);
        if ( qtab == NULL || (qtab->text() == "") )continue;
        str += qtab->text() + " ";
    }
    qtab = item(1,0);
    qtab->setText(str);
    QObject::connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(table_cellChanged(int,int)));
}
// ��Ԫ��ı䣬�ڲ��������Զ��ϳ�����
void canPack::table_cellChanged(int row, int column)
{
    if(column){;}
    if(row!=0)return;//ֻ�����һ��
    //qDebug()<<column;
    composeStr();//���ºϳ�
}
// �ⲿ���� ---------------------------------------------------------------------------------------
// ���õ�Ԫ�����-ֻ��������Ͳ������������������ͻᲹ��
void canPack::setCanPack_OrderArg(QStringList qsl)
{
    int i;
    QTableWidgetItem *qtab;
    // ������������Ͳ��հף����̫���ͻᱻ�ض�
    for(i=0;i<columnCount()-7;i++)
    {
        qtab = item(0,i+3+2);
        if(qsl.size()<=i)//������Χ���հ�
        {
           qtab->setText("");
        }
        else
        {
            qtab->setText(qsl.at(i));
        }
    }
}
// ���õ�Ԫ�����-ֻ���ÿ�����
void canPack::setCanPack_ctlCode(QString str)
{
    QTableWidgetItem *qtab;
    qtab = item(0,1+2);
    qtab->setText(str);
}
// ���õ�Ԫ�����-ֻ���÷����շ�ID
void canPack::setCanPack_IdCode(QString str1,QString str2)
{
    QTableWidgetItem *qtab;
    qtab = item(0,0);
    qtab->setText(str1);
    qtab = item(0,1);
    qtab->setText(str2);
}
// ���͵�Ԫ�����
void canPack::sendCanPack(void)
{
    QTableWidgetItem *qtab;
    //��ȡ��Ԫ��
    qtab=item(1,0);
    if ( qtab == NULL || (qtab->text() == "") )return; //�հ��˳�
    QString str = qtab->text();
    emit send_can_pack(str);//��������
}


