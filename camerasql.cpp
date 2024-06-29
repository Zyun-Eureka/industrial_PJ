#include "camerasql.h"

#include <QDebug>

cameraSql::cameraSql(QObject *parent)
    : QObject{parent}
{
//    this->cid = cid;
}

bool cameraSql::init(QString sqlpath, QString imgPath)
{
    qDebug()<<"init func";
    return false;
    db = QSqlDatabase::addDatabase(sqlpath,"QSQLITE");
    if(!db.open())return false;
    //
    QSqlQuery query(db);
    query.exec("create table cameraImg(id integer primary key autoincrement,name char(256),time date,cameraId int,imgPath char(256),result boolean)");
    path = imgPath;
    return true;
}

bool cameraSql::insertImg(QString imgName, bool result, QString camera_id)
{
    if(!db.isOpen()){
        return false;
    }
    QSqlQuery query;
    query.prepare("insert into imgs(camera_id,imgName,time,result) values(:0,:1,:2,:3)");
    query.bindValue(0,camera_id);
    query.bindValue(1,imgName);
    query.bindValue(2,QDateTime::currentDateTime().toString(""));
    query.bindValue(3,result);
    return query.exec();
}

bool cameraSql::newCamera(QString cameraId, QString path)
{
    if(!db.isOpen()){
        return false;
    }
    QSqlQuery query;
    query.prepare("insert into cameras(camera_id,path) values(:0,:1)");
    query.bindValue(0,cameraId);
    query.bindValue(1,path);
    return query.exec();
}

bool cameraSql::initDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.dat");
    if(!db.open()){
        qDebug()<<"DB init failed";
        return false;
    }
    initTable();
    return true;
}

bool cameraSql::initTable()
{
    QSqlQuery query;
    //"create table cameraImg(id integer primary key autoincrement,name char(256),time date,cameraId int,imgPath char(256),result boolean)"
    query.exec("create table if not exists cameras(id integer primary key autoincrement,camera_id char(5) primary key,path char(256))");
    query.exec("create table if not exists imgs(id integer primary key autoincrement,camera_id integer primary key,imgName char(128),time date,result boolean)");
    return false;
}

QStringList cameraSql::querImgsName(QString querystr)
{
    if(!db.isOpen()){
    }
    QSqlQuery query;

    query.exec(QString("select imgName from imgs where %1").arg(querystr));
    while (query.next()) {
        qDebug()<<query.value(0).toString()<<query.value(1).toString();
    }
    qDebug()<<"end";
    return QStringList();
}
