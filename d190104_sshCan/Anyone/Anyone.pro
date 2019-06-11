#-------------------------------------------------
#
# Project created by QtCreator 2018-08-15T21:12:54
#
#-------------------------------------------------

QT       += core gui network # ssh need
QT       += axcontainer      # 为了使用excel工具

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zhengCan
TEMPLATE = app

RC_ICONS    = happy.ico         # 图标
CODECFORSRC = GB2312            # 编码方式

# head file path
INCLUDEPATH += ../../mylib/fdebug/ \
               ../../mylib/canExplain/ \
               ../../mylib/strListTurn/ \
               ../../mylib/FtreeDateBase/ \
               ./youLib/canExplain/ \
               ./youLib/canSend/ \
               ./youLib/canRecv/ \
               ./youLib/fssh/ \
               ./youLib/messageBoard/ \
               ./youLib/rtabwidget/ \
               ./youLib/canPack/ \
               ./youLib/ftmpConfig/ \


SOURCES += main.cpp\
        anyone.cpp \
    ../../mylib/fdebug/fdebug.cpp \
    ../../mylib/strListTurn/excel2treeWidget.cpp \
    ../../mylib/strListTurn/strlist2excel.cpp \
    ../../mylib/strListTurn/strlist2treeWidget.cpp \
    ../../mylib/FtreeDateBase/ftreeDabeBase.cpp \
    ../../mylib/strListTurn/dat2excel.cpp \
    ../../mylib/strListTurn/dat2treeWidget.cpp \
    ../../mylib/strListTurn/strlist2dat.cpp \
    youLib/fssh/fssh.cpp \
    youLib/fssh/FsshGui.cpp \
    youLib/canSend/canSend.cpp \
    youLib/canRecv/canRecv.cpp \
    youLib/fssh/FsshGuiAutoAck.cpp \
    youLib/messageBoard/messageBoard.cpp \
    youLib/canRecv/fcanshow.cpp \
    youLib/canpack/canpack.cpp \
    youLib/ftmpConfig/cantmpconfig.cpp

HEADERS  += anyone.h \
    ../../mylib/fdebug/fdebug.h \
    ../../mylib/strListTurn/excel2treeWidget.h \
    ../../mylib/strListTurn/strlist2excel.h \
    ../../mylib/strListTurn/strlist2treeWidget.h \
    ../../mylib/FtreeDateBase/ftreeDabeBase.h \
    ../../mylib/strListTurn/dat2excel.h \
    ../../mylib/strListTurn/dat2treeWidget.h \
    ../../mylib/strListTurn/strlist2dat.h \
    youLib/fssh/fssh.h \
    youLib/fssh/FsshGui.h \
    youLib/canSend/canSend.h \
    youLib/canRecv/canRecv.h \
    youLib/fssh/FsshGuiAutoAck.h \
    youLib/messageBoard/messageBoard.h \
    youLib/canRecv/fcanshow.h \
    youLib/canpack/canpack.h \
    youLib/ftmpConfig/cantmpconfig.h
    ssh.h


FORMS    += anyone.ui \
    ../../mylib/fdebug/fdebug.ui \
    ../../mylib/FtreeDateBase/ftreeDabeBase.ui \
    youLib/fssh/FsshGui.ui \
    youLib/canSend/canSend.ui \
    youLib/canRecv/canRecv.ui \
    youLib/fssh/FsshGuiAutoAck.ui \
    youLib/messageBoard/messageBoard.ui \
    youLib/canRecv/fcanshow.ui \
    youLib/ftmpConfig/cantmpconfig.ui

LIBS += -L$$PWD/qssh/release/lib -lQSsh    # ssh need

INCLUDEPATH += $$PWD/qssh/src/libs/ssh     # ssh need

DISTFILES += \
    编程声明.dat


