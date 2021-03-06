#ifndef RADIA_LAYOUT_H
#define RADIA_LAYOUT_H

#include <QLayout>
#include <QWidget>
#include <QList>
#include "fin.h"

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

private:
    QList<QLayoutItem*> list;
};

#endif // RADIA_LAYOUT_H
