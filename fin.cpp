#include "fin.h"
#include <iostream>
#include <cmath>

double fin::angle = 5;
int fin::res = 500;
int fin::x = 0;
int fin::y = 0;
int fin::span = 30;

fin::fin(QWidget *parent, int e_id, QObject * model) : QWidget(parent)
{
    m = model;
    event_id = e_id;
    grab = 0;
    off = false;
    inner_res = res/1.5;
    bound = QRectF(x,y,res,res);
    bound2 = QRectF(((inner_res+x)*.25), ((inner_res+y)*.25),inner_res, inner_res);
    setGeometry(x,y, res, res);
    image = QImage("/home/knil/Pictures/test.png");
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
    QRectF source(0.0, 0.0, 64, 64);
    image = image.scaled(64,64);
    QRectF target = center_img(image);
    circle = QPainterPath();
    circle.arcTo(target, 0, 360);
    painter.setClipPath(circle);
    if (!off){
        painter.drawImage(target, image, source);
    }
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
        angle = int(angle) % 360;
        QCoreApplication::postEvent(m, new QEvent(QEvent::Type(event_id)));
        this->repaint();
    } else {
        event->ignore();
    }
}

void fin::make_path()
{
    loc_angle =angle+offset;
    center = QPainterPath();
    if (loc_angle < 140 && loc_angle >= 0)
    {
        center.arcMoveTo(bound, loc_angle);
        center.arcTo(bound, loc_angle, span);
        center.arcTo(bound2, (span+loc_angle), -span);
        center.closeSubpath();
        center.setFillRule(Qt::WindingFill);
        if (ang_check > 0)
        {
            off = false;
            //printf("%d\n", grab);
        }
    }
    else
    {
        off = true;
    }
}

double fin::calc_angle(QPoint c)
{
    double x = c.x()-(res/2);
    double ang = rad_to_deg(atan(((c.y()*-1)+(res/2))/x)); //Mmmm Pi
    if (c.x() < res/2) {
        ang+=180;
    }
    return ang;
}

QRectF fin::center_img(QImage img)
{
    //Sos the algo is this:
    int r = int ((res+inner_res)/4); //Take the average of the RADII
    double rad = deg_to_rad(loc_angle+(span/2));
    int centeredx = ((res+x)/2)-(img.size().width()/2);
    int centeredy = ((res+y)/2)-(img.size().height()/2);
    int i_x = int (r*cos(-rad)+centeredx); //move from radial to cartesian and adjust for placement
    int i_y = int (r*sin(-rad)+centeredy); //also ajust for finding the upper left corner
    QRectF ret(i_x,i_y,img.size().width(),img.size().height());
    return ret;
}

QSize fin::sizeHint() const
{
    return QSize(1920, 1080);
}

double fin::deg_to_rad(double theta)
{
    return theta*(3.14159/180);
}

double fin::rad_to_deg(double theta)
{
    return theta*(180/3.14159);
}

fin::~fin(){
    center.~QPainterPath();
}
