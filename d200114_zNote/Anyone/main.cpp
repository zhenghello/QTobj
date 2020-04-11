#include "anyone.h"
#include <QApplication>

// 解决中文乱码的问题.
#if     _MSC_VER >= 1600
#pragma  execution_character_set("utf-8")
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AnyOne w;
    w.show();

    return a.exec();
}




