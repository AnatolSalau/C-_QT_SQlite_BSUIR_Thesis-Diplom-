#ifndef HELPER_H
#define HELPER_H
#include <QString>
#include <QWidget>

/*
  Обновление 1.0.1.2 - добавили запись строк и байт
*/

class Helper
{
public:
    Helper();
    static QString readAllText(const QString & filename, const QString & defvalue="") ;
    // 1.0.1.2
    static bool writeAllText(const QString & filename, const QString & str) ;
    static QByteArray readAllBytes(const QString & filename) ;
    // 1.0.1.2
    static bool writeAllBytes(const QString & filename, const QByteArray & data) ;
    static bool confirm(QWidget * parent, const QString &msg, const QString & header="")  ;
};

#endif // HELPER_H
