#include "radia.h"
#include "model.h"
#include "search.h"
#include "fin.h"
#include "radia_layout.h"
#include <QtWidgets>

/*
 * This encompassing class serves as the View and Controller of the MVC design pattern. The model is called inside of it.
*/
Radia::Radia(QWidget *parent) :
    QMainWindow(parent)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::FramelessWindowHint);
    //set screen invisble and frameless

    QRect off = QApplication::desktop()->screenGeometry(this);
    int h, w;
    h = w = 0;
    for (QScreen * s : QGuiApplication::screens()) {
        QRect screen = s->availableGeometry();
        h+=screen.height();
        w+=screen.width();
    }
    //setMouseTracking(true);
    l = new Radia_Layout;
    m = new Model(l, this);

    QSize *size = new QSize(h, w);

    //Get demensions for the launcher

    QRect *start = new QRect(QPoint(0,0), *size);
    setGeometry(*start);
    setFixedHeight(h);
    setFixedWidth(w);
}

void Radia::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    m->set_angle(event->pos());
    this->repaint();
}

void Radia::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QColor c(127, 0, 127);
    painter.setPen(Qt::NoPen);
    painter.setBrush(c);
    QPainterPath center;
    painter.drawPath(center);
    painter.end();
}

void Radia::mousePressEvent(QMouseEvent *event)
{
    qInfo();
    QApplication::quit();
}


Radia::~Radia()
{

}
