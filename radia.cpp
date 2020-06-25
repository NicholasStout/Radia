#include "radia.h"
#include "model.h"
#include "search.h"
#include "fin.h"
#include "radia_layout.h"
#include <QtWidgets>
#include <iostream>

/*
 * This encompassing class serves as the View and Controller of the MVC design pattern. The model is called inside of it.
*/
Radia::Radia(QWidget *parent) :
    QWidget(parent)
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
    l = new Radia_Layout(this);
    //setLayout(l);
    m = new Model(l, this);

    QSize *size = new QSize(500, 500);

    //Get demensions for the launcher

    QRect *start = new QRect(QCursor::pos(), *size);
    setGeometry(*start);
    setFixedHeight(h);
    setFixedWidth(w);
}

void Radia::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    //printf("%d,%d\n", event->pos().x(), event->y());
    m->set_angle(event->pos());
    this->repaint();
}

bool Radia::eventFilter(QObject *object, QEvent *event)
{
    //qDebug() << event->type();
    return false;
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

void Radia::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        printf("Mouse release: %d,%d\n", event->x(), event->y());
        event->ignore();
    }
}

void Radia::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::ActivationChange) {
        if (!this->isActiveWindow()) {
            QApplication::quit();
        }
    }
}

Radia::~Radia()
{

}
