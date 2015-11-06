#include "serial.h"
#include "ui_serial.h"

Serial::Serial(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Serial)
{
    ui->setupUi(this);
    startUiIint();
    myCom=NULL;
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(getSerialPort()));
    timer->start(1000);
}

Serial::~Serial()
{
    if(myCom != NULL){
        if(myCom->isOpen()){
            myCom->close();
        }
        delete myCom;
    }
    delete ui;
}

void Serial::startUiIint()
{
    ui->sendMsgBtn->setEnabled(false);
    ui->obocheckBox->setEnabled(false);
    ui->delayspinBox->setEnabled(false);
}
void Serial::getSerialPort()
{
    QStringList list;
    ui->portNameComboBox->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
       list<<info.portName();
    }
    qSort(list.begin(),list.end());
    ui->portNameComboBox->addItems(list);

}

void Serial::setSerialPort()
{
    QString portName=ui->portNameComboBox->currentText();
    qDebug()<<tr("Serial number:")<<portName;
    myCom=new QSerialPort(portName);

    if(myCom->open(QIODevice::ReadWrite)){
        ui->statusBar->showMessage(tr("打开成功"));
        ui->sendMsgBtn->setEnabled(true);
        ui->obocheckBox->setEnabled(true);
        ui->delayspinBox->setEnabled(false);

        myCom->setBaudRate(ui->baundRateComboBox->currentText().toInt(),QSerialPort::AllDirections);
//        myCom->setDataBits(QSerialPort::Data8);
//        myCom->setParity(QSerialPort::NoParity);
//        myCom->setStopBits(QSerialPort::OneStop);
        myCom->setFlowControl(QSerialPort::NoFlowControl);
        //设置数据位
        switch (ui->dataBitsComboBox->currentIndex()) {
        case 0:
            myCom->setDataBits(QSerialPort::Data8);
            break;
        case 1:
            myCom->setDataBits(QSerialPort::Data7);
            break;
        case 2:
            myCom->setDataBits(QSerialPort::Data6);
            break;
        case 3:
            myCom->setDataBits(QSerialPort::Data5);
            break;
        default:
            myCom->setDataBits(QSerialPort::UnknownDataBits);
            break;
        }

        //设置校验
        switch(ui->pariatyComboBox->currentIndex()){
        case 0:
             myCom->setParity(QSerialPort::NoParity);
             break;
        case 1:
            myCom->setParity(QSerialPort::OddParity);
            break;
        case 2:
            myCom->setParity(QSerialPort::EvenParity);
            break;
        default:
            myCom->setParity(QSerialPort::UnknownParity);
            qDebug("set to default : PAR_NONE");
            break;
        }

        //设置停止位
        switch (ui->stopBitsComboBox->currentIndex()) {
        case 0:
            myCom->setStopBits(QSerialPort::OneStop);
            break;
        case 1:
            myCom->setStopBits(QSerialPort::OneAndHalfStop);
            break;
        case 2:
            myCom->setStopBits(QSerialPort::TwoStop);
            break;
        default:
            myCom->setStopBits(QSerialPort::UnknownStopBits);
            break;
        }

        connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
    }
    else {
        QMessageBox::information(this,"information",tr("请检查串口设置"),QMessageBox::Ok);
        return;
    }
}

//发送数据函数
void Serial::writeMyCom(){
    myCom->write(ui->lineEdit->text().toAscii());//以ASCII码的形式写入数据
    qDebug()<<tr("writing");
    ui->statusBar->showMessage(tr("writing"));
}

//读数据函数
void Serial::readMyCom(){
    qDebug()<<"read"<<myCom->bytesAvailable()<<"bytes";
    QByteArray temp=myCom->readAll();//读取串口缓冲区数据；
   //ui->textBrowser->insertPlainText(temp);//将串口数据显示在textBrowser文本浏览器中
    ui->textBrowser->append(temp);
   ui->textBrowser->moveCursor(QTextCursor::End);

//   QString buf = QString::fromLocal8Bit( temp );
//    ui->textBrowser->insertPlainText(buf);//将串口数据显示在textBrowser文本浏览器中

}

void Serial::on_OpenPortBtn_clicked()
{
    setSerialPort();
}


void Serial::on_sendMsgBtn_clicked()
{
    writeMyCom();

}

void Serial::on_closePoetBtn_clicked()
{
    myCom->close();
    ui->statusBar->clearMessage();
}
void Serial::on_clearSendBtn_clicked()
{
    ui->lineEdit->clear();
}

void Serial::on_clearRecBtn_clicked()
{
    ui->textBrowser->clear();
}


