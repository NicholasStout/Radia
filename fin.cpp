#include "fin.h"
#include <iostream>
#include <cmath>
#include <string>

/*
 * This class is to be the radial widget that encircles the center widget. When this widget is clicked, the program it is representing launches.
 * */

double fin::angle = 5;
int fin::res = 500;
int fin::x = 0;
int fin::y = 0;
int fin::span = 30;

fin::fin(QWidget *parent, int e_id, QObject * model, QImage* img, QString command) : QWidget(parent)
{
    m = model;
    event_id = e_id;
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
        image = QImage("/home/knil/Pictures/test.jpg");
    }
    com = command;
}

void fin::paintEvent(QPaintEvent *)
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
    ang_string.setNum(angle);
    painter.drawText(target, Qt::AlignCenter, ang_string);
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
            event->accept();
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
        event->ignore();
    }
}

void fin::mouseMoveEvent(QMouseEvent *event)
{
    if (grab)
    {
        //angle = calc_angle(event->pos());
        double curr_angle = calc_angle(event->pos());
        //printf("%d,%d,%f,%f ", event->x(), event->y(),delta,grab_angle);
        int delta = round(curr_angle-grab_angle);
        if (delta != 0) {
            angle+=delta;
            grab_angle=curr_angle;
        }
        angle = int(angle+360) % 360;
        QCoreApplication::postEvent(m, new QEvent(QEvent::Type(event_id)));
        this->repaint();
        event->accept();
    } else {
        event->ignore();
    }
}

void fin::make_path()
{
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
    double ang = rad_to_deg(atan(((c.y()*-1)+(res/2))/x)); //Mmmm Pi
    if (c.x() < res/2) {
        ang+=180;
    } else if (c.y() >= (res/2.0)) {
        ang+=360;
    }
    return ang;
}

QRectF fin::center_img(QImage img)
{
    //Sos the algo is this:
    int r = int ((res+inner_res)/4); //Take the average of the radii
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
