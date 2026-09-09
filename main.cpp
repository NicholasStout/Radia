#include "radia.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Radia w = Radia();
    w.show();
    a.installEventFilter(&w);
    return a.exec();
}
