#include "mainpage.h"
#include "ui_mainpage.h"

#include <QDebug>

mainpage::mainpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainpage)
{
    ui->setupUi(this);
    //
    setWindowFlags(Qt::WindowMaximizeButtonHint|Qt::WindowCloseButtonHint);
    ui->main_area->setCurrentIndex(0);

    initTable();


    update_mvimg = new QWidget(this);
    update_mvimg->hide();
    all_NG=all_OK=com_NG=com_OK=0;


    ui->AllData->installEventFilter(this);
    ui->SubData->installEventFilter(this);
    ui->cl1->addw(update_mvimg);
    ui->cl2->addw(update_mvimg);
    ui->cl1->setmapparent(this);
    ui->cl2->setmapparent(this);
    ui->cl1->link(ui->cl2);
    ui->cl2->link(ui->cl1);

    _layout = nullptr;

    setting = new SettingPage(ui->data_area,ui->display_area);
    _cameras = setting->getCameraList();
    connect(setting,SIGNAL(change(int,int)),this,SLOT(updateCamera(int,int)));
    connect(setting,SIGNAL(dr_valueChange(int,int)),this,SLOT(camera_value_change(int,int)));
    setting->sysn();
}

mainpage::~mainpage()
{
    delete ui;
}

void mainpage::updateCamera(int r, int c)
{
    setcamera(r,c);
}

bool mainpage::eventFilter(QObject *obj, QEvent *e)
{
    if(obj==ui->AllData){
        if(e->type()==QEvent::Paint){
        }else if(e->type()==QEvent::Resize){
            ui->AllData->setMinimumHeight(ui->AllData->width());
        }
    }else if(obj == ui->SubData){

    }
    return QWidget::eventFilter(obj,e);
}

void mainpage::setcamera(int row, int column)
{
    if(_cameras==nullptr)return;
    camNum = row*column;
    if(_layout!=nullptr){
        foreach (camera *w,*_cameras) {
            w->hide();
            w->state->hide();
        }
        delete _layout;
        delete _b_data_layout;
    }
    _layout = new QGridLayout();
    _b_data_layout = new QGridLayout();
    ui->display_area->setLayout(_layout);
    ui->b_data_area->setLayout(_b_data_layout);
    _layout->setSpacing(0);
    _layout->setMargin(1);
    _b_data_layout->setSpacing(6);
    _b_data_layout->setMargin(0);
    for(row = 0;row<camNum;row++){
        _layout->addWidget(_cameras->at(row),row/column,row%column);
        _b_data_layout->addWidget(_cameras->at(row)->state,row/column,row%column);
        _cameras->at(row)->show();
        _cameras->at(row)->state->show();
    }
    updataTable(camNum);
}

void mainpage::initTable()
{
    _tableModel = new QStandardItemModel();    
    _tableModel->setHorizontalHeaderLabels({TableHeadStr_OK,TableHeadStr_NG,TableHeadStr_persents});
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(_tableModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void mainpage::updataTable(int c)
{
    if(_tableModel->rowCount()==++c)return;
    int len = 1,rc = _tableModel->rowCount();
    _tableModel->setRowCount(c);
    QStringList list;
    for(;len<=c;len++){
        list << QString::number(len);
    }
    list.last()="总数";
    _tableModel->setVerticalHeaderLabels(list);
    for(len=0;len<c;len++){
        _tableModel->verticalHeaderItem(len)->setTextAlignment(Qt::AlignCenter);
    }
    for(;rc<c;rc++){
        _tableModel->setData(_tableModel->index(rc,0),TableDataNull);
        _tableModel->setData(_tableModel->index(rc,1),TableDataNull);
        _tableModel->setData(_tableModel->index(rc,2),TableDataNull);
        _tableModel->item(rc,0)->setTextAlignment(Qt::AlignCenter);
        _tableModel->item(rc,1)->setTextAlignment(Qt::AlignCenter);
        _tableModel->item(rc,2)->setTextAlignment(Qt::AlignCenter);
    }
}

void mainpage::on_setting_bt_released()
{
    setting->show();
}

void mainpage::on_update_bt_released()
{
    ui->main_area->setCurrentIndex(ui->main_area->currentIndex()==1?0:1);
}

void mainpage::camera_value_change(int id, int type)
{
    if(type==0){
        _tableModel->setData(_tableModel->index(id,0),QString::number(_cameras->at(id)->GetValueOK()));
        _tableModel->setData(_tableModel->index(_tableModel->rowCount()-1,0),QString::number(++all_OK));
    }else{
        _tableModel->setData(_tableModel->index(id,1),QString::number(_cameras->at(id)->GetValueNG()));
        _tableModel->setData(_tableModel->index(_tableModel->rowCount()-1,1),QString::number(++all_NG));
    }
    _tableModel->setData(_tableModel->index(id,2),QString::number(_cameras->at(id)->yield(),'f',0)+"%");
    _tableModel->setData(_tableModel->index(_tableModel->rowCount()-1,2),QString::number(camera::calculate(all_OK,all_NG),'f',0)+"%");
    if(id == ui->comboBox->currentIndex()){
        if(ui->comboBox->currentIndex()<0||ui->comboBox->currentIndex()>=_cameras->length()){
            return;
        }
        com_NG = _cameras->at(id)->GetValueNG();
        com_OK = _cameras->at(id)->GetValueOK();
        ui->SubData->update();
    }
}

