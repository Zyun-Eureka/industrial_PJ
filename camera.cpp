#include "camera.h"
#include "ui_camera.h"

#include <QDebug>

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

    //注册事件循环监听
    ui->display->installEventFilter(this);
    ui->frame_top->installEventFilter(this);
    ui->img->installEventFilter(this);

    img = new QImage();
    reader.setImgBuffer(img);
    thread = new QThread();
    reader.moveToThread(thread);
    thread->start();
    connect(this,&camera::sig_next,&reader,&FileReader::next);
    connect(&reader,&FileReader::Readready,this,[&](){
        ui->img->update();
    });

    if(systemConf::values[CONF_CAMERA_NUM].toInt()>ID){
        setPath(systemConf::values[CONF_CAMERA_PATH+QString::number(ID)].toString());
    }
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
        if(event->type()==QEvent::Resize){
            reader.setSize(ui->display->size());
        }else if(event->type()==QEvent::ContextMenu){
            QString str = QFileDialog::getExistingDirectory(nullptr,"open",reader.getpath(),QFileDialog::ShowDirsOnly);
            if(!str.isEmpty()){
                setPath(str);
            }
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
            if(img!=nullptr){
                QPainter pa(ui->img);
                pa.drawImage(reader.x,reader.y,*img);
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
    reader.setPath(path);
    systemConf::save(CONF_CAMERA_GROUP,CONF_CAMERA_PATH+QString::number(ID),path);
}

QString camera::getPath()
{
    return reader.getpath();
}

void camera::nextimg()
{
    sig_next();
}

void camera::initfolder()
{
}

void camera::query()
{

}

void camera::query(QString)
{

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
