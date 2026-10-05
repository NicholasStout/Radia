#ifndef DATABASE_H
#define DATABASE_H

#include "ipopulator.h"
#include <QtSql>

class Database : public QObject
{
public:
    Database(QObject *parent = nullptr);
    void addProgram(FinDetails fd);
    void addProgram(QString path, QString name, QString exec, QDateTime lastModified, QString ico);
    void removeProgram(FinDetails fd);
    void incrementPopularity(FinDetails fd);
    void pinFin(FinDetails fd);
    QList<FinDetails> getByPopScore();
    QList<FinDetails> getAll();
    QList<FinDetails> getPinned();

private:
    QSqlDatabase db;
    QSqlQuery query;
    QList<FinDetails> generateList();
};

#endif // DATABASE_H
