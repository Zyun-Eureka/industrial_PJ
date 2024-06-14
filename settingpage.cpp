#include "settingpage.h"
#include "ui_settingpage.h"

#include <QDebug>

SettingPage::SettingPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingPage)
{
    ui->setupUi(this);

    lock();
    row =row_t= defaultR;
    column =column_t= defalutC;
    saveSate = true;
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    connect(&v,SIGNAL(success()),this,SLOT(vertify_success()));

    btlist.push_back(ui->style);
    btlist.push_back(ui->style_1);
    btlist.push_back(ui->style_2);
    btlist.push_back(ui->style_3);
    btlist.push_back(ui->udefine);
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
}

void SettingPage::setColumn(int c)
{
    column_t = c;
    updateinfo();
    saveSate = false;
}

void SettingPage::updateinfo()
{
    ui->info_a->setText(QString("视频布局设置(当前配置为 %0 X %1 %2):").arg(QString::number(row_t)).arg(QString::number(column_t)).arg(saveSate?"":"[未保存]"));
}

void SettingPage::show()
{
    updateinfo();
    QDialog::show();
}

int SettingPage::exec()
{
    updateinfo();
    return QDialog::exec();
}

void SettingPage::sysn()
{
    unlock();
    int tmp = systemConf::values[CONF_SETTING_VLAYOUT].toInt();
    row = systemConf::values[CONF_SETTING_ROW].toInt();
    column = systemConf::values[CONF_SETTING_COLUMN].toInt();
    ui->row->setValue(row);
    ui->column->setValue(column);
    btlist[tmp]->click();
    on_save_clicked();
    lock();
}

void SettingPage::on_style_clicked()
{
    setRow(1);
    setColumn(1);
}


void SettingPage::on_style_1_clicked()
{
    setRow(2);
    setColumn(2);
}

void SettingPage::on_style_2_clicked()
{
    setRow(2);
    setColumn(3);
}

void SettingPage::on_style_3_clicked()
{
    setRow(3);
    setColumn(3);
}

void SettingPage::unlock()
{
    ui->unlock->setText("已解锁");
    ui->marea->setEnabled(true);
    ui->save->show();
    ui->row->setEnabled(ui->udefine->isChecked());
    ui->column->setEnabled(ui->udefine->isChecked());
}


void SettingPage::on_udefine_toggled(bool checked)
{
    ui->row->setEnabled(checked);
    ui->column->setEnabled(checked);
    if(checked){
        setRow(ui->row->value());
        setColumn(ui->column->value());
    }
}


void SettingPage::on_save_clicked()
{
    if(ui->udefine->isChecked()){
        setRow(ui->row->value());
        setColumn(ui->column->value());
    }
    row = row_t;
    column = column_t;
    emit change(row,column);
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
    close();
}


void SettingPage::on_row_valueChanged(int arg1)
{
    setRow(arg1);
}


void SettingPage::on_column_valueChanged(int arg1)
{
    setColumn(arg1);
}

void SettingPage::vertify_success()
{
    unlock();
}

