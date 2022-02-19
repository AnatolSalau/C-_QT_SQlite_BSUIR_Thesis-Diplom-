#ifndef DIALOGEDITOBJECT_H
#define DIALOGEDITOBJECT_H

#include <QDialog>
#include <QJsonObject>
#include <QtScript/QScriptEngine>

namespace Ui {
class DialogEditObject;
}

class DialogEditObject : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditObject(const QJsonObject & obj, const QJsonObject & settings,
                              QScriptEngine * engine, QWidget *parent = nullptr);
    ~DialogEditObject();

    QJsonObject getObject() const ;
private:
    Ui::DialogEditObject *ui;
    QJsonObject saved ;
    QJsonObject settings ;
    QScriptEngine * engine ;
    void addRow(const QJsonObject & obj, const QString & key, const QString & caption,
                const QJsonObject & optrow) ;

};

#endif // DIALOGEDITOBJECT_H
