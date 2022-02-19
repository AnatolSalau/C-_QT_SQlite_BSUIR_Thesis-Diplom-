#ifndef DIALOGVIEWDIAG_H
#define DIALOGVIEWDIAG_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class DialogViewDiag;
}

class DialogViewDiag : public QDialog
{
    Q_OBJECT

public:
    explicit DialogViewDiag(QWidget *parent = nullptr);
    ~DialogViewDiag();

    void setDiag(const QJsonArray & diag_data, const QJsonObject & diag_info) ;

private:
    Ui::DialogViewDiag *ui;
};

#endif // DIALOGVIEWDIAG_H
