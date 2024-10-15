#ifndef N_FILEREADER_H
#define N_FILEREADER_H

#include <QObject>
#include <QImage>
#include <QMutex>
#include <QFile>

#include <QSize>

#include <QDir>

#include <QSqlQuery>
// new file reader
// 2024/9/12 by eureka

class n_fileReader : public QObject
{
    Q_OBJECT
public:
    explicit n_fileReader(QString connectionName,QObject *parent = nullptr);

    //set image path
    //auto scan folder
    void setInputPath(QString);
    //change to next image,paint image from buffer if get readready signal
    bool next(bool Retry = false);

    //get image buffer point
    QImage* ImgBuffer(){return _img;};
    //put new screen size ,the image will change sutiable size and send readready signal
    bool screenSizeChange(double width,double height);
    bool screenSizeChange();
    //image position in screen
    double GetIX();
    double GetIY();
signals:
    // when the signal send, from ImgBuffer() Get Image point and painting to the screen
    //
    void Readready();
    //
    void ReadImgPath();
private:
    //scan folder
    void scan(bool mclear = false);
    //from _sfiles read frist name to read image
    bool readImage();
    //
    void setScreenSize(double width,double height);
    //
    double _X;
    double _Y;
    //image buffer
    QImage *_img;
    //
    int i;
    QStringList _tmpStrs;
    //folder file list
    QStringList _files;
    //scanned file list
    QStringList _sfiles;
    //thread lock
    QMutex _wlock;
    QStringList _filefilterlist;
    //folder dir
    QDir _dir;
    QFile _file;
    //camera screen size
    QSize _size;
    // sqlquery
    QSqlQuery* query;
    //
    int dbcount;
    // input path
    QString _InPath;
    // ok path
    QString _OKPath;
    // ng path
    QString _NGPath;
};

#endif // N_FILEREADER_H
