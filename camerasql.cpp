#include "camerasql.h"

#include <QDebug>

cameraSql::cameraSql(QObject *parent)
    : QObject{parent}
{
//    this->cid = cid;
}

//bool cameraSql::init(QString sqlpath, QString imgPath)
//{
//    qDebug()<<"init func";
//    return false;
//    db = QSqlDatabase::addDatabase(sqlpath,"QSQLITE");
//    if(!db.open())return false;
//    //
//    QSqlQuery query(db);
//    query.exec("create table cameraImg(id integer primary key autoincrement,name char(256),time date,cameraId int,imgPath char(256),result boolean)");
//    path = imgPath;
//    return true;
//}

//bool cameraSql::insertImg(QString imgName, bool result, QString camera_id)
//{
//    if(!db.isOpen()){
//        return false;
//    }
//    QSqlQuery query;
//    query.prepare("insert into imgs(camera_id,imgName,time,result) values(:0,:1,:2,:3)");
//    query.bindValue(0,camera_id);
//    query.bindValue(1,imgName);
//    query.bindValue(2,QDateTime::currentDateTime().toString(""));
//    query.bindValue(3,result);
//    return query.exec();
//}

//bool cameraSql::newCamera(QString cameraId, QString path)
//{
//    if(!db.isOpen()){
//        return false;
//    }
//    QSqlQuery query;
//    query.prepare("insert into cameras(camera_id,path) values(:0,:1)");
//    query.bindValue(0,cameraId);
//    query.bindValue(1,path);
//    return query.exec();
//}

bool cameraSql::initDB(QString id,QString path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE",id);
    db.setDatabaseName(path+"/"+id);
    if(!db.open()){
        qDebug()<<"DB init failed";
        return false;
    }
//    initTable();
    QSqlQuery query(db);
    query.exec("create table if not exists imgs(id integer primary key autoincrement,imgOldName char(32),imgNewName char(32),iscv boolean,result boolean,times time,dates date)");
    qDebug()<<db.databaseName()<<"DB init Successful";
    return true;
}


//QStringList cameraSql::querImgsName(QString querystr)
//{
//    if(!db.isOpen()){
//    }
//    QSqlQuery query;

//    query.exec(QString("select imgName from imgs where %1").arg(querystr));
//    while (query.next()) {
//        qDebug()<<query.value(0).toString()<<query.value(1).toString();
//    }
//    qDebug()<<"end";
//    return QStringList();
//}
