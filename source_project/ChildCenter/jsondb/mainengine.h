#ifndef MAINENGINE_H
#define MAINENGINE_H

#include <QObject>
#include <QtScript/QScriptEngine>

class MainEngine: public QObject
{
    Q_OBJECT
private:
    QScriptEngine * engine ;
public:    
    MainEngine(QScriptEngine * engine);
    QScriptEngine *getEngine() ;
    static QDate str2rusdate(const QString & rusdate) ;
public slots:
    QScriptValue parseRusDate(const QString & rusdate) ;
    QScriptValue nowDate() ;
    QScriptValue formatPhone(const QString & phone, const QString & format) ;
};

#endif // MAINENGINE_H
