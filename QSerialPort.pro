#-------------------------------------------------
#
# Project created by QtCreator 2015-11-05T14:20:29
#
#-------------------------------------------------

QT       += core gui
CONFIG+=  serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSerialPort
TEMPLATE = app


SOURCES += main.cpp\
        serial.cpp

HEADERS  += serial.h

FORMS    += \
    serial.ui
