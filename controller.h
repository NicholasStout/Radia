#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "ipopulator.h"
#include "database.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(Database *d, QObject *parent = nullptr);

signals:
    void updateFinList();

public slots:
    void launchProgram(FinDetails fd) const;
    void togglePin(FinDetails fd) const;

private:
    Database * db;
};

#endif // CONTROLLER_H
