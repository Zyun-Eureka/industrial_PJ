#include "camera.h"
#include "ui_camera.h"

#include <QDebug>
#include "mcore.h"

camera::camera(int ID, QWidget *state_area, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::camera)
{
    ui->setupUi(this);

    this->ID = ID;
    state = new QLabel(state_area);
    state->setStyleSheet("");
    ui->ID->setText(QString("相机ID :%1").arg(ID+1));

    value_NG = 0;
    value_OK = 0;

//    ui->display->installEventFilter(this);
    ui->frame_top->installEventFilter(this);
    ui->img->installEventFilter(this);

    nreader = new n_fileReader(MCore::GetDBName(QString::number(ID)));
    thread = new QThread();
    nreader->moveToThread(thread);
    thread->start();

    tmp_timer = new QTimer(this);
    connect(tmp_timer,SIGNAL(timeout()),this,SLOT(timeouts()));
    tmp_timer->start(1);


    connect(nreader,SIGNAL(Readready()),ui->img,SLOT(update()));
    p_StateChange(WINSTATE::_Normal);

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
    if(watched == ui->img){
        if(event->type()==QEvent::Resize){
            nreader->screenSizeChange(ui->img->width(),ui->img->height());

            // @false
//            reader.setSize(ui->display->size());
        }else if(false&&event->type()==QEvent::ContextMenu){
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
    }else if(watched == ui->img){
        if(event->type()==QEvent::Paint){
            if(nreader->ImgBuffer()!=nullptr){
                QPainter pa(ui->img);
                pa.drawImage(nreader->GetIX(),nreader->GetIY(),*nreader->ImgBuffer());
            }
        }
    }
    return QWidget::eventFilter(watched,event);
}

void camera::ang_clicked()
{
    if(!ui->enabled_bt->isChecked())return;
    value_NG++;
    state->setStyleSheet("image: url(:/SVG/no.svg);");
    emit valueChange(this->ID,1);
}


void camera::aok_clicked()
{
    if(!ui->enabled_bt->isChecked())return;
    value_OK++;
    state->setStyleSheet("image: url(:/SVG/yes.svg);");
    emit valueChange(this->ID,0);
}

void camera::closecamera()
{

}

void camera::p_StateChange(WINSTATE state)
{
    StateChange(ID,state);
}

void camera::setPath(QString path)
{
    nreader->setInputPath(path);
}

QString camera::getPath()
{
    return false;
//    return reader.getpath();
}

void camera::nextimg()
{
    sig_next();
}


void camera::StateChange(int cid,WINSTATE s)
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
            winState = WINSTATE::_Out;
            hide();
            if(state!=nullptr){
                state->hide();
            }
            break;
        case WINSTATE::_Max:
            break;
        case WINSTATE::_Normal:
            winState = WINSTATE::_Normal;
            StateChange(-1,WINSTATE::_Normal);
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

void camera::getResult(int i)
{
    if(i==1){
        aok_clicked();
    }else{
        ang_clicked();
    }
}

void camera::timeouts()
{
//    nreader->next();
}
