#ifndef IPOPULATOR_H
#define IPOPULATOR_H

#include <QObject>
#include <QImage>
#include <QIcon>

struct FinDetails
{
    QString name;
    QString exec;
    QIcon ico;
};

class IPopulator
{
public:
    virtual ~IPopulator() = default;
    virtual const QList<FinDetails> populateList() = 0;
    virtual QIcon findIcon(QString ico) const = 0;
};

#endif // IPOPULATOR_H
