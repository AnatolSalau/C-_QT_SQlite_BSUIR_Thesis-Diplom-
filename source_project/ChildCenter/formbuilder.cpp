#include "formbuilder.h"

FormBuilder::FormBuilder(QWidget * parent, const QString & title)
{
    dlg = new QDialog(parent) ;
    dlg->setWindowTitle(title) ;
    vlayout = new QVBoxLayout() ;
    QDialogButtonBox * box = new QDialogButtonBox() ;
    box->addButton("OK",QDialogButtonBox::ButtonRole::AcceptRole) ;
    box->addButton("Отмена",QDialogButtonBox::ButtonRole::RejectRole) ;
    QObject::connect(box,SIGNAL(rejected()),dlg,SLOT(reject())) ;
    QObject::connect(box,SIGNAL(accepted()),dlg,SLOT(accept())) ;
    box->setMinimumHeight(40) ;

    vlayout->addWidget(box,0,Qt::AlignBottom) ;
    dlg->setLayout(vlayout) ;
}

FormBuilder::~FormBuilder()
{
    delete dlg ;
}

QFormLayout *FormBuilder::addFormLayout()
{
    QFormLayout * layout = new QFormLayout() ;
    vlayout->insertLayout(0,layout) ;
    return layout ;
}

bool FormBuilder::exec()
{
    return dlg->exec()==QDialog::Accepted ;
}
