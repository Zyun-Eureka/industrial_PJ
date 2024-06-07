#include "filemanager.h"

#include <QDebug>

FileManager::FileManager(QObject *parent)
    : QObject{parent}
{
    u_model = new QStandardItemModel();
//    u_model->set
    u_fmodel = new QStandardItemModel();
    folder_ico=QIcon(":/SVG/folder.svg");
    picture_ico=QIcon(":/SVG/picture.svg");
}

void FileManager::getUpdataPath()
{
    QString str = QFileDialog::getExistingDirectory(nullptr,"open","",QFileDialog::ShowDirsOnly);
    if(str.isEmpty())return;
    u_path = str;
    QDir dir;
    dir.setPath(u_path);
    u_model->clear();
    QStandardItem *root = new QStandardItem(dir.path());
    dirfind(u_path,root,folder_ico);
    root->setIcon(folder_ico);
    u_model->appendRow(root);
}

void FileManager::u_flist_change(const QModelIndex &index)
{
    QString path=itempath(index);
    f_path = path;
    QDir dir(path);
    QStandardItem *item;
    u_fmodel->clear();
    QStringList list;
    list << "*.jpg"<<"*.png";
    for(QString i:dir.entryList(list,QDir::NoDotAndDotDot|QDir::Files)){
        item = new QStandardItem(i);
        item->setIcon(picture_ico);
        u_fmodel->appendRow(item);
    }
}

void FileManager::u_flist_click(const QModelIndex &index)
{
#ifdef Q_OS_LINUX
    up_buffer = QImage(f_path+"/"+index.data().toString()).scaled(up_img_size,Qt::KeepAspectRatio);
#endif
    if(up_buffer.isNull())return;
    _index = index;
    up_img_x = (up_img_size.width()-up_buffer.width())/2.0;
    up_img_y = (up_img_size.height()-up_buffer.height())/2.0;
    up_img_update();
}

void FileManager::u_img_size_change(QSize size)
{
    up_img_size = size;
    u_flist_click(_index);
}

void FileManager::dirfind(QString path, QStandardItem *root, QIcon icon)
{
    QDir dir(path);
    QStandardItem *item;
    for(QString i:dir.entryList(QDir::NoDotAndDotDot|QDir::Dirs)){
        item = new QStandardItem(i);
        item->setIcon(icon);
        dirfind(dir.filePath(i),item,icon);
        root->appendRow(item);
    }
}

QString FileManager::itempath(const QModelIndex &index)
{
    QString str = index.data().toString();
    if(index.parent().isValid()){
#ifdef Q_OS_LINUX
        str=itempath(index.parent())+"/"+str;
#elif false
#endif
    }
    return str;
}
