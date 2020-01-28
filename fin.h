#ifndef FIN_H
#define FIN_H

#include <QWidget>
#include <QtWidgets>

class fin : public QWidget
{
    Q_OBJECT
public:
    int angle;
    int span;
    int res;
    QRectF bound;
    QRect container;
    int grab;
    explicit fin(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void setContainer(QRect box) {container = box;}
    QPainterPath center;

    void mousePressEvent(QMouseEvent *event);
    void make_path();
    void mouseMoveEvent(QMouseEvent *event);
    QSize sizeHint() const;
    ~fin();

signals:

public slots:
};

#endif // FIN_H
