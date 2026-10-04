#ifndef IPOPULATOR_H
#define IPOPULATOR_H

//#include <QObject>
#include <QImage>
#include <QIcon>
#include <QDateTime>

struct FinDetails
{
    QString path;
    QString name;
    QString exec;
    QDateTime lastModified;
    QIcon ico;
};

class IPopulator
{
public:
    virtual ~IPopulator() = default;
    virtual QList<FinDetails> populateList() = 0;
    virtual QIcon findIcon(QString ico) const = 0;
};

#endif // IPOPULATOR_H
