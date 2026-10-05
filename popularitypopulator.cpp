#include "popularitypopulator.h"

PopularityPopulator::PopularityPopulator(Database *d, QObject *parent)
    : QObject{parent}
{
    db = d;
}

QList<FinDetails> PopularityPopulator::populateList()
{
    return db->getByPopScore();
}

QIcon PopularityPopulator::findIcon(QString ico) const
{
    QIcon img;
    QFileInfo path(ico);

    if (path.isAbsolute()) {
        img = QIcon(ico);
    } else {
        img = QIcon::fromTheme(ico);
    }
    return img;
}
