#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "all_qjson.h"
#include "mainengine.h"
#include "qjsonsortproxymodel.h"
#include "qjsontablemodel.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;    

    QJsonArray cities ;
    QJsonArray categories ;
    MainEngine * engine ;
    QJsonTableModel * modelclient ;
    QJsonSortProxyModel * modelclientsorted ;
    QJsonObject view_client ;
    QJsonObject view_children ;
    QJsonObject editor_client ;
    QJsonObject editor_child ;

    QJsonTableModel * modelchildren ;
    QSqlDatabase db;

    int user_id = 0 ;

    void UpdatePanel(const QModelIndex &index) ;

    void insertClient(int id) ;
    int getFirstIntFromSQL(const QString & sql) ;
    void loadCities() ;
    void loadCategories() ;
    bool fillFilterData(QJsonObject & filter, const QJsonArray & filter_array) ;
    QJsonArray buildJoinedSource() ;
    QJsonArray buildDiagData(const QJsonArray & source, const QJsonObject & diag_info, const QJsonObject &filter) ;

public slots:
    void on_row_select(const QItemSelection &selected, const QItemSelection &deselected) ;
    void messageNoSelected(const QString & whatis) ;
    void getParseError(const QString & filename,const QString & error) ;
    void dataChangedClients(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>()) ;

private slots:
    void on_ButList_clicked();
    void on_ButFind_clicked();
    void on_butAddClient_clicked();

    void doAuth() ;

    void reloadClients() ;
    void updateInfo(const QJsonArray & data) ;
    void on_butEditClient_clicked();
    void on_butDelClient_clicked();
    void on_butEditChild_clicked();
    void on_butAddChild_clicked();
    void on_butDelChild_clicked();
    void on_butSetCats_clicked();
    void on_butRefs_clicked();
    void on_butDiag_clicked();
};
#endif // MAINWINDOW_H
