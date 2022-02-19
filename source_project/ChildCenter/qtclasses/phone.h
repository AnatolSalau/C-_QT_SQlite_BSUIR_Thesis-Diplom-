#ifndef PHONE_H
#define PHONE_H

#include <QString>

class Phone
{
private:
    QString str ;
    bool iscorrect ;
public:
    Phone();
    Phone(const Phone & src);
    Phone(const QString & src);
    QString getStr() const ;
    QString getFormattedStr(const QString &phoneformat) const ;
    bool isCorrect() const ;
};

#endif // PHONE_H
