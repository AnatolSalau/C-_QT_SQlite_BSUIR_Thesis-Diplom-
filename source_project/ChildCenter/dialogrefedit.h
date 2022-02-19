#ifndef DIALOGREFEDIT_H
#define DIALOGREFEDIT_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>

namespace Ui {
class DialogRefEdit;
}

class DialogRefEdit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRefEdit(QWidget *parent = nullptr);
    ~DialogRefEdit();

    void setRefer(const QString & tablename, const QString & fieldname) ;

private slots:
    void on_butAdd_clicked();

    void on_butEdit_clicked();

    void on_butDel_clicked();

private:
    QString tablename ;
    QString fieldname ;
    QSqlQueryModel * model ;
    Ui::DialogRefEdit *ui;
};

#endif // DIALOGREFEDIT_H
