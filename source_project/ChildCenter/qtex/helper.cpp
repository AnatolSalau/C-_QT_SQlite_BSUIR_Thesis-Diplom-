#include "helper.h"

#include <QFile>
#include <QMessageBox>

Helper::Helper()
{

}

QString Helper::readAllText(const QString & filename, const QString & defvalue) {
    QFile file(filename);
    if (!file.exists()) return defvalue ;
    if (!file.open(QIODevice::ReadOnly)) return defvalue ;

    QString res = file.readAll() ;
    file.close();
    return res ;
}

bool Helper::writeAllText(const QString &filename, const QString &str)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) return false ;
    file.write(str.toUtf8()) ;
    file.close();
    return true ;
}

QByteArray Helper::readAllBytes(const QString & filename) {
    QFile file(filename);
    if (!file.exists()) return QByteArray() ;
    if (!file.open(QIODevice::ReadOnly)) return QByteArray() ;

    QByteArray res = file.readAll() ;
    file.close();
    return res ;
}

bool Helper::writeAllBytes(const QString &filename, const QByteArray &data)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) return false ;
    file.write(data) ;
    file.close();
    return true ;
}

bool Helper::confirm(QWidget * parent, const QString &msg, const QString & header)
{
    QMessageBox msgbox(QMessageBox::Question,
                (header!="")?header:"Подтверждение",msg,
                QMessageBox::Yes | QMessageBox::No,
                parent);
    msgbox.setButtonText(QMessageBox::Yes, "Да");
    msgbox.setButtonText(QMessageBox::No, "Нет");
    return (msgbox.exec() == QMessageBox::Yes) ;
}


