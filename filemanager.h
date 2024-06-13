#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

#include <QFileDialog>
#include <QDir>
#include <QFile>

#include <QStandardItemModel>
#include <QStandardItem>
#include <QIcon>
#include <QModelIndex>

#include <QImage>
#include <QThread>
#include "filereader.h"

struct FRER
{
    FRER() {
        buffer = new QImage();
        thread = new QThread();
        fr = new FileReader();
        fr->setImgBuffer(buffer);
        fr->moveToThread(thread);
        thread->start();
    }
    ~FRER() {}
    FileReader* fr;
    QImage* buffer;
    QSize camSize;
    QThread* thread;
    void deleteLater(){
        if(buffer!=nullptr)delete buffer;
        if(thread!=nullptr)delete thread;
    }
};

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);
    //up_area
    void getUpdataPath();
    QStandardItemModel* u_model;
    QStandardItemModel* u_fmodel;
    void u_flist_change(const QModelIndex &index);
    void u_flist_click(const QModelIndex &index);
    void u_img_size_change(QSize size);
    double up_img_x;
    double up_img_y;
    QImage up_buffer;
    QImage up_c_buffer;
    //camera load
    //QMap<QObject*,FRER> ciloders;
    QMap<int,FRER> camimgloder;
    //
//    QMap<int,FileReader*> Readers;
//    QMap<int,QImage*> camera_buffer;
//    QMap<int,QSize> camera_size;
    QImage* registerPath(int cid, QString path);
    void setSize(int cid,QSize size);
    void removePath(int cid);

    void nextImg(int cid);
signals:
    void up_img_update();
    void imgReady(int cid);
    void nextimgsig(int sig_cid);
private slots:

private:
    QModelIndex _index;
    QSize up_img_size;
    QString u_path;
    QString f_path;
    QIcon folder_ico;
    QIcon picture_ico;
    //
    void dirfind(QString path, QStandardItem *root, QIcon icon);
    QString itempath(const QModelIndex& index);
};

#endif // FILEMANAGER_H
