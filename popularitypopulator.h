#ifndef POPULARITYPOPULATOR_H
#define POPULARITYPOPULATOR_H

#include <QObject>
#include "ipopulator.h"
#include "filehandler.h"

class PopularityPopulator : public IPopulator, QObject
{
    Q_OBJECT
public:
    explicit PopularityPopulator(FileHandler *f, QObject *parent = nullptr);
    QList<FinDetails> populateList() override;
    QIcon findIcon(QString ico) const override;
    ~PopularityPopulator(){}


signals:

private:
    FileHandler *fh;
};

#endif // POPULARITYPOPULATOR_H
