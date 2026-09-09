#include "radia_layout.h"

radia_layout::radia_layout(QWidget *parent) : QLayout{parent} {
}

void radia_layout::addItem(QLayoutItem *item)
{
    itemList.append(item);
}

void radia_layout::setGeometry(const QRect &r)
{
    QLayout::setGeometry(r);
    for (int i = 0; i < count(); ++i)
    {
        itemAt(i)->setGeometry(r);
    }

}

QSize radia_layout::sizeHint() const
{
    return QSize(500, 500);
}

QLayoutItem *radia_layout::itemAt(int index) const
{
     return itemList.value(index);
}

QLayoutItem *radia_layout::takeAt(int index)
{
    if (index >= 0 && index < itemList.size())
        return itemList.takeAt(index);
    return nullptr;
}

void radia_layout::setUpperDial(Dial *d)
{
    d->setBoundaryAngles(0, 180);
    QLayout::addWidget(d);

}

void radia_layout::setLowerDial(Dial *d)
{
    d->setBoundaryAngles(-27.5, -125);
    QLayout::addWidget(d);
}

int radia_layout::count() const
{
    return itemList.count();
}


