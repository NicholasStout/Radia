#include "database.h"

//TODO:Finish

Database::Database() {
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
    query.exec("CREATE TABLE IF NOT EXISTS radia ("
               "popularity INTEGER default 0,"
               "pinned INTEGER default 0,"
               "name TEXT NOT NULL,"
               "exec TEXT NOT NULL UNIQUE,"
               "ico TEXT"
               ");");
}

void Database::addProgram(FinDetails fd)
{
    query.prepare("INSERT INTO radia (name, exec, ico) "
                  "VALUES (?, ?, ?);");
    query.addBindValue(fd.name);
    query.addBindValue(fd.exec);
    query.addBindValue(fd.ico.name());
    query.exec();
}

void Database::removeProgram(FinDetails fd)
{
    query.prepare("DELETE FROM radia WHERE exec = ?;");
    //query.addBindValue(fd.name);
    query.addBindValue(fd.exec);
    //query.addBindValue(fd.ico.name());
    query.exec();
}

void Database::incrementPopularity(FinDetails fd)
{
    query.prepare("UPDATE radia SET popularity = popularity + 1 WHERE exec = ?;");
    query.addBindValue(fd.exec);
    query.exec();
}

void Database::pinFin(FinDetails fd)
{
    query.prepare("UPDATE radia SET pinned = (SELECT COALESCE(MAX(pinned), 0) + 1 "
                  "FROM radia) WHERE exec = ?;");
    query.addBindValue(fd.exec);
    query.exec();
}

QList<FinDetails> Database::getByPopScore()
{
    query.exec("SELECT name, exec, ico FROM radia WHERE pinned = 0 ORDER BY popularity DESC;");
    return generateList();
}

QList<FinDetails> Database::getPinned()
{
    query.exec("SELECT name, exec, ico FROM radia WHERE pinned > 0 ORDER BY pinned ASC;");
    return generateList();
}

QList<FinDetails> Database::generateList()
{
    QList<FinDetails> list;
    while (query.next())
    {
        FinDetails fd;
        fd.name = query.value(0).toString();
        fd.exec = query.value(1).toString();
        fd.ico = QIcon(query.value(2).toString());
        list.append(fd);
    }
    return list;
}
