/********************************************************************************
** Form generated from reading UI file 'dialogloader.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLOADER_H
#define UI_DIALOGLOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_DialogLoader
{
public:
    QLabel *labProgress;

    void setupUi(QDialog *DialogLoader)
    {
        if (DialogLoader->objectName().isEmpty())
            DialogLoader->setObjectName(QString::fromUtf8("DialogLoader"));
        DialogLoader->resize(364, 91);
        labProgress = new QLabel(DialogLoader);
        labProgress->setObjectName(QString::fromUtf8("labProgress"));
        labProgress->setGeometry(QRect(20, 10, 171, 16));

        retranslateUi(DialogLoader);

        QMetaObject::connectSlotsByName(DialogLoader);
    } // setupUi

    void retranslateUi(QDialog *DialogLoader)
    {
        DialogLoader->setWindowTitle(QCoreApplication::translate("DialogLoader", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260", nullptr));
        labProgress->setText(QCoreApplication::translate("DialogLoader", "\320\230\320\264\320\265\321\202 \320\267\320\260\320\263\321\200\321\203\320\267\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogLoader: public Ui_DialogLoader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLOADER_H
