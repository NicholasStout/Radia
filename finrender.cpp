#include "finrender.h"

FinRender::FinRender() {}

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
}

void FinRender::setStop(int newStop)
{
    stop = newStop;
}

void FinRender::setAngle(float ang)
{
    angle = ang;
}

void FinRender::setSpan(int s)
{
    span = s;
}
