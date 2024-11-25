#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include <QDialog>
#include <vertify_d.h>
#include <QGridLayout>

#include "camera.h"

#define defaultR 2
#define defalutC 2

#include "systemconf.h"
#include "camera_setting.h"

namespace Ui {
class SettingPage;
}

class SettingPage : public QDialog
{
    Q_OBJECT

public:
    explicit SettingPage(QWidget* data, QWidget* display, QWidget *parent = nullptr);
    ~SettingPage();

    void lock();
    void setRow(int);
    void setColumn(int);
    void updateinfo();
    void show();
//    int exec();

    void sysn();



    //
    int getRow();
    int getColumn();

    QVector<camera*>* getCameraList();

signals:
    void change(int,int);
    void d_changeState(int,WINSTATE);
    void dr_valueChange(int,int);

private slots:

    void on_style_clicked();

    void on_style_1_clicked();

    void on_style_2_clicked();

    void on_style_3_clicked();

    void on_udefine_toggled(bool checked);

    void on_save_clicked();

    void on_unlock_clicked();

    void on_exit_clicked();

    void on_row_valueChanged(int arg1);

    void on_column_valueChanged(int arg1);

    void vertify_success();
private:

    vertify_d v;
    int row;
    int column;
    int row_t;
    int column_t;
    bool saveSate;

    int camNum;
    QWidget* data_a;
    QWidget* display_a;

    QList<QPushButton*> btlist;
    QVector<camera*> _cameras;
    QVector<camera_setting*> _tmp_settings;
    QGridLayout *_settings_layout;
    QWidget* _settings_w;

    void unlock();
    void updateSetting();

    Ui::SettingPage *ui;
};

#endif // SETTINGPAGE_H
