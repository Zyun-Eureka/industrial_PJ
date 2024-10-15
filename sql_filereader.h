#ifndef SQL_FILEREADER_H
#define SQL_FILEREADER_H

#include <QObject>
#include <QImage>

#include <QSqlQuery>
#include <QVariant>

class sql_filereader : public QObject
{
    Q_OBJECT
public:
    explicit sql_filereader(QObject *parent = nullptr);

    QList<QImage> OK_img_list;
    QList<QImage> NG_img_list;
    bool readDB(QString connectDBName);
    void setPath(QString path);

signals:
    void imgReady(bool type,int index);
    void clearList();
    void pri_start();
private slots:
    void read();
private:
    QSqlQuery* query;
    // ok path
    QString _OKPath;
    // ng path
    QString _NGPath;
};

#endif // SQL_FILEREADER_H
