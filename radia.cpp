#include "radia.h"
#include "model.h"
#include "search.h"
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
    QRect screen = QApplication::desktop()->availableGeometry(this);

    QSize *size = new QSize(screen.height(), screen.width());

    //Get demensions for the launcher

    QRect *start = new QRect(QPoint(0,0), *size);
    setGeometry(*start);
    setFixedHeight(screen.height());
    setFixedWidth(screen.width());
    m = Model();
}


void Radia::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QColor c(127, 0, 127);
    painter.setPen(Qt::NoPen);
    painter.setBrush(c);
    QPainterPath center;
    //painter.drawPath(center);
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
