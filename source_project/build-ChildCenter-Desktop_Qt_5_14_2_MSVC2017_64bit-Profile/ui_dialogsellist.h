/********************************************************************************
** Form generated from reading UI file 'dialogsellist.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSELLIST_H
#define UI_DIALOGSELLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogSelList
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogSelList)
    {
        if (DialogSelList->objectName().isEmpty())
            DialogSelList->setObjectName(QString::fromUtf8("DialogSelList"));
        DialogSelList->resize(400, 300);
        verticalLayout = new QVBoxLayout(DialogSelList);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(DialogSelList);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        buttonBox = new QDialogButtonBox(DialogSelList);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DialogSelList);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogSelList, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogSelList, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogSelList);
    } // setupUi

    void retranslateUi(QDialog *DialogSelList)
    {
        DialogSelList->setWindowTitle(QCoreApplication::translate("DialogSelList", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogSelList: public Ui_DialogSelList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSELLIST_H
