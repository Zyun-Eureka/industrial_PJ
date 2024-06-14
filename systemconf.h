#ifndef SYSTEMCONF_H
#define SYSTEMCONF_H

#include <QObject>
#include <QMutex>
#include <QSettings>


#define CONF_CAMERA_GROUP "camera"
#define CONF_CAMERA_PATH "cam_P"
#define CONF_CAMERA_NUM "cam_num"

#define CONF_SETTING_GROUP "setings"
#define CONF_SETTING_VLAYOUT "VLayout"
#define CONF_SETTING_ROW "VRow"
#define CONF_SETTING_COLUMN "VColumn"

class systemConf : public QObject
{
    Q_OBJECT
public:
    explicit systemConf(QObject *parent = nullptr);

    static void init();
    static void save(QString group,QString key,QVariant value);

    static QSettings set;
    static QMutex mutex;
    static QMap<QString,QVariant> values;
signals:
private:

};

#endif // SYSTEMCONF_H
