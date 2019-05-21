#include "fcom.h"
#include "ui_fcom.h"

Fcom::Fcom(QString filename,QWidget *parent) :QWidget(parent),ui(new Ui::Fcom)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()|Qt::Window);//����Ϊ���
    // ���ٶ��߳�
    qDebug() << "\r\n Fcom" << QThread::currentThreadId();
    myThread = new QThread();
    mySerial = new Fserial();
    mySerial->moveToThread(myThread);
    myThread->start();
    QObject::connect(this,SIGNAL(open_serial()),mySerial,SLOT(open_serial()));
    QObject::connect(this,SIGNAL(close_serial()),mySerial,SLOT(close_serial()));

    QObject::connect(this,SIGNAL(serial_write(QString,bool,bool)),mySerial,SLOT(serial_write(QString,bool,bool)),Qt::QueuedConnection);
    QObject::connect(mySerial,SIGNAL(serial_read_line(QByteArray)),this,SIGNAL(serial_read_line(QByteArray)),Qt::QueuedConnection);
    QObject::connect(mySerial,SIGNAL(serial_read_line(QByteArray)),this,SLOT(update_show(QByteArray)),Qt::QueuedConnection);
    QObject::connect(mySerial,SIGNAL(serial_isOpen(bool)),this,SLOT(updat_isOpen(bool)));//���´��ڿ���״̬
    isOpen = false;
    on_b_serial_up_info_clicked();              //���µ��Դ�����Ϣ
    //��ʱ���½��պͷ��͸���
    QObject::connect(&updateCount1s,SIGNAL(timeout()),this,SLOT(update_count()));//���´��ڿ���״̬
    updateCount1s.start(1000);
    //��չ������
    table_init();   //��ʼ����
    //��������
    config_filename = filename;  //�������ݵ��ļ���,Ĭ�����ã���紴���������ʱ��Ҫ�����������֡�
    dat_config_load(config_filename);            // ���õ���

    //����TABLE,x
    QObject::connect(&hideFrame,SIGNAL(timeout()),this,SLOT(hideMyTable()));//���´��ڿ���״̬
}
Fcom::~Fcom()
{
    qDebug()<<"\r\nFcom close ==================================";
    dat_config_save(config_filename);            // �������
    delete ui;
}
// *********************************************************************************** ���¼���ֵ
void Fcom::update_count(void)
{
    ui->label_rec_count->setText(QString::fromLocal8Bit("Rece=") + QString::number(mySerial->serial_rx_count,10));
    ui->label_sen_count->setText(QString::fromLocal8Bit("Send=") + QString::number(mySerial->serial_tx_count,10));
}
// *********************************************************************************** ��ʾ����
void Fcom::update_show(QByteArray qby)
{
    //qDebug() << "update_show" << QThread::currentThreadId();
    // 4.������ʾ
    if(ui->check_show_hex->isChecked())//HEX�򿪵����
    {
        for(int i=0;i<qby.length();i++)
        {
            char buffer[10];
            sprintf(buffer,"%02X ",(unsigned char)(qby.at(i)));
            serial_hex_show.append(buffer,3);   // ����hex����
        }
        ui->serial_show->setText(QString::fromLocal8Bit(serial_hex_show));//�õ��٣�ֱ�ӵ���
    }
    else
    {
        ui->serial_show->insertPlainText(QString::fromLocal8Bit(qby));// ����ʾ
    }
    ui->serial_show->moveCursor(QTextCursor::End);//�ƶ���굽���
    //emit serial_read_line(qby);
}


// *********************************************************************************** ������򿪴��ڡ�
void Fcom::on_serial_open_clicked()
{
    if(ui->serial_open->text() == QString::fromLocal8Bit("��"))
    {
        // ������->����
        mySerial->name = ui->serial_PortName->currentText();
        // ������
        mySerial->baudRate = ui->serial_BaudRate->currentText ().toInt ();
        // ����λ
        switch(ui->serial_DataBits->currentText ().toInt ())
        {
            case 5     :mySerial->dataBits = QSerialPort::Data5 ;  break;
            case 6     :mySerial->dataBits = QSerialPort::Data6 ;  break;
            case 7     :mySerial->dataBits = QSerialPort::Data7 ;  break;
            case 8     :mySerial->dataBits = QSerialPort::Data8 ;  break;
            default    :Fdebug::myDebug()->setText (QString::fromLocal8Bit("E:����λ����.")); break;
        }
        // ֹͣλ
        switch(ui->serial_StopBits->currentIndex ())
        {
            case 0     :mySerial->stopBits = QSerialPort::OneStop  ;     break;
            case 1     :mySerial->stopBits = QSerialPort::OneAndHalfStop;break;
            case 2     :mySerial->stopBits = QSerialPort::TwoStop  ;     break;
            default    :Fdebug::myDebug()->setText (QString::fromLocal8Bit("E:ֹͣλ����."));break;
        }
        // У��λ
        switch(ui->serial_Parity->currentIndex ())
        {
            case 0    :mySerial->parity = QSerialPort::NoParity  ; break;
            case 1    :mySerial->parity = QSerialPort::EvenParity; break;
            case 2    :mySerial->parity = QSerialPort::OddParity ; break;
            default   :Fdebug::myDebug()->setText (QString::fromLocal8Bit("E:У��λ����."));break;
        }
        //����������
        mySerial->flowControl = QSerialPort::NoFlowControl;
        //my_port.setReadBufferSize(1024*32);
        //�򿪴���
        emit open_serial();
    }
    else
    {
        //�رմ���
        emit close_serial();
    }
}
// *********************************************************************************** ���ڿ��ظ��£����ڲ������̣߳�ֻ��ͨ�������ź���ʵ�ֹ���
void Fcom::updat_isOpen(bool state)
{
    qDebug()<<"updat_isOpen"<<state;
    qDebug()<<"isOpen = "<<mySerial->isOpen;
    isOpen = state;
    if(isOpen)
    {
        Fdebug::myDebug()->setText(QString::fromLocal8Bit("�򿪴���"));
        ui->serial_open->setText(QString::fromLocal8Bit("�ر�"));         //���ð�ť����
        ui->serial_open->setStyleSheet("background-color: rgb(255, 0, 127);");//���ð�ť����ɫ
        //��ֹ��������ѡ��
        ui->serial_PortName->setEnabled (false);
        ui->serial_BaudRate->setEnabled (false);
        ui->serial_DataBits->setEnabled (false);
        ui->serial_Parity  ->setEnabled (false);
        ui->serial_StopBits->setEnabled (false);
    }
    else
    {
        Fdebug::myDebug()->setText(QString::fromLocal8Bit("���ڹر�"));
        ui->serial_open->setText(QString::fromLocal8Bit("��"));             //���ð�ť����
        ui->serial_open->setStyleSheet("background-color: rgb(85, 255, 127);");  //���ð�ť����ɫ
        //�����������ѡ��
        ui->serial_PortName->setEnabled (true);
        ui->serial_BaudRate->setEnabled (true);
        ui->serial_DataBits->setEnabled (true);
        ui->serial_Parity  ->setEnabled (true);
        ui->serial_StopBits->setEnabled (true);
    }
}
// *********************************************************************************** �����hex��ʾ��
void Fcom::on_check_show_hex_clicked()
{
    if(ui->check_show_hex->isChecked())
        ui->serial_show->setText(QString::fromLocal8Bit(serial_hex_show));
    else
        ui->serial_show->setText(QString::fromLocal8Bit(mySerial->serial_buf));
    ui->serial_show->moveCursor(QTextCursor::End);//�ƶ���굽���
}
// *********************************************************************************** ��������͡�
void Fcom::on_b_serial_send_clicked()
{
    emit serial_write(ui->serial_send->text(),ui->check_hex_send->isChecked(),ui->check_new_line);
}
// *    ���´��ڵ���Ϣ        **************************************** ��������ںš�
void Fcom::on_b_serial_up_info_clicked()
{
    //1.��ȡ������Ϣ 2.��ӡ���ô��ں�
    QSerialPortInfo info; //������Ϣ����
    ui->serial_PortName->clear();
    foreach (info, QSerialPortInfo::availablePorts())
    {
        ui->serial_PortName->addItem (info.portName()); //��Ӵ���һ��ѡ��
    }
}
// *********************************************************************************** ������������ڡ�
void Fcom::on_b_save_clicked()
{
    QDateTime curTime = QDateTime::currentDateTime();
    QString   str = "UART_"+curTime.toString("yy_MM_dd_hh_mm_ss")+".dat";//��ǰʱ��

    QString file_full = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("���洰������"),str);
    if(nullptr == file_full)return; //û��ѡ���ȡ��
    QFile       file(file_full); // �ļ�handle
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    file.write(ui->serial_show->toPlainText().toLocal8Bit());  //���洰������
    file.close();
}
// *********************************************************************************** ��������봰�ڡ�
void Fcom::on_b_load_clicked()
{
    QString file_full = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("���봰������"),"./config");
    if(nullptr == file_full)return; //û��ѡ���ȡ��
    QFile       file(file_full); // �ļ�handle
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))return;    // �򲻿���ʧ��
    while(!file.atEnd())
    {   // ��������
        QByteArray line = file.readLine();
        emit mySerial->serial_read_line(QString::fromUtf8(line).toLocal8Bit());
    }
    file.close();
}
// *********************************************************************************** ����������ʾ��
void Fcom::on_b_serial_clear_clicked()
{
    serial_hex_show.clear();
    mySerial->clear_count();
    ui->serial_show->clear();
    ui->label_sen_count->setText(QString::fromLocal8Bit("����="));
    ui->label_rec_count->setText(QString::fromLocal8Bit("����="));
}
// *********************************************************************************** �����������չ��
void Fcom::on_check_hide_clicked(bool checked)
{
    if(checked)
    {
        ui->frame_hide->hide();
        hideFrame.start(10);//����ִ��
        //Fcom::resize(Fcom::width(),hu-ht);
    }
    else
    {
        int ht = ui->frame_hide->height();
        int hu = Fcom::height();
        Fcom::resize(Fcom::width(),hu+ht);
        ui->frame_hide->show();
    }
}
// *********************************************************************************** �������ʱ���͡�
QTimer timeSend2,timeSend3;

void Fcom::on_b_serial_send2_clicked()//���������2��
{
        emit serial_write(ui->serial_send2->text(),ui->check_hex_send->isChecked(),ui->check_new_line);
}
void Fcom::on_b_serial_send3_clicked()//���������3��-����������������
{
    static int ch=0;
    if(ch)
    {
        emit serial_write(ui->serial_send3->text(),ui->check_hex_send->isChecked(),ui->check_new_line);
        ch=0;
    }
    else
    {
        emit serial_write(ui->serial_send2->text(),ui->check_hex_send->isChecked(),ui->check_new_line);
        ch=1;
    }

}
void Fcom::on_check_timeSend2_clicked(bool checked)
{
    if(checked)
    {
        timeSend2.start(ui->spinBox_timeSend2->value());
        connect(&timeSend2,SIGNAL(timeout()),this,SLOT(on_b_serial_send2_clicked()));//��ʱ2�������Ͱ�ť
    }
    else
    {
        timeSend2.stop();
    }
}
void Fcom::on_check_timeSend3_clicked(bool checked)
{
    if(checked)
    {
        timeSend3.start(ui->spinBox_timeSend3->value());
        connect(&timeSend3,SIGNAL(timeout()),this,SLOT(on_b_serial_send3_clicked()));//��ʱ3�������Ͱ�ť
    }
    else
    {
        timeSend3.stop();
    }
}
// *********************************************************************************** �������С��ȡ�
void Fcom::on_check_minWidth_clicked(bool checked)
{
    if(checked)
    {
        setMaximumWidth(350);
    }
    else
    {
        setMaximumWidth(700);
    }
}
// ���صĺ�������
void Fcom::hideMyTable(void)
{
    hideFrame.stop();
    Fcom::resize(Fcom::width(),Fcom::height()-ui->table->height());
}

// ���⿪�ţ��жϴ��ڴ�
bool Fcom::comIsOpen(void)
{
    if(ui->serial_open->text() == QString::fromLocal8Bit("��"))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
// ���⿪�ţ���ղ�����
void Fcom::clear_serial()
{
    on_b_serial_clear_clicked();
}
// *********************************************************************************** ÿ����½��պͷ��͵����ݸ���
// ******************************************** excel ���� ******************************************** begin
// ��ʼ��һ���µ�excel��
void Fcom::table_init(void)
{
    ui->table->clear ();
    //������
    ui->table->setRowCount (4);               // ����
    QStringList t;
    t.append (QString::fromLocal8Bit("Send"));
    t.append (QString::fromLocal8Bit("T"));
    t.append (QString::fromLocal8Bit("+"));
    t.append (QString::fromLocal8Bit("-"));
    ui->table->setHorizontalHeaderLabels(t);  // �б���
    //�����п�
    ui->table->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->table->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui->table->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    ui->table->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
    ui->table->setColumnWidth(1,20);//�޸��п�
    ui->table->setColumnWidth(2,20);
    ui->table->setColumnWidth(3,20);
    ui->table->setFont(QFont("����",8));// �޸�tabled�������
    ui->table->verticalHeader()->setFont(QFont("����",6)); // �޸���ͷ�������
    //��������
    if(ui->table->rowCount()<5)ui->table->setRowCount (5);
    //�����и�
    ui->table->verticalHeader()->setDefaultSectionSize(20);//����Ĭ���и�
    //������������
    QObject::connect(ui->table,SIGNAL(pressed(QModelIndex)),this,SLOT(table_pressed(QModelIndex)));
}
//��갴��,excel�Ķ���
void Fcom::table_pressed(const QModelIndex &index)
{
    int cur_row     =index.row();    //��ǰ��
    int cur_column  =index.column(); //��ǰ��
    QTableWidgetItem *qtab;
    // 0.ֻ���һ���������
    if( qApp->mouseButtons() != Qt::RightButton)return ;

    switch(cur_column)
    {
        case 0://������
            qtab=ui->table->item(cur_row,0);//��ȡ��Ԫ��ָ��
            if ( qtab == NULL || (qtab->text() == "") )
            {
                Fdebug::myDebug()->setText(QString::fromLocal8Bit("��Ԫ��û������."));
                return;
            }
            //1.1.��������Ϊ��������
            emit serial_write(qtab->text(),ui->check_hex_send->isChecked(),ui->check_new_line);
        break;
        case 1://������
            qtab=ui->table->item(cur_row,0);//��ȡ��Ԫ��ָ��
            if ( qtab == NULL || (qtab->text() == "") )
            {
                Fdebug::myDebug()->setText(QString::fromLocal8Bit("��Ԫ��û������."));
                return;
            }
            //1.1.��������Ϊ��������
            emit mySerial->serial_read_line(qtab->text().toLocal8Bit());
        break;
        case 2://�����
            //�Ϸ�������
            ui->table->insertRow(cur_row);
            ui->table->selectRow (cur_row+1); //ѡ������
        break;
        case 3://ɾ����
            if(ui->table->rowCount () > 10)
            {//������ >10 ��ɾ����
                ui->table->removeRow (cur_row);
            }
            //����������ݾͿ�����
            else
            {
                ui->table->setItem(cur_row,0,nullptr);
                ui->table->setItem(cur_row,1,nullptr);
            }
        break;
        default:break;
    }
}
// ******************************************** excel ���� ******************************************** end
// ******************************************** ���ݱ��� ******************************************** begin
//�������ܣ���������
//���������
//���������
//��ע��
void Fcom::dat_config_save(QString filename)
{
    // ��������
    QSettings save_dat(filename,QSettings::IniFormat);
    save_dat.clear();
    save_dat.setIniCodec("GB2312");//֧������
    // ------------------------ �������õı���
    save_dat.setValue ("serial_BaudRate"        ,ui->serial_BaudRate->currentIndex ());
    save_dat.setValue ("serial_DataBits"        ,ui->serial_DataBits->currentIndex ());
    save_dat.setValue ("serial_Parity"          ,ui->serial_Parity->currentIndex   ());
    save_dat.setValue ("serial_PortName"        ,ui->serial_PortName->currentText  ());
    save_dat.setValue ("serial_StopBits"        ,ui->serial_StopBits->currentIndex ());
    save_dat.setValue ("serial_isOpen"          ,isOpen                              );
    // ------------------------ �������õı���
    save_dat.setValue ("check_hex_send"         ,ui->check_hex_send->isChecked()     );
    save_dat.setValue ("check_new_line"         ,ui->check_new_line->isChecked()     );
    save_dat.setValue ("check_show_hex"         ,ui->check_show_hex->isChecked()     );
    save_dat.setValue ("serial_send"            ,ui->serial_send->text()             );
    save_dat.setValue ("check_hide"             ,ui->check_hide->isChecked()         );
    save_dat.setValue ("timeSend2"              ,ui->spinBox_timeSend2->value()      );
    save_dat.setValue ("timeSend3"              ,ui->spinBox_timeSend3->value()      );

    // talbe �ı���
    QStringList strlist;
    for(int i=0;i<ui->table->rowCount();i++)
    {
        QTableWidgetItem *qtab;
        qtab=ui->table->item(i,0);//��ȡ��Ԫ��ָ��
        if ( qtab == NULL || (qtab->text() == "") )
        {
            strlist.append(" ");
        }
        else strlist.append(qtab->text());
    }
    save_dat.setValue ("table_rowCount"        ,ui->table->rowCount()           );
    save_dat.setValue ("table_strlist"         ,strlist                         );
    save_dat.setValue ("check_minWidth"        ,ui->check_minWidth->isChecked() );
}
//�������ܣ���������
//���������
//���������
//��ע��
void Fcom::dat_config_load(QString filename)
{
    QSettings save_dat(filename,QSettings::IniFormat);
    save_dat.setIniCodec("GB2312");//֧������
    //�ж��ļ�����
    if(save_dat.contains("serial_isOpen")==false)
    {
        Fdebug::myDebug()->setChar("no file!");
        return;
    }
    Fdebug::myDebug()->setChar("have file!");
    // ------------------------ �������õĶ�ȡ
    ui->serial_BaudRate->setCurrentIndex (save_dat.value("serial_BaudRate").toInt());
    ui->serial_DataBits->setCurrentIndex (save_dat.value("serial_DataBits").toInt());
    ui->serial_Parity  ->setCurrentIndex (save_dat.value("serial_Parity"  ).toInt());
    ui->serial_StopBits->setCurrentIndex (save_dat.value("serial_StopBits").toInt());
    //�����ַ������ϴεĴ���
    int i = ui->serial_PortName->findText (save_dat.value ("serial_PortName").toString());
    if( 0 <= i )
    {
        ui->serial_PortName->setCurrentIndex (i);
        if( save_dat.value ("serial_isOpen").toBool())
        {   //�ϴδ��ڴ򿪣����Ҳ��
            on_serial_open_clicked();
        }
    }
    // ------------------------ �������õĶ�ȡ
    ui->spinBox_timeSend2->setValue(save_dat.value("timeSend2").toInt());
    ui->spinBox_timeSend3->setValue(save_dat.value("timeSend3").toInt());
    ui->check_hex_send->setChecked(save_dat.value("check_hex_send").toBool());
    ui->check_new_line->setChecked(save_dat.value("check_new_line").toBool());
    ui->check_show_hex->setChecked(save_dat.value("check_show_hex").toBool());
    ui->check_hide->setChecked(save_dat.value("check_hide").toBool());
    ui->serial_send->setText(save_dat.value("serial_send").toString());
    on_check_hide_clicked(ui->check_hide->isChecked());

    ui->check_minWidth->setChecked(save_dat.value("check_minWidth").toBool());
    on_check_minWidth_clicked(ui->check_minWidth->isChecked());

    // talbe �ĵ���
    if(save_dat.contains("table_rowCount")==false)return;
    ui->table->setRowCount(save_dat.value("table_rowCount").toInt()    );
    if(save_dat.contains("table_strlist")==false)return;
    QStringList strlist;
    strlist = save_dat.value("table_strlist").toStringList();
    for(int i=0;i<ui->table->rowCount();i++)
    {
        QTableWidgetItem *qtab = new QTableWidgetItem();
        qtab->setText(strlist.at(i));
        ui->table->setItem(i,0,qtab);
    }
}
// ******************************************** ���ݱ��� ******************************************** end




