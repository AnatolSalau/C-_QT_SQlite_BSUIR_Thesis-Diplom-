#ifndef DIALOGSELLIST_H
#define DIALOGSELLIST_H

#include <QDialog>
#include <QJsonArray>
#include <QJsonObject>

/*
  Добавили возможность указать multiselect
 */

namespace Ui {
class DialogSelList;
}

class DialogSelList : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSelList(const QJsonArray & list, const QJsonObject & view, QWidget *parent = nullptr);
    ~DialogSelList();

    QJsonObject getSelected() const ;
    QJsonArray getChecked(const QString &keyfield="") const ;
    void setChecked(const QJsonArray & checked, const QString & keyfield) ;
private:
    Ui::DialogSelList *ui;
    QJsonArray list ;
    QJsonObject view ;
};

#endif // DIALOGSELLIST_H
