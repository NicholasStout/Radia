#include "controller.h"

Controller::Controller(FileHandler *f, QObject *parent)
    : QObject{parent}
{
    fh = f;
}

void Controller::updateFinList()
{

}

void Controller::launchProgram(FinDetails fd) const
{

}

void Controller::togglePin(FinDetails fd) const
{

}
