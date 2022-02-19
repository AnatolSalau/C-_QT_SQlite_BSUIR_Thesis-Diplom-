/********************************************************************************
** Form generated from reading UI file 'dialogphotoview.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGPHOTOVIEW_H
#define UI_DIALOGPHOTOVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include "qlabelclickable.h"

QT_BEGIN_NAMESPACE

class Ui_DialogPhotoView
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labInfo;
    QLabelClickable *labView;

    void setupUi(QDialog *DialogPhotoView)
    {
        if (DialogPhotoView->objectName().isEmpty())
            DialogPhotoView->setObjectName(QString::fromUtf8("DialogPhotoView"));
        DialogPhotoView->resize(400, 300);
        verticalLayout = new QVBoxLayout(DialogPhotoView);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labInfo = new QLabel(DialogPhotoView);
        labInfo->setObjectName(QString::fromUtf8("labInfo"));
        labInfo->setMaximumSize(QSize(16777215, 20));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        labInfo->setFont(font);
        labInfo->setFrameShape(QFrame::Box);
        labInfo->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labInfo);

        labView = new QLabelClickable(DialogPhotoView);
        labView->setObjectName(QString::fromUtf8("labView"));
        labView->setFrameShape(QFrame::NoFrame);

        verticalLayout->addWidget(labView);


        retranslateUi(DialogPhotoView);

        QMetaObject::connectSlotsByName(DialogPhotoView);
    } // setupUi

    void retranslateUi(QDialog *DialogPhotoView)
    {
        DialogPhotoView->setWindowTitle(QCoreApplication::translate("DialogPhotoView", "\320\244\320\276\321\202\320\276", nullptr));
        labInfo->setText(QCoreApplication::translate("DialogPhotoView", "TextLabel", nullptr));
        labView->setText(QCoreApplication::translate("DialogPhotoView", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogPhotoView: public Ui_DialogPhotoView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGPHOTOVIEW_H
