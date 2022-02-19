#ifndef FORMBUILDER_H
#define FORMBUILDER_H

#include <QWidget>
#include <QDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QObject>

class FormBuilder
{
private:
    QDialog * dlg ;
    QVBoxLayout * vlayout ;
public:
    FormBuilder(QWidget * parent, const QString & title);
    ~FormBuilder() ;

    QFormLayout * addFormLayout() ;
    bool exec() ;
};

#endif // FORMBUILDER_H
