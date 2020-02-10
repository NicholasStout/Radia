#ifndef FIN_H
#define FIN_H

#include <QWidget>
#include <QtWidgets>

class fin : public QWidget
{
    Q_OBJECT
public:
    static double angle;
    static int span;
    static int res;
    static int x;
    static int y;

    int offset;
    double loc_angle;
    double inner_res;
    QRectF bound;
    QRectF bound2;
    QRect container;
    int grab;
    double grab_angle;
    bool off;
    double ang_check;
    int event_id;

    explicit fin(QWidget *parent = nullptr, int e_id = -1, QObject * model = nullptr);
    void paintEvent(QPaintEvent *);
    void setContainer(QRect box) {container = box;}
    QPainterPath center;
    QPainterPath circle;
    QImage image;
    QObject * m;

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void make_path();
    void mouseMoveEvent(QMouseEvent *event);
    double calc_angle(QPoint c);
    double deg_to_rad(double theta);
    double rad_to_deg(double theta);
    QSize sizeHint() const;
    QRectF center_img(QImage img);
    ~fin();

signals:

public slots:
};

#endif // FIN_H
