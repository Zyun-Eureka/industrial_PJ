#include "camerasql.h"

#include <QDebug>

cameraSql::cameraSql(QObject *parent)
    : QObject{parent}
{
    //    db = QSqlDatabase::addDatabase()
}

bool cameraSql::init(QString name)
{
    db = QSqlDatabase::addDatabase(name);
    if(!db.open())return false;
    //
    QSqlQuery query(db);
    query.exec("create table cameraImg(id integer primary key autoincrement,name char(256),time date,cameraId int,imgPath char(256),result boolean)");
    return true;
}

bool cameraSql::insertImg(QString name, bool result, QString path)
{
    QSqlQuery query(db);
    query.prepare("insert into cameraImg(name,time,cameraId,imgPath,result) values(:0,:1,:2,:3,:4,:5)");
    query.bindValue(0,name);
    query.bindValue(1,QDateTime::currentDateTime().toString(""));
    query.bindValue(2,cid);
    if(path.isEmpty()){
        query.bindValue(3,this->path);
    }else{
        query.bindValue(3,path);
    }
    query.bindValue(4,result);
    qDebug()<<query.executedQuery();
    return query.exec();
}

QStringList cameraSql::querData(QString querystr)
{
    QSqlQuery query(db);
//    query.prepare("select name,imgPath from cameraImg where resualt = :0");
//    query.bindValue(0,querystr);
    query.exec(QString("select name,imgPath from cameraImg where %1").arg(querystr));
    while (query.next()) {
        qDebug()<<query.value(0).toString()<<query.value(1).toString();
    }
    qDebug()<<"end";
    return QStringList();
}
