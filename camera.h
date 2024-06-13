#ifndef CAMERA_H
#define CAMERA_H

//这是相机类的头文件
//相机类介绍，相机类用于在主页面，初始化为一个个的监视卡片
//计划用于展示图片，视频流等

//此类与统计数值功能绑定，使用getvalue获取统计到的数值
//在获取后端数据函数内使用对应相机 ang_clicked aok_clicked 添加异常和正常数值的统计，调用即添加一次数值
//并会同时触发 valuechange(int 拟定为相机id,int 拟定为数值变更类型 1为异常加1 0为正常加1) 信号
//到主页面进行数据统计表和图表更新
//图片加载，本项目拟通过重写控件绘制事件实现加载图片功能，具体说明在 camera.cpp 文件内eventFilter函数下查看
//程序制作 钟明辉 & 黄志涣

#include <QWidget>
#include <QLabel>

#include <QPainter>
#include <QEvent>

#include "filereader.h"
#include <QThread>

#include <QFileDialog>

//窗口状态:正常，最大化，隐藏，未在范围内
enum WINSTATE{_Normal = 0,_Max,_Hide,_Out};

namespace Ui {
class camera;

}

class camera : public QWidget
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

    //函数重写
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
private:
    //img load
    QThread* thread;
    FileReader reader;

    int value_OK;
    int value_NG;
    //窗口状态
    WINSTATE winState;

    int ID;
    QImage* img;
    Ui::camera *ui;
};

#endif // CAMERA_H
