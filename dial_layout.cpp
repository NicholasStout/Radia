#include <cstdlib>
#include "dial_layout.h"


/* Sublayout to handle the dials on the top and bottom of the UI
 */

Dial_Layout::Dial_Layout(QWidget* parent, FinRender* fr) :
    QLayout(parent)
{
    right = 0;
    left = 0;
    rend = fr;
    rend->setAngle(0);
    rend->setSpan(20);
    //setGeometry(parent->geometry());
    num_visible = (rend->getStop()-rend->getStart())/(rend->getAngle()+5);
    conGrad = new QConicalGradient(sizeHint().height()/2, sizeHint().width()/2, 0);
}

void Dial_Layout::addItem(QLayoutItem* item)
{
    list.append(item);
}

void Dial_Layout::addFin(Fin *f)
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect;
    setupEffect();
    eff->setOpacity(1);
    eff->setOpacityMask(QBrush(*conGrad));
    f->setGraphicsEffect(eff);
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
        conGrad = new QConicalGradient(r.height()/2, r.width()/2, 0);
    }
}

void Dial_Layout::setGeometry(const QRect &r, float ang)
{
    rend->setAngle(ang);
    setGeometry(r);
}

void Dial_Layout::setupEffect()
{
    auto normalizeAngle = [](double degrees) -> double {
        return (degrees - 360.0 * std::floor(degrees / 360.0)) / 360.0;
    };

    conGrad->setStops({});
    conGrad->setColorAt(normalizeAngle(rend->getStart()-5), Qt::transparent);
    conGrad->setColorAt(normalizeAngle(rend->getStart()+rend->getSpan()/4), Qt::black);
    conGrad->setColorAt(normalizeAngle(rend->getStop()-rend->getSpan()/4), Qt::black);
    conGrad->setColorAt(normalizeAngle(rend->getStop()+5), Qt::transparent);
}

void Dial_Layout::setSpan(float start, float stop)
{
    rend->setStart(start);
    rend->setStop(stop);
    num_visible = std::abs(start-stop)/(rend->getSpan()+5);
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
    if (index >= list.count())
        return nullptr;
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
    stretch = false;
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

    int rightFinLoc = int(rightFin->get_loc_angle())%360;
    int leftFinLoc = int(leftFin->get_loc_angle())%360;

    //move the dial left
    if (leftFinLoc >= rend->getStop()+rend->getSpan())
    {
        if (right > 0 && list.count()>num_visible) {moveLeft();}
        else {stretch = true;}
    }

    //move the dial right
    else if (rightFinLoc <=rend->getStart()-rend->getSpan())
    {
        if (left < list.count()-1&& list.count()>num_visible){moveRight();}
        else {stretch = true;}
    }
    else {stretch = true;}

    redraw();
}

void Dial_Layout::moveLeft()
{
    stretch = false;
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
    stretch = false;
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
    left=-1;
    if (list.count() > 0) {
        Fin * f = qobject_cast<Fin *>(list[0]->widget());
        f->offset = rend->getStart();
        f->show();

        int num = (num_visible < list.count()) ? num_visible : list.count()-1;
        for (left = 1; left <= num; left++)
        {
            Fin * newf = qobject_cast<Fin *>(list[left]->widget());
            newf->offset =  f->offset + (rend->getSpan())+5;
            newf->show();
            f = newf;
        }
        left=num;
    }
}

bool Dial_Layout::handleEvent(QInputEvent *e)
{
    bool ret = false;
    for (int i = right; i <= left; i++)
    {
        if (i >= list.count())
        {
            return ret;
        }
        Fin * f = static_cast<Fin *>(list[i]->widget());
        if(f->handleEvent(e))
        {
            if (e->type() == QEvent::MouseButtonRelease){release();}
            ret = true;
        }
    }
    return ret;
}

void Dial_Layout::release()
{
    if(stretch)
    {
        QPropertyAnimation *anim = new QPropertyAnimation(rend, "angle", this);
        anim->setDuration(500);
        anim->setStartValue(rend->getAngle());
        anim->setEndValue(0);
        anim->setEasingCurve(QEasingCurve::OutBounce);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void Dial_Layout::setGrabAngle(float newGrabAngle)
{
    grabAngle = newGrabAngle;
}

void Dial_Layout::redraw()
{
    if(!list.empty())
    {
        for (int i = right; i <= left; i++)
        {
            Fin * f = static_cast<Fin *>(list[i]->widget());
            f->update();
        }
    }
}








