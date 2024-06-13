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
    scan();
}

bool FileReader::next()
{
    if(img==nullptr)return false;
    if(files.isEmpty())return false;
    img->load(dir.path()+"/"+files.front());
    Readready();
    files.push_back(files.front());
    files.pop_front();
}

void FileReader::scan()
{
    QStringList list;
    list << "*.jpg"<<"*.png";
    for(QString i:dir.entryList(list,QDir::NoDotAndDotDot|QDir::Files)){
        files.push_back(i);
    }
}
