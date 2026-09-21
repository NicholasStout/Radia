#ifndef FINRENDER_H
#define FINRENDER_H

class FinRender
{
public:
    FinRender();
    float getAngle();
    int getSpan();
    int getStop() const;

    int getStart() const;
private:
    float angle;
    int span;
    int start;
    int stop;
    void setAngle(float ang);
    void setSpan(int s);
    void setStop(int newStop);
    void setStart(int newStart);


    friend class Dial_Layout;
};

#endif // FINRENDER_H
