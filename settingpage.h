#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include <QDialog>
#include <vertify_d.h>

#define defaultR 2
#define defalutC 2

// 程序设置界面
// 用于修改页面布局
// 使用 vertify_d 进行身份验证
// 程序制作 钟明辉 & 黄志涣

namespace Ui {
class SettingPage;
}

class SettingPage : public QDialog
{
    Q_OBJECT

public:
    explicit SettingPage(QWidget *parent = nullptr);
    ~SettingPage();

    void lock();
    void setRow(int);
    void setColumn(int);
    void updateinfo();
    void show();
    int exec();

    void sysn();
signals:
    void change(int,int);

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
    void unlock();
    int row;
    int column;
    int row_t;
    int column_t;
    bool saveSate;
    Ui::SettingPage *ui;
};

#endif // SETTINGPAGE_H
