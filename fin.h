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

    explicit fin(QWidget *parent = nullptr, int e_id = -1, QObject * model = nullptr, QImage* img = nullptr,  QString command = nullptr);
    void paintEvent(QPaintEvent *);
    void setContainer(QRect box) {container = box;}
    QPainterPath center;
    QPainterPath circle;
    QImage image;
    QObject* m;
    QString com;

    void mousePressEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);
    void make_path();
    //void mouseMoveEvent(QMouseEvent *event);
    QSize sizeHint() const;
    QRectF center_img(QImage img);
    double get_loc_angle(){return loc_angle;}
    ~fin();

signals:

public slots:
};

#endif // FIN_H
