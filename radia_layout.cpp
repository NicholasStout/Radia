#include "radia_layout.h"



/*
 *  This class serves as a layout for the dials and other bits of UI. In QT, a layout is important for automatic loading and placement of apps.
 * This class overrides this functionality in order to lay the widgets on top of one another.
 * This is necessary as they must be the same size and in the same position to draw and rotate correctly.
 * */

Radia_Layout::Radia_Layout(QWidget* parent) :
    QLayout(parent)
{
    angle = 35;
    count_w = 0;
    upper = nullptr;
    lower = nullptr;
}

void Radia_Layout::addItem(QLayoutItem *item)
{

}

void Radia_Layout::setGeometry(const QRect &r)
{
    if (r.width() == r.height())
    {
        geom = &r;
        if (upper != nullptr){
            upper->setGeometry(r);
        }
        if (lower != nullptr){
            lower->setGeometry(r);
        }
    }
    //TODO: add a way to change angle
}

void Radia_Layout::setGeometry(const QRect &r, int &ang)
{
    setGeometry(r);
    //TODO: add a way to change angle
}

int Radia_Layout::count() const
{
    return list.size();
}

bool Radia_Layout::can_add_fin()
{
    return (list.size() < (180/angle));
}

QSize Radia_Layout::sizeHint() const
{
    return QSize(500, 500);
}
QLayoutItem * Radia_Layout::itemAt(int index) const
{
    if (index > 0 && index < list.size())
        return list.at(index);
    else
            return 0;
}
QLayoutItem * Radia_Layout::takeAt(int index)
{
    if (index > 0 && index < list.size())
        return list.takeAt(index);
    else
            return 0;
}
void Radia_Layout::setUpperDial(Dial_Layout* l)
{
    if (upper != nullptr) {
        delete upper;
    }
    upper = l;
    l->setGeometry(*geom);
}


