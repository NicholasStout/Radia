#ifndef RADIA_H
#define RADIA_H
//#include "model.h"
#include "fin.h"
#include "radia_layout.h"
#include "dial_layout.h"
#include <QMainWindow>

namespace Ui {
class Radia;
}

class Radia : public QWidget
{
    Q_OBJECT

public:
    QRect container;
    QPainter * painter;
    Fin f;
    Radia_Layout *l;
    //Model * m;

    explicit Radia(QWidget *parent = nullptr);
    void begin_state(std::string * img, std::string * name);
    //void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void changeEvent(QEvent *) override;
    bool eventFilter(QObject *object, QEvent *event) override;
    ~Radia();

private:
    Ui::Radia *ui;
};

#endif // RADIA_H
