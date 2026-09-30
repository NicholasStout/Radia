#ifndef DIAL_H
#define DIAL_H

#include <QWidget>
#include "dial_layout.h"
#include "ipopulator.h"

class Dial : public QWidget
{
    Q_OBJECT
public:
    void setBoundaryAngles(float start, float stop);
    explicit Dial(QWidget *parent = nullptr, QRect * size = nullptr);
    void setPopulator(IPopulator *newPopulator);
    bool handleEvent(QInputEvent *e);

private:
    float angle;
    bool grab;
    IPopulator *populator;
    FinRender fr;
    void createFins();
    void loadVisible(Dial_Layout * l);
    Dial_Layout * l;
    float startAng, stopAng;
};

#endif // DIAL_H
