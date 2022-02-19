#include "qphonetools.h"

QPhoneTools::QPhoneTools(QObject *parent) : QObject(parent)
{

}

bool QPhoneTools::isPhoneCorrect(const QString & phone) const
{
    Phone p(phone) ;
    return p.isCorrect() ;
}

QString QPhoneTools::formatPhone(const QString & phone, const QString & format) const
{
    Phone p(phone) ;
    return p.getFormattedStr(format) ;
}
