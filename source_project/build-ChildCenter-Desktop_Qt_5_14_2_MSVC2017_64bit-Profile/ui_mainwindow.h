/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *butAddClient;
    QPushButton *butEditClient;
    QPushButton *butDelClient;
    QPushButton *butAddChild;
    QPushButton *butEditChild;
    QPushButton *butDelChild;
    QPushButton *butSetCats;
    QPushButton *ButList;
    QPushButton *butDiag;
    QPushButton *ButFind;
    QPushButton *butRefs;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QTableView *tableClients;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QTableView *tableChildrens;
    QLabel *label;
    QTextEdit *textInfo;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labInfo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1064, 646);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 50));
        widget->setMaximumSize(QSize(16777215, 50));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        butAddClient = new QPushButton(widget);
        butAddClient->setObjectName(QString::fromUtf8("butAddClient"));

        horizontalLayout->addWidget(butAddClient);

        butEditClient = new QPushButton(widget);
        butEditClient->setObjectName(QString::fromUtf8("butEditClient"));

        horizontalLayout->addWidget(butEditClient);

        butDelClient = new QPushButton(widget);
        butDelClient->setObjectName(QString::fromUtf8("butDelClient"));

        horizontalLayout->addWidget(butDelClient);

        butAddChild = new QPushButton(widget);
        butAddChild->setObjectName(QString::fromUtf8("butAddChild"));

        horizontalLayout->addWidget(butAddChild);

        butEditChild = new QPushButton(widget);
        butEditChild->setObjectName(QString::fromUtf8("butEditChild"));

        horizontalLayout->addWidget(butEditChild);

        butDelChild = new QPushButton(widget);
        butDelChild->setObjectName(QString::fromUtf8("butDelChild"));

        horizontalLayout->addWidget(butDelChild);

        butSetCats = new QPushButton(widget);
        butSetCats->setObjectName(QString::fromUtf8("butSetCats"));

        horizontalLayout->addWidget(butSetCats);

        ButList = new QPushButton(widget);
        ButList->setObjectName(QString::fromUtf8("ButList"));

        horizontalLayout->addWidget(ButList);

        butDiag = new QPushButton(widget);
        butDiag->setObjectName(QString::fromUtf8("butDiag"));

        horizontalLayout->addWidget(butDiag);

        ButFind = new QPushButton(widget);
        ButFind->setObjectName(QString::fromUtf8("ButFind"));

        horizontalLayout->addWidget(ButFind);

        butRefs = new QPushButton(widget);
        butRefs->setObjectName(QString::fromUtf8("butRefs"));

        horizontalLayout->addWidget(butRefs);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addWidget(widget);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, 5, 5, 5);
        tableClients = new QTableView(widget_2);
        tableClients->setObjectName(QString::fromUtf8("tableClients"));

        horizontalLayout_2->addWidget(tableClients);

        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout = new QVBoxLayout(widget_3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        tableChildrens = new QTableView(widget_3);
        tableChildrens->setObjectName(QString::fromUtf8("tableChildrens"));
        tableChildrens->setMinimumSize(QSize(0, 200));
        tableChildrens->setMaximumSize(QSize(16777215, 200));

        verticalLayout->addWidget(tableChildrens);

        label = new QLabel(widget_3);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        textInfo = new QTextEdit(widget_3);
        textInfo->setObjectName(QString::fromUtf8("textInfo"));
        textInfo->setAutoFillBackground(false);
        textInfo->setReadOnly(true);

        verticalLayout->addWidget(textInfo);


        horizontalLayout_2->addWidget(widget_3);


        verticalLayout_2->addWidget(widget_2);

        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setMinimumSize(QSize(0, 40));
        widget_4->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labInfo = new QLabel(widget_4);
        labInfo->setObjectName(QString::fromUtf8("labInfo"));

        horizontalLayout_3->addWidget(labInfo);


        verticalLayout_2->addWidget(widget_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1064, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\221\320\260\320\267\320\260 \320\264\320\265\321\202\321\201\320\272\320\276\320\263\320\276 \321\206\320\265\320\275\321\202\321\200\320\260", nullptr));
        butAddClient->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\320\265\320\274\321\214\321\216", nullptr));
        butEditClient->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\200\321\200\320\265\320\272\321\206\320\270\321\217", nullptr));
        butDelClient->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265", nullptr));
        butAddChild->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\200\320\265\320\261\320\265\320\275\320\272\320\260", nullptr));
        butEditChild->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\200\321\200\320\265\320\272\321\206\320\270\321\217", nullptr));
        butDelChild->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265", nullptr));
        butSetCats->setText(QCoreApplication::translate("MainWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270", nullptr));
        ButList->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272", nullptr));
        butDiag->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\264\320\270\320\260\320\263\321\200\320\260\320\274\320\274\321\203", nullptr));
        ButFind->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270", nullptr));
        butRefs->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\276\321\207\320\275\320\270\320\272\320\270", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\321\202\320\270", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", nullptr));
        labInfo->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
