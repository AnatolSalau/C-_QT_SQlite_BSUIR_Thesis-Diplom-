#include "dialogeditobject.h"
#include "ui_dialogeditobject.h"
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include "qjsonutils.h"
#include <QJsonValue>
#include <QPushButton>
#include <QDebug>
#include <QDateEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include "mainengine.h"

DialogEditObject::DialogEditObject(const QJsonObject & obj, const QJsonObject & settings,
                                   QScriptEngine *engine, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditObject)
{
    ui->setupUi(this);

    this->engine = engine ;
    this->settings = settings ;
    saved = obj ;

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("ОК");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Отмена");
    setWindowTitle(settings.value("title").toString()) ;

    if (settings.value("inputs").toArray().count()==0)
        foreach (QString key, saved.keys())
            addRow(saved,key,key,QJsonObject()) ;
    else
        foreach (QJsonValue v, settings.value("inputs").toArray()) {
            QJsonObject optrow = v.toObject() ;
            QString key = optrow["field"].toString() ;
            if (saved[key].isNull()||saved[key].isUndefined())
                if (optrow["default"].isString()||optrow["default"].isDouble()||optrow["default"].isBool())
                    saved[key] = optrow["default"] ;
            addRow(saved,key,optrow["caption"].toString(),optrow) ;
        }

    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(reject())) ;
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accept())) ;
    //connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(saveObject())) ;
}

void DialogEditObject::addRow(const QJsonObject &obj, const QString &key, const QString &caption, const QJsonObject &optrow)
{
    QJsonValue data = obj[key] ;
    QWidget * widget = NULL;

    if (data.isString()) {
        if (optrow["control"].toString()==QString("dateedit")) {
            widget = new QDateEdit(MainEngine::str2rusdate(data.toString()),this) ;
            ((QDateEdit*)widget)->setCalendarPopup(true) ;
        }
        else
        if (optrow["control"].toString()==QString("memo")) {
            widget = new QPlainTextEdit(data.toString(),this) ;
            ((QPlainTextEdit*)widget)->setFixedHeight(
                        optrow["memoheight"].isDouble()?
                        optrow["memoheight"].toInt():100) ;
        }
        else
        if (optrow["control"].toString()==QString("combo")) {
            widget = new QComboBox(this) ;
            ((QComboBox*)widget)->insertItem(0,"-") ;
            QStringList source = optrow["combosource"].toString().split("::") ;
            if (source.length()==2) {
                if (source[0]=="[func]") {
                    QScriptValue list = engine->evaluate(source[1]) ;
                    for (int i=0; i<list.property("length").toInt32(); i++)
                        ((QComboBox*)widget)->addItem(list.property(i).toString());
                    int idx = ((QComboBox*)widget)->findText(data.toString()) ;
                    if (idx!=-1) ((QComboBox*)widget)->setCurrentIndex(idx) ;
                    else ((QComboBox*)widget)->setCurrentIndex(0) ;
                }
            }
        }
        else
            widget = new QLineEdit(data.toString(),this) ;
    }
    else
    if (data.isDouble())
        widget = new QLineEdit(QString::number(data.toDouble()),this) ;
    else
    if (data.isBool()) {
        widget = new QCheckBox(this) ;
        ((QCheckBox*)widget)->setChecked(data.toBool()) ;
    }

    if (widget!=NULL) {
        widget->setProperty("pkey",key) ;
        ui->formLayout->addRow(caption,widget) ;
    }
}

DialogEditObject::~DialogEditObject()
{
    delete ui;
}

QJsonObject DialogEditObject::getObject() const
{
    QJsonObject res = saved ;
    for (int i=0; i<ui->formLayout->rowCount(); i++) {
        QLayoutItem * wItem = ui->formLayout->itemAt(i,QFormLayout::FieldRole) ;
        QString key = wItem->widget()->property("pkey").toString() ;

        if (res[key].isString()) {
            if (QDateEdit * dateedit = qobject_cast<QDateEdit*>(wItem->widget())) {
                res[key]=dateedit->date().toString("dd.MM.yyyy") ;
            }
            else
            if (QPlainTextEdit * memo = qobject_cast<QPlainTextEdit*>(wItem->widget())) {
                res[key]=memo->toPlainText() ;
            }
            else
            if (QComboBox * combo = qobject_cast<QComboBox*>(wItem->widget())) {
                res[key]=combo->currentText() ;
            }
            else
                res[key]=((QLineEdit*)wItem->widget())->text() ;
        }
        else
        if (res[key].isDouble())
            res[key]=((QLineEdit*)wItem->widget())->text().toDouble() ;
        else
        if (res[key].isBool())
            res[key]=((QCheckBox*)wItem->widget())->isChecked() ;
    }
    return res ;

}

