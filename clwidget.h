#ifndef CLWIDGET_H
#define CLWIDGET_H

#include <QWidget>
#include <QImage>

#include <QEvent>


class clWidget : public QWidget
{
    Q_OBJECT
public:
    explicit clWidget(QWidget *parent = nullptr);
    QImage image;
    bool eventFilter(QObject *watched, QEvent *event);
    void setimg(QImage);
signals:
private:
    int img_index;
    int x;
    int y;
};

#endif // CLWIDGET_H
