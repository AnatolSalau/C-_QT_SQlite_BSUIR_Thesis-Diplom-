#ifndef DIALOGVIEWLIST_H
#define DIALOGVIEWLIST_H

#include <QDialog>
#include <QSortFilterProxyModel>

namespace Ui {
class DialogViewList;
}

class DialogViewList : public QDialog
{
    Q_OBJECT

public:
    explicit DialogViewList(QWidget *parent = nullptr);
    ~DialogViewList();

    void setModel(QSortFilterProxyModel * model) ;

private slots:
    void on_ButExport_clicked();

    void on_butDel_clicked();

    void on_ButExportCSV_clicked();

private:
    Ui::DialogViewList *ui;
    QSortFilterProxyModel * model ;
};

#endif // DIALOGVIEWLIST_H
