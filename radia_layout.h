#ifndef RADIA_LAYOUT_H
#define RADIA_LAYOUT_H

#include <QLayout>
#include <QObject>
#include <QWidget>
#include "dial.h"


class radia_layout : public QLayout
{
public:
    radia_layout(QWidget *parent);
    void setGeometry(const QRect &r) override;
    void addItem(QLayoutItem *item) override;
    QSize sizeHint() const override;
    QLayoutItem * itemAt(int index) const override;
    QLayoutItem * takeAt(int index) override;
    bool handleEvent(QInputEvent *e);
    void setUpperDial(Dial* d);
    void setLowerDial(Dial* d);
    int count() const override;

    void passEvent(QEvent *event);
private:
    QList<QLayoutItem *> itemList;

};

#endif // RADIA_LAYOUT_H
