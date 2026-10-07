#ifndef POPULARITYPOPULATOR_H
#define POPULARITYPOPULATOR_H

#include <QObject>
#include "ipopulator.h"
#include "database.h"

class PopularityPopulator : public QObject, public IPopulator
{
    Q_OBJECT
public:
    explicit PopularityPopulator(Database *d, QObject *parent = nullptr);
    QList<FinDetails> populateList() override;
    QIcon findIcon(QString ico) const override;
    ~PopularityPopulator(){}


signals:

private:
    Database *db;
};

#endif // POPULARITYPOPULATOR_H
