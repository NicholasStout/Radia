#include "fin.h"
#include <iostream>
#include <cmath>
//#include <model.h>
//#include "dial_layout.h"



/*
 * This class is to be the radial widget that encircles the center widget. When this widget is clicked, the program it is representing launches.
 * */

double Fin::angle = 5;
double Fin::grab_angle = 0;
int Fin::res = 500;
int Fin::x = 0;
int Fin::y = 0;
int Fin::span = 30;

Fin::Fin(QWidget *parent, QIcon* img, QString command) : QWidget(parent)
{
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
        image = QIcon();
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
    //QRectF source(0.0, 0.0, 64, 64);
    QRectF target = center_img(image);
    circle = QPainterPath();
    circle.arcTo(target, 0, 360);
    painter.setClipPath(circle);
    image.paint(&painter, target.toRect());
    QString ang_string;
    ang_string.setNum(loc_angle);
    painter.drawText(target, Qt::AlignCenter, ang_string);
    painter.end();
}

void Fin::make_path()
{
    loc_angle = angle+offset;
    center = QPainterPath();
    center.arcMoveTo(bound, loc_angle);
    center.arcTo(bound, loc_angle, span);
    center.arcTo(bound2, (span+loc_angle), -span);
    center.closeSubpath();
    center.setFillRule(Qt::WindingFill);
}

QRectF Fin::center_img(QIcon img)
{
    //Sos the algo is this:
    QSize size = img.actualSize(QSize(64,64));
    int r = int ((res+inner_res)/4); //Take the average of the radii
    double rad = degToRad(loc_angle+(span/2));
    int centeredx = ((res+x)/2)-(size.width()/2);
    int centeredy = ((res+y)/2)-(size.height()/2);
    int i_x = int (r*cos(-rad)+centeredx); //move from radial to cartesian and adjust for placement
    int i_y = int (r*sin(-rad)+centeredy); //also ajust for finding the upper left corner
    QRectF ret(i_x,i_y,size.width(),size.height());
    return ret;
}

void Fin::startProgram() {
    QProcess *process = new QProcess();
    QStringList lst = com.split(' ');
    QString prog = lst.takeFirst();
    qDebug() << "launching " << com;
    int result = process->startDetached(prog, lst);
    qDebug() << "result: " << result;
    QApplication::quit();
}

QSize Fin::sizeHint() const
{
    return QSize(1920, 1080);
}

Fin::~Fin(){
    //center.~QPainterPath();
}


bool Fin::handleEvent(QInputEvent *e)
{
    //qDebug() << "fin";
    switch (e->type())
    {
    case QEvent::MouseButtonPress:
        return mousePress(static_cast<QMouseEvent *>(e));
    case QEvent::MouseButtonRelease:
        return mouseRelease(static_cast<QMouseEvent *>(e));
    case QEvent::MouseMove:
        return true;
    default:
        return false;
    }
}

bool Fin::mousePress(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF p(event->pos().x(), event->pos().y());
        //qDebug()<<event->pos().x();
        //qDebug() <<event->pos().y();
        //qDebug() << center.boundingRect();

        if (center.contains(p))
        {
            std::cout << "Mouse grabbed by "+ com.toStdString()+'\n';
            grab_angle = calcAngle(event->pos(), res);
            event->accept();
            setFocus(Qt::MouseFocusReason);
            return true;
        }
        else
        {
            event->ignore();
            return false;
        }
    }
    else
    {
        event->ignore();
        return false;
    }
}

bool Fin::mouseRelease(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (calcAngle(event->pos(), res) == grab_angle && center.contains(event->pos()))
        {
                startProgram();
                event->accept();
                return true;
        } else {
            return true;
            event->ignore();
        }
    } else {
        return true;
        event->ignore();
    }
}

void Fin::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event);
    event->accept();
}

void Fin::showUp()
{
    setVisible(true);
}


