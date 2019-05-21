#include "fcom.h"
#include "ui_fcom.h"

Fcom::Fcom(QString filename,QWidget *parent) :QWidget(parent),ui(new Ui::Fcom)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()|Qt::Window);//设置为外框
    // 开辟多线程
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
    QObject::connect(mySerial,SIGNAL(serial_isOpen(bool)),this,SLOT(updat_isOpen(bool)));//更新串口开关状态
    isOpen = false;
    on_b_serial_up_info_clicked();              //更新电脑串口信息
    //定时更新接收和发送个数
    QObject::connect(&updateCount1s,SIGNAL(timeout()),this,SLOT(update_count()));//更新串口开关状态
    updateCount1s.start(1000);
    //扩展命令区
    table_init();   //初始化表
    //导入配置
    config_filename = filename;  //保存数据的文件名,默认配置，外界创建多个串口时，要重新配置名字。
    dat_config_load(config_filename);            // 配置导入

    //隐藏TABLE,x
    QObject::connect(&hideFrame,SIGNAL(timeout()),this,SLOT(hideMyTable()));//更新串口开关状态
}
Fcom::~Fcom()
{
    qDebug()<<"\r\nFcom close ==================================";
    dat_config_save(config_filename);            // 配置输出
    delete ui;
}
// *********************************************************************************** 更新计数值
void Fcom::update_count(void)
{
    ui->label_rec_count->setText(QString::fromLocal8Bit("Rece=") + QString::number(mySerial->serial_rx_count,10));
    ui->label_sen_count->setText(QString::fromLocal8Bit("Send=") + QString::number(mySerial->serial_tx_count,10));
}
// *********************************************************************************** 显示更新
void Fcom::update_show(QByteArray qby)
{
    //qDebug() << "update_show" << QThread::currentThreadId();
    // 4.更新显示
    if(ui->check_show_hex->isChecked())//HEX打开的情况
    {
        for(int i=0;i<qby.length();i++)
        {
            char buffer[10];
            sprintf(buffer,"%02X ",(unsigned char)(qby.at(i)));
            serial_hex_show.append(buffer,3);   // 保存hex数据
        }
        ui->serial_show->setText(QString::fromLocal8Bit(serial_hex_show));//用得少，直接调用
    }
    else
    {
        ui->serial_show->insertPlainText(QString::fromLocal8Bit(qby));// 添补显示
    }
    ui->serial_show->moveCursor(QTextCursor::End);//移动光标到最后
    //emit serial_read_line(qby);
}


// *********************************************************************************** 点击“打开串口”
void Fcom::on_serial_open_clicked()
{
    if(ui->serial_open->text() == QString::fromLocal8Bit("打开"))
    {
        // 串口名->设置
        mySerial->name = ui->serial_PortName->currentText();
        // 波特率
        mySerial->baudRate = ui->serial_BaudRate->currentText ().toInt ();
        // 数据位
        switch(ui->serial_DataBits->currentText ().toInt ())
        {
            case 5     :mySerial->dataBits = QSerialPort::Data5 ;  break;
            case 6     :mySerial->dataBits = QSerialPort::Data6 ;  break;
            case 7     :mySerial->dataBits = QSerialPort::Data7 ;  break;
            case 8     :mySerial->dataBits = QSerialPort::Data8 ;  break;
            default    :Fdebug::myDebug()->setText (QString::fromLocal8Bit("E:数据位错误.")); break;
        }
        // 停止位
        switch(ui->serial_StopBits->currentIndex ())
        {
            case 0     :mySerial->stopBits = QSerialPort::OneStop  ;     break;
            case 1     :mySerial->stopBits = QSerialPort::OneAndHalfStop;break;
            case 2     :mySerial->stopBits = QSerialPort::TwoStop  ;     break;
            default    :Fdebug::myDebug()->setText (QString::fromLocal8Bit("E:停止位错误."));break;
        }
        // 校验位
        switch(ui->serial_Parity->currentIndex ())
        {
            case 0    :mySerial->parity = QSerialPort::NoParity  ; break;
            case 1    :mySerial->parity = QSerialPort::EvenParity; break;
            case 2    :mySerial->parity = QSerialPort::OddParity ; break;
            default   :Fdebug::myDebug()->setText (QString::fromLocal8Bit("E:校验位错误."));break;
        }
        //设置流控制
        mySerial->flowControl = QSerialPort::NoFlowControl;
        //my_port.setReadBufferSize(1024*32);
        //打开串口
        emit open_serial();
    }
    else
    {
        //关闭串口
        emit close_serial();
    }
}
// *********************************************************************************** 串口开关更新，由于采用子线程，只能通过发送信号来实现功能
void Fcom::updat_isOpen(bool state)
{
    qDebug()<<"updat_isOpen"<<state;
    qDebug()<<"isOpen = "<<mySerial->isOpen;
    isOpen = state;
    if(isOpen)
    {
        Fdebug::myDebug()->setText(QString::fromLocal8Bit("打开串口"));
        ui->serial_open->setText(QString::fromLocal8Bit("关闭"));         //设置按钮内容
        ui->serial_open->setStyleSheet("background-color: rgb(255, 0, 127);");//设置按钮背景色
        //禁止操作串口选项
        ui->serial_PortName->setEnabled (false);
        ui->serial_BaudRate->setEnabled (false);
        ui->serial_DataBits->setEnabled (false);
        ui->serial_Parity  ->setEnabled (false);
        ui->serial_StopBits->setEnabled (false);
    }
    else
    {
        Fdebug::myDebug()->setText(QString::fromLocal8Bit("串口关闭"));
        ui->serial_open->setText(QString::fromLocal8Bit("打开"));             //设置按钮内容
        ui->serial_open->setStyleSheet("background-color: rgb(85, 255, 127);");  //设置按钮背景色
        //允许操作串口选项
        ui->serial_PortName->setEnabled (true);
        ui->serial_BaudRate->setEnabled (true);
        ui->serial_DataBits->setEnabled (true);
        ui->serial_Parity  ->setEnabled (true);
        ui->serial_StopBits->setEnabled (true);
    }
}
// *********************************************************************************** 点击“hex显示”
void Fcom::on_check_show_hex_clicked()
{
    if(ui->check_show_hex->isChecked())
        ui->serial_show->setText(QString::fromLocal8Bit(serial_hex_show));
    else
        ui->serial_show->setText(QString::fromLocal8Bit(mySerial->serial_buf));
    ui->serial_show->moveCursor(QTextCursor::End);//移动光标到最后
}
// *********************************************************************************** 点击“发送”
void Fcom::on_b_serial_send_clicked()
{
    emit serial_write(ui->serial_send->text(),ui->check_hex_send->isChecked(),ui->check_new_line);
}
// *    更新串口的信息        **************************************** 点击“串口号”
void Fcom::on_b_serial_up_info_clicked()
{
    //1.读取串口信息 2.打印可用串口号
    QSerialPortInfo info; //串口信息类型
    ui->serial_PortName->clear();
    foreach (info, QSerialPortInfo::availablePorts())
    {
        ui->serial_PortName->addItem (info.portName()); //添加串口一个选项
    }
}
// *********************************************************************************** 点击“导出窗口”
void Fcom::on_b_save_clicked()
{
    QDateTime curTime = QDateTime::currentDateTime();
    QString   str = "UART_"+curTime.toString("yy_MM_dd_hh_mm_ss")+".dat";//当前时间

    QString file_full = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("保存窗口内容"),str);
    if(nullptr == file_full)return; //没有选择就取消
    QFile       file(file_full); // 文件handle
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    file.write(ui->serial_show->toPlainText().toLocal8Bit());  //保存窗口内容
    file.close();
}
// *********************************************************************************** 点击“导入窗口”
void Fcom::on_b_load_clicked()
{
    QString file_full = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("导入窗口内容"),"./config");
    if(nullptr == file_full)return; //没有选择就取消
    QFile       file(file_full); // 文件handle
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))return;    // 打不开就失败
    while(!file.atEnd())
    {   // 读行数据
        QByteArray line = file.readLine();
        emit mySerial->serial_read_line(QString::fromUtf8(line).toLocal8Bit());
    }
    file.close();
}
// *********************************************************************************** 点击“清空显示”
void Fcom::on_b_serial_clear_clicked()
{
    serial_hex_show.clear();
    mySerial->clear_count();
    ui->serial_show->clear();
    ui->label_sen_count->setText(QString::fromLocal8Bit("发送="));
    ui->label_rec_count->setText(QString::fromLocal8Bit("接收="));
}
// *********************************************************************************** 点击“隐藏扩展”
void Fcom::on_check_hide_clicked(bool checked)
{
    if(checked)
    {
        ui->frame_hide->hide();
        hideFrame.start(10);//待会执行
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
// *********************************************************************************** 点击“定时发送”
QTimer timeSend2,timeSend3;

void Fcom::on_b_serial_send2_clicked()//点击“发送2”
{
        emit serial_write(ui->serial_send2->text(),ui->check_hex_send->isChecked(),ui->check_new_line);
}
void Fcom::on_b_serial_send3_clicked()//点击“发送3”-可以两个轮流发送
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
        connect(&timeSend2,SIGNAL(timeout()),this,SLOT(on_b_serial_send2_clicked()));//定时2触发发送按钮
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
        connect(&timeSend3,SIGNAL(timeout()),this,SLOT(on_b_serial_send3_clicked()));//定时3触发发送按钮
    }
    else
    {
        timeSend3.stop();
    }
}
// *********************************************************************************** 点击“最小宽度”
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
// 隐藏的后续触发
void Fcom::hideMyTable(void)
{
    hideFrame.stop();
    Fcom::resize(Fcom::width(),Fcom::height()-ui->table->height());
}

// 对外开放，判断串口打开
bool Fcom::comIsOpen(void)
{
    if(ui->serial_open->text() == QString::fromLocal8Bit("打开"))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
// 对外开放，清空操作。
void Fcom::clear_serial()
{
    on_b_serial_clear_clicked();
}
// *********************************************************************************** 每秒更新接收和发送的数据个数
// ******************************************** excel 操作 ******************************************** begin
// 初始化一个新的excel表
void Fcom::table_init(void)
{
    ui->table->clear ();
    //设置列
    ui->table->setRowCount (4);               // 列数
    QStringList t;
    t.append (QString::fromLocal8Bit("Send"));
    t.append (QString::fromLocal8Bit("T"));
    t.append (QString::fromLocal8Bit("+"));
    t.append (QString::fromLocal8Bit("-"));
    ui->table->setHorizontalHeaderLabels(t);  // 列标题
    //设置列宽
    ui->table->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->table->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui->table->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    ui->table->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
    ui->table->setColumnWidth(1,20);//修改行宽
    ui->table->setColumnWidth(2,20);
    ui->table->setColumnWidth(3,20);
    ui->table->setFont(QFont("宋体",8));// 修改tabled的字体号
    ui->table->verticalHeader()->setFont(QFont("宋体",6)); // 修改行头的字体号
    //设置行数
    if(ui->table->rowCount()<5)ui->table->setRowCount (5);
    //设置行高
    ui->table->verticalHeader()->setDefaultSectionSize(20);//设置默认行高
    //关联触发按键
    QObject::connect(ui->table,SIGNAL(pressed(QModelIndex)),this,SLOT(table_pressed(QModelIndex)));
}
//鼠标按下,excel的动作
void Fcom::table_pressed(const QModelIndex &index)
{
    int cur_row     =index.row();    //当前行
    int cur_column  =index.column(); //当前列
    QTableWidgetItem *qtab;
    // 0.只有右击触发有用
    if( qApp->mouseButtons() != Qt::RightButton)return ;

    switch(cur_column)
    {
        case 0://缓存列
            qtab=ui->table->item(cur_row,0);//获取单元格指针
            if ( qtab == NULL || (qtab->text() == "") )
            {
                Fdebug::myDebug()->setText(QString::fromLocal8Bit("单元格没有内容."));
                return;
            }
            //1.1.把数据作为参数发送
            emit serial_write(qtab->text(),ui->check_hex_send->isChecked(),ui->check_new_line);
        break;
        case 1://测试列
            qtab=ui->table->item(cur_row,0);//获取单元格指针
            if ( qtab == NULL || (qtab->text() == "") )
            {
                Fdebug::myDebug()->setText(QString::fromLocal8Bit("单元格没有内容."));
                return;
            }
            //1.1.把数据作为参数测试
            emit mySerial->serial_read_line(qtab->text().toLocal8Bit());
        break;
        case 2://添加行
            //上方插入行
            ui->table->insertRow(cur_row);
            ui->table->selectRow (cur_row+1); //选择到新行
        break;
        case 3://删除行
            if(ui->table->rowCount () > 10)
            {//总行数 >10 就删除行
                ui->table->removeRow (cur_row);
            }
            //否则清除内容就可以了
            else
            {
                ui->table->setItem(cur_row,0,nullptr);
                ui->table->setItem(cur_row,1,nullptr);
            }
        break;
        default:break;
    }
}
// ******************************************** excel 操作 ******************************************** end
// ******************************************** 数据保存 ******************************************** begin
//函数功能：导出配置
//输入参数：
//输出参数：
//备注：
void Fcom::dat_config_save(QString filename)
{
    // 保存配置
    QSettings save_dat(filename,QSettings::IniFormat);
    save_dat.clear();
    save_dat.setIniCodec("GB2312");//支持中文
    // ------------------------ 串口配置的保存
    save_dat.setValue ("serial_BaudRate"        ,ui->serial_BaudRate->currentIndex ());
    save_dat.setValue ("serial_DataBits"        ,ui->serial_DataBits->currentIndex ());
    save_dat.setValue ("serial_Parity"          ,ui->serial_Parity->currentIndex   ());
    save_dat.setValue ("serial_PortName"        ,ui->serial_PortName->currentText  ());
    save_dat.setValue ("serial_StopBits"        ,ui->serial_StopBits->currentIndex ());
    save_dat.setValue ("serial_isOpen"          ,isOpen                              );
    // ------------------------ 其他配置的保存
    save_dat.setValue ("check_hex_send"         ,ui->check_hex_send->isChecked()     );
    save_dat.setValue ("check_new_line"         ,ui->check_new_line->isChecked()     );
    save_dat.setValue ("check_show_hex"         ,ui->check_show_hex->isChecked()     );
    save_dat.setValue ("serial_send"            ,ui->serial_send->text()             );
    save_dat.setValue ("check_hide"             ,ui->check_hide->isChecked()         );
    save_dat.setValue ("timeSend2"              ,ui->spinBox_timeSend2->value()      );
    save_dat.setValue ("timeSend3"              ,ui->spinBox_timeSend3->value()      );

    // talbe 的保存
    QStringList strlist;
    for(int i=0;i<ui->table->rowCount();i++)
    {
        QTableWidgetItem *qtab;
        qtab=ui->table->item(i,0);//获取单元格指针
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
//函数功能：导入配置
//输入参数：
//输出参数：
//备注：
void Fcom::dat_config_load(QString filename)
{
    QSettings save_dat(filename,QSettings::IniFormat);
    save_dat.setIniCodec("GB2312");//支持中文
    //判断文件存在
    if(save_dat.contains("serial_isOpen")==false)
    {
        Fdebug::myDebug()->setChar("no file!");
        return;
    }
    Fdebug::myDebug()->setChar("have file!");
    // ------------------------ 串口配置的读取
    ui->serial_BaudRate->setCurrentIndex (save_dat.value("serial_BaudRate").toInt());
    ui->serial_DataBits->setCurrentIndex (save_dat.value("serial_DataBits").toInt());
    ui->serial_Parity  ->setCurrentIndex (save_dat.value("serial_Parity"  ).toInt());
    ui->serial_StopBits->setCurrentIndex (save_dat.value("serial_StopBits").toInt());
    //根据字符串打开上次的串口
    int i = ui->serial_PortName->findText (save_dat.value ("serial_PortName").toString());
    if( 0 <= i )
    {
        ui->serial_PortName->setCurrentIndex (i);
        if( save_dat.value ("serial_isOpen").toBool())
        {   //上次串口打开，这次也打开
            on_serial_open_clicked();
        }
    }
    // ------------------------ 其他配置的读取
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

    // talbe 的导出
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
// ******************************************** 数据保存 ******************************************** end




