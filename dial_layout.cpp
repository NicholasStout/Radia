#include <cstdlib>
#include "dial_layout.h"


/* Sublayout to handle the dials on the top and bottom of the UI
 */

Dial_Layout::Dial_Layout(QWidget* parent, FinRender* fr) :
    QLayout(parent)
{

    rend = fr;
    rend->setAngle(0);
    rend->setSpan(25);
    //setGeometry(parent->geometry());
    num_visible = (rend->getStop()-rend->getStart())/(rend->getAngle()+5);
}

void Dial_Layout::addItem(QLayoutItem* item)
{
    list.append(item);
}

void Dial_Layout::addFin(Fin *f)
{
    addWidget(f);
}

void Dial_Layout::removeFin(QString name)
{

    for (QList<QLayoutItem*>::iterator it = list.begin();
         it != list.end();
         ++it)
    {
        QLayoutItem *item = *it;

        if (item->widget() && item->widget()->objectName() == name) {
            list.erase(it);
            break;
        }
    }
}

void Dial_Layout::setGeometry(const QRect &r)
{
    if (r.width() == r.height())
    {
        QList<QLayoutItem *>::iterator itr = list.begin();
        Fin *f;
        for (; itr != list.end(); itr++) {
            f = qobject_cast<Fin *>((*itr)->widget());
            f->setGeometry(r);
            //f->span = angle-5;
        }
    }
}

void Dial_Layout::setGeometry(const QRect &r, float ang)
{
    rend->setAngle(ang);
    setGeometry(r);
}

void Dial_Layout::setSpan(float start, float stop)
{
    rend->setStart(start);
    rend->setStop(stop);
    qDebug() << rend->getStop();
    num_visible = std::abs(start-stop)/(rend->getSpan()+5);
    loadVisible();
}

QSize Dial_Layout::sizeHint() const
{
    return QSize(500, 500);
}

QLayoutItem *Dial_Layout::itemAt(int index) const
{
    if (index >= list.count())
        return nullptr;
    return list.at(index);
}

QLayoutItem *Dial_Layout::takeAt(int index)
{
    return list.takeAt(index);
}

int Dial_Layout::count() const
{
    return list.count();
}

bool Dial_Layout::canAddFin()
{

    return ((right-left) < (180/rend->getAngle()));
}

void Dial_Layout::setAngle(QPoint p)
{
    Fin * leftFin = qobject_cast<Fin *>(list[left]->widget());
    Fin * rightFin = qobject_cast<Fin *>(list[right]->widget());
    float prev = grabAngle;
    float curr_angle = calcAngle(p, 500);
    if(prev <= 1)
    {
        if (rend->getAngle() > 300)
            rend->setAngle(0);
        curr_angle = curr_angle-360;}
    float delta = curr_angle-grabAngle;
    if (delta != 0) {
        grabAngle=curr_angle;
        rend->setAngle(rend->getAngle()+delta);
    }
    qDebug() << rend->getStop();
    int finAngle = int(rightFin->get_loc_angle())%360;
    if (int(leftFin->get_loc_angle())%360 >= rend->getStop()+rend->getSpan())
    {
        if (right > 0 && list.count()>num_visible) {moveLeft();}
        else {rend->setAngle(rend->getStop() - leftFin->offset);}
    }
    else if (finAngle <=rend->getStart()-rend->getSpan())
    {
        if (left < list.count()-1&& list.count()>num_visible){moveRight();}
        else {rend->setAngle(rightFin->offset+1+rend->getStart());}
    }

    for (int i = right; i <= left; i++)
    {
        Fin * f = static_cast<Fin *>(list[i]->widget());
        f->update();
    }
}

void Dial_Layout::moveLeft()
{
    //qDebug()<<"move left";
    //qobject_cast<Fin *>(list[left]->widget())->angle=0;
    rend->setAngle(0);
    float back1 = qobject_cast<Fin *>(list[left]->widget())->offset;
    float back2 = 0;

    for (int i = left-1; i >= right-1; i--)
    {
        back2 = qobject_cast<Fin *>(list[i]->widget())->offset;
        qobject_cast<Fin *>(list[i]->widget())->offset = back1;
        back1 = back2;
    }

    list[left]->widget()->hide();
    left--;
    right--;
    list[right]->widget()->show();
}

void Dial_Layout::moveRight()
{
    //qDebug()<<"move right";
    //qobject_cast<Fin *>(list[right]->widget())->angle=0;
    rend->setAngle(0);
    float back1 = qobject_cast<Fin *>(list[right]->widget())->offset;
    float back2 = 0;

    for (int i = right+1; i <= left+1; i++)
    {
        back2 = qobject_cast<Fin *>(list[i]->widget())->offset;
        qobject_cast<Fin *>(list[i]->widget())->offset = back1;
        back1 = back2;
    }

    list[right]->widget()->hide();
    right++;
    left++;
    list[left]->widget()->show();

}

void Dial_Layout::loadVisible()
{
    right = 0;
    if (list.count() > 0) {
        Fin * f = qobject_cast<Fin *>(list[0]->widget());
        f->offset = rend->getStart();
        f->show();

        int num = (num_visible < list.count()) ? num_visible : list.count()-1;
        for (left = 1; left <= num; left++)
        {
            Fin * newf = qobject_cast<Fin *>(list[left]->widget());
            newf->offset =  f->offset + (rend->getSpan());
            newf->show();
            f = newf;
        }
        left--;
    }
}

bool Dial_Layout::handleEvent(QInputEvent *e)
{
    bool ret = false;
    for (int i = right; i <= left; i++)
    {
        Fin * f = static_cast<Fin *>(list[i]->widget());
        if(f->handleEvent(e))
        {
            ret = true;
        }
    }
    return ret;
}








