#ifndef IMGLIST_H
#define IMGLIST_H

#include <QDialog>

#include <QEvent>
#include <QImage>

#include <QDir>
#include <QFileDialog>
#include "filereader.h"

#define imgsize 50
#define imgmargin 5
//#define imgleft 5
//#define imgright 5+

namespace Ui {
class Imglist;
}

class Imglist : public QDialog
{
    Q_OBJECT

public:
    explicit Imglist(QWidget *parent = nullptr);
    ~Imglist();

    bool eventFilter(QObject *, QEvent *);
    void initlist();
private slots:
    void on_pushButton_clicked();

private:
    FileReader* reader;

    bool type;
    QDir dir;
    QList<QWidget*> tmp;
    QList<QImage> imgs;
    Ui::Imglist *ui;
};

#endif // IMGLIST_H
