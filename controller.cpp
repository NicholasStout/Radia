#include "controller.h"
#include "qapplication.h"

Controller::Controller(Database *d, QObject *parent)
    : QObject{parent}
{
    db = d;
}

void Controller::launchProgram(FinDetails fd) const
{
    QProcess *process = new QProcess();
    QStringList lst = fd.exec.split(' ');
    QString prog = lst.takeFirst();
    qDebug() << "launching " << fd.exec;
    int result = process->startDetached(prog, lst);
    qDebug() << "result: " << result;
    db->incrementPopularity(fd);
    QApplication::quit();
}

void Controller::togglePin(FinDetails fd) const
{

}
