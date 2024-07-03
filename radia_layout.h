#ifndef RADIA_LAYOUT_H
#define RADIA_LAYOUT_H

#include <QLayout>
#include <QWidget>
#include <QList>
//#include "fin.h"
#include "dial_layout.h"

class Radia_Layout : public QLayout
{
public:
    int angle;
    int count_w;

    Radia_Layout(QWidget* parent);
    void addItem(QLayoutItem *item);
    void addWidget(QWidget *w);
    void removeWidget(QWidget *w);
    void setGeometry(const QRect &r);
    void setGeometry(const QRect &r, int &ang);
    QSize sizeHint() const;
    QLayoutItem * itemAt(int index) const;
    QLayoutItem * takeAt(int index);
    int count() const;
    bool can_add_fin();
    void addLayout(QLayout l);
    void setUpperDial(Dial_Layout* d);
    void setLowerDial(Dial_Layout* d);
//    void addCenterLayout(Center_Layout* c);

private:
    QList<QLayoutItem*> list;
    Dial_Layout* upper;
    Dial_Layout* lower;
};

#endif // RADIA_LAYOUT_H
