#include "imgcl.h"
#include "ui_imgcl.h"

#include <QDebug>

#include <QLabel>

imgCL::imgCL(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::imgCL)
{
    ui->setupUi(this);

    //
    _tcolumnCount = -1;
    _oimgcl = nullptr;
    updateCC();
    //
    _mainl =  new QGridLayout();
    _mainb = new QWidget();
    _imgW = nullptr;

    _mainb->setLayout(_mainl);
    _mainl->setSpacing(SPACEING);
    _mainl->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    ui->scrollArea->setWidget(_mainb);
    ui->scrollArea->setWidgetResizable(true);

    _mainb->installEventFilter(this);
    installEventFilter(this);

//    t_add(nullptr);
//    t_add(nullptr);
}

imgCL::~imgCL()
{
    delete ui;
}

void imgCL::addImage(QImage img, QString id)
{

}

void imgCL::t_add(QImage i)
{
    clWidget * w = new clWidget();
    w->setimg(i);
    w->installEventFilter(this);
    if(_lists.count()!=0){
        _mainl->addWidget(w,_lists.count()/_columnCount,_lists.count()%_columnCount);
    }else{
        _mainl->addWidget(w,0,0);
    }
    _lists.append(w);
    _lists.last()->setStyleSheet(":hover{border:1px solid;}");
    _lists.last()->setMinimumSize(MinW,MinH);
}

void imgCL::t_add_w(clWidget *w)
{
    w->installEventFilter(this);
    if(_lists.count()!=0){
        _mainl->addWidget(w,_lists.count()/_columnCount,_lists.count()%_columnCount);
    }else{
        _mainl->addWidget(w,0,0);
    }
    _lists.append(w);
    _lists.last()->setStyleSheet(":hover{border:1px solid;}");
    _lists.last()->setMinimumSize(MinW,MinH);
}

bool imgCL::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this){
        if(event->type()==QEvent::Resize){
            updateCC();
        }
    }else if(watched == _mainb){
        if(event->type() == QEvent::Leave){
        }
    }else if(watched->parent()==_mainb){
        if(event->type()==QEvent::Paint){
            QPainter pa((QWidget*)watched);

        }
        if(_imgW==nullptr)return false;
        if(event->type()==QEvent::MouseButtonPress){
            tmp = ((QWidget*)watched)->mapTo(_mapP,((QMouseEvent*)event)->pos()-QPoint(_imgW->width()/2,_imgW->height()/2));
            _imgW->move(tmp);
            tmp-=QCursor::pos();
            _imgW->show();
        }else if(event->type()==QEvent::MouseMove){
            _imgW->move(tmp+QCursor::pos());
        }else if(event->type()==QEvent::MouseButtonRelease){
            _imgW->hide();
            if(_oimgcl!=nullptr){
                if(QRectF(_oimgcl->mapTo(_mapP,QPoint(0,0)),_oimgcl->size()).contains(_imgW->pos())){
                    _lists.removeOne((QWidget*)watched);
                    _mainl->removeWidget((QWidget*)watched);
                    this->removeEventFilter(((QWidget*)watched));
                    ((imgCL*)_oimgcl)->t_add_w(((clWidget*)watched));
                    updateCC(false);
                }
            }
        }
    }
    return false;
}

void imgCL::link(QWidget *w)
{
    _oimgcl = w;
}

void imgCL::addw(QWidget *w)
{
    _imgW = w;
}

void imgCL::setmapparent(QWidget *w)
{
    _mapP = w;
}

void imgCL::cle()
{
    _lists.clear();
}

void imgCL::updateCC(bool a)
{
    int tmp = width()-SPACEING *3;;
    _columnCount = tmp/MinW;
    if(a&&_tcolumnCount==_columnCount){
        return;
    }
    _tcolumnCount = _columnCount;
    for(tmp = 0;tmp<_lists.count();tmp++){
        _mainl->addWidget(_lists[tmp],tmp/_columnCount,tmp%_columnCount);

    }
}
