#include "dialogsellist.h"
#include "ui_dialogsellist.h"
#include <QPushButton>

DialogSelList::DialogSelList(const QJsonArray & list, const QJsonObject & view,
                             QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSelList)
{
    ui->setupUi(this);

    this->view = view ;
    this->list = list ;

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("ОК");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Отмена");
    setWindowTitle(view["title"].toString()) ;
    bool multiselect = false ;
    if (view.contains("multiselect"))
            multiselect=view["multiselect"].toBool() ;

    foreach (auto obj, list) {
        QString caption = obj.toObject()[view["itemcaption"].toString()].toString() ;
        auto item = new QListWidgetItem(caption,ui->listWidget) ;
        item->setData(QListWidgetItem::UserType,obj.toObject()) ;
        if (multiselect) {
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable) ;
            item->setCheckState(Qt::Unchecked) ;
        }
        ui->listWidget->addItem(item) ;
    }
    if (multiselect) ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection) ;
    if (ui->listWidget->count()>0) ui->listWidget->setCurrentRow(0) ;

    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(reject())) ;
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accept())) ;
}

DialogSelList::~DialogSelList()
{
    delete ui;
}

QJsonObject DialogSelList::getSelected() const
{
    if (ui->listWidget->currentItem()==NULL) return QJsonObject() ;

    return ui->listWidget->currentItem()->data(QListWidgetItem::UserType).toJsonObject() ;
}

QJsonArray DialogSelList::getChecked(const QString & keyfield) const
{
    QJsonArray res ;
    for (int i=0; i<ui->listWidget->count(); i++)
        if (ui->listWidget->item(i)->checkState()==Qt::Checked) {
            QJsonObject row = ui->listWidget->item(i)->data(
                        QListWidgetItem::UserType).toJsonObject() ;
            if (keyfield!="") res.append(row[keyfield]) ; else res.append(row) ;
        }
    return res ;
}

void DialogSelList::setChecked(const QJsonArray &checked, const QString &keyfield)
{
    for (int i=0; i<ui->listWidget->count(); i++)
        ui->listWidget->item(i)->setCheckState(
            checked.contains(ui->listWidget->item(i)->data(
                       QListWidgetItem::UserType).toJsonObject()[keyfield])?
                        Qt::Checked:Qt::Unchecked) ;
}
