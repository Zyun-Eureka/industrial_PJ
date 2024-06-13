#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>

#include <QImage>
#include <QDir>

class FileReader : public QObject
{
    Q_OBJECT
public:
    explicit FileReader(QObject *parent = nullptr);
    void setImgBuffer(QImage *);
    void setPath(QString);
    bool next();
    void scan();
signals:
    void Readready();
private:
    QDir dir;
    QImage *img;
    QString path;
    QStringList files;
};

#endif // FILEREADER_H
