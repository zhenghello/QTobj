
#include "fhid.h"
#include "ui_fhid.h"

usbPack  *lpcHid;    // hid设备
Fdebug    *uniRx;  // 透传接收框

Fdebug    *sFrame; //
Fdebug    *sPack ; //
Fdebug    *sGram ; //

Fhid::Fhid(QWidget *parent) :QWidget(parent),ui(new Ui::Fhid)
{
    ui->setupUi(this);
    rxCount=0;
    txCount=0;
    config_filename =".\\config\\hid_config.dat";
    // 初始化Table
    table_init();

    // 导入信息
    dat_config_load(config_filename);
    // hid设备初始化
    lpcHid = new usbPack(ui->spinBox_VID->value(),ui->spinBox_PID->value());
    // 接收框
    uniRx = new Fdebug(QString::fromLocal8Bit("接收透传框"),false,this);
    ui->verticalLayout_show->addWidget(uniRx,1);

    showFrame = new Fdebug(QString::fromLocal8Bit("Frame框"),false,this);
    ui->verticalLayout_frame->insertWidget(0,sFrame);
    showPack  = new Fdebug(QString::fromLocal8Bit("Pack框"),false,this);
    ui->verticalLayout_Pack->insertWidget(0,sPack);
    showFrame = new Fdebug(QString::fromLocal8Bit("Gram框"),false,this);
    ui->verticalLayout_Gram->insertWidget(0,sGram);

    //定时更新接收和发送个数
    QObject::connect(&updateCount1s,SIGNAL(timeout()),this,SLOT(update_count()));//更新串口开关状态
    updateCount1s.start(1000);
    // 关联信号 -> 读取hid
    connect(lpcHid,SIGNAL(receive_frame(QVector<char> )),this,SLOT(readUsb(QVector<char> )));
    // 关联信号 -> 隐藏框
    QObject::connect(&hideFrame,SIGNAL(timeout()),this,SLOT(hideMyTable()));//更新串口框

}

Fhid::~Fhid()
{
    dat_config_save(config_filename);
    delete ui;
}
// ******************************************** excel 操作 ******************************************** begin
// 初始化一个新的excel表
void Fhid::table_init(void)
{
    ui->table->clear ();
    //设置列
    ui->table->setRowCount (4);               // 列数
    QStringList t;
    t.append (QString::fromLocal8Bit("扩展"));
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
    //设置行数
    if(ui->table->rowCount()<5)ui->table->setRowCount (5);
    //设置行高
    ui->table->verticalHeader()->setDefaultSectionSize(20);//设置默认行高
    //关联触发按键
    QObject::connect(ui->table,SIGNAL(pressed(QModelIndex)),this,SLOT(table_pressed(QModelIndex)));
}
//鼠标按下,excel的动作
void Fhid::table_pressed(const QModelIndex &index)
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
                Fdebug::myDebug()->setText(QString::fromLocal8Bit("单元格没有内容"));
                return;
            }
            //1.1.把数据作为参数发送
            // emit serial_write(qtab->text(),ui->check_hex_send->isChecked(),ui->check_new_line);
        break;
        case 1://测试列
            qtab=ui->table->item(cur_row,0);//获取单元格指针
            if ( qtab == NULL || (qtab->text() == "") )
            {
                Fdebug::myDebug()->setText(QString::fromLocal8Bit("单元格没有内容"));
                return;
            }
            //1.1.把数据作为参数测试
            // emit mySerial->serial_read_line(qtab->text().toLocal8Bit());
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
// usb改动时会触发这个函数
bool Fhid::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    if(eventType == nullptr){};
    if(result    == nullptr){};
    MSG* msg = reinterpret_cast<MSG*>(message);
    // WM_DEVICECHANGE 设备改变事件
    if(msg->message == WM_DEVICECHANGE)
    {
        if(lpcHid->hidState())//状态正关联着
        {
            if(FALSE == lpcHid->hidIsConnect())
            {
                lpcHid->hidClose();
                uniRx->setTextStyle(QString::fromLocal8Bit("HID设备断连"),Qt::red,16);
            }
        }
        qDebug()<<"usb change";
    }
    return FALSE;
}
// *********************************************************************************** 点击“打开”
void Fhid::on_b_open_clicked()
{
    if(ui->b_open->text()==QString::fromLocal8Bit("HID关闭"))
    {
       closeUsb();
       ui->b_open->setText(QString::fromLocal8Bit("HID打开"));
       ui->b_open->setStyleSheet("background-color: rgb(0, 255, 127);");
    }
    else
    {
        if(TRUE == lpcHid->hidOpen())
        {
            ui->b_open->setText(QString::fromLocal8Bit("HID关闭"));
            ui->b_open->setStyleSheet("background-color: rgb(255, 127, 127)");
        }
    }
}
// *********************************************************************************** 点击“发送”
void Fhid::on_b_hid_send_clicked()
{
    writeUsb();
}
// *********************************************************************************** 点击“清除”
void Fhid::on_b_hid_clear_clicked()
{
    uniRx->clear();
    lpcHid->hidIsConnect();
}
// *********************************************************************************** 点击“最小宽度”
void Fhid::on_check_minWidth_clicked(bool checked)
{
    if(checked)
    {
        setMaximumWidth(340);
    }
    else
    {
        setMaximumWidth(700);
    }
}
// *********************************************************************************** 点击“隐藏扩展”
void Fhid::on_check_hide_clicked(bool checked)
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
        int hu = height();
        resize(width(),hu+ht);
        ui->frame_hide->show();
    }
}
// 隐藏的后续触发
void Fhid::hideMyTable(void)
{
    hideFrame.stop();
    resize(width(),height()-ui->table->height());
}
// *********************************************************************************** 更新计数值
void Fhid::update_count(void)
{
    ui->label_rec_count->setText(QString::fromLocal8Bit("接收=") + QString::number(rxCount,10));
    ui->label_sen_count->setText(QString::fromLocal8Bit("发送=") + QString::number(txCount,10));
}
// 打开usb
bool Fhid::openUsb()
{
    bool b;
    b = lpcHid->hidOpen();
    if(b)
        uniRx->setTextStyle(QString::fromLocal8Bit("HID连接上"),Qt::green,16);
    else
        uniRx->setTextStyle(QString::fromLocal8Bit("HID没有连接"),Qt::red,16);
    return b;
}
// 关闭usb
void Fhid::closeUsb()
{
    bool b;
    b = lpcHid->hidClose();
    Fdebug::myDebug()->setText(QString::fromLocal8Bit("关闭usb设备"));
}
// 写入usb->从hid_send读取，一次最多64个
void Fhid::writeUsb()
{
    bool b;
    QVector <char>buff;    // 待发送的数据
    // 2.读取待发送数据
    lineStr2charVector(ui->hid_send->text(),&buff);
    // 3.usb 写入数据
    b = lpcHid->hidSend(buff);
    if(b)
    {
        Fdebug::myDebug()->setText(QString::fromLocal8Bit("写入成功"));
        txCount++;
    }
    else
        Fdebug::myDebug()->setText(QString::fromLocal8Bit("写入失败"));
}
void Fhid::readUsb(QVector<char>R)
{
    static int num=0;
    QString str;
    num++;
    str="num= "+QString::number(num);
    for(int i=0;i<R.size();i++)
    {
        if(i%READ_PACK_LEN == 0)str += "\r\n";
        str += QString::asprintf("%02x ",(uchar)(R.at(i)));
    }
    uniRx->setTextAutoTime(str);// 写入数据
    rxCount++;
}



// ******************************************** 数据保存 ******************************************** begin
//函数功能：导出配置
//输入参数：
//输出参数：
//备注：
void Fhid::dat_config_save(QString filename)
{
    // 保存配置
    QSettings save_dat(filename,QSettings::IniFormat);
    save_dat.clear();
    save_dat.setIniCodec("GB2312");//支持中文
    // ------------------------ 其他配置的保存
    save_dat.setValue ("hid_send"       ,ui->hid_send->text()           );
    save_dat.setValue ("VID"            ,ui->spinBox_VID->value()       );
    save_dat.setValue ("PID"            ,ui->spinBox_PID->value()       );
    save_dat.setValue ("check_hide"     ,ui->check_hide->isChecked()    );
    save_dat.setValue ("check_minWidth" ,ui->check_minWidth->isChecked());
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
void Fhid::dat_config_load(QString filename)
{
    QSettings save_dat(filename,QSettings::IniFormat);
    save_dat.setIniCodec("GB2312");//支持中文
    //判断文件存在
    if(save_dat.contains("VID")==false)
    {
        Fdebug::myDebug()->setChar("FHid:no file!");
        return;
    }
    Fdebug::myDebug()->setChar("FHid:have file!");
    // ------------------------ 其他配置的读取
    ui->hid_send->setText(save_dat.value("hid_send").toString());
    ui->spinBox_PID->setValue(save_dat.value("PID").toInt());
    ui->spinBox_VID->setValue(save_dat.value("VID").toInt());
    ui->check_hide->setChecked(save_dat.value("check_hide").toBool());
    on_check_hide_clicked(ui->check_hide->isChecked());

    ui->check_minWidth->setChecked(save_dat.value("check_minWidth").toBool());
    on_check_minWidth_clicked(ui->check_minWidth->isChecked());

    // talbe 的导出
    if(save_dat.contains("table_rowCount")==false)return;
    if(ui->table->rowCount()<10)
    {
        ui->table->setRowCount(10);
    }
    else
    {
        ui->table->setRowCount(save_dat.value("table_rowCount").toInt()    );
        if(save_dat.contains("table_strlist")==false)return;
        QStringList strlist;
        strlist = save_dat.value("table_strlist").toStringList();

        {
            for(int i=0;i<ui->table->rowCount();i++)
            {
                QTableWidgetItem *qtab = new QTableWidgetItem();
                qtab->setText(strlist.at(i));
                ui->table->setItem(i,0,qtab);
            }
        }
    }
}
// ******************************************** 数据保存 ******************************************** end






