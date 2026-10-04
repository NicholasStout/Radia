#include "filehandler.h"
#include <QDir>
#include <QDirIterator>
#include <QIcon>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include "ipopulator.h"

QString base_uri = "/usr/share/applications/";
FileHandler::FileHandler(Database *data, QObject *parent) : QObject(parent){
    db = data;
    QFileSystemWatcher *watcher = new QFileSystemWatcher(this);
    watcher->addPath(base_uri);
    connect(watcher, &QFileSystemWatcher::directoryChanged,
                     this, &FileHandler::assessChange);
}

QList<FinDetails> FileHandler::populateList()
{
    return getDesktopFiles();
}

QList<FinDetails> FileHandler::getDesktopFiles()
{
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

void FileHandler::assessChange(const QString &path)
{

}

void FileHandler::increasePopularity(const FinDetails fd)
{

}

void FileHandler::pinFin(const FinDetails fd)
{

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
