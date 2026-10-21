#ifndef IDIAL_H
#define IDIAL_H

#include "controller.h"

class IDial
{
public:
    virtual ~IDial() = default;
    virtual void setBoundaryAngles(float start, float stop) = 0;
    virtual void createFins(Controller &c) = 0;
public slots:
    void resetFins();
};

#endif // IDIAL_H
