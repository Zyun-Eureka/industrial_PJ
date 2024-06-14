#include "systemconf.h"

#include <QDebug>

systemConf::systemConf(QObject *parent)
    : QObject{parent}
{
}

void systemConf::init()
{
    mutex.lock();
    values.clear();
    set.beginGroup(CONF_SETTING_GROUP);
    values[CONF_SETTING_VLAYOUT] = set.value(CONF_SETTING_VLAYOUT);
    int tmp = values[CONF_SETTING_VLAYOUT].toInt();
    values[CONF_SETTING_ROW] = set.value(CONF_SETTING_ROW);
    values[CONF_SETTING_COLUMN] = set.value(CONF_SETTING_COLUMN);
    set.endGroup();
    set.beginGroup(CONF_CAMERA_GROUP);
    values[CONF_CAMERA_NUM] = set.value(CONF_CAMERA_NUM).toInt();
    tmp = values[CONF_CAMERA_NUM].toInt();
    for(int i = 0;i<tmp;i++){
        values[CONF_CAMERA_PATH+QString::number(i)]=set.value(CONF_CAMERA_PATH+QString::number(i));
        values["cam_E"+QString::number(i)]=set.value("cam_E"+QString::number(i));
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

QSettings systemConf::set = QSettings("ind.conf",QSettings::IniFormat);
QMutex systemConf::mutex = QMutex();
QMap<QString,QVariant> systemConf::values = QMap<QString,QVariant>();
