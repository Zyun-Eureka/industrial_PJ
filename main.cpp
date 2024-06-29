#include "dialog.h"
#include <QApplication>

#include "systemconf.h"

#include "imglist.h"

//开发环境 Linux Qt 5.15.2MinGW_64_bit

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    systemConf::init();
    Dialog w;
 //   Imglist w;
    w.show();
    return a.exec();
}
