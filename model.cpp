#include "model.h"
#include <string>
#include <stdlib.h>


/*
 * This is a model under the MVC design pattern, as well as acting as a factory for the fin Objects, which are their own controllers.
 * This objects creats fins based on what programs they are to run, as well as adding and hiding objects as they are needed.
 */

Model::Model(Radia_Layout * l, QWidget * parent) : QObject(nullptr)
{
    layout = l;
    p = parent;
    event_id = QEvent::registerEventType();
    populate_list();
    angle = &visible.front()->angle;
    prev_angle = int(*angle);
}

void Model::move_left()
{
    if (!fout_stack.isEmpty())
    {
        printf("Move left\n");
        fin * hold = visible.takeLast();
        layout->removeWidget(hold);
        hold->hide();
        fin_stack.push(hold);
        hold = fout_stack.pop();
        hold->offset = visible.first()->offset-layout->angle;
        visible.front()->setParent(hold);
        hold->setParent(p);
        hold->show();

        visible.prepend(hold);
        layout->addWidget(hold);
    }
}
void Model::move_right()
{
    if (!fin_stack.isEmpty())
    {
        printf("Move right\n");
        fin * hold = visible.takeFirst();
        visible.first()->setParent(p);
        visible.first()->show();
        layout->removeWidget(hold);
        hold->hide();
        fout_stack.push(hold);
        hold = fin_stack.pop();
        hold->setParent(visible.back());
        hold->show();
        hold->offset = visible.back()->offset+layout->angle;
        visible.append(hold);
        layout->addWidget(hold);
    }
}
bool Model::event(QEvent * e)
{
    if (int(e->type()) == event_id)
    {
        int delta;
        if (*angle)
        if (*angle >= (prev_angle+layout->angle)%360)
        {
            //move_left();
            prev_angle = int(*angle);
        } else if (abs(*angle-prev_angle) >= layout->angle)
        {
            //move_right();
            prev_angle = int(*angle);
        }
        return true;
    }
    e->ignore();
    return false;
}
void Model::populate_list()
{
    fin * f = new fin(p, event_id, this);
    f->offset = 0;
    fin_stack.push(f);
    f->hide();
    for (int i = 1; i < 7; i++)
    {
        f = new fin(f, event_id, this);
        f->offset = layout->angle*i;
        fin_stack.prepend(f);
        f->hide();
    }    
    while (layout->can_add_fin())
    {
        visible.append(fin_stack.pop());
        layout->addWidget(visible.last());
    }
    if (visible.isEmpty()) {
        throw 1;
    }
}

Model::~Model(){}

