#ifndef RADIA_H
#define RADIA_H
//#include "model.h"
#include "fin.h"
#include <QMainWindow>
#include "fin.h"
#include <QtWidgets>
#include "dial.h"
#include "radia_layout.h"



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
    radia_layout *l;
    Dial *upper;
    //Model * m;

    explicit Radia(QWidget *parent = nullptr);
    void begin_state(std::string * img, std::string * name);
    //void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void changeEvent(QEvent *) override;
    bool eventFilter(QObject *object, QEvent *event) override;
    ~Radia();
private:
    Ui::Radia *ui;
};

#endif // RADIA_H
