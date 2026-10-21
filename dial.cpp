#include "dial.h"
#include "dial_layout.h"

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
    QObject::connect(&fr, &FinRender::redraw, l, &Dial_Layout::redraw);
    //createFins();
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
            l->setGrabAngle(angle);
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
    l->loadVisible();
}

void Dial::updateFins(Controller * c)
{
    QList<FinDetails> finList = populator->populateList();
    int i = 0;
    QLayoutItem * item = l->itemAt(i);
    while(item != nullptr)
    {
        Fin *f = static_cast<Fin*>(item->widget());
        int index = finList.indexOf(f->getFinDetails());
        qDebug() << index;
        if(index > -1)
        {
            finList.remove(index);
        }
        else
        {
            f = static_cast<Fin*>(l->takeAt(i)->widget());
            f->hide();
            delete f;
        }
        i++;
        item = l->itemAt(i);
    }
    QListIterator<FinDetails> it(finList);
    while(it.hasNext()) {
        FinDetails deetz = it.next();
        Fin * f = new Fin(this, deetz, &fr);
        f->installEventFilter(parent());
        QObject::connect(f, &Fin::finSelected, c, &Controller::launchProgram);
        QObject::connect(f, &Fin::TogglePin, c, &Controller::togglePin);
        f->hide();
        l->addFin(f);
    }
    l->loadVisible();
    l->redraw();
}
