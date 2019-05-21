#-------------------------------------------------
#
# Project created by QtCreator 2018-08-15T21:12:54
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Anyone
TEMPLATE = app

RC_ICONS = happy.ico   # 图标


# head file path
INCLUDEPATH += ../../mylib/fdebug/

SOURCES += main.cpp\
        anyone.cpp \
    ../../mylib/fdebug/fdebug.cpp

HEADERS  += anyone.h \
    ../../mylib/fdebug/fdebug.h

FORMS    += anyone.ui \
    ../../mylib/fdebug/fdebug.ui


