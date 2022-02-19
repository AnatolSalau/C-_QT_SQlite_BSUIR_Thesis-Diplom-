/********************************************************************************
** Form generated from reading UI file 'dialogviewdiag.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGVIEWDIAG_H
#define UI_DIALOGVIEWDIAG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_DialogViewDiag
{
public:

    void setupUi(QDialog *DialogViewDiag)
    {
        if (DialogViewDiag->objectName().isEmpty())
            DialogViewDiag->setObjectName(QString::fromUtf8("DialogViewDiag"));
        DialogViewDiag->resize(422, 405);

        retranslateUi(DialogViewDiag);

        QMetaObject::connectSlotsByName(DialogViewDiag);
    } // setupUi

    void retranslateUi(QDialog *DialogViewDiag)
    {
        DialogViewDiag->setWindowTitle(QCoreApplication::translate("DialogViewDiag", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogViewDiag: public Ui_DialogViewDiag {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGVIEWDIAG_H
