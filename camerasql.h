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
    bool init(QString sqlpath, QString imgPath);
    //create table cameraImg(id integer primary key autoincrement,name char(256),time date,cameraId int,imgPath char(256),result boolean)

    bool initDB();
    bool initTable();
//    static QStringList querData(QString querystr);
    bool insertImg(QString imgName, bool result, QString camera_id);
    bool newCamera(QString cameraId,QString path);

    QStringList querImgsName(QString querystr);
signals:
private:
    QSqlDatabase db;
    QString cid;
    QString path;
};

#endif // CAMERASQL_H
