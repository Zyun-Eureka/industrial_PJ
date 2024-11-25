#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QTimer>
#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QStandardItemModel>
#include <QStandardItem>

#include "camera.h"
#include "settingpage.h"

#define TableDataNull "--"
#define SystemDateFormat "yyyy-MM-dd hh:mm:ss"
#define TableHeadStr_OK "OK"
#define TableHeadStr_NG "NG"
#define TableHeadStr_persents "良品率"


namespace Ui {
class mainpage;
}

class mainpage : public QWidget
{
    Q_OBJECT

public:
    explicit mainpage(QWidget *parent = nullptr);
    ~mainpage();


private slots:
    void updateCamera(int r,int c);

    void on_setting_bt_released();

    void on_update_bt_released();
public slots:
    void camera_value_change(int id,int type);

private:
    bool eventFilter(QObject *obj, QEvent *e);

    void initTable();
    void updataTable(int);

    void setcamera(int,int);

    int camNum;
    unsigned long long all_NG,all_OK,com_NG,com_OK;

    QVector<camera*>* _cameras = nullptr;
    QWidget *update_mvimg;
    QStandardItemModel *_tableModel= nullptr;
    QGridLayout *_layout = nullptr;
    QGridLayout *_b_data_layout = nullptr;

    //
    SettingPage *setting;

    Ui::mainpage *ui;
};

#endif // MAINPAGE_H
