#include "dial.h"
#include "dial_layout.h"
#include "filehandler.h"

void Dial::setBoundaryAngles(float start, float stop)
{
    startAng = start;
    stopAng = stop;
    l->setSpan(start, stop);
}

Dial::Dial(QWidget *parent, QRect *size)
    : QWidget{parent}
{
    //QWidget::setWindowOpacity(0);
    setGeometry(*size);
    populator = new FileHandler();
    l = new Dial_Layout(this);
    l->setGeometry(*size);
    setLayout(l);
    createFins();
    //l->loadVisible();
    //show();
}

void Dial::setGrab(bool msg)
{

}

void Dial::slide(QMouseEvent *e)
{

}

void Dial::setPopulator(IPopulator *newPopulator)
{
    populator = newPopulator;
}

void Dial::createFins()
{
    //int i = 0;
    QWidget * head = this;
    QList<FinDetails> finList = populator->populateList();
    QListIterator<FinDetails> it(finList);
    while(it.hasNext()) {
        FinDetails deetz = it.next();
        Fin * f = new Fin(head, &deetz.ico, deetz.exec);
        QObject::connect(f, &Fin::setGrab, this, &Dial::setGrab);
        QObject::connect(f, &Fin::mouseMoved, this, &Dial::slide);
        //f->offset = int(angle*i) % 360;
        f->hide();
        //head = f;
        l->addFin(f);
        //i++;
    }
}

// void Dial::loadVisible(Dial_Layout * l)
// {
//     Fin * f;
//     while (l->canAddFin() && !l->fin_stack.isEmpty())
//     {
//         f = l->fin_stack.pop();
//         l->visible.append(f);
//         f->showUp();

//     }
//     if (l->visible.isEmpty()) {
//         throw 1;
//     }
// }
