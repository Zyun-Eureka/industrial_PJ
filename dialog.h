#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>

#include <QFrame>
#include <QWidget>
#include <QBoxLayout>
#include "camera.h"
#include <QLabel>

#include "settingpage.h"

#include <QTableWidgetItem>

// 这个是程序主页面
// 实现功能有相机布局自动生成
// 图表统计和画图功能
// 程序制作 钟明辉 & 黄志涣


#define TableDataNull "--"
#define SystemDateFormat "yyyy-MM-dd hh:mm:ss"
#define TableHeadStr_OK "OK"
#define TableHeadStr_NG "NG"
#define TableHeadStr_persents "良品率"

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

signals:
    void d_changeState(QString myid,WINSTATE state);


private:
    bool eventFilter(QObject *obj, QEvent *e);
    void setcamera(int,int);
    void initTable();
    void updataTable(int);

    QVector<camera*> cameras;
    QVector<QTableWidgetItem*> items;
    QVector<QTableWidgetItem*> vhs;
    QVector<QLayout*> layouts_c;
    QVector<QLayout*> layouts_l;

    SettingPage settings;

    QTimer *timer;

    void connect_state(camera*);
    void disconnect_state(camera*);

private slots:
    void timer_event();
    void cvchange(int,int);

    void setting_c(int,int);
    void on_setting_bt_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_full_toggled(bool checked);

private:

    int camNum;
    unsigned   long long all_NG,all_OK,com_NG,com_OK;

    void updateNum();
    void updateCom();
    const QStringList diagram_color = {"#00B000","#FF3131"};
    Ui::Dialog *ui;
};
#endif // DIALOG_H
