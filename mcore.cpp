#include "mcore.h"
#include <QDebug>

MCore::MCore(QObject *parent)
    : QObject{parent}
{
    _cdir.setPath("/home/eureka/Pictures/cam");

    qDebug()<<"Sql init status:"<<sql.initDB();
}

QString MCore::initCFolder(QString camid)
{
    _cdir.mkdir(camid);
    QDir dir(_cdir);
    dir.cd(camid);
    dir.mkdir(OK_FOLDER);
    dir.mkdir(NG_FOLDER);
    sql.newCamera(camid,dir.path());
    return dir.path();
}
