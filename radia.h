#ifndef RADIA_H
#define RADIA_H
#include "model.h"
#include "fin.h"
#include <QMainWindow>

namespace Ui {
class Radia;
}

class Radia : public QMainWindow
{
    Q_OBJECT

public:
    QRect container;
    QPainter * painter;
    fin f;
    Radia_Layout *l;
    Model * m;

    explicit Radia(QWidget *parent = nullptr);
    void begin_state(std::string * img, std::string * name);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event);
    ~Radia();

private:
    Ui::Radia *ui;
};

#endif // RADIA_H
