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
    int grab;


    Dial_Layout(QWidget* parent = nullptr);
    void addItem(QLayoutItem *item);
    void addFin(Fin *f);
    void removeFin(Fin *f);
    void setGeometry(const QRect &r);
    void setGeometry(const QRect &r, float ang);
    QSize sizeHint() const;
    QLayoutItem * itemAt(int index) const;
    QLayoutItem * takeAt(int index);
    int count() const;
    bool canAddFin();
    //Moving certain functions from model.h here
    void setAngle(QPoint p);
    static float calcAngle(QPoint c, int res);



public slots:
    void startProgram(QString s);
private:
    QList<QLayoutItem *> list;
    QWidget* p;
    QStack<Fin *> fin_stack;
    QStack<Fin *> fout_stack;
    QList<Fin *> visible;
    float grab_angle;
    int click_angle;
    int res;

    void moveLeft();
    void moveRight();
    void populateList(QWidget* parent);
    //bool event(QEvent * e);
    void mouseMoveEvent(QMouseEvent *event);
    QImage * findIcon(QString s);
};

#endif // DIAL_LAYOUT_H
