#include "camera_setting.h"
#include "ui_camera_setting.h"

camera_setting::camera_setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::camera_setting)
{
    ui->setupUi(this);
}

camera_setting::~camera_setting()
{
    delete ui;
}
