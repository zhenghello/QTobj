#include "fserial.h"

Fserial::Fserial()
{
    qDebug()<<"Fserial================\r\n";
    name        = "COM1";                    // 串口的配置数据
    baudRate    = 115200;                    // 串口的配置数据
    dataBits    = QSerialPort::Data8;        // 串口的配置数据
    stopBits    = QSerialPort::OneStop;      // 串口的配置数据
    parity      = QSerialPort::NoParity;     // 串口的配置数据
    flowControl = QSerialPort::NoFlowControl;// 串口的配置数据
    isOpen  = false ;
    serial_rx_count = 0;
    serial_tx_count = 0;
}
//打开串口
void Fserial::open_serial(void)
{
    qDebug() << "open_serial" << QThread::currentThreadId();
    mySerial = new QSerialPort();
    if(mySerial==nullptr)return;  //串口空
    mySerial->setPortName(name);
    mySerial->setBaudRate(baudRate);
    mySerial->setDataBits(dataBits);
    mySerial->setStopBits(stopBits);
    mySerial->setParity(parity);
    mySerial->setFlowControl(flowControl);
    //return mySerial->open(QIODevice::ReadWrite);//采用子线程查询的方式
    //打开串口
    bool ret=false;
    ret = mySerial->open(QIODevice::ReadWrite);
    if(ret)
    {
        qDebug()<<"open serial is succeed";
        QObject::connect(mySerial,SIGNAL(readyRead()),this,SLOT(deal_serial_interrupt()),Qt::QueuedConnection);//连接信号槽
        emit serial_isOpen(true);   //告知外部串口信息
        isOpen = true;
    }
    else
    {
        qDebug()<<"open serial is failure";
        emit serial_isOpen(false);    //告知外部串口信息
        isOpen = false;
    }
}
//关闭串口
void Fserial::close_serial(void)
{
    qDebug() << "close_serial" << QThread::currentThreadId();
//    mySerial->close(); //关闭串口 //去掉这一步，可以防止大量数据打印时死机。
    mySerial->deleteLater();//清除
    QObject::disconnect(mySerial,SIGNAL(readyRead()),this,SLOT(deal_serial_interrupt()));//连接信号槽
    isOpen = false;
    emit serial_isOpen(false);      //告知外部串口信息
}
//处理串口接收的数据,串口中断进入
void Fserial::deal_serial_interrupt(void)
{
    //qDebug() << "deal_serial_interrupt" << QThread::currentThreadId();
    bool   ret = true;
//    static int overTime = 0;
    ret = mySerial->waitForReadyRead(5);
    // 把所有行都读出来并发送信号
    while(mySerial->canReadLine())
    {
        QByteArray qby;
        qby = mySerial->readLine();
        emit serial_read_line(qby);
        serial_buf.append(qby);
//        overTime = 0;
        // qDebug()<<"(1)->"<<qby;
    }
    if(mySerial->size() > 1024)//大于1K并且都不是行数据，强制发送出去
    {
        QByteArray qby;
        qby = mySerial->readAll();
        emit serial_read_line(qby);
        serial_buf.append(qby);
        // qDebug()<<"(2)->"<<qby;
    }
    if((ret==false)&&(mySerial->size()>0))//等待不到数据，但是缓存区还是有剩余数据，也强制发送出来
    {
//        overTime++;
//        if(overTime>5)// 25ms的超时发送
//        {
            QByteArray qby;
            qby = mySerial->readAll();
            emit serial_read_line(qby);
            serial_buf.append(qby);
            // qDebug()<<"(3)->"<<qby;
            // while(1);
            qDebug()<<"serial timeout!";
//        }
    }
    serial_rx_count++;
}
//串口发送数据
void Fserial::serial_write(QString str,bool isHex,bool isNewLine)   // 发送一行数据
{
    // qDebug() << "serial_write" << QThread::currentThreadId();
    // 0.判断串口打开
    if(isOpen ==false)
    {
        qDebug()<<"serial is not open!";
        return;
    }
    // 1.判断空发送行
    if(str == NULL)
    {
        qDebug()<<"input is null!";
        return ;
    }
    // 2.判断hex发送
    if(isHex == true )
    {
        QByteArray array ;  //存放将Qstr 转为 HEX 的所有数据
        lineStr2charArray(str,&array);
        mySerial->write(array.data(),array.length());//发送数据
    }
    else
    {
        // 3.判断发送新行
        if(isNewLine)
        {
            //str = str.simplified();//清除自身的无效字符
            str += "\r\n";
        }
        //qDebug()<<str.toLocal8Bit().data();
        mySerial->write(str.toLocal8Bit().data(),str.toLocal8Bit().size());//QString
    }
    serial_tx_count++;
//    qDebug()<<"write serial is succeed!";// 调试信息
}
// 清除数据
void Fserial::clear_count(void)
{
    serial_rx_count = 0;
    serial_tx_count = 0;
    serial_buf.clear();
}
