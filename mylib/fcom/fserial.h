#ifndef FSERIAL_H
#define FSERIAL_H

#include <QDebug>
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "charStr.h"
class Fserial:public QObject
{
    Q_OBJECT
public:
    Fserial();
    void clear_count(void);
    bool isOpen         ;
    int  serial_rx_count;      //  发送和接收计数
    int  serial_tx_count;      //
    QByteArray serial_buf;     //  串口接收的直接数据

    QString name;                        //串口的配置数据
    qint32 baudRate;                     //串口的配置数据
    QSerialPort::DataBits dataBits;      //串口的配置数据
    QSerialPort::StopBits stopBits;      //串口的配置数据
    QSerialPort::Parity parity;          //串口的配置数据
    QSerialPort::FlowControl flowControl;//串口的配置数据
public slots:
    void open_serial(void);//打开串口
    void close_serial(void);    //关闭串口
    void serial_write(QString str,bool isHex,bool isNewLine);   // 发送一行数据
private slots:  //内部中断
    void deal_serial_interrupt(void);
signals: //触发信号
    void serial_read_line(QByteArray str);
    void serial_isOpen(bool isOpen);
private:
    QSerialPort *mySerial;
};

#endif // FSERIAL_H
