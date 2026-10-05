#include "controller.h"

Controller::Controller(Database *d, QObject *parent)
    : QObject{parent}
{
    db = d;
}

void Controller::launchProgram(FinDetails fd) const
{

}

void Controller::togglePin(FinDetails fd) const
{

}
