#include "database.h"

//TODO:Finish

Database::Database(QObject *parent) : QObject(parent)
{
    setParent(parent);
    QString name = qgetenv("USER");
    if (name.isEmpty())
        name = qgetenv("USERNAME");
    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName("localhost");
    //db.setDatabaseName("/home/"+name+"/.local/share/Radia/radiadb");
    db.setDatabaseName("radiadb");
    //db.setUserName(name);
    //db.setPassword("BingusTingus");
    bool ok = db.open();
    if (!ok) {
        qDebug() << "Database error:" << db.lastError().text();
        return;
    }
    else
    {
        qDebug() << "Database ok";
    }

    query = QSqlQuery(db);
    query.exec("CREATE TABLE IF NOT EXISTS radia ("
               "popularity INTEGER default 0,"
               "pinned INTEGER default 0,"
               "path TEXT NOT NULL UNIQUE,"
               "name TEXT NOT NULL,"
               "exec TEXT NOT NULL UNIQUE,"
               "lastModified INTEGER default 0,"
               "ico TEXT"
               ");");
}

void Database::addProgram(FinDetails fd)
{
    addProgram(fd.path, fd.name, fd.exec, fd.lastModified, fd.ico.name());
}

void Database::addProgram(QString path, QString name, QString exec, QDateTime lastModified, QString ico)
{
    query.prepare("INSERT INTO radia (path, name, exec, lastModified, ico) "
                  "VALUES (?, ?, ?, ?, ?);");
    query.addBindValue(path);
    query.addBindValue(name);
    query.addBindValue(exec);
    query.addBindValue(lastModified.toMSecsSinceEpoch());
    query.addBindValue(ico);
    query.exec();
}

void Database::removeProgram(FinDetails fd)
{
    query.prepare("DELETE FROM radia WHERE path = ?;");
    //query.addBindValue(fd.name);
    query.addBindValue(fd.path);
    //query.addBindValue(fd.ico.name());
    query.exec();
}

void Database::incrementPopularity(FinDetails fd)
{
    query.prepare("UPDATE radia SET popularity = popularity + 1 WHERE path = ?;");
    query.addBindValue(fd.path);
    query.exec();
}

void Database::pinFin(FinDetails fd)
{
    query.prepare("UPDATE radia SET pinned = (SELECT COALESCE(MAX(pinned), 0) + 1 "
                  "FROM radia) WHERE path = ?;");
    query.addBindValue(fd.path);
    query.exec();
}

void Database::unpinFin(FinDetails fd)
{
    query.prepare("UPDATE radia SET pinned = 0"
                  "WHERE path = ?;");
    query.addBindValue(fd.path);
    query.exec();
}

QList<FinDetails> Database::getByPopScore()
{
    query.exec("SELECT path, name, exec, lastModified, ico FROM radia WHERE pinned = 0 ORDER BY popularity DESC;");
    return generateList();
}

QList<FinDetails> Database::getAll()
{
    query.exec("SELECT path, name, exec, lastModified, ico FROM radia;");
    return generateList();
}

QList<FinDetails> Database::getPinned()
{
    query.exec("SELECT path, name, exec, lastModified, ico FROM radia WHERE pinned > 0 ORDER BY pinned ASC;");
    return generateList();
}

QList<FinDetails> Database::generateList()
{
    QList<FinDetails> list;
    while (query.next())
    {
        FinDetails fd;
        QDateTime dt;
        fd.path = query.value(0).toString();
        fd.name = query.value(1).toString();
        fd.exec = query.value(2).toString();
        fd.lastModified = dt.addMSecs(query.value(3).toInt());
        QFileInfo path(query.value(4).toString());
        if (path.isAbsolute()) {
            fd.ico = QIcon(query.value(4).toString());
        } else {
            fd.ico = QIcon::fromTheme(query.value(4).toString());
        }
        list.append(fd);
    }
    return list;
}
