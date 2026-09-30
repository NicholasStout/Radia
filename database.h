#ifndef DATABASE_H
#define DATABASE_H

#include "ipopulator.h"
#include <QtSql>

class Database
{
public:
    Database();
    void addProgram(FinDetails fd);
    void removeProgram(FinDetails fd);
    void incrementPopularity(FinDetails fd);
    void pinFin(FinDetails fd);
    QList<FinDetails> getByPopScore();
    QList<FinDetails> getPinned();

private:
    QSqlDatabase db;
    QSqlQuery query;
    QList<FinDetails> generateList();
};

#endif // DATABASE_H
