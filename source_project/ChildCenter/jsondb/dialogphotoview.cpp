#include "dialogphotoview.h"
#include "ui_dialogphotoview.h"
#include <QTimer>
#include <QDesktopWidget>

DialogPhotoView::DialogPhotoView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPhotoView)
{    
    ui->setupUi(this);

    connect(ui->labView,SIGNAL(click()),this,SLOT(goNext())) ;
}

DialogPhotoView::~DialogPhotoView()
{
    delete ui;
}

void DialogPhotoView::goPhotos(const QStringList &photos, int tekn, const QString & photodir)
{
    this->photos = photos ;
    this->photodir = photodir ;
    this->tekn=tekn ;

    int sw = QDesktopWidget().availableGeometry().width() ;
    int sh = QDesktopWidget().availableGeometry().height() ;

    int w = 800 ;
    int h = 600 ;
    this->setGeometry((sw-w)/2,(sh-h)/2,w,h) ;

    QTimer::singleShot(1,this,SLOT(showTekPhoto())) ;
}

void DialogPhotoView::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_PageUp) goNext() ;
    if (event->key()==Qt::Key_PageDown) goPrior() ;
    if (event->key()==Qt::Key_Escape) accept() ;
}

void DialogPhotoView::showTekPhoto()
{
    QPixmap p ;
    int w=-1 ;
    int h=-1 ;
    if (p.load(photodir+photos[tekn])) {
        w = p.width() ;
        h = p.height() ;
        if (p.height()>ui->labView->height()) {
            QPixmap resized = p.scaledToHeight(ui->labView->height()) ;
            //this->setWindowTitle(QString::number(ui->labView->height())) ;
            ui->labView->setPixmap(resized) ;
        }
        else
            ui->labView->setPixmap(p) ;
    }

    ui->labInfo->setText(QString("Фото %1 / %2, %3, %4x%5")
                         .arg(tekn+1)
                         .arg(photos.count())
                         .arg(photos[tekn])
                         .arg(w).arg(h)) ;
}

void DialogPhotoView::goNext() {
    tekn++ ;
    if (tekn>=photos.count()) tekn=0 ;
    showTekPhoto() ;
}

void DialogPhotoView::goPrior() {
    tekn-- ;
    if (tekn<0) tekn=photos.count()-1 ;
    showTekPhoto() ;
}
