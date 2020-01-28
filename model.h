#ifndef MODEL_H
#define MODEL_H
#include <string>

class Model
{
public:
    enum stage{
        end,
        begin
    };
    typedef struct state
    {
        stage curr_stage;
        std::string *img;
        std::string *name;
    };

    state s = {end, NULL, NULL};

    Model();
    int get_angle(int x, int y);
    state * reg_click(int x, int y);
    state * get_state();

};

#endif // MODEL_H
