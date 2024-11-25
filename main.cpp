#include "dialog.h"
#include <QApplication>

#include "systemconf.h"
#include "mainpage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    systemConf::init();
    mainpage w;
    w.show();
    return a.exec();
}
