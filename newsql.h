#ifndef NEWSQL_H
#define NEWSQL_H

#include <QObject>

#include <QSqlDatabase>

class newSql : public QObject
{
    Q_OBJECT
public:
    explicit newSql(QObject *parent = nullptr);

    void init(QString cid);

signals:
private:
    QSqlDatabase db;
};

#endif // NEWSQL_H
