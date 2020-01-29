#include "fin.h"
#include <iostream>
#include <cmath>

int fin::angle = 0;
int fin::res = 500;

fin::fin(QWidget *parent, int off) : QWidget(parent)
{
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

void fin::mouseMoveEvent(QMouseEvent *event)
{
    if (grab)
    {
        angle+=grab_angle-calc_angle(event->pos());
        this->repaint();
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
    return sqrt(pow(c.x()-res/2, 2)+pow(c.y()-res/2, 2));
}

QSize fin::sizeHint() const
{
    return QSize(1920, 1080);
}

fin::~fin(){
    center.~QPainterPath();
}
