#include "fin.h"
#include <iostream>

fin::fin(QWidget *parent) : QWidget(parent)
{
    res = 260;
    angle =30;
    span = 80;
    bound = QRectF(res * 0.75, res * 0.75, res * 1.5, res * 1.5);
    setGeometry(0,0, 1920, 1080);
    //make_path();
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
    //painter.end();
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
        angle+=30;
        this->repaint();
    }
}

void fin::make_path()
{
    //center.~QPainterPath();
    center = QPainterPath();
    center.arcMoveTo(bound, angle);
    center.arcTo(bound, angle, span);
    center.arcTo(-res, -res, res * 2, res * 2, (span+angle), -span);
    center.closeSubpath();
    center.setFillRule(Qt::WindingFill);
}

QSize fin::sizeHint() const
{
    return QSize(1920, 1080);
}

fin::~fin(){
    center.~QPainterPath();
}
