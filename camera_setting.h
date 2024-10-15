#ifndef CAMERA_SETTING_H
#define CAMERA_SETTING_H

#include <QWidget>

namespace Ui {
class camera_setting;
}

class camera_setting : public QWidget
{
    Q_OBJECT

public:
    explicit camera_setting(QWidget *parent = nullptr);
    ~camera_setting();

private:
    Ui::camera_setting *ui;
};

#endif // CAMERA_SETTING_H
