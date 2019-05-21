#include "anyone.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AnyOne w;
    w.show();

    return a.exec();
}

