#include "localdatabase.h"

LocalDatabase::LocalDatabase(QObject *parent) : QObject(parent)
{
    db_ = QSqlDatabase::addDatabase("QSQLITE","nce");
    db_.setDatabaseName("nce.db");
    if (db_.open()) {
        Q_ASSERT(db_.isOpen());

    } else {
        Q_ASSERT(false);
    }

}

