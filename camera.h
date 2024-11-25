#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include <QLabel>

#include <QPainter>
#include <QEvent>

#include "filereader.h"
#include "systemconf.h"
#include <QThread>

#include <QFileDialog>

#include <n_filereader.h>

#include <QTimer>

//窗口状态:正常，最大化，隐藏，未在范围内
enum WINSTATE{_Normal = 0,_Max,_Hide,_Out};

namespace Ui {
class camera;

}

class camera :public QWidget
{
    Q_OBJECT

public:
    explicit camera(int ID,QWidget *state_area,QWidget *parent = nullptr);
    ~camera();


    QLabel *state;

    int GetValueOK(){return value_OK;}
    int GetValueNG(){return value_NG;}
    int GetID(){return ID;}
    static double calculate(long OK,long NG){
        if(NG==0)return 100;
        double tmp = OK+NG;
        if(tmp == 0)return -1;
        return (1-NG/tmp)*100;
    }
    double yield(){
        return calculate(value_OK,value_NG);
    }
    //
    void ang_clicked();
    void aok_clicked();

    void show();
    bool eventFilter(QObject *watched, QEvent *event);
    //
    void closecamera();
    void p_StateChange(WINSTATE state);

    void setPath(QString path);
    QString getPath();

    void nextimg();

signals:
    void valueChange(int cid,int type);
    void changeState(int myid,WINSTATE state);
    void sig_next(bool = false);
private slots:
    void StateChange(int cid,WINSTATE state);
    void getResult(int);

    void timeouts();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QThread* thread;
    n_fileReader* nreader;

    //tmp timer
    QTimer *tmp_timer;

    int value_OK;
    int value_NG;
    //窗口状态
    WINSTATE winState;

    int ID;
//    QImage* img;
    Ui::camera *ui;
};

#endif // CAMERA_H
