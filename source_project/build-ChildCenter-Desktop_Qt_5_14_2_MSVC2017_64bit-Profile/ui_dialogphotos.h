/********************************************************************************
** Form generated from reading UI file 'dialogphotos.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGPHOTOS_H
#define UI_DIALOGPHOTOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogPhotos
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *ButAddPhoto;
    QPushButton *ButDelPhoto;
    QPushButton *ButSetPhotDefault;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogPhotos)
    {
        if (DialogPhotos->objectName().isEmpty())
            DialogPhotos->setObjectName(QString::fromUtf8("DialogPhotos"));
        DialogPhotos->resize(537, 416);
        verticalLayout = new QVBoxLayout(DialogPhotos);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(DialogPhotos);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 40));
        widget->setMaximumSize(QSize(16777215, 40));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        ButAddPhoto = new QPushButton(widget);
        ButAddPhoto->setObjectName(QString::fromUtf8("ButAddPhoto"));

        horizontalLayout->addWidget(ButAddPhoto);

        ButDelPhoto = new QPushButton(widget);
        ButDelPhoto->setObjectName(QString::fromUtf8("ButDelPhoto"));

        horizontalLayout->addWidget(ButDelPhoto);

        ButSetPhotDefault = new QPushButton(widget);
        ButSetPhotDefault->setObjectName(QString::fromUtf8("ButSetPhotDefault"));

        horizontalLayout->addWidget(ButSetPhotDefault);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget);

        buttonBox = new QDialogButtonBox(DialogPhotos);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DialogPhotos);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogPhotos, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogPhotos, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogPhotos);
    } // setupUi

    void retranslateUi(QDialog *DialogPhotos)
    {
        DialogPhotos->setWindowTitle(QCoreApplication::translate("DialogPhotos", "Dialog", nullptr));
        ButAddPhoto->setText(QCoreApplication::translate("DialogPhotos", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\204\320\276\321\202\320\276", nullptr));
        ButDelPhoto->setText(QCoreApplication::translate("DialogPhotos", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\204\320\276\321\202\320\276", nullptr));
        ButSetPhotDefault->setText(QCoreApplication::translate("DialogPhotos", "\320\241\320\264\320\265\320\273\320\260\321\202\321\214 \320\277\320\276 \321\203\320\274\320\276\320\273\321\207\320\260\320\275\320\270\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogPhotos: public Ui_DialogPhotos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGPHOTOS_H
