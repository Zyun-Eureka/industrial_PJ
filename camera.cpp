#include "camera.h"
#include "ui_camera.h"

#include <QDebug>

camera::camera(QString ID, QWidget *state_area, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::camera)
{
    ui->setupUi(this);

    this->ID = ID;
    state = new QLabel(state_area);
    state->setStyleSheet("");
    ui->ID->setText(QString("ID:%1").arg(ID));

    value_NG = 0;
    value_OK = 0;

    //注册事件循环监听
    ui->display->installEventFilter(this);

    ui->frame_top->installEventFilter(this);
    tmp_str = ID;
}

camera::~camera()
{
    delete ui;
}

void camera::show()
{
    if(winState==WINSTATE::_Hide || winState==WINSTATE::_Out)return;
    QWidget::show();
    if(state!=nullptr){
        state->show();
    }
}

bool camera::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->display){
        if(event->type()==QEvent::Paint){
            //控件绘制实现
            QPainter pa(ui->display);
            pa.setBrush(Qt::black);
            //设置画笔颜色
            QPen pen;
            pen.setColor(Qt::red);
            pa.setPen(pen);
            //因为画笔也有厚度所以画面会溢出，可以减去画笔厚度
            pa.drawRect(0,0,ui->display->width()-pen.width()*2,ui->display->height()-pen.width()*2);
            //此处可以通过id或者sting变量区分摄像头
            //我在h文件声明了个tmp_str初始化为相机ID
            //if(tmp_str==""){//code}
            //或者存入路径用于打开文件夹/网页api?
            //open(tmp_str)
            //此处使用画笔将tmp_str储存的id打印在区域中间
            pa.drawText(QRect(0,0,ui->display->width()-pen.width()*2,ui->display->height()-pen.width()*2),Qt::AlignCenter,"此为相机:"+tmp_str);

        }
    }else if(watched == ui->frame_top){
        if(event->type()==QEvent::MouseButtonDblClick){
            if(winState == WINSTATE::_Max){
                winState = WINSTATE::_Normal;
            }else if(winState == WINSTATE::_Normal){
                winState = WINSTATE::_Max;
            }
            emit changeState(ID,winState);
        }
    }
    return QWidget::eventFilter(watched,event);
}

void camera::ang_clicked()
{
    if(!ui->enabled_bt->isChecked())return;
    value_NG++;
    state->setStyleSheet("image: url(:/SVG/no.svg);");
    emit valueChange(this->ID.toInt(),1);
}


void camera::aok_clicked()
{
    if(!ui->enabled_bt->isChecked())return;
    value_OK++;
    state->setStyleSheet("image: url(:/SVG/yes.svg);");
    emit valueChange(this->ID.toInt(),0);
}

void camera::closecamera()
{

}

void camera::p_StateChange(WINSTATE state)
{
    StateChange(ID,state);
}

void camera::StateChange(QString cid,WINSTATE s)
{
    if(cid != ID){
        if(winState==WINSTATE::_Out)return;
        switch (s) {
        case WINSTATE::_Hide:
            break;
        case WINSTATE::_Normal:
            winState = WINSTATE::_Normal;
            show();
            if(state!=nullptr){
                state->show();
            }
            break;
        case WINSTATE::_Max:
            winState = WINSTATE::_Hide;
            hide();
            if(state!=nullptr){
                state->hide();
            }
            break;
        case WINSTATE::_Out:
            break;
        default:
            qDebug()<<"Error at"<<__func__<<cid<<s;
            break;
        }
    }else{
        switch (s) {
        case WINSTATE::_Out:
            winState == WINSTATE::_Out;
            hide();
            if(state!=nullptr){
                state->hide();
            }
            break;
        case WINSTATE::_Max:
            break;
        case WINSTATE::_Normal:
            winState = WINSTATE::_Normal;
            StateChange("",WINSTATE::_Normal);
            break;
        case WINSTATE::_Hide:
            break;
        default:
            qDebug()<<"Error at"<<__func__<<cid<<s;
            break;
        }
    }
    winState = s;
}

