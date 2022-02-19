#include "dialogrefedit.h"
#include "ui_dialogrefedit.h"
#include <QInputDialog>
#include "helper.h"

DialogRefEdit::DialogRefEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRefEdit)
{
    ui->setupUi(this);
}

DialogRefEdit::~DialogRefEdit()
{
    delete model ;
    delete ui;
}

void DialogRefEdit::setRefer(const QString &tablename, const QString &fieldname)
{
    this->tablename = tablename ;
    this->fieldname = fieldname ;
    model = new QSqlQueryModel(this) ;
    model->setQuery("SELECT * FROM "+tablename) ;
    model->setHeaderData(0,Qt::Horizontal,"id",Qt::DisplayRole) ;
    model->setHeaderData(1,Qt::Horizontal,"Значение",Qt::DisplayRole) ;
    ui->tableView->setModel(model) ;
    ui->tableView->verticalHeader()->hide() ;
}

void DialogRefEdit::on_butAdd_clicked()
{
    QString str = QInputDialog::getText(this,"Ввод значение",
                                        "Введите новое значение справочника") ;
    if (str.trimmed().length()==0) return ;

    QSqlQuery query ;
    query.prepare("INSERT INTO "+tablename+" ("+fieldname+") VALUES (:refvalue)") ;
    query.bindValue(":refvalue",str.trimmed()) ;
    query.exec() ;

    model->setQuery("SELECT * FROM "+tablename) ;
}

void DialogRefEdit::on_butEdit_clicked()
{
    QModelIndex index = ui->tableView->currentIndex() ;
    if (!index.isValid()) return ;

    int id = model->data(index.siblingAtColumn(0),Qt::DisplayRole).toInt() ;
    QString oldvalue = model->data(index.siblingAtColumn(1),Qt::DisplayRole).toString() ;

    QString str = QInputDialog::getText(this,"Ввод значение",
                                        "Измените значение справочника",
                                        QLineEdit::Normal,
                                        oldvalue) ;
    if (str.trimmed().length()==0) return ;

    QSqlQuery query ;
    query.prepare("UPDATE "+tablename+" SET "+fieldname+"=:refvalue WHERE id=:id") ;
    query.bindValue(":refvalue",str.trimmed()) ;
    query.bindValue(":id",id) ;
    query.exec() ;

    model->setQuery("SELECT * FROM "+tablename) ;
}

void DialogRefEdit::on_butDel_clicked()
{
    QModelIndex index = ui->tableView->currentIndex() ;
    if (!index.isValid()) return ;

    int id = model->data(index.siblingAtColumn(0),Qt::DisplayRole).toInt() ;
    QString oldvalue = model->data(index.siblingAtColumn(1),Qt::DisplayRole).toString() ;

    if (!Helper::confirm(this,"Удалить запись "+oldvalue+"?","Подтверждение")) return ;

    QSqlQuery query ;
    query.prepare("DELETE FROM "+tablename+" WHERE id=:id") ;
    query.bindValue(":id",id) ;
    query.exec() ;

    model->setQuery("SELECT * FROM "+tablename) ;
}
