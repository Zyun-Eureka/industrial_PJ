#ifndef SYSTEMCONF_H
#define SYSTEMCONF_H

#include <QObject>
#include <QMutex>
#include <QSettings>

class systemConf : public QObject
{
    Q_OBJECT
public:
    explicit systemConf(QObject *parent = nullptr);

    void init();
    void save(QString group,QString key,QVariant value);

    static QSettings set;
    static QMutex mutex;
signals:
private:

};

#endif // SYSTEMCONF_H
