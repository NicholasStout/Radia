#include "face.h"
#include "QDateTime"

Face::Face(QWidget *parent)
    : QWidget{parent}
{}

void Face::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QColor c(127, 0, 127);
    painter.setPen(Qt::NoPen);
    painter.setBrush(c);
    painter.drawEllipse(geometry());

    QDateTime time = QDateTime().currentDateTime();
    painter.drawText(0,0, time.toString());
}

bool Face::handleEvent(QInputEvent *e)
{
    return false;
}
