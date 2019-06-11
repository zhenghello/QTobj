/*
    ���������������һ��CAN������
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
void canPack::table_init(int argNum)
{
    int columnNum = 10 + argNum; // ���� canͷ+ͷβ��ʶ��+У��λ+3���̶�������
    int i;
    // ����ȫ���ĸ߶ȺͿ��
    setMaximumHeight(CELL_HEIGHT * 3+2);
    setMaximumWidth(CELL_WIDTH*(argNum+10)+2);

    clear ();
    //��������
    setRowCount(2);               // ����
    setColumnCount(columnNum);  // ����
    //�����б�ͷ���б�ͷ����
    horizontalHeader()->hide();
    verticalHeader()->hide();
    horizontalHeader()->setDefaultSectionSize(CELL_WIDTH);   //����Ĭ���п�
    verticalHeader()->setDefaultSectionSize(CELL_HEIGHT);    //����Ĭ���и�
    //��������->����һ�ѵ�Ԫ��
    QTableWidgetItem *qtab;
    for(i=0;i<columnNum;i++)
    {
        //  �������
        qtab = new QTableWidgetItem();
        qtab->setText("00");
        setItem(0,i,qtab);
    }
    // ����ͷ����IDѡ��Ĭ��Ϊ��
    qtab = item(0,0);
    qtab->setBackgroundColor(QColor(255, 50, 255));//��ɫ
    qtab->setText("");
    qtab = item(0,1);
    qtab->setBackgroundColor(QColor(255, 50, 255));//��ɫ
    qtab->setText("");

    // ����ͷβ�ͳ��Ȳ��ɱ༭
    qtab = item(0,2);
    qtab->setBackgroundColor(QColor(200, 200, 100));//��ɫ
    qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//���ɱ༭
    qtab->setText("aa");
    //setItem(0,0,qtab);

    qtab = item(0,columnNum-1);
    qtab->setBackgroundColor(QColor(200, 200, 100));//��ɫ
    qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//���ɱ༭
    qtab->setText("55");
    //setItem(0,columnNum-1,qtab);

    qtab = item(0,4);   // ����
    qtab->setBackgroundColor(QColor(200, 200, 200));//��ɫ
    qtab->setFlags(qtab->flags() & (~Qt::ItemIsEditable));//���ɱ༭
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
//��갴��,excel�Ķ���
void canPack::table_pressed(const QModelIndex &index)
{
    int cur_row     =index.row();    //��ǰ��
    int cur_column  =index.column(); //��ǰ��
    QTableWidgetItem *qtab;
    // 0.ֻ���һ���������
    //if( qApp->mouseButtons() != Qt::RightButton)return ;
    if(1!=cur_row || 0!=cur_column)return;//ֻ�еڶ��в�����

    //����ǰ�Ⱥϳ�
    composeStr();
    //��ȡ��Ԫ��
    qtab=item(cur_row,cur_column);
    if ( qtab == NULL || (qtab->text() == "") )return; //�հ��˳�
    QString str = qtab->text();

    emit send_can_pack( str);//��������
}
// �ϳ��ַ���
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
        if ( qtab == NULL || (qtab->text() == "") )continue;
        else count++;
    }
    qtab = takeItem(0,2+2);
    qtab->setText(QString("%1").arg(count,2,16,QChar('0')));
    setItem(0,2+2,qtab);
    // ����У���
    int sumcheck=0;
    for(i=1+2;i<columnCount()-2;i++)
    {
        qtab = item(0,i);
        if ( qtab == NULL || (qtab->text() == "") )continue;
        else sumcheck += qtab->text().toInt(nullptr,16);
    }
    qtab = takeItem(0,columnCount()-2);
    qtab->setText(QString("%1").arg(sumcheck%256,2,16,QChar('0')));
    setItem(0,columnCount()-2,qtab);
    // �ϳ��ַ���
    QString str;
    for(i=0;i<columnCount();i++)
    {
        qtab = item(0,i);
        if ( qtab == NULL || (qtab->text() == "") )continue;
        str += qtab->text() + " ";
    }
    qtab = takeItem(1,0);
    qtab->setText(str);
    setItem(1,0,qtab);
    QObject::connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(table_cellChanged(int,int)));
}
// ��Ԫ��ı�
void canPack::table_cellChanged(int row, int column)
{
    column = 0;
    if(row!=0)return;//ֻ�����һ��
    //qDebug()<<column;
    composeStr();//���ºϳ�
}
// �ⲿ���� ---------------------------------------------------------------------------------------
// ���õ�Ԫ�����-ֻ��������Ͳ�����
void canPack::setCanPack_OrderArg(QStringList qsl)
{
    if(qsl.size()!=columnCount()-5-2)return;//�����������˳�
    int i;
    QTableWidgetItem *qtab;//
    for(i=0;i<qsl.size();i++)
    {
        qtab = takeItem(0,i+3+2);
        qtab->setText(qsl.at(i));
        setItem(0,i+3+2,qtab);
    }
}
// ���õ�Ԫ�����-ֻ���ÿ�����
void canPack::setCanPack_ctlCode(QString str)
{
    QTableWidgetItem *qtab;
    qtab = takeItem(0,1+2);
    qtab->setText(str);
    setItem(0,1,qtab);
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
// ���赥Ԫ�����
void canPack::setCanPack_ArgNum(int argNum)
{
    int i;
    QTableWidgetItem *qtab;
    // ɾ��ԭ�еĿռ�
    for(i=0;i<columnCount();i++)
    {
        qtab = item(0,i);
        removeCellWidget(0,i);
        delete qtab;

    }
    qtab = item(1,0);
    removeCellWidget(1,0);
    delete qtab;

    // ���³�ʼ��
    table_init(argNum);
}
