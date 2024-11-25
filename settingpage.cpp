#include "settingpage.h"
#include "ui_settingpage.h"

#include <QDebug>

SettingPage::SettingPage(QWidget *data, QWidget *display, QWidget *parent)
: QDialog(parent), data_a(data), display_a(display), ui(new Ui::SettingPage)
{
    ui->setupUi(this);

    lock();
    row =row_t= defaultR;
    column =column_t= defalutC;
    saveSate = true;
    setWindowFlags(Qt::WindowTitleHint|Qt::WindowStaysOnTopHint);
    setWindowTitle("设置");
    connect(&v,SIGNAL(success()),this,SLOT(vertify_success()));

    btlist.push_back(ui->style);
    btlist.push_back(ui->style_1);
    btlist.push_back(ui->style_2);
    btlist.push_back(ui->style_3);
    btlist.push_back(ui->udefine);
    _settings_layout = nullptr;
    _settings_w = new QWidget();
    ui->scrollArea->setWidget(_settings_w);
    ui->scrollArea->setWidgetResizable(true);

}

SettingPage::~SettingPage()
{
    delete ui;
}

void SettingPage::lock()
{
    ui->unlock->setText("未解锁");
    ui->marea->setEnabled(false);
    ui->save->hide();
}

void SettingPage::setRow(int r)
{
    row_t = r;
    updateinfo();
    saveSate = false;
    camNum = row_t*column_t;
}

void SettingPage::setColumn(int c)
{
    column_t = c;
    updateinfo();
    saveSate = false;
    camNum = row_t*column_t;
}

void SettingPage::updateinfo()
{
    ui->info_a->setText(QString("视频布局设置(当前配置为 %0 X %1 %2)").arg(QString::number(row_t)).arg(QString::number(column_t)).arg(saveSate?"":"[未保存]"));
    setWindowTitle(saveSate?"设置":"设置[未保存]");
}

void SettingPage::show()
{
    lock();
    updateinfo();
    QDialog::show();
}

void SettingPage::sysn()
{
    unlock();
    int tmp = systemConf::values[CONF_SETTING_VLAYOUT].toInt();
    setRow(systemConf::values[CONF_SETTING_ROW].toInt());
    setColumn(systemConf::values[CONF_SETTING_COLUMN].toInt());
    ui->row->setValue(row);
    ui->column->setValue(column);
    btlist[tmp]->click();
    on_save_clicked();
    lock();
}

int SettingPage::getRow()
{
    return 0;
}

int SettingPage::getColumn()
{
    return 0;
}

QVector<camera *> *SettingPage::getCameraList()
{
    return &_cameras;
}

void SettingPage::on_style_clicked()
{
    setRow(1);
    setColumn(1);
    updateSetting();
}


void SettingPage::on_style_1_clicked()
{
    setRow(2);
    setColumn(2);
    updateSetting();
}

void SettingPage::on_style_2_clicked()
{
    setRow(2);
    setColumn(3);
    updateSetting();
}

void SettingPage::on_style_3_clicked()
{
    setRow(3);
    setColumn(3);
    updateSetting();
}

void SettingPage::unlock()
{
    ui->unlock->setText("已解锁");
    ui->marea->setEnabled(true);
    ui->save->show();
    ui->row->setEnabled(ui->udefine->isChecked());
    ui->column->setEnabled(ui->udefine->isChecked());
}

void SettingPage::updateSetting()
{
    camNum = row_t*column_t;
    while (camNum>_tmp_settings.length()) {
        _tmp_settings.push_back(new camera_setting(QString::number(_tmp_settings.length()+1)));
    }
    if(_settings_layout!=nullptr){
        foreach (QWidget*w,_tmp_settings) {
            w->hide();
        }
        delete _settings_layout;
    }
    _settings_layout = new QGridLayout();
    _settings_w->setLayout(_settings_layout);

    for(int i = 0;i<camNum;i++){
        _settings_layout->addWidget(_tmp_settings.at(i),i/column_t,i%column_t);
        _tmp_settings.at(i)->show();
    }
}


void SettingPage::on_udefine_toggled(bool checked)
{
    ui->row->setEnabled(checked);
    ui->column->setEnabled(checked);
    if(checked){
        setRow(ui->row->value());
        setColumn(ui->column->value());
        updateSetting();
    }
}


void SettingPage::on_save_clicked()
{
    if(ui->udefine->isChecked()){
        setRow(ui->row->value());
        setColumn(ui->column->value());
    }
    // update camera
    row = row_t;
    column = column_t;
    camNum = row*column;
    while (_cameras.count()<camNum) {
        _cameras.push_back(new camera(_cameras.length(),data_a,display_a));
        connect(_cameras.last(),SIGNAL(changeState(int,WINSTATE)),this,SIGNAL(d_changeState(int,WINSTATE)));
        connect(this,SIGNAL(d_changeState(int,WINSTATE)),_cameras.last(),SLOT(StateChange(int,WINSTATE)));
        connect(_cameras.last(),SIGNAL(valueChange(int,int)),this,SIGNAL(dr_valueChange(int,int)));
    }
    emit change(row,column);
    _tmp_settings.clear();
    // save config
    systemConf::save(CONF_CAMERA_GROUP,CONF_CAMERA_NUM,row*column);
    systemConf::save(CONF_SETTING_GROUP,CONF_SETTING_ROW,row);
    systemConf::save(CONF_SETTING_GROUP,CONF_SETTING_COLUMN,column);
    for(int i = 0;i<btlist.size();i++){
        if(btlist[i]->isChecked()){
            systemConf::save(CONF_SETTING_GROUP,CONF_SETTING_VLAYOUT,i);
        }
    }
    saveSate = true;
    close();
}

void SettingPage::on_unlock_clicked()
{
    v.show();
}


void SettingPage::on_exit_clicked()
{
    row_t = row;
    column_t = column;
    updateSetting();
    close();
}


void SettingPage::on_row_valueChanged(int arg1)
{
    setRow(arg1);
    updateSetting();
}


void SettingPage::on_column_valueChanged(int arg1)
{
    setColumn(arg1);
    updateSetting();
}

void SettingPage::vertify_success()
{
    unlock();
}

