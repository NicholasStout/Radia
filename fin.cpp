#include "fin.h"
#include <iostream>
#include <cmath>
#include <string>
#include <model.h>


/*
 * This class is to be the radial widget that encircles the center widget. When this widget is clicked, the program it is representing launches.
 * */

double fin::angle = 5;
double fin::grab_angle = 0;
int fin::res = 500;
int fin::x = 0;
int fin::y = 0;
int fin::span = 30;

fin::fin(QWidget *parent, int e_id, QObject * model, QImage* img, QString command) : QWidget(parent)
{
    setMouseTracking(true);
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
    ang_string.setNum(loc_angle);
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
            Model * mod = (Model*)m;
            mod->grab = 1;
            grab_angle = Model::calc_angle(event->pos(), res);
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

//void fin::mouseReleaseEvent(QMouseEvent *event)
//{
//    if (event->button() == Qt::LeftButton)
//    {
//        grab = 0;
//        event->ignore();
//    }
//}

//void fin::mouseMoveEvent(QMouseEvent *event)
//{
//    //if (grab)
//    //{
//        //angle = calc_angle(event->pos());
////    if (!grab) {
////        event->ignore();
////    } else {
//        event->accept();
//        double curr_angle = calc_angle(event->pos());
//        double delta = curr_angle-grab_angle;
//        printf("%f", grab_angle);
//        if (delta != 0) {
//            angle+=delta;
//            grab_angle=curr_angle;
//        }
//        if (angle > 360 || angle < 0) {
//            angle = int(angle+360) % 360;
//        }
//        QCoreApplication::postEvent(m, new QEvent(QEvent::Type(event_id)));
//        this->repaint();
//    //} else {
//    //    event->ignore();
////    }
//}

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

QRectF fin::center_img(QImage img)
{
    //Sos the algo is this:
    int r = int ((res+inner_res)/4); //Take the average of the radii
    double rad = Model::deg_to_rad(loc_angle+(span/2));
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

fin::~fin(){
    center.~QPainterPath();
}
