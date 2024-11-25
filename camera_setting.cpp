#include "camera_setting.h"
#include "ui_camera_setting.h"

#include <QDebug>

camera_setting::camera_setting(QString id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::camera_setting)
{
    ui->setupUi(this);
    setid(id);
}

camera_setting::~camera_setting()
{
    delete ui;
}

void camera_setting::setid(QString id)
{
    ui->id->setText(QString("Camera ID： %1").arg(id));
}
