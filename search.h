#ifndef SEARCH_H
#define SEARCH_H
#include <QtWidgets>

class Search : public QWidget
{
public:
    int size;
    QPainterPath center;
    Search(QWidget *parent);
    void paintEvent(QPaintEvent *);
};

#endif // SEARCH_H
