#ifndef DATABASE_H
#define DATABASE_H

#include "ipopulator.h"

class Database
{
public:
    Database();
    void addProgram(FinDetails fd);
    void removeProgram(FinDetails fd);
    QList<FinDetails> getByPopScore();
    QList<FinDetails> getPinned();

};

#endif // DATABASE_H
