#ifndef VERTIFY_D_H
#define VERTIFY_D_H

#include <QDialog>

// 身份验证功能
// 目前只实现页面未实现验证功能
// 验证成功会发送 success() 信号到设置界面解锁
// 程序制作 钟明辉 & 黄志涣

namespace Ui {
class vertify_d;
}

class vertify_d : public QDialog
{
    Q_OBJECT

public:
    explicit vertify_d(QWidget *parent = nullptr);
    ~vertify_d();

    void show();
signals:
    void success();
private slots:
    void on_close_bt_clicked();
    void on_vertify_bt_clicked();
private:
    Ui::vertify_d *ui;
};

#endif // VERTIFY_D_H
