#include "dialogviewlist.h"
#include "ui_dialogviewlist.h"
#include <QDesktopServices>
#include <QUuid>
#include <QUrl>
#include <QDir>
#include "helper.h"
#include "qjsontablemodel.h"

DialogViewList::DialogViewList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogViewList)
{
    ui->setupUi(this);

    ui->tableList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents) ;
    ui->tableList->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents) ;
    ui->tableList->setSelectionBehavior(QAbstractItemView::SelectRows) ;
    ui->tableList->setSelectionMode(QAbstractItemView::SingleSelection) ;

    ui->comboCoding->addItem("UTF-8") ;
    ui->comboCoding->addItem("ANSI") ;
    ui->comboCoding->setCurrentIndex(0) ;
}

DialogViewList::~DialogViewList()
{
    delete ui;
}

void DialogViewList::setModel(QSortFilterProxyModel * model)
{
    this->model = model ;
    ui->tableList->setModel(model) ;
    ui->tableList->sortByColumn(0, Qt::AscendingOrder);
}

void DialogViewList::on_ButExport_clicked()
{
    QStringList res ;
    for (int i=0; i<ui->tableList->model()->rowCount(); i++) {
        QString str = QString::number(i+1)+". " ;
        for (int j=0; j<ui->tableList->model()->columnCount(); j++)
            str+=ui->tableList->model()->data(ui->tableList->model()->index(i,j)).toString()+"  " ;
        res.append(str.trimmed()) ;
    }

    QString filename=QDir::tempPath()+'/'+QUuid::createUuid().toString()+".txt" ;
    QString data = res.join("\r\n") ;
    QFile file(filename);
    file.open(QIODevice::WriteOnly) ;
    if (ui->comboCoding->currentIndex()==0)
        file.write(data.toUtf8()) ;
    else
        file.write(data.toLocal8Bit()) ;
    file.close();

    QDesktopServices::openUrl(QUrl::fromLocalFile(filename));
}

void DialogViewList::on_butDel_clicked()
{
    QJsonTableModel * sourcemodel = (QJsonTableModel *)model->sourceModel() ;

    QModelIndex index = model->mapToSource(ui->tableList->currentIndex()) ;
    if (!sourcemodel->isCurrent(index)) return ;

    sourcemodel->deleteFromModel(index) ;
}

void DialogViewList::on_ButExportCSV_clicked()
{
    QStringList res ;
    QString str = "№;" ;
    for (int j=0; j<ui->tableList->model()->columnCount(); j++)
        str+="\""+ui->tableList->model()->headerData(j,Qt::Horizontal).toString()+"\";" ;
    res.append(str.trimmed()) ;

    for (int i=0; i<ui->tableList->model()->rowCount(); i++) {
        QString str = QString::number(i+1)+";" ;
        for (int j=0; j<ui->tableList->model()->columnCount(); j++)
            str+="\""+ui->tableList->model()->data(ui->tableList->model()->index(i,j)).toString().replace("\"","")+"\";" ;
        res.append(str.trimmed()) ;
    }

    QString filename=QDir::tempPath()+'/'+QUuid::createUuid().toString()+".csv" ;
    QString data = res.join("\r\n") ;
    QFile file(filename);
    file.open(QIODevice::WriteOnly) ;
    if (ui->comboCoding->currentIndex()==0)
        file.write(data.toUtf8()) ;
    else
        file.write(data.toLocal8Bit()) ;
    file.close();

    QDesktopServices::openUrl(QUrl::fromLocalFile(filename));
}
