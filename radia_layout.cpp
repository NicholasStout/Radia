#include "radia_layout.h"

Radia_Layout::Radia_Layout() :
    QLayout(nullptr)
{
    angle = 35;
    count_w = 0;
}
void Radia_Layout::addItem(QLayoutItem *item)
{
    fin *f = (fin*) item->widget();
    list.append(item);

}

void Radia_Layout::addWidget(QWidget *w)
{
    fin* f =(fin*) w;
    f->offset = count_w*angle;
    count_w++;
    addItem(new QWidgetItem(w));
}

void Radia_Layout::setGeometry(const QRect &r)
{
    if (r.width() == r.height())
    {
        QList<QLayoutItem *>::iterator itr = list.begin();
        fin *f = (fin *)(*itr)->widget();
        f->x = r.x();
        f->y = r.y();
        f->span = angle;

        for (; itr != list.end(); itr++) {
            f = (fin *)(*itr)->widget();
            f->setGeometry(r);
        }
    }
    //TODO: add a way to change angle
}

int Radia_Layout::count() const
{
    return list.size();
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
            return nullptr;
}
QLayoutItem * Radia_Layout::takeAt(int index)
{
    if (index > 0 && index < list.size())
        return list.takeAt(index);
    else
            return nullptr;
}


