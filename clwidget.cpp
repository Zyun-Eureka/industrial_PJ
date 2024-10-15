#include "clwidget.h"
#include <QPainter>

clWidget::clWidget(QWidget *parent)
    : QWidget{parent}
{
    installEventFilter(this);
}

bool clWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::Paint){
        QPainter pa(this);
        pa.fillRect(rect(),Qt::black);
        if(image.isNull()){return false;}
        pa.drawImage(x,y,image);
    }else if(event->type()==QEvent::Resize){
        setimg(image);
    }
    return false;
}

void clWidget::setimg(QImage i)
{
    image = i.scaled(size(),Qt::KeepAspectRatio);
    x = (size().width()-image.width())/2;
    y = (size().height()-image.height())/2;
    this->update();
}
