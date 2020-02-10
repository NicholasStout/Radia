#include "model.h"
#include <string>

/*
 * This is a model under the MVC design pattern, as well as acting as a factory for the fin Objects, which are their own controllers.
 * This objects creats fins based on what programs they are to run, as well as adding and hiding objects as they are needed.
 */

Model::Model(Radia_Layout * l) : QObject(nullptr)
{
    event_id = QEvent::registerEventType();
    populate_list();
}

void Model::move_left()
{

}
void Model::move_right()
{

}
bool Model::event(QEvent * e)
{
    if (int(e->type()) == event_id)
        return true;
}
void Model::populate_list()
{

}
Model::~Model(){}

