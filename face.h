#ifndef FACE_H
#define FACE_H

#include <QWidget>
#include <QInputEvent>
#include <QPainter>
#include <QPainterPath>

class Face : public QWidget
{
    Q_OBJECT
public:
    explicit Face(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
    bool handleEvent(QInputEvent *e);

signals:
};

#endif // FACE_H
