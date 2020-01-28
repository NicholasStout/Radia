#include "radia.h"
#include "fin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Radia w;
    w.show();
    fin f(&w);
    f.show();

    return a.exec();
}
