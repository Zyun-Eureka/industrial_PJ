#ifndef CAMERASQL_H
#define CAMERASQL_H

#include <QObject>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>

#include <QVariant>

class cameraSql : public QObject
{
    Q_OBJECT
public:
    explicit cameraSql(QObject *parent = nullptr);
    bool init(QString name);
    //create table cameraImg(id integer primary key autoincrement,name char(256),time date,cameraId int,imgPath char(256),result boolean)
    bool insertImg(QString name,bool result,QString path="");

    QStringList querData(QString querystr);

signals:
private:
    QSqlDatabase db;
    QString cid;
    QString path;
};

#endif // CAMERASQL_H
