#include "fin.h"
#include <iostream>
#include <cmath>

double fin::angle = 5;
int fin::res = 500;

fin::fin(QWidget *parent, int off) : QWidget(parent)
{
    grab = 0;
    offset = off;
    inner_res = res/1.5;
    span = 40;
    bound = QRectF(0,0,res,res);
    bound2 = QRectF((inner_res*.25), (inner_res*.25),inner_res, inner_res);
    setGeometry(0,0, res, res);
    make_path();
}

void fin::paintEvent(QPaintEvent *)
{
    make_path();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QColor c(127, 0, 127);
    painter.setPen(Qt::NoPen);
    painter.setBrush(c);
    painter.drawPath(center);
    painter.end();
}

void fin::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //event->pos().x() - offset.x(), event->pos().y() - offset.y()
        QPointF p(event->pos().x(), event->pos().y());
        if (center.contains(p))
        {
            grab = 1;
            grab_angle = calc_angle(event->pos());
        }
        else
        {
            event->ignore();
        }
    }
}

void fin::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        grab = 0;
    }
}

void fin::mouseMoveEvent(QMouseEvent *event)
{
    if (grab)
    {
        double delta = calc_angle(event->pos());
        angle+=delta-grab_angle;
        grab_angle=delta;
        this->repaint();
    } else {
        event->ignore();
    }
}

void fin::make_path()
{
    //center.~QPainterPath();
    loc_angle =angle+offset;
    center = QPainterPath();
    center.arcMoveTo(bound, loc_angle);
    center.arcTo(bound, loc_angle, span);
    center.arcTo(bound2, (span+loc_angle), -span);
    center.closeSubpath();
    center.setFillRule(Qt::WindingFill);
}

double fin::calc_angle(QPoint c)
{
    double x = c.x()-(res/2);
    double ang = (atan(((c.y()*-1)+(res/2))/x)*180)/3.14159;
    if (c.x() < 250) {
        ang+=180;
    }
    return ang;
}

QSize fin::sizeHint() const
{
    return QSize(1920, 1080);
}

fin::~fin(){
    center.~QPainterPath();
}
