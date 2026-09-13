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
    float angle;
    bool grab;
    explicit Dial(QWidget *parent = nullptr, QRect * size = nullptr);

    void setPopulator(IPopulator *newPopulator);
    //void mouseMoveEvent(QMouseEvent *event) override;

    bool handleEvent(QInputEvent *e);
signals:

//public slots:
//    void setGrab(bool msg);
//    void slide(QMouseEvent* e);

private:
    IPopulator *populator;
    void createFins();
    void loadVisible(Dial_Layout * l);
    Dial_Layout * l;
    float startAng, stopAng;
};

#endif // DIAL_H
