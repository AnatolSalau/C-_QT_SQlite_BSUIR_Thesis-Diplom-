QT       += core gui script sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogloader.cpp \
    dialogrefedit.cpp \
    dialogviewdiag.cpp \
    dialogviewlist.cpp \
    formbuilder.cpp \
    jsondb/dialogeditobject.cpp \
    jsondb/dialogphotos.cpp \
    jsondb/dialogphotoview.cpp \
    jsondb/dialogsellist.cpp \
    jsondb/mainengine.cpp \
    jsondb/qjsonsortproxymodel.cpp \
    jsondb/qjsontablemodel.cpp \
    jsondb/qjsonutils.cpp \
    main.cpp \
    mainwindow.cpp \
    qjsonsearchinobject.cpp \
    qtclasses/phone.cpp \
    qtclasses/qlabelclickable.cpp \
    qtclasses/qphonetools.cpp \
    qtex/helper.cpp

HEADERS += \
    Consts.h \
    all_qjson.h \
    dialogloader.h \
    dialogrefedit.h \
    dialogviewdiag.h \
    dialogviewlist.h \
    formbuilder.h \
    jsondb/dialogeditobject.h \
    jsondb/dialogphotos.h \
    jsondb/dialogphotoview.h \
    jsondb/dialogsellist.h \
    jsondb/mainengine.h \
    jsondb/qjsonsortproxymodel.h \
    jsondb/qjsontablemodel.h \
    jsondb/qjsonutils.h \
    mainwindow.h \
    qjsonsearchinobject.h \
    qtclasses/phone.h \
    qtclasses/qlabelclickable.h \
    qtclasses/qphonetools.h \
    qtex/helper.h

FORMS += \
    dialogloader.ui \
    dialogrefedit.ui \
    dialogviewdiag.ui \
    dialogviewlist.ui \
    jsondb/dialogeditobject.ui \
    jsondb/dialogphotos.ui \
    jsondb/dialogphotoview.ui \
    jsondb/dialogsellist.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/qtex
INCLUDEPATH += $$PWD/qtclasses
INCLUDEPATH += $$PWD/jsondb
