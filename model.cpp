#include "model.h"
#include <string>

Model::Model()
{
    s.curr_stage = begin;
    s.img = NULL;
    s.name = NULL;
}

int Model::get_angle(int x, int y)
{
 return x+y; //temp to make warning go away
}

Model::state* Model::get_state()
{
    return &s;
}

Model::state* Model::reg_click(int x, int y)
{
    x+y;
    return &s;
}

