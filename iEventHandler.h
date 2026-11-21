#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H

#include <QInputEvent>

class iEventHandler
{
public:
    virtual ~iEventHandler() = default;
    virtual bool handleEvent(QInputEvent *e);
};

#endif // IEVENTHANDLER_H
