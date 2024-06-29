#include "filereader.h"

#include <QDebug>
#include <QThread>

#include <QPainter>

FileReader::FileReader(QObject *parent)
    : QObject{parent}
{
    img = nullptr;
    //path to read
    connect(this,&FileReader::opencvrun,this,[=](QString pa){
        opencv::run(pa,&op_sig);
    });

    connect(&op_sig,SIGNAL(ImgResult(QString,size_t,float)),this,SLOT(opencvresult(QString,size_t,float)));


    //pen
    ok_pen.setBrush(QColor(255,255,255,100));
    ok_pen.setWidth(2);
    ok_pen.setColor(Qt::green);
    //font
    ok_font.setPixelSize(30);
//    sql.init(
//    sql = nullptr;
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

bool FileReader::writeBuffer(QString _imgPath,int flage)
{
    if(img==nullptr)return false;
    *img =QImage(_imgPath).scaled(size,Qt::KeepAspectRatio);
    if(flage!=-1){
        QPainter pa(img);
        pa.setPen(flage==0?ok_pen:ng);
        pa.setFont(ok_font);
//        pa.setBrush(flage==0?QColor(255,255,255,100):QColor(255,0,0,100));
        pa.drawRect(4,4,80,30);
        pa.drawText(4,4,80,30,Qt::AlignCenter,flage==0?"OK":"NG");
    }
    if(!img->isNull()){
        x = (size.width()-img->width())/2.0;
        y = (size.height()-img->height())/2.0;
        Readready();
    }
}

void FileReader::setPath(QString path)
{
    //img save path
    this->path = path;
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

void FileReader::scan()
{
    return;
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
}

void FileReader::ReadImg(QString str,bool r)
{
    //    QImage img(str);
    //opencv
    qDebug()<<str<<path;
    if(r&&!str.isEmpty())
        opencvrun(str);
    else
        writeBuffer(str);
    //save
}

int FileReader::GetType()
{
    return -1;
}

double FileReader::GetValue()
{
    return -1;
}

void FileReader::opencvresult(QString path, size_t size, float value)
{
    QString name;
    int i =path.size()-1;
    for(;i>0;i--){
        if(path[i]=='/'){
            break;
        }
    }
    name = path.mid(i);
    //qDebug()<<path<<size<<value;
    if(!cid.isEmpty()){
//        cameraSql::insertImg(name,true,cid);
    }else{
        qDebug()<<"sqls need cid";
    }
    writeBuffer(path,size);
    qDebug()<<QFile::copy(path,this->path+"/OK"+name);
}
