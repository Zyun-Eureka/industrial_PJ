#include "mcore.h"
#include <QDebug>

MCore::MCore(QObject *parent)
    : QObject{parent}
{
//    _cdir.setPath("/home/eureka/Pictures/cam");
    _cdir.setPath("D:\\imgs");

//    qDebug()<<"Sql init status:"<<sql.initDB();
}

QString MCore::initCFolder(QString camid)
{
    _cdir.mkdir(camid);
    QDir dir(_cdir);
    dir.cd(camid);
    //tmp
    dir.mkdir("input");
    //
    dir.mkdir(OK_FOLDER);
    dir.mkdir(NG_FOLDER);
    cameraSql::initDB(GetDBName(camid),dir.path());
    return dir.path();
    //    return "";
}

QString MCore::GetDBName(QString cid)
{
    return "DB"+cid+".dat";
}
