#include "dialog.h"
#include <QApplication>

//开发环境 Qt 5.15.2MinGW_64_bit

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
