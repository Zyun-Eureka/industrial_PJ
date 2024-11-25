#include "sql_filereader.h"
#include <QDebug>

#include <QThread>

sql_filereader::sql_filereader(QObject *parent)
    : QObject{parent}
{
    query = nullptr;
    connect(this,SIGNAL(pri_start()),this,SLOT(read()));
}

bool sql_filereader::readDB(QString connectDBName)
{
    query = new QSqlQuery(QSqlDatabase::database((connectDBName)));
    emit clearList();
    OK_img_list.clear();
    NG_img_list.clear();
    emit pri_start();
    qDebug()<<"readdb by"<<thread()->currentThreadId();
    return QSqlDatabase::database((connectDBName)).isOpen();
}

void sql_filereader::setPath(QString path)
{
    _OKPath = path + "/OK/%1";
    _NGPath = path + "/NG/%1";
}

void sql_filereader::read()
{
    //imgNewName,result
    query->exec("select imgNewName,result from imgs");
    while(query->next()){
        if(query->value(1).toBool()){
            OK_img_list.push_back(QImage(_OKPath.arg(query->value(0).toString())));
            if(OK_img_list.last().isNull()){
                OK_img_list.pop_back();
                qDebug()<<_OKPath.arg(query->value(0).toString());
                continue;
            }
            emit imgReady(true,OK_img_list.length()-1);
        }else{
            NG_img_list.push_back(QImage(_NGPath.arg(query->value(0).toString())));
            if(NG_img_list.last().isNull()){
                NG_img_list.pop_back();
                continue;
            }
            emit imgReady(false,NG_img_list.length()-1);
        }
    }
}
