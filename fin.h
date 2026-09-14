#ifndef FIN_H
#define FIN_H

#include <QWidget>
#include <QtWidgets>

class Fin : public QWidget
{
    Q_OBJECT
public:
    static double angle;
    static int span;
    static int res;
    static int x;
    static int y;
    static double grab_angle;

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

    explicit Fin(QWidget *parent = nullptr, QIcon* img = nullptr,  QString command = nullptr);
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
    double get_loc_angle(){return angle+loc_angle;}
    ~Fin();

    void showUp();
signals:
    void setGrab(bool g);
    void mouseMoved(QMouseEvent* e);

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
