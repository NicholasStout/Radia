#ifndef DIAL_LAYOUT_H
#define DIAL_LAYOUT_H

#include <QLayout>
#include <QWidget>
#include <QList>
#include <QEvent>
#include <QtSvg/QSvgRenderer>
#include "fin.h"
#include "finrender.h"

class Dial_Layout : public QLayout
{
//    Q_OBJECT
public:
    //float angle;
    //float grabAngle;
    //float finAngle;
    bool grab;


    Dial_Layout(QWidget* parent = nullptr, FinRender* fr = nullptr);
    void addItem(QLayoutItem *item) override;
    void setGeometry(const QRect &r) override;
    QSize sizeHint() const override;
    QLayoutItem * itemAt(int index) const override;
    QLayoutItem * takeAt(int index) override;
    int count() const override;
    void addFin(Fin *f);
    void removeFin(QString name);
    void setGeometry(const QRect &r, float ang);
    void setSpan(float start, float stop);
    bool canAddFin();
    void setAngle(QPoint p);
    void moveLeft();
    void moveRight();
    void loadVisible();
    QList<QLayoutItem *> list;
    QWidget* p;
    bool handleEvent(QInputEvent *e);
    void setGrabAngle(float newGrabAngle);

public slots:
    void redraw();

private:
    bool stretch;
    float grabAngle;
    int click_angle;
    int res;
    int left, right, num_visible;
    void release();
    FinRender *rend;
};

#endif // DIAL_LAYOUT_H
