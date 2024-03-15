#include "dialog.h"
#include "ui_dialog.h"

#include <QDateTime>

#include <QDebug>
#include <QTableWidget>

#include <QPainter>
#include <QtMath>

#include <QRandomGenerator>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    initTable();

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_event()));

    connect(&settings,SIGNAL(change(int,int)),this,SLOT(setting_c(int,int)));

    ui->AllData->installEventFilter(this);
    ui->SubData->installEventFilter(this);
    setWindowFlags(Qt::WindowMaximizeButtonHint|Qt::WindowCloseButtonHint);

    all_NG=all_OK=com_NG=com_OK=0;
    settings.sysn();
}

Dialog::~Dialog()
{
    while (cameras.length()>0) {
        cameras.last()->closecamera();
        delete cameras.last();
        cameras.pop_back();
    }
    delete ui;
}

bool Dialog::eventFilter(QObject *obj, QEvent *e){
    if(e->type()==QEvent::Paint){
        QVector<double> value;
        if(obj == ui->AllData){
            value.push_back(all_OK);
            value.push_back(all_NG);
        }else if(obj == ui->SubData){
            value.push_back(com_OK);
            value.push_back(com_NG);
        }else{
            goto e_f_end;
        }
        QPainter pa(static_cast<QWidget*>(obj));
        pa.setRenderHint(QPainter::Antialiasing);
        double width,height,diameter,startAngle,nowAngle,max,color_pos;
        width = static_cast<QWidget*>(obj)->width()-pa.pen().width();
        height = static_cast<QWidget*>(obj)->height()-pa.pen().width();
        diameter = qMin(width,height);
        startAngle = 90;
        max = color_pos = 0;
        foreach (double i,value) {
            max +=i;
        }
        width -=diameter;
        width/=2;
        width +=pa.pen().width();
        height -=diameter;
        height /=2;
        height +=pa.pen().width();
        if(max == 0){
            pa.setPen(QColor(diagram_color[0]));
            QRectF rect(width,height,diameter-pa.pen().width(),diameter-pa.pen().width());
            pa.drawEllipse(rect);
            QFont font;
            font.setPixelSize(20);
            font.setBold(true);
            pa.setFont(font);
            pa.drawText(rect,Qt::AlignCenter,"No Data");
            return false;
        }
        foreach (double i,value) {
            nowAngle = i*360.0/max;
            pa.setBrush(QColor(diagram_color[color_pos]));
            pa.setPen(Qt::transparent);
            color_pos++;
            pa.drawPie(width,height,diameter-pa.pen().width(),diameter-pa.pen().width(),startAngle*16,nowAngle*16);
            startAngle +=nowAngle;
        }
    }else if(e->type()==QEvent::Resize){
        if(obj==ui->AllData){
            ui->AllData->setMinimumHeight(ui->AllData->width());
        }
    }
    e_f_end:
    return QDialog::eventFilter(obj,e);
}

void Dialog::setcamera(int row, int column)
{
    camNum = row*column;
    int num = camNum;
    //
    updataTable(num);
    //
    while (num > cameras.length()) {
        cameras.push_back(new camera(QString::number(cameras.length()),ui->b_data_area,ui->display_area));
        connect_state(cameras.last());
    }
    for(QVector<camera*>::Iterator it = cameras.begin();it != cameras.end();it++){
        (*it)->p_StateChange(WINSTATE::_Out);
        //(*it)->hide();
        //(*it)->state->hide();
    }
    //清除原先位置样式
    while (layouts_c.length()>0) {
        delete layouts_c.last();
        delete layouts_l.last();
        layouts_c.pop_back();
        layouts_l.pop_back();
    }
    QVBoxLayout * box = new QVBoxLayout();
    QVBoxLayout * lbox = new QVBoxLayout();
    layouts_c.push_back(box);
    layouts_l.push_back(lbox);
    QHBoxLayout * hb;
    QHBoxLayout * lhb;
    camera *tmp;
    for(int j = 0;j<row;j++){
        hb = new QHBoxLayout();
        lhb = new QHBoxLayout();
        layouts_c.push_back(hb);
        layouts_l.push_back(lhb);
        for(int i = 0;i<column;i++){
            tmp = cameras.at(j*column+i);
            hb->addWidget(tmp);
            lhb->addWidget(tmp->state);
            tmp->p_StateChange(WINSTATE::_Normal);
        }
        box->addLayout(hb);
        lbox->addLayout(lhb);
    }
    box->setSpacing(6);
    box->setMargin(1);
    //
    lbox->setSpacing(6);
    lbox->setMargin(0);
    ui->b_data_area->setLayout(lbox);
    ui->display_area->setLayout(box);
}

void Dialog::initTable()
{
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({TableHeadStr_OK,TableHeadStr_NG,TableHeadStr_persents});
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i = 0;i<3;i++){
        items.push_back(new QTableWidgetItem(TableDataNull));
        items.last()->setTextAlignment(Qt::AlignCenter);
    }
}

void Dialog::updataTable(int count)
{
    //增加总数的位置
    count++;
    int len = ui->tableWidget->rowCount();
    if(count == len){
        return;
    }
    int i,j;
    for(i = 0;i<len;i++){
        for(j = 0;j< 3;j++){
            ui->tableWidget->takeItem(i,j);
        }
        ui->tableWidget->takeVerticalHeaderItem(i);
    }
    ui->tableWidget->setRowCount(count);
    i = count*3;
    while(items.size()<i){
        items.push_back(new QTableWidgetItem(TableDataNull));
        items.last()->setTextAlignment(Qt::AlignCenter);
    }
    while (vhs.size()<count) {
        vhs.push_back(new QTableWidgetItem());
        vhs.last()->setTextAlignment(Qt::AlignCenter);
    }
    //减去总数的位置
    count --;
    ui->comboBox->clear();
    for(i = 0;i<count;i++){
        j = (i+1)*3;
        ui->tableWidget->setItem(i,0,items[j]);
        ui->tableWidget->setItem(i,1,items[j+1]);
        ui->tableWidget->setItem(i,2,items[j+2]);
        vhs[i]->setText(QString::number(i));
        ui->comboBox->addItem("相机 "+QString::number(i));
        ui->tableWidget->setVerticalHeaderItem(i,vhs[i]);
    }
    //添加总数栏
    //序号位置
    ui->tableWidget->setVerticalHeaderItem(i,vhs[i]);
    vhs[i]->setText("总数");
    //表格设置
    j = ui->tableWidget->rowCount()-1;
    for(i = 0;i<3;i++){
        ui->tableWidget->setItem(j,i,items[i]);
    }
}

void Dialog::connect_state(camera * obj)
{
    connect(obj,SIGNAL(changeState(QString,WINSTATE)),this,SIGNAL(d_changeState(QString,WINSTATE)));
    connect(this,SIGNAL(d_changeState(QString,WINSTATE)),obj,SLOT(StateChange(QString,WINSTATE)));
    connect(obj,SIGNAL(valueChange(int,int)),this,SLOT(cvchange(int,int)));
}

void Dialog::disconnect_state(camera *obj)
{
    disconnect(obj,SIGNAL(changeState(QString,WINSTATE)),this,SIGNAL(d_changeState(QString,WINSTATE)));
    disconnect(this,SIGNAL(d_changeState(QString,WINSTATE)),obj,SLOT(StateChange(QString,WINSTATE)));
    disconnect(obj,SIGNAL(valueChange(int,int)),this,SLOT(cvchange(int,int)));
}

void Dialog::timer_event()
{
    ui->Date->setText(QDateTime::currentDateTime().toString(SystemDateFormat));
    if(QRandomGenerator::global()->generate()%9==1){
        cameras[QRandomGenerator::global()->generate()%cameras.size()]->ang_clicked();
    }else{
        cameras[QRandomGenerator::global()->generate()%cameras.size()]->aok_clicked();
    }
}

void Dialog::cvchange(int id,int t)
{
    if(t==0){
        t = (id+1) *3;
        items[t]->setText(QString::number(cameras[id]->GetValueOK()));
    }else{
        t = (id+1)*3;
        items[t+1]->setText(QString::number(cameras[id]->GetValueNG()));
    }
    items[t+2]->setText(QString::number(cameras[id]->yield(),'f',0)+"%");
    updateNum();
    if(id == ui->comboBox->currentIndex()){
        updateCom();
    }
}

void Dialog::setting_c(int r, int c)
{
    setcamera(r,c);
    updateNum();
}

void Dialog::on_setting_bt_clicked()
{    
    settings.lock();
    settings.show();
}

void Dialog::updateNum()
{
    int i;
    all_NG = all_OK = 0;
    for(i = 0;i<camNum;i++){
        all_OK+=cameras[i]->GetValueOK();
    }
    items[0]->setText(QString::number(all_OK));
    for(i = 0;i<camNum;i++){
        all_NG+=cameras[i]->GetValueNG();
    }
    items[1]->setText(QString::number(all_NG));
    items[2]->setText(QString::number(camera::calculate(all_OK,all_NG),'f',0)+"%");
    ui->AllData->update();
}

void Dialog::updateCom()
{
    if(ui->comboBox->currentIndex()<0||ui->comboBox->currentIndex()>=cameras.size()){
        return;
    }
    com_NG = cameras[ui->comboBox->currentIndex()]->GetValueNG();
    com_OK = cameras[ui->comboBox->currentIndex()]->GetValueOK();
    ui->SubData->update();
}


void Dialog::on_comboBox_currentIndexChanged(int index)
{
    updateCom();
}


void Dialog::on_pushButton_clicked()
{
    if(!timer->isActive()){
        timer->start(100);
    }
}

void Dialog::on_full_toggled(bool checked)
{
    if(checked){
        setWindowState(Qt::WindowFullScreen);
    }else{
        setWindowState(Qt::WindowNoState);
    }
}

