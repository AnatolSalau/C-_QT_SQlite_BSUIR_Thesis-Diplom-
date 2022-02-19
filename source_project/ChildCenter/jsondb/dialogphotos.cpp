#include "dialogphotos.h"
#include "ui_dialogphotos.h"
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QDebug>
#include <QCheckBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QUuid>
#include "qlabelclickable.h"
#include "dialogphotoview.h"

const int PHOTO_HEIGHT = 100 ;

DialogPhotos::DialogPhotos(const QJsonObject &obj, const QString & photodir, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPhotos)
{
    ui->setupUi(this);
    saved = obj ;
    this->photodir = photodir ;

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("ОК");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Отмена");
    setWindowTitle("Фотографии") ;

    foreach(auto v, obj["Photos"].toArray())
       photos.append(v.toString()) ;

    photos2form() ;

    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(reject())) ;
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accept())) ;
}

DialogPhotos::~DialogPhotos()
{
    delete ui;
}

QJsonObject DialogPhotos::getObject()
{
    QJsonObject obj = saved ;

    QJsonArray arr ;
    foreach(auto photo, photos)
        arr.append(QJsonValue(photo)) ;
    obj["Photos"]=arr ;

    return obj ;
}

void DialogPhotos::photos2form()
{
    widget = new QWidget(this);
    form = new QFormLayout(widget);

    for (int i=0; i<photos.count(); i++) {
        QLabelClickable * lab = new QLabelClickable(this) ;
        QPixmap p ;
        if (p.load(photodir+photos[i])) {
            QPixmap ico = p.scaledToHeight(PHOTO_HEIGHT) ;
            lab->setMinimumSize(ico.width(),PHOTO_HEIGHT) ;
            lab->setMaximumSize(ico.width(),PHOTO_HEIGHT) ;
            lab->setPixmap(ico) ;
            lab->setProperty("index",i) ;
            lab->setCursor(Qt::PointingHandCursor) ;
            connect(lab,SIGNAL(click()),this,SLOT(clickphoto())) ;
        }

        QCheckBox * cb = new QCheckBox(this) ;

        form->addRow(cb,lab) ;
    }

    ui->verticalLayout->removeWidget(scroll) ;

    scroll = new QScrollArea(this) ;
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setWidget(widget);

    ui->verticalLayout->insertWidget(1,scroll) ;
}

void DialogPhotos::on_ButAddPhoto_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Файлы", QDir::currentPath(), "*.jpg *.png");
    if (filename=="") return ;

    QFileInfo fi(filename) ;
    QUuid uid = QUuid::createUuid() ;
    QString dstfilename = uid.toString()+"."+fi.suffix() ;
    photos.append(dstfilename) ;

    QFile::copy(filename,photodir+dstfilename) ;

    photos2form() ;
}

void DialogPhotos::on_ButDelPhoto_clicked()
{
    for (int i=0; i<form->rowCount(); i++) {
        QLayoutItem * wItem = form->itemAt(i,QFormLayout::LabelRole) ;
        if (((QCheckBox *)wItem->widget())->isChecked()) {
            QFile file(photodir+photos[i]) ;
            file.remove() ;
            photos.removeAt(i) ;

            photos2form() ;
            return ;
        }
    }
    QMessageBox::about(this,"Ошибка","Не выделено фото") ;
}

void DialogPhotos::on_ButSetPhotDefault_clicked()
{
    for (int i=0; i<form->rowCount(); i++) {
        QLayoutItem * wItem = form->itemAt(i,QFormLayout::LabelRole) ;
        if (((QCheckBox *)wItem->widget())->isChecked()) {
            QStringList newlist ;
            newlist.append(photos[i]) ;
            for (int j=0; j<photos.count(); j++)
                if (j!=i) newlist.append(photos[j]) ;
            photos = newlist ;
            photos2form() ;
            return ;
        }
    }
    QMessageBox::about(this,"Ошибка","Не выделено фото") ;
}

void DialogPhotos::clickphoto()
{
    DialogPhotoView d(this) ;
    d.goPhotos(photos,
               ((QLabel*)QObject::sender())->property("index").toInt(),photodir) ;
    d.exec() ;
}
