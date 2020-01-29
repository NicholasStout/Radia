#ifndef FIN_H
#define FIN_H

#include <QWidget>
#include <QtWidgets>

class fin : public QWidget
{
    Q_OBJECT
public:
    static double angle;
    int span;
    static int res;
    int offset;
    double loc_angle;
    double inner_res;
    QRectF bound;
    QRectF bound2;
    QRect container;
    int grab;
    double grab_angle;
    explicit fin(QWidget *parent = nullptr, int off = 0);
    void paintEvent(QPaintEvent *);
    void setContainer(QRect box) {container = box;}
    QPainterPath center;

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void make_path();
    void mouseMoveEvent(QMouseEvent *event);
    double calc_angle(QPoint c);
    QSize sizeHint() const;
    ~fin();

signals:

public slots:
};

#endif // FIN_H
