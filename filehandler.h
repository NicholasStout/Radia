#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QMap>
#include "ipopulator.h"
#include "database.h"

class FileHandler : public QObject
{
    Q_OBJECT
public:
    FileHandler(Database *data, QObject *parent = nullptr);
    QList<FinDetails> populateList();
    QIcon findIcon(QString ico) const;
    QList<FinDetails> getDesktopFiles();
private:
    QList<QMap<QString, QString>> cache;
    Database *db;
private slots:
    void assessChange(const QString &path);
    //void increasePopularity(FinDetails fd) const;
    //void pinFin(FinDetails fd) const;
};

#endif // FILEHANDLER_H
