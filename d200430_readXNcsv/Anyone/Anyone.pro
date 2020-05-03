#-------------------------------------------------
#
# Project created by QtCreator 2018-08-15T21:12:54
#
#-------------------------------------------------

QT       += core gui
QT       += axcontainer      # use excel function
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XNcsvReader
TEMPLATE = app

RC_ICONS = happy.ico   # ico


# head file path
INCLUDEPATH += ./zLib/fdebug/ \
                ./zLib/strListTurn/
SOURCES += main.cpp\
        anyone.cpp \
    ./zLib/fdebug/fdebug.cpp \
    zLib/strListTurn/dat2excel.cpp \
    zLib/strListTurn/dat2tableWidget.cpp \
    zLib/strListTurn/dat2treeWidget.cpp \
    zLib/strListTurn/excel2tableWidget.cpp \
    zLib/strListTurn/excel2treeWidget.cpp \
    zLib/strListTurn/strlist2dat.cpp \
    zLib/strListTurn/strlist2excel.cpp \
    zLib/strListTurn/strlist2tableWidget.cpp \
    zLib/strListTurn/strlist2treeWidget.cpp \
    zLib/strListTurn/excel2mat.cpp

HEADERS  += anyone.h \
    ./zLib/fdebug/fdebug.h \
    zLib/strListTurn/dat2excel.h \
    zLib/strListTurn/dat2tableWidget.h \
    zLib/strListTurn/dat2treeWidget.h \
    zLib/strListTurn/excel2tableWidget.h \
    zLib/strListTurn/excel2treeWidget.h \
    zLib/strListTurn/strlist2dat.h \
    zLib/strListTurn/strlist2excel.h \
    zLib/strListTurn/strlist2tableWidget.h \
    zLib/strListTurn/strlist2treeWidget.h \
    zLib/strListTurn/excel2mat.h

FORMS    += anyone.ui \
    ./zLib/fdebug/fdebug.ui

RESOURCES += \
    anyone.qrc


