#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "ipopulator.h"
#include "filehandler.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(FileHandler *f, QObject *parent = nullptr);

signals:
    void updateFinList();

public slots:
    void launchProgram(FinDetails fd) const;
    void togglePin(FinDetails fd) const;

private:
    FileHandler * fh;
};

#endif // CONTROLLER_H
