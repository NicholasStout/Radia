#include "dial.h"
#include "dial_layout.h"
#include "filehandler.h"

void Dial::setBoundaryAngles(float start, float stop)
{
    l->setSpan(start, stop);
}

Dial::Dial(IPopulator * pop, QWidget *parent, QRect *size)
    : QWidget{parent}
{
    grab = false;
    setGeometry(*size);
    populator = pop;
    //populator = new test_populator(8);
    l = new Dial_Layout(this, &fr);
    l->setGeometry(*size);
    setLayout(l);
    //createFins();
}

void Dial::setPopulator(IPopulator *newPopulator)
{
    populator = newPopulator;
}

bool Dial::handleEvent(QInputEvent *e)
{
    //qDebug() << grab;
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

void Dial::createFins(Controller &c)
{
    QWidget * head = this;
    QList<FinDetails> finList = populator->populateList();
    QListIterator<FinDetails> it(finList);
    while(it.hasNext()) {
        FinDetails deetz = it.next();
        Fin * f = new Fin(head, deetz, &fr);
        f->installEventFilter(parent());
        QObject::connect(f, &Fin::finSelected, &c, &Controller::launchProgram);
        QObject::connect(f, &Fin::TogglePin, &c, &Controller::togglePin);
        f->hide();
        l->addFin(f);
    }
}
