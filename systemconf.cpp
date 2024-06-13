#include "systemconf.h"

systemConf::systemConf(QObject *parent)
    : QObject{parent}
{
   //set.setPath(QSettings::IniFormat,QSettings::UserScope,"ind.conf");
}

void systemConf::init()
{
    mutex.lock();
    set.beginGroup("setings");
    int layout = set.value("VLayout").toInt();
    int row,colum;
    if(layout == 5){
        row = set.value("VRow").toInt();
        colum = set.value("VColum").toInt();
    }
    set.endGroup();
    set.beginGroup("camera");
    int cameraNum = set.value("num").toInt();
    QStringList path_list;
    QVector<bool> enable;
    for(int i = 0;i<cameraNum;i++){
        path_list << set.value("Path"+QString::number(i)).toString();
        enable.push_back(set.value("enable"+QString::number(i)).toInt());
    }
    set.endGroup();
    mutex.unlock();
}

void systemConf::save(QString group,QString key,QVariant value)
{
    mutex.lock();
    set.beginGroup(group);
    set.setValue(key,value);
    set.endGroup();
    mutex.unlock();
}

QSettings systemConf::set = QSettings(QSettings::IniFormat,QSettings::UserScope,"ind.conf");
QMutex systemConf::mutex = QMutex();
