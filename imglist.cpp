#include "imglist.h"
#include "ui_imglist.h"

#include <QScrollBar>
#include <QDebug>

Imglist::Imglist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Imglist)
{
    ui->setupUi(this);

    this->installEventFilter(this);
    ui->scrollArea->installEventFilter(this);

    ui->scrollArea->setWidget(new QWidget());
//    for(int i = 0;i<250;i++){
//        tmp.push_back(new QWidget(ui->scrollArea->widget()));
//    }
}

Imglist::~Imglist()
{
    delete ui;
}

bool Imglist::eventFilter(QObject *o, QEvent *e)
{
    if(ui->scrollArea == o){
        if(e->type()==QEvent::Resize){
            ui->scrollArea->widget()->setMinimumWidth(ui->scrollArea->width());
            initlist();
        }else if(e->type()==QEvent::ContextMenu){
            //reader.setPath(QFileDialog::getExistingDirectory(nullptr,"open",dir.path(),QFileDialog::ShowDirsOnly));
            //reader.scan();
        }
    }
    return QWidget::eventFilter(o,e);
}

void Imglist::initlist()
{
    QWidget *a = ui->scrollArea->widget();
    int width = imgsize+imgmargin;
    int wnum = (a->width()-(ui->scrollArea->verticalScrollBar()->isHidden()?0:ui->scrollArea->verticalScrollBar()->width()))/width;
    double left = a->width()-wnum*width;
    left /=2;
//    tmp.push_back(new QWidget(ui->scrollArea->widget()));
    for(int i = 0;i<tmp.size();i++){
        a = tmp.at(i);
        a->setGeometry(i%wnum*width+left,i/wnum*width,imgsize,imgsize);
        a->setStyleSheet("background-color: rgb(153, 193, 241);");
        a->show();
    }
    ui->scrollArea->widget()->setMinimumHeight((tmp.size()+wnum-1)/wnum*width);
}

void Imglist::on_pushButton_clicked()
{
    initlist();
}

