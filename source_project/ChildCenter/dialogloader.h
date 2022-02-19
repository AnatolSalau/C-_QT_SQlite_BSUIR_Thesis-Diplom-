#ifndef DIALOGLOADER_H
#define DIALOGLOADER_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class DialogLoader;
}

class DialogLoader : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLoader(QWidget *parent = nullptr);
    ~DialogLoader();

private:
    Ui::DialogLoader *ui;
    QTimer timer ;
    int sec ;

private slots:
    void update1sec() ;

public slots:
    void updateNext(int tek, int all) ;
    void updateText(const QString & text) ;
};

#endif // DIALOGLOADER_H
