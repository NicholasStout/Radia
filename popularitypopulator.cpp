#include "popularitypopulator.h"

PopularityPopulator::PopularityPopulator(FileHandler *f, QObject *parent)
    : QObject{parent}
{
    fh = f;
}

QList<FinDetails> PopularityPopulator::populateList()
{
    return QList<FinDetails>();
}

QIcon PopularityPopulator::findIcon(QString ico) const
{
    return QIcon();
}
