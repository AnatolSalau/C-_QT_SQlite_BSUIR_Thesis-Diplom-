#include "phone.h"

Phone::Phone()
{
    str="0000000000" ;
    iscorrect=false ;
}

Phone::Phone(const Phone &src)
{
    str=src.str ;
    iscorrect = src.iscorrect ;
}

const QString DIGITS = "0123456789" ;
const int MIN_PHONE_LEN = 5;
const int MAX_PHONE_LEN = 7;

QString stripExceptDigits(const QString & str)
{
    QString res = "";
    foreach (auto c, str)
        if (DIGITS.indexOf(c)!=-1) res.append(c);
    return res;
}

Phone::Phone(const QString &src)
{
    iscorrect = true ;

    QString ph = stripExceptDigits(src) ;
    if (ph.length() == 10)
        str = ph ;
    else
        if ((ph.length() == 11) && ((ph[0]=='7')||(ph[0]=='8')))
            str = ph.mid(1);
        else
            if ((ph.length() >= MIN_PHONE_LEN) && (ph.length() <= MAX_PHONE_LEN))
                str = ph ;
            else
                iscorrect=false ;
}

QString Phone::getFormattedStr(const QString & phoneformat) const
{
    QString res = "";
    int p = 0;
    foreach (auto c, phoneformat)
        if (c=='X') {
            if (p>=str.length()) break ;
            res.append(str[p++]);
        }
            else res.append(c);
    return res;
}

bool Phone::isCorrect() const
{
    return iscorrect ;
}
