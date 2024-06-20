#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>

#include <QImage>
#include <QDir>

#include "camerasql.h"


#define OK_FOLDER "OK"
#define NG_FOLDER "NG"

class FileReader : public QObject
{
    Q_OBJECT
public:
    explicit FileReader(QObject *parent = nullptr);
    void setImgBuffer(QImage *);
    void setPath(QString);
    QString getpath(){return path;}
    bool next(bool = false);
    void scan();
    void setSize(QSize);

    void initFolder(QString id);
    int x;
    int y;
signals:
    void Readready();
private:
    QSize size;
    QDir dir;
    QImage *img;
    QString path;
    QStringList files;
    cameraSql sql;
};

#endif // FILEREADER_H
