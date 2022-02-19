#ifndef DIALOGPHOTOVIEW_H
#define DIALOGPHOTOVIEW_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class DialogPhotoView;
}

class DialogPhotoView : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPhotoView(QWidget *parent = nullptr);
    ~DialogPhotoView();

    void goPhotos(const QStringList & photos, int tekn,
                  const QString & photodir) ;

private:
    Ui::DialogPhotoView *ui;
    QStringList photos ;
    QString photodir ;
    int tekn ;

protected:
    void keyPressEvent(QKeyEvent *event) ;

private slots:
    void showTekPhoto() ;
    void goNext() ;
    void goPrior() ;

};

#endif // DIALOGPHOTOVIEW_H
