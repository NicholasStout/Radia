#ifndef PINNEDPOPULATOR_H
#define PINNEDPOPULATOR_H

#include <QObject>
#include "ipopulator.h"
#include "database.h"

class PinnedPopulator : public QObject, public IPopulator
{
    Q_OBJECT
public:
    explicit PinnedPopulator(Database *d, QObject *parent = nullptr);
    QList<FinDetails> populateList() override;
    QIcon findIcon(QString ico) const override;
    ~PinnedPopulator(){}

private:
    Database *db;
};

#endif // PINNEDPOPULATOR_H
