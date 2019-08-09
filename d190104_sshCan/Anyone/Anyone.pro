#-------------------------------------------------
#
# Project created by QtCreator 2018-08-15T21:12:54
#
# NO CHINE WORD
#-------------------------------------------------

QT       += core gui network # ssh need
QT       += axcontainer      # use excel function

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zhengCan
TEMPLATE = app

RC_ICONS    = happy.ico         # logo
CODECFORSRC = GB2312            # Coding rules

# head file path add -- YOU NEED WIRTE BY YOURSELF
INCLUDEPATH += ./youLib/fdebug/ \
               ./youLib/canExplain/ \
               ./youLib/strListTurn/ \
               ./youLib/FtreeDateBase/ \
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
    youLib/fssh/fssh.cpp \
    youLib/fssh/FsshGui.cpp \
    youLib/canSend/canSend.cpp \
    youLib/canRecv/canRecv.cpp \
    youLib/fssh/FsshGuiAutoAck.cpp \
    youLib/messageBoard/messageBoard.cpp \
    youLib/canRecv/fcanshow.cpp \
    youLib/canpack/canpack.cpp \
    youLib/ftmpConfig/cantmpconfig.cpp \
    youLib/strListTurn/dat2excel.cpp \
    youLib/strListTurn/dat2tableWidget.cpp \
    youLib/strListTurn/dat2treeWidget.cpp \
    youLib/strListTurn/excel2tableWidget.cpp \
    youLib/strListTurn/excel2treeWidget.cpp \
    youLib/strListTurn/strlist2dat.cpp \
    youLib/strListTurn/strlist2excel.cpp \
    youLib/strListTurn/strlist2tableWidget.cpp \
    youLib/strListTurn/strlist2treeWidget.cpp \
    youLib/FtreeDateBase/ftreeDabeBase.cpp \
    youLib/FtreeDateBase/timeSeqExplain.cpp \
    youLib/fdebug/fdebug.cpp

HEADERS  += anyone.h \
    youLib/fssh/fssh.h \
    youLib/fssh/FsshGui.h \
    youLib/canSend/canSend.h \
    youLib/canRecv/canRecv.h \
    youLib/fssh/FsshGuiAutoAck.h \
    youLib/messageBoard/messageBoard.h \
    youLib/canRecv/fcanshow.h \
    youLib/canpack/canpack.h \
    youLib/ftmpConfig/cantmpconfig.h \
    youLib/strListTurn/dat2excel.h \
    youLib/strListTurn/dat2tableWidget.h \
    youLib/strListTurn/dat2treeWidget.h \
    youLib/strListTurn/excel2tableWidget.h \
    youLib/strListTurn/excel2treeWidget.h \
    youLib/strListTurn/strlist2dat.h \
    youLib/strListTurn/strlist2excel.h \
    youLib/strListTurn/strlist2tableWidget.h \
    youLib/strListTurn/strlist2treeWidget.h \
    youLib/FtreeDateBase/ftreeDabeBase.h \
    youLib/FtreeDateBase/timeSeqExplain.h \
    youLib/fdebug/fdebug.h
    ssh.h


FORMS    += anyone.ui \
    youLib/fssh/FsshGui.ui \
    youLib/canSend/canSend.ui \
    youLib/canRecv/canRecv.ui \
    youLib/fssh/FsshGuiAutoAck.ui \
    youLib/messageBoard/messageBoard.ui \
    youLib/canRecv/fcanshow.ui \
    youLib/ftmpConfig/cantmpconfig.ui \
    youLib/FtreeDateBase/ftreeDabeBase.ui \
    youLib/fdebug/fdebug.ui

LIBS += -L$$PWD/qssh/release/lib -lQSsh    # ssh need

INCLUDEPATH += $$PWD/qssh/src/libs/ssh     # ssh need

#DISTFILES += \
#    ��������.dat

DISTFILES += \
    programmingStatement.dat


