#include "filehandler.h"
#include <QDir>
#include <QDirIterator>
#include <QIcon>
#include <QFileInfo>
#include "ipopulator.h"

FileHandler::FileHandler() : IPopulator{} {}

const QList<FinDetails> FileHandler::populateList()
{
    QString base_uri = "/usr/share/applications/";
    QDirIterator programs(base_uri, QStringList() << "*.desktop",QDir::Files, QDirIterator::Subdirectories);
    QList<FinDetails> ret;
    while (programs.hasNext()) {
        QString app = programs.next();
        QFile file(app);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {continue;}


        QMap<QString, QString> dict;
        while (!file.atEnd()){
            QStringList parse = QString(file.readLine()).trimmed().split('=');
            if (!dict.contains(parse.first())) {
                dict.insert(parse.first(), parse.last());
            }
        }
        if (dict.value("NoDisplay")=="true") {continue;}
        if (dict.value("Terminal")=="true") {continue;}
        if (dict.value("Type") != "Application") {continue;}

        QString ico = dict.value("Icon");
        QIcon img = findIcon(ico);

        FinDetails fd;
        fd.exec=dict.value("Exec");
        fd.ico=img;
        fd.name=dict.value("Name");

        ret.append(fd);
        cache.append(dict);
    }
    return ret;
}

QIcon FileHandler::findIcon(QString ico) const
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
