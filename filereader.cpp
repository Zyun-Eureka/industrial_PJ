#include "filereader.h"

#include <QDebug>
#include <QThread>

#include <QPainter>

#include <QFile>

#include <QRandomGenerator>

FileReader::FileReader(QObject *parent)
    : QObject{parent}
{
    img = nullptr;
    //path to read
    //pen
    ok_pen.setBrush(QColor(255,255,255,100));
    ok_pen.setWidth(2);
    ok_pen.setColor(Qt::green);
    //font
    ok_font.setPixelSize(30);

    watcher = new QFileSystemWatcher();
//    connect(watcher,SIGNAL(directoryChanged(QString)),this,SLOT(FileChange(QString)));
}

FileReader::~FileReader()
{
//    watcher->deleteLater();
}

bool FileReader::setcid(int cid)
{
    this->cid = cid;
//    return false;
//    if(path.isEmpty())return false;
//    if(sql!=nullptr){
//        delete sql;
//    }
//    sql = new cameraSql(cid);
    return true;
}

void FileReader::setImgBuffer(QImage *img)
{
    this->img = img;
}

//bool FileReader::writeBuffer(QString _imgPath,int flage)
//{
//    if(img==nullptr)return false;
//    *img =QImage(_imgPath).scaled(size,Qt::KeepAspectRatio);
//    if(flage!=-1){
//        QPainter pa(img);
//        pa.setPen(flage==0?ok_pen:ng);
//        pa.setFont(ok_font);
////        pa.setBrush(flage==0?QColor(255,255,255,100):QColor(255,0,0,100));
//        pa.drawRect(4,4,80,30);
//        pa.drawText(4,4,80,30,Qt::AlignCenter,flage==0?"OK":"NG");
//    }
//    if(!img->isNull()){
//        x = (size.width()-img->width())/2.0;
//        y = (size.height()-img->height())/2.0;
//        Readready();
//    }
//}

void FileReader::setPath(QString path)
{
    //img save path
//    qDebug()<<path;
    this->path = path;
    dir.setPath(path);
//    watcher->addPath(dir.path()+"/input");
}

bool FileReader::next(bool change)
{
    return false;
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

void FileReader::scan(bool again)
{
//    if(!again&&!wlock.tryLock())return;

//    files.clear();
//    QFile file;
//    QDir _dir = dir;
//    _dir.cd("input");
//    for(QString i:_dir.entryList(list,QDir::NoDotAndDotDot|QDir::Files)){
//        file.setFileName(_dir.path()+"\\"+i);
//        if(img==nullptr)break;
//        *img = QImage(file.fileName()).scaled(size,Qt::KeepAspectRatio);
//        if(!img->isNull()){
//            x = (size.width()-img->width())/2.0;
//            y = (size.height()-img->height())/2.0;
//            Readready();
//            if(QRandomGenerator::global()->generate()%9==1){
//                file.rename(dir.path()+"\\NG\\"+i);
//                cvResult(0);
//            }else{
//                file.rename(dir.path()+"\\OK\\"+i);
//                cvResult(1);
//            }
//        }else{
//            qDebug()<<file.fileName();
//        }
//    }
//    if(again){
//        scan(false);
//    }
//    else wlock.unlock();
}

void FileReader::setSize(QSize size)
{
    this->size = size;
    next(true);
}

int FileReader::GetType()
{
    return -1;
}

double FileReader::GetValue()
{
    return -1;
}

void FileReader::FileChange(QString s)
{
//    qDebug()<<s;
    scan();
}
