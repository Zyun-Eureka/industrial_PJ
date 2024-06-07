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

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);
    void getUpdataPath();
    QStandardItemModel* u_model;
    QStandardItemModel* u_fmodel;
    void u_flist_change(const QModelIndex &index);
    void u_flist_click(const QModelIndex &index);
    void u_img_size_change(QSize size);

    double up_img_x;
    double up_img_y;
    QImage up_buffer;
signals:
    void up_img_update();
private slots:

private:
    QModelIndex _index;
    QSize up_img_size;
    QString u_path;
    QString f_path;
    QIcon folder_ico;
    QIcon picture_ico;
    void dirfind(QString path, QStandardItem *root, QIcon icon);

    QString itempath(const QModelIndex& index);
};

#endif // FILEMANAGER_H