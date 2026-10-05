#ifndef DIAL_H
#define DIAL_H

#include <QWidget>
#include "dial_layout.h"
#include "ipopulator.h"
#include "controller.h"

class Dial : public QWidget
{
    Q_OBJECT
public:
    void setBoundaryAngles(float start, float stop);
    explicit Dial(IPopulator * pop, QWidget *parent = nullptr, QRect * size = nullptr);
    void setPopulator(IPopulator *newPopulator);
    bool handleEvent(QInputEvent *e);
    void createFins(Controller &c);

private:
    float angle;
    bool grab;
    IPopulator *populator;
    FinRender fr;
    void loadVisible(Dial_Layout * l);
    Dial_Layout * l;
    float startAng, stopAng;
};

#endif // DIAL_H
