#ifndef MCORE_H
#define MCORE_H

#include <QObject>

#include <QEvent>

#include <QDir>

#include "camerasql.h"

#define OK_FOLDER "OK"
#define NG_FOLDER "NG"

class MCore : public QObject
{
    Q_OBJECT
public:
    explicit MCore(QObject *parent = nullptr);


    QString getCDir(){return _cdir.path();}
    void setCDir(QString dir){_cdir.setPath(dir);}
    QString initCFolder(QString camid);

signals:
private:
    //camera dir
    cameraSql sql;
//
    QDir _cdir;
};

#endif // MCORE_H
