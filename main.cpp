#include "radia.h"
#include "fin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Radia w;
    w.show();
    fin f(&w, 0);
    f.show();
    fin g(&f, 45);
    g.show();

    return a.exec();
}
