#ifndef SERIAL_H
#define SERIAL_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QTimer>
#include <QTime>

namespace Ui {
class Serial;
}

class Serial : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Serial(QWidget *parent = 0);
    ~Serial();
    void startUiIint();
    void setSerialPort();

    
private:
    Ui::Serial *ui;
    QSerialPort *myCom;
    QTimer *timer;

private slots:
    void writeMyCom();
    void readMyCom();
    void getSerialPort();


    void on_OpenPortBtn_clicked();
    void on_sendMsgBtn_clicked();
    void on_clearSendBtn_clicked();
    void on_clearRecBtn_clicked();
    void on_closePoetBtn_clicked();
};

#endif // SERIAL_H
