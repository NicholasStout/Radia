#ifndef MODEL_H
#define MODEL_H
#include <string>
#include <QWidget>
#include <QtWidgets>
#include <QEvent>
#include "fin.h"
#include "radia_layout.h"

class Model : public QObject
{
public:

    explicit Model(Radia_Layout * l);
    ~Model();
private:
    QStack<fin *> fin_stack;
    QStack<fin *> fout_stack;
    QList<fin *> visible;
    Radia_Layout * layout;
    int event_id;

    void move_left();
    void move_right();
    void populate_list();
    bool event(QEvent * e);
};

#endif // MODEL_H
