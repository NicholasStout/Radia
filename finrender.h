#ifndef FINRENDER_H
#define FINRENDER_H
#include <QObject>


class FinRender : public QObject
{
Q_OBJECT
Q_PROPERTY(float angle READ getAngle WRITE setAngle)
public:
    FinRender(QObject *parent = nullptr);
    float getAngle();
    int getSpan();
    int getStop() const;

    int getStart() const;

signals:
    void redraw();

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
