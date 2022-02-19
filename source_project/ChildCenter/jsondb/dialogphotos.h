#ifndef DIALOGPHOTOS_H
#define DIALOGPHOTOS_H

#include <QDialog>
#include "all_qjson.h"
#include <QFormLayout>
#include <QStringList>
#include <QScrollArea>
#include <QLabel>

namespace Ui {
class DialogPhotos;
}

class DialogPhotos : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPhotos(const QJsonObject & obj, const QString &photodir, QWidget *parent = nullptr);
    ~DialogPhotos();

    QJsonObject getObject() ;
private slots:
    void on_ButAddPhoto_clicked();

    void on_ButDelPhoto_clicked();

    void on_ButSetPhotDefault_clicked();

    void clickphoto() ;

private:
    Ui::DialogPhotos *ui;
    QJsonObject saved ;
    QStringList photos ;
    QFormLayout * form ;
    QScrollArea * scroll ;
    QWidget* widget ;
    QString photodir ;
    void photos2form() ;
};

#endif // DIALOGPHOTOS_H
