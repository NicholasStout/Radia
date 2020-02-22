#include "radia.h"
#include "fin.h"
#include "radia_layout.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Radia *w = new Radia;
    w->show();
    return a.exec();
}
