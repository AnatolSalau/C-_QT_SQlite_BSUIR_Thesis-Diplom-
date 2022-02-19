/********************************************************************************
** Form generated from reading UI file 'dialogeditobject.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGEDITOBJECT_H
#define UI_DIALOGEDITOBJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogEditObject
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogEditObject)
    {
        if (DialogEditObject->objectName().isEmpty())
            DialogEditObject->setObjectName(QString::fromUtf8("DialogEditObject"));
        DialogEditObject->resize(561, 300);
        verticalLayout = new QVBoxLayout(DialogEditObject);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));

        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(DialogEditObject);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DialogEditObject);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogEditObject, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogEditObject, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogEditObject);
    } // setupUi

    void retranslateUi(QDialog *DialogEditObject)
    {
        DialogEditObject->setWindowTitle(QCoreApplication::translate("DialogEditObject", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogEditObject: public Ui_DialogEditObject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGEDITOBJECT_H
