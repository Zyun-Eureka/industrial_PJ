#include "vertify_d.h"
#include "ui_vertify_d.h"

vertify_d::vertify_d(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vertify_d)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Window|Qt::WindowStaysOnTopHint);
}

vertify_d::~vertify_d()
{
    delete ui;
}

void vertify_d::show()
{
    ui->password->clear();
    QDialog::show();
    this->setWindowState(Qt::WindowFullScreen|Qt::WindowActive);
}

void vertify_d::on_close_bt_clicked()
{
    close();
}


void vertify_d::on_vertify_bt_clicked()
{
    emit success();
    close();
}
