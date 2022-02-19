#include "dialogloader.h"
#include "ui_dialogloader.h"

DialogLoader::DialogLoader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLoader)
{
    ui->setupUi(this);
    sec = 0 ;
    connect(&timer,SIGNAL(timeout()),this,SLOT(update1sec())) ;
    timer.start(1000) ;
}

DialogLoader::~DialogLoader()
{
    delete ui;
}

void DialogLoader::update1sec()
{
    QString s ;
    sec++ ;
    if (sec==4) sec=0 ;
    this->setWindowTitle("Загрузка"+s.fill('.',sec)) ;
}

void DialogLoader::updateNext(int tek, int all)
{
    ui->labProgress->setText(QString("Загружено %1 из %2 (%3 %)").arg(tek).arg(all).arg(100*tek/all)) ;
}

void DialogLoader::updateText(const QString &text)
{
    ui->labProgress->setText(text) ;
}
