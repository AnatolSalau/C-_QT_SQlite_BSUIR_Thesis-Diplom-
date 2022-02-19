#include "mainengine.h"
#include <QDate>
#include <QDebug>
#include "phone.h"

MainEngine::MainEngine(QScriptEngine *engine)
{
    this->engine = engine ;
    this->engine->globalObject().setProperty("tools",engine->newQObject(this));
}

QScriptEngine * MainEngine::getEngine()
{
    return engine ;
}

QDate MainEngine::str2rusdate(const QString &rusdate)
{
    QDate date = QDate::fromString(rusdate,"dd.MM.yyyy") ;
    if (!date.isValid()) date = QDate::currentDate() ;
    return date ;
}

QScriptValue MainEngine::parseRusDate(const QString &rusdate)
{
    return engine->newDate(QDateTime(str2rusdate(rusdate))) ;
}

QScriptValue MainEngine::nowDate()
{
    return engine->newDate(QDateTime(QDate::currentDate())) ;
}

QScriptValue MainEngine::formatPhone(const QString &phone, const QString &format)
{
    Phone p(phone) ;
    if (!p.isCorrect()) return phone ;
    return p.getFormattedStr(format) ;
}

