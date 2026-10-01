#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QMap>
#include "ipopulator.h"

class FileHandler : public QObject, public IPopulator
{
    Q_OBJECT
public:
    FileHandler(QObject *parent = nullptr);
    const QList<FinDetails> populateList() override;
    QIcon findIcon(QString ico) const override;
    const QList<FinDetails> getDesktopFiles();
private:
    QList<QMap<QString, QString>> cache;
private slots:
    void assessChange(const QString &path);
};

#endif // FILEHANDLER_H
