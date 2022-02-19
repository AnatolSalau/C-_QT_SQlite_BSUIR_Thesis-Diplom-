/********************************************************************************
** Form generated from reading UI file 'dialogviewlist.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGVIEWLIST_H
#define UI_DIALOGVIEWLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogViewList
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *ButExport;
    QPushButton *ButExportCSV;
    QComboBox *comboCoding;
    QPushButton *butDel;
    QSpacerItem *horizontalSpacer;
    QTableView *tableList;

    void setupUi(QDialog *DialogViewList)
    {
        if (DialogViewList->objectName().isEmpty())
            DialogViewList->setObjectName(QString::fromUtf8("DialogViewList"));
        DialogViewList->resize(611, 522);
        verticalLayout = new QVBoxLayout(DialogViewList);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        widget = new QWidget(DialogViewList);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        ButExport = new QPushButton(widget);
        ButExport->setObjectName(QString::fromUtf8("ButExport"));

        horizontalLayout->addWidget(ButExport);

        ButExportCSV = new QPushButton(widget);
        ButExportCSV->setObjectName(QString::fromUtf8("ButExportCSV"));

        horizontalLayout->addWidget(ButExportCSV);

        comboCoding = new QComboBox(widget);
        comboCoding->setObjectName(QString::fromUtf8("comboCoding"));

        horizontalLayout->addWidget(comboCoding);

        butDel = new QPushButton(widget);
        butDel->setObjectName(QString::fromUtf8("butDel"));

        horizontalLayout->addWidget(butDel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget);

        tableList = new QTableView(DialogViewList);
        tableList->setObjectName(QString::fromUtf8("tableList"));

        verticalLayout->addWidget(tableList);


        retranslateUi(DialogViewList);

        QMetaObject::connectSlotsByName(DialogViewList);
    } // setupUi

    void retranslateUi(QDialog *DialogViewList)
    {
        DialogViewList->setWindowTitle(QString());
        ButExport->setText(QCoreApplication::translate("DialogViewList", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202 TXT", nullptr));
        ButExportCSV->setText(QCoreApplication::translate("DialogViewList", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202 CSV", nullptr));
        butDel->setText(QCoreApplication::translate("DialogViewList", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogViewList: public Ui_DialogViewList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGVIEWLIST_H
