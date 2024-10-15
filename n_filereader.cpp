#include "n_filereader.h"
#include <QDateTime>
#include <QTime>
#include <QDate>
#include <QDebug>

#include <QFile>

n_fileReader::n_fileReader(QString connectionName, QObject *parent)
    : QObject{parent}
{
    _img = new QImage();
    _filefilterlist << "*.jpg"<<"*.png"<<"*.jpeg";
    _tmpStrs<<""<<"";
    _sfiles.clear();
    dbcount = 0;//tmp
    return;
    query = new QSqlQuery(QSqlDatabase::database(connectionName));
    query->exec("select count(*) from imgs");
    if(query->next()){
        dbcount = query->value(0).toInt();
    }
}

void n_fileReader::setInputPath(QString str)
{
    _InPath = str + "/input/";
    _dir.setPath(_InPath);
    _OKPath = str + "/OK/";
    _NGPath = str + "/NG/";
    scan();
}

bool n_fileReader::next(bool Retry)
{
    if(!readImage()){
        if(!Retry){
            scan(true);
            return next(true);
        }
        return false;
    }
    if(!screenSizeChange()){
        return false;
    }
    //opencv
    //sql
    //"imgs(id integer primary key autoincrement,imgOldName char(32),imgNewName char(32),result boolean,times time,dates date)"
    i = QString(_tmpStrs[0]).length()-1;
    for(;i>0;i--){
        if(_tmpStrs[0][i]=='.')break;
    }
    query->prepare("insert into imgs(imgOldName,imgNewName,iscv,result,times,dates) values(:0,:1,:2,:3,:4,:5)");
    _tmpStrs[1] = QDateTime::currentDateTime().toString("yyMMddhhmmss%1%2").arg(QString::number(dbcount++)).arg(QString(_tmpStrs[0]).mid(i));
    query->bindValue(0,_tmpStrs[0]);
    query->bindValue(1,_tmpStrs[1]);
    query->bindValue(2,false);
    query->bindValue(3,true);
    query->bindValue(4,QTime::currentTime().toString("hh:mm:ss"));
    query->bindValue(5,QDate::currentDate().toString("yyyy-MM-dd"));
    query->exec();
    //save
    QFile::rename(_InPath+_tmpStrs[0],_NGPath+_tmpStrs[1]);
    emit Readready();
    return true;
}

bool n_fileReader::screenSizeChange(double width, double height)
{
    setScreenSize(width,height);
    if(_img&&_img->isNull())return false;
    if(screenSizeChange()){
        emit Readready();
        return true;
    }
    return false;
}

bool n_fileReader::screenSizeChange()
{
    if(_img&&_img->isNull())return false;
    _X = (_size.width()-_img->width())/2.0;
    _Y = (_size.height()-_img->height())/2.0;
    return true;
}

void n_fileReader::scan(bool mclear)
{
    if(mclear){
        _sfiles.clear();
    }
    if(!_sfiles.isEmpty())return;
    _sfiles = _dir.entryList(_filefilterlist,QDir::NoDotAndDotDot|QDir::Files);
}

bool n_fileReader::readImage()
{
    if(_sfiles.isEmpty())return false;
    _tmpStrs[0] = _sfiles.front();
    *_img = QImage(_InPath+_tmpStrs[0]).scaled(_size,Qt::KeepAspectRatio);
    _sfiles.pop_front();
    return !(_img->isNull());
}

double n_fileReader::GetIX()
{
    return _X;
}

double n_fileReader::GetIY()
{
    return _Y;
}

void n_fileReader::setScreenSize(double width, double height)
{
    _size.setWidth(width);
    _size.setHeight(height);
}

