#ifndef FCOM_H
#define FCOM_H

#include <QMainWindow>
// 保存相关
#include <QSettings>
//串口相关
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>

#include "fserial.h"
#include "fdebug.h"
// #include "charStr.h"



namespace Ui {class Fcom;}

class Fcom : public QWidget
{
    Q_OBJECT

public:
    explicit Fcom(QString filename, QWidget *parent = 0);
    ~Fcom();

    /* 懒汉式->单例模式 Fcom::uart1()->*/
    static Fcom *uart1()      // 用于调试界面
    {
        static Fcom *_uart1;
        if(_uart1 == NULL) //判断是否第一次调用
            _uart1 = new Fcom("./config/uart1_config.dat");
        return _uart1;
    }
    static Fcom *uart2()       // 用于主显示
    {
        static Fcom *_uart2;
        if(_uart2 == NULL)
            _uart2 = new Fcom("./config/uart2_config.dat");
        return _uart2;
    }
public slots:
    void clear_serial(void);                    // 清空显示
    bool comIsOpen(void);                       // 判断串口打开
private slots:
    //串口相关
    void updat_isOpen(bool state);

    void on_serial_open_clicked();
    void on_b_serial_up_info_clicked();
    void on_b_serial_clear_clicked();
    void on_check_show_hex_clicked();
    void on_check_hide_clicked(bool checked);
    void on_b_serial_send_clicked();
    void on_b_save_clicked();
    void update_show(QByteArray qby);
    void update_count(void);

    void table_init(void);
    void table_pressed(const QModelIndex &index);

    void hideMyTable(void);
    void on_b_load_clicked();
    void on_check_minWidth_clicked(bool checked);


    void on_b_serial_send2_clicked();
    void on_b_serial_send3_clicked();
    void on_check_timeSend2_clicked(bool checked);
    void on_check_timeSend3_clicked(bool checked);


signals:
    void open_serial(void);//打开串口
    void close_serial(void);    //关闭串口
    void serial_write(QString str, bool isHex, bool isNewLine);   // 发送一行数据
    void serial_read_line(QByteArray str);
private:
    Ui::Fcom *ui;
    //缓存数据
    bool            isOpen;                // 串口打开状态
    QByteArray      serial_hex_show;       //  串口接收的直接数据转hex显示
    // 自定义
    void dat_config_save(QString filename);//保存
    void dat_config_load(QString filename);//导入
    QString         config_filename;       //  保存文件名
    QTimer          updateCount1s;
    QTimer          hideFrame;
    Fserial *mySerial;//新建串口
    QThread *myThread;//新建线程
};

#endif // Fcom_H
