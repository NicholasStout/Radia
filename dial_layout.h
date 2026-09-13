#ifndef DIAL_LAYOUT_H
#define DIAL_LAYOUT_H

#include <QLayout>
#include <QWidget>
#include <QtWidgets>
#include <QList>
#include <QEvent>
#include <QtSvg/QSvgRenderer>
#include "fin.h"

class Dial_Layout : public QLayout
{
//    Q_OBJECT
public:
    float angle;
    bool grab;


    Dial_Layout(QWidget* parent = nullptr);
    void addItem(QLayoutItem *item) override;
    void addFin(Fin *f);
    void removeFin(QString name);
    void setGeometry(const QRect &r) override;
    void setGeometry(const QRect &r, float ang);
    void setSpan(float start, float stop);
    QSize sizeHint() const override;
    QLayoutItem * itemAt(int index) const override;
    QLayoutItem * takeAt(int index) override;
    int count() const override;
    bool canAddFin();
    //bool hasHeightForWidth();
    //int heightForWidth();
    //Moving certain functions from model.h here
    void setAngle(QPoint p);
    //static float calcAngle(QPoint c, int res);
    void moveLeft();
    void moveRight();
    void loadVisible();
    QList<QLayoutItem *> list;
    QWidget* p;
    bool handleEvent(QInputEvent *e);

public slots:
    void setGrab(bool msg);
    void slide(QMouseEvent* e);

private:
    float grab_angle;
    int click_angle;
    int res;
    int left, right, num_visible;
    float startAng, stopAng;

    //bool event(QEvent * e);
    //void mouseMoveEvent(QMouseEvent *event);
    //bool eventFilter(QObject *object, QEvent *event);
};

#endif // DIAL_LAYOUT_H
