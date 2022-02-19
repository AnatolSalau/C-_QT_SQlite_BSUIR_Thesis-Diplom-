#ifndef QPHONETOOLS_H
#define QPHONETOOLS_H

#include <QObject>
#include "phone.h"

class QPhoneTools : public QObject
{
    Q_OBJECT
public:
    explicit QPhoneTools(QObject *parent = nullptr);

signals:

public slots:
    bool isPhoneCorrect(const QString & phone) const ;
    QString formatPhone(const QString & phone, const QString & format) const ;
};

#endif // QPHONETOOLS_H
