#include "qjsonsearchinobject.h"
#include <QStringList>

QJsonSearchInObject::QJsonSearchInObject(const QString & str)
{    
    this->str = str.trimmed() ;
}

void QJsonSearchInObject::recFindInObject(const QJsonObject & obj, const QString & parentpart)
{
    foreach (auto key, obj.keys()) {
        if (obj[key].isString())
            if (obj[key].toString().contains(str,Qt::CaseInsensitive))
                fields.insert(parentpart+key,obj[key].toString()) ;
        if (obj[key].isDouble())
            if (QString::number(obj[key].toDouble()).contains(str,Qt::CaseInsensitive))
                fields.insert(parentpart+key,QString::number(obj[key].toDouble())) ;
        if (obj[key].isObject())
            recFindInObject(obj[key].toObject(),key+"_") ;
        if (obj[key].isArray())
            foreach(auto item, obj[key].toArray())
                if (item.isObject())
                    recFindInObject(item.toObject(),key+"_") ;
    }
}

void QJsonSearchInObject::findInObject(const QJsonObject & obj)
{
    fields.clear() ;
    recFindInObject(obj,"") ;
}

QMap<QString,QString> QJsonSearchInObject::getWhereFind() const {
    return fields ;
}
