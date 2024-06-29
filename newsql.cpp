#include "newsql.h"

#include <QDebug>

newSql::newSql(QObject *parent)
    : QObject{parent}
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

void newSql::init(QString cid)
{
    db.setDatabaseName(cid);
    qDebug()<<"DB "<<cid<<" status"<<db.open();
}
