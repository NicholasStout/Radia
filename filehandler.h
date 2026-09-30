#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QMap>
#include "ipopulator.h"

class FileHandler : public IPopulator
{
public:
    FileHandler();
    const QList<FinDetails> populateList() override;
    QIcon findIcon(QString ico) const override;
private:
    QList<QMap<QString, QString>> cache;
};

#endif // FILEHANDLER_H
