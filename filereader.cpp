#include "filereader.h"

#include <QDebug>
#include <QThread>

FileReader::FileReader(QObject *parent)
    : QObject{parent}
{
    img = nullptr;
}

void FileReader::setImgBuffer(QImage *img)
{
    this->img = img;
}

void FileReader::setPath(QString path)
{
    this->path = path;
    dir.setPath(path);
    files.clear();

//    scan();
//    next();
}

bool FileReader::next(bool change)
{
    if(img==nullptr)return false;
    if(change&&img->isNull())return false;
    if(files.isEmpty())return false;
    if(!change){
        *img =QImage(dir.path()+"/"+files.front()).scaled(size,Qt::KeepAspectRatio);
    }else{
        *img =img->scaled(size,Qt::KeepAspectRatio);
    }
    if(!img->isNull()){
        x = (size.width()-img->width())/2.0;
        y = (size.height()-img->height())/2.0;
        Readready();
    }
    if(!change){
        files.push_back(files.front());
        files.pop_front();
    }
}

void FileReader::scan()
{
    QStringList list;
    list << "*.jpg"<<"*.png";
    for(QString i:dir.entryList(list,QDir::NoDotAndDotDot|QDir::Files)){
        files.push_back(i);
    }
}

void FileReader::setSize(QSize size)
{
    this->size = size;
    next(true);
}

void FileReader::initFolder(QString id)
{
    dir.mkdir(id);
    QDir tmp = dir;
    tmp.cd(id);
    tmp.mkdir(OK_FOLDER);
    tmp.mkdir(NG_FOLDER);
    sql.init(tmp.path()+"/mydb.dat");
}
