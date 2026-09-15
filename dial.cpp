#include "dial.h"
#include "dial_layout.h"
#include "filehandler.h"
#include "test_populator.h"

void Dial::setBoundaryAngles(float start, float stop)
{
    startAng = start; //TODO: Delete
    stopAng = stop; //TODO: Delete
    l->setSpan(start, stop);
}

Dial::Dial(QWidget *parent, QRect *size)
    : QWidget{parent}
{
    setGeometry(*size);
    populator = new FileHandler(); //This is leaking TODO: Move this to radia
    //populator = new test_populator(8);
    l = new Dial_Layout(this);
    l->setGeometry(*size);
    setLayout(l);
    createFins();
}

void Dial::setPopulator(IPopulator *newPopulator)
{
    populator = newPopulator;
}

bool Dial::handleEvent(QInputEvent *e)
{
    bool ret = false;
    if (l->handleEvent(e))
    {
        ret = true;
        switch (e->type())
        {
        case QEvent::MouseButtonPress:
            grab = true;
            angle = calcAngle(static_cast<QMouseEvent *>(e)->pos(), 500);
            l->grabAngle = angle;
            //l->setAngle(static_cast<QMouseEvent *>(e)->pos());
            break;
        case QEvent::MouseButtonRelease:
            grab = false;
            break;
        case QEvent::MouseMove:
            if (grab)
            {
                angle = calcAngle(static_cast<QMouseEvent *>(e)->pos(), 500);
                l->setAngle(static_cast<QMouseEvent *>(e)->pos());
            }
        default:
            return true;
        }
    }
    return ret;
}

void Dial::createFins()
{
    QWidget * head = this;
    QList<FinDetails> finList = populator->populateList();
    QListIterator<FinDetails> it(finList);
    while(it.hasNext()) {
        FinDetails deetz = it.next();
        Fin * f = new Fin(head, &deetz.ico, deetz.exec);
        f->installEventFilter(parent());
        //QObject::connect(f, &Fin::setGrab, this, &Dial::setGrab);
        //QObject::connect(f, &Fin::mouseMoved, this, &Dial::slide);
        f->hide();
        l->addFin(f);
    }
}
