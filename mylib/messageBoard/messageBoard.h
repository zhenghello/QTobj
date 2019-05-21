#ifndef MESSAGEBOARD_H
#define MESSAGEBOARD_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QTextEdit>
#include <QSpinBox>
#include <QSettings>

class messageBoard : public QWidget
{
    Q_OBJECT
public:
    explicit messageBoard(QWidget *parent = 0, QString setTitle = "message");
    ~messageBoard(void);
    void dat_config_load(QString filename);
    void dat_config_save(QString filename);

signals:

public slots:
    void setMaxHeight(int height);
private:
    QGridLayout *mainGridLayout;
    QTextEdit   *message;
    QLabel      *title;
    QSpinBox    *messageHigh;
    QString     config_filename;
};

#endif // MESSAGEBOARD_H
