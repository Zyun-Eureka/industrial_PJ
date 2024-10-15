#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>

#include <QImage>
#include <QDir>

#include <QPen>
#include <QFont>
#include "camerasql.h"

//#include "opencv.h"

#include <QFileSystemWatcher>
#include <QMutex>

//#define OK_FOLDER "OK"
//#define NG_FOLDER "NG"
//
//
//

class FileReader : public QObject
{
    Q_OBJECT
public:
    explicit FileReader(QObject *parent = nullptr);
    ~FileReader();

    // sql camera id
    bool setcid(int cid);
    // camera save img path
    void setPath(QString);
    QString getpath(){return path;}

    // set img buffer
    void setImgBuffer(QImage *);

//    bool writeBuffer(QString _imgPath, int flage=-1);
    //old
    bool next(bool = false);
    void scan(bool again = true);
    void setSize(QSize);

    void putImg(QString str);

    int GetType();
    double GetValue();

    int x;
    int y;
signals:
    void Readready();
    void cvResult(int);
private slots:
    void FileChange(QString);
private:
    QPen ok_pen,ng;
    QFont ok_font;
    //opencv op_sig;

    QSize size;
    QDir dir;
    QImage *img;
    QString path;
    QString cid;
    QStringList files;
    QFileSystemWatcher *watcher;
    QMutex wlock;
//    cameraSql* sql;
};

#endif // FILEREADER_H
