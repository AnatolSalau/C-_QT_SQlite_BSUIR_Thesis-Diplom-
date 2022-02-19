/********************************************************************************
** Form generated from reading UI file 'dialogrefedit.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGREFEDIT_H
#define UI_DIALOGREFEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogRefEdit
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *butAdd;
    QPushButton *butEdit;
    QPushButton *butDel;
    QSpacerItem *horizontalSpacer;
    QTableView *tableView;

    void setupUi(QDialog *DialogRefEdit)
    {
        if (DialogRefEdit->objectName().isEmpty())
            DialogRefEdit->setObjectName(QString::fromUtf8("DialogRefEdit"));
        DialogRefEdit->resize(400, 365);
        verticalLayout = new QVBoxLayout(DialogRefEdit);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(DialogRefEdit);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        butAdd = new QPushButton(widget);
        butAdd->setObjectName(QString::fromUtf8("butAdd"));

        horizontalLayout->addWidget(butAdd);

        butEdit = new QPushButton(widget);
        butEdit->setObjectName(QString::fromUtf8("butEdit"));

        horizontalLayout->addWidget(butEdit);

        butDel = new QPushButton(widget);
        butDel->setObjectName(QString::fromUtf8("butDel"));

        horizontalLayout->addWidget(butDel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget);

        tableView = new QTableView(DialogRefEdit);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);


        retranslateUi(DialogRefEdit);

        QMetaObject::connectSlotsByName(DialogRefEdit);
    } // setupUi

    void retranslateUi(QDialog *DialogRefEdit)
    {
        DialogRefEdit->setWindowTitle(QCoreApplication::translate("DialogRefEdit", "Dialog", nullptr));
        butAdd->setText(QCoreApplication::translate("DialogRefEdit", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        butEdit->setText(QCoreApplication::translate("DialogRefEdit", "\320\232\320\276\321\200\321\200\320\265\320\272\321\206\320\270\321\217", nullptr));
        butDel->setText(QCoreApplication::translate("DialogRefEdit", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogRefEdit: public Ui_DialogRefEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGREFEDIT_H
