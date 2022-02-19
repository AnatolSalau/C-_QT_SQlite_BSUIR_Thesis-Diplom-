#ifndef QJSONUTILS_H
#define QJSONUTILS_H

#include <QObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

class QJsonUtils : public QObject
{
    Q_OBJECT
private:
    QJsonParseError error ;
public:
    explicit QJsonUtils(QObject *parent = nullptr);
    static QJsonUtils * getGlobalUtils() ;
    QJsonObject loadObjectFromFile(const QString &filename) ;
    QJsonArray loadArrayFromFile(const QString &filename) ;
    void saveArrayToFile(QString filename, const QJsonArray & array) ;
    QJsonObject createDefaultObj(const QJsonObject & settings) ;
    static QJsonObject createObjectWith1Field(QString fieldname, QJsonValue value) ;
    static QJsonObject createObjectWith2Field(QString fieldname1, QJsonValue value1,
                                              QString fieldname2, QJsonValue value2) ;
    static QJsonValue getValue(const QJsonObject & obj, const QString & field, const QJsonValue & defvalue) ;

public slots:
    QString getJsonValueAsString(const QJsonValue &value) ;

signals:
    void sendParseError(const QString & filename, const QString & error) ;
};

#endif // QJSONUTILS_H
