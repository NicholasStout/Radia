#ifndef MODEL_H
#define MODEL_H
#include <string>
#include <QWidget>
#include <QtWidgets>
#include <QEvent>
#include <QtSvg/QSvgRenderer>
#include "fin.h"
#include "radia_layout.h"

class Model : public QObject
{
public:
    int grab;

    explicit Model(Radia_Layout * l, QWidget * parent);
    void set_angle(QPoint p);
    static double calc_angle(QPoint c, int res);
    static double deg_to_rad(double theta)
    {
        return theta*(3.14159/180);
    }

    static double rad_to_deg(double theta)
    {
        return theta*(180/3.14159);
    }
    ~Model();
private:
    QStack<fin *> fin_stack;
    QStack<fin *> fout_stack;
    QList<fin *> visible;
    Radia_Layout * layout;
    int event_id;
    double * angle;
    double * grab_angle;
    int prev_angle;
    int * res;
    QWidget * p;

    void move_left();
    void move_right();
    void populate_list();
    //bool event(QEvent * e);
    void mouseMoveEvent(QMouseEvent *event);
    QImage * find_icon(QString s);
};

#endif // MODEL_H
