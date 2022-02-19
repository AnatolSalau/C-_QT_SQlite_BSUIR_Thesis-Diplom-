#ifndef QJSONSEARCHINOBJECT_H
#define QJSONSEARCHINOBJECT_H

#include "all_qjson.h"
#include <QMap>
class QJsonSearchInObject
{
private:
    QString str ;
    QMap<QString,QString> fields ;
    void recFindInObject(const QJsonObject &obj, const QString &parentpart) ;
public:
    QJsonSearchInObject(const QString & str);
    void findInObject(const QJsonObject &obj) ;
    QMap<QString,QString> getWhereFind() const ;
};

#endif // QJSONSEARCHINOBJECT_H
