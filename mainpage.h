#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QTimer>
#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QStandardItemModel>
#include <QStandardItem>

#include "camera.h"

#define TableDataNull "--"
#define SystemDateFormat "yyyy-MM-dd hh:mm:ss"
#define TableHeadStr_OK "OK"
#define TableHeadStr_NG "NG"
#define TableHeadStr_persents "良品率"

namespace Ui {
class mainpage;
}

class mainpage : public QWidget
{
    Q_OBJECT

public:
    explicit mainpage(QWidget *parent = nullptr);
    ~mainpage();


signals:
    void d_changeState(int,WINSTATE);

private:
    bool eventFilter(QObject *obj, QEvent *e);

    void initTable();
    void updataTable(int);

    void setcamera(int,int);

    int camNum;
    unsigned long long all_NG,all_OK,com_NG,com_OK;

    QVector<camera*> _cameras;
    QWidget *update_mvimg;
    QStandardItemModel *_tableModel;
    QGridLayout *_layout;
    QGridLayout *_b_data_layout;

    Ui::mainpage *ui;
};

#endif // MAINPAGE_H
