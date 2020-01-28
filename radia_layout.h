#ifndef RADIA_LAYOUT_H
#define RADIA_LAYOUT_H

#include <QLayout>
#include <QWidget>

class Radia_Layout : public QLayout
{
public:
    Radia_Layout(QWidget *parent);
    void addWidget(QWidget *w);
};

#endif // RADIA_LAYOUT_H
