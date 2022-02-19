#include "qjsonutils.h"
#include <QString>
#include <QFile>

QJsonUtils globalutils ;

QJsonUtils::QJsonUtils(QObject *parent) : QObject(parent)
{

}

QJsonUtils *QJsonUtils::getGlobalUtils()
{
    return &globalutils ;
}

QJsonObject QJsonUtils::loadObjectFromFile(const QString & filename)
{
    QFile jfile(filename);
    jfile.open(QIODevice::ReadOnly);    
    QJsonDocument doc = QJsonDocument::fromJson(jfile.readAll(),&error) ;
    if (error.error!=QJsonParseError::NoError)
        emit sendParseError(filename,error.errorString()) ;
    jfile.close() ;
    return doc.object() ;
}

QJsonArray QJsonUtils::loadArrayFromFile(const QString & filename)
{
    QFile jfile(filename);
    jfile.open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(jfile.readAll(),&error) ;
    if (error.error!=QJsonParseError::NoError)
        emit sendParseError(filename,error.errorString()) ;
    jfile.close() ;
    return doc.array() ;
}

void QJsonUtils::saveArrayToFile(QString filename, const QJsonArray &array)
{
    QJsonDocument doc ;
    doc.setArray(array) ;

    QFile file(filename) ;
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson()) ;
    file.close() ;
}

QJsonObject QJsonUtils::createObjectWith1Field(QString fieldname, QJsonValue value)
{
    QJsonObject obj ;
    obj[fieldname]=value ;
    return obj ;
}

QJsonObject QJsonUtils::createObjectWith2Field(QString fieldname1, QJsonValue value1, QString fieldname2, QJsonValue value2)
{
    QJsonObject obj ;
    obj[fieldname1]=value1 ;
    obj[fieldname2]=value2 ;
    return obj ;
}

QJsonValue QJsonUtils::getValue(const QJsonObject &obj, const QString &field, const QJsonValue &defvalue)
{
    if (obj.contains(field)) return obj[field] ; else return defvalue ;
}

QString QJsonUtils::getJsonValueAsString(const QJsonValue & value)
{
    if (value.isString()) return value.toString() ;
    if (value.isDouble()) return QString::number(value.toDouble()) ;
    if (value.isBool()) return value.toBool()?QString("Да"):QString("Нет") ;
    if (value.isNull()) return "(null)" ;
    if (value.isObject()) return "(object)" ;
    if (value.isArray()) return "(array)" ;
    return "Unknown value type" ;
}
