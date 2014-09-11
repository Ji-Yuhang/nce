#include "database.hxx"
#include <assert.h>
Database* Database::g_db = 0;
Database::Database(QObject *parent) :
    QObject(parent)
{
    assert(!g_db);
    g_db = this;
}

Database *Database::instance()
{
    return g_db;
}
