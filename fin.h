#ifndef FIN_H
#define FIN_H

#include <QWidget>
#include <QtWidgets>
#include "finrender.h"
#include "ipopulator.h"

class Fin : public QWidget
{
    Q_OBJECT
public:
    static int res;
    static int x;
    static int y;
    static float grab_angle;

    int offset;
    double loc_angle;
    double inner_res;
    QRectF bound;
    QRectF bound2;
    QRect container;
    int grab;
    bool off;
    double ang_check;
    int event_id;
    float span;

    FinDetails det;
    FinRender *rend;

    explicit Fin(QWidget *parent, FinDetails fd, FinRender* fr = nullptr);
    void paintEvent(QPaintEvent *) override;
    void setContainer(QRect box) {container = box;}
    QPainterPath center;
    QPainterPath circle;
    QIcon image;
    QObject* m;
    QString com;

    bool handleEvent(QInputEvent *e);

    bool mousePress(QMouseEvent *event);
    bool mouseRelease(QMouseEvent *event);
    void make_path();
    void mouseMoveEvent(QMouseEvent *event) override;
    QSize sizeHint() const override;
    QRectF center_img(QIcon img);
    double get_loc_angle(){return rend->getAngle()+offset;}
    ~Fin();

    void showUp();
signals:
    void finSelected(FinDetails det);
    void TogglePin(FinDetails det);
    //void mouseMoved(QMouseEvent* e);

public slots:
private:
    void startProgram();
};


static float degToRad(double theta)
    {
        return theta*(3.14159/180);
    }

static float radToDeg(double theta)
    {
        return theta*(180/3.14159);
    }

static float calcAngle(QPoint c, int res)
    {
        double x = c.x()-(res/2);
        double ang = radToDeg(atan(((c.y()*-1)+(res/2))/x)); //Mmmm Pi
        if (c.x() < res/2) {
            ang+=180;
        } else if (c.y() >= (res/2.0)) {
            ang+=360;
        }
        return ang;
    }




#endif // FIN_H
