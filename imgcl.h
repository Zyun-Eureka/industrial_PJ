#ifndef IMGCL_H
#define IMGCL_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QGridLayout>

#include <QResizeEvent>

#include <QSpacerItem>

#include "clwidget.h"

#define SPACEING 10

#define MinW 180
#define MinH 150

struct ImgData{
    QImage img;
    QString id;
};

namespace Ui {
class imgCL;
}

class imgCL : public QWidget
{
    Q_OBJECT

public:
    explicit imgCL(QWidget *parent = nullptr);
    ~imgCL();
    void addImage(QImage img,QString id);
    void t_add(QImage);

    void t_add_w(clWidget *);

    bool eventFilter(QObject *watched, QEvent *event);
    void link(QWidget*);
    void addw(QWidget*);

    void setmapparent(QWidget*);

    void cle();
signals:
private slots:

private:
    Ui::imgCL *ui;
    //
    QList<QImage> imgs;
    QList<QWidget*> _lists;
    //
    QList<clWidget*> _li;
    QPoint tmp;
    //
    //
    QWidget *_mainb;
    QWidget *_imgW;
    QWidget *_mapP;
    QGridLayout *_mainl;
    //
    QWidget * _oimgcl;
//    QRectF _oimg;

    int _width;
    int _height;
    //
    int _columnCount;
    int _tcolumnCount;

    //
    void updateCC(bool a = true);

//    QSpacerItem item;
};

#endif // IMGCL_H
