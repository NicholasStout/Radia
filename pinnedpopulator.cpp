#include "pinnedpopulator.h"

PinnedPopulator::PinnedPopulator(Database *d, QObject *parent) : QObject{parent}
{
    db = d;
}

QList<FinDetails> PinnedPopulator::populateList()
{
    return db->getPinned();
}

QIcon PinnedPopulator::findIcon(QString ico) const
{
    return QIcon();
}
