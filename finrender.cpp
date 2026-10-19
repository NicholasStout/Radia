#include "finrender.h"
#include <QDebug>

FinRender::FinRender(QObject *parent) : QObject(parent) {}

float FinRender::getAngle()
{
    return angle;
}

int FinRender::getSpan()
{
    return span;
}

int FinRender::getStop() const
{
    return stop;
}

int FinRender::getStart() const
{
    return start;
}

void FinRender::setStart(int newStart)
{
    start = newStart;
    emit redraw();
}

void FinRender::setStop(int newStop)
{
    stop = newStop;
    emit redraw();
}

void FinRender::setAngle(float ang)
{
    angle = ang;
    emit redraw();
}

void FinRender::setSpan(int s)
{
    span = s;
    emit redraw();
}
