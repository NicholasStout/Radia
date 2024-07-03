#include "fin.h"
#include <iostream>
#include <cmath>
#include <string>
//#include <model.h>
#include "dial_layout.h"



/*
 * This class is to be the radial widget that encircles the center widget. When this widget is clicked, the program it is representing launches.
 * */

double Fin::angle = 5;
double Fin::grab_angle = 0;
int Fin::res = 500;
int Fin::x = 0;
int Fin::y = 0;
int Fin::span = 30;

Fin::Fin(QWidget *parent, QObject* dial, QImage* img, QString command) : QWidget(parent)
{
    //setMouseTracking(true);
    m = dial;
    grab = 0;
    off = false;
    inner_res = res/1.5;
    bound = QRectF(x,y,res,res);
    bound2 = QRectF(((inner_res+x)*.25), ((inner_res+y)*.25),inner_res, inner_res);
    setGeometry(x,y, res, res);
    if (img && !img->isNull()) {
        image = *img;
    }
    else {
        image = QImage("nothin");
    }
    com = command;
}

void Fin::paintEvent(QPaintEvent *)
{
    make_path();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QColor c(127, 0, 127);
    //painter.setPen(Qt::NoPen);
    painter.setBrush(c);
    painter.drawPath(center);
    QRectF source(0.0, 0.0, 64, 64);
    try {
        image = image.scaled(64,64);
    } catch (QException e) {
        std::cout << com.toStdString();
    }
    QRectF target = center_img(image);
    circle = QPainterPath();
    circle.arcTo(target, 0, 360);
    painter.setClipPath(circle);
    painter.drawImage(target, image, source);
    QString ang_string;
    ang_string.setNum(loc_angle);
    //painter.drawText(target, Qt::AlignCenter, ang_string);
    painter.end();
}

void Fin::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //event->pos().x() - offset.x(), event->pos().y() - offset.y()
        QPointF p(event->pos().x(), event->pos().y());
        if (center.contains(p))
        {
            std::cout << "Mouse grabbed by "+ com.toStdString()+'\n';
            //Model * mod = (Model*)m;
            //mod->grab = 1;
            grab_angle = calcAngle(event->pos(), res);
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
    else
    {
        event->ignore();
    }
}

void Fin::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (calcAngle(event->pos(), res) == grab_angle && center.contains(event->pos()))
        {
                emit start(com);
                event->accept();
        } else {
            event->ignore();
        }
    } else {
        event->ignore();
    }
}

void Fin::mouseMoveEvent(QMouseEvent *event)
{
    //printf("fin mouse move: %d,%d\n", event->x(),event->y());
    event->ignore();
}

void Fin::make_path()
{
    loc_angle =angle+offset;
    center = QPainterPath();
    center.arcMoveTo(bound, loc_angle);
    center.arcTo(bound, loc_angle, span);
    center.arcTo(bound2, (span+loc_angle), -span);
    center.closeSubpath();
    center.setFillRule(Qt::WindingFill);
}

QRectF Fin::center_img(QImage img)
{
    //Sos the algo is this:
    int r = int ((res+inner_res)/4); //Take the average of the radii
    double rad = degToRad(loc_angle+(span/2));
    int centeredx = ((res+x)/2)-(img.size().width()/2);
    int centeredy = ((res+y)/2)-(img.size().height()/2);
    int i_x = int (r*cos(-rad)+centeredx); //move from radial to cartesian and adjust for placement
    int i_y = int (r*sin(-rad)+centeredy); //also ajust for finding the upper left corner
    QRectF ret(i_x,i_y,img.size().width(),img.size().height());
    return ret;
}

QSize Fin::sizeHint() const
{
    return QSize(1920, 1080);
}

Fin::~Fin(){
    center.~QPainterPath();
}
