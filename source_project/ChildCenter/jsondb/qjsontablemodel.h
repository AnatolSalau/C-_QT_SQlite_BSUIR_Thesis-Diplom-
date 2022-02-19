#ifndef QJSONTABLEMODEL_H
#define QJSONTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QJsonArray>
#include <QJsonObject>
#include <QtScript/QScriptEngine>
#include "mainengine.h"

/*
  Обновление 1.0.1.2 - добавили получение копии массива из модели
*/

class QJsonTableModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    QJsonArray array ;
    QJsonObject view ;
    QStringList autocolumns ;
    bool useautocolumns ;
    QJsonArray columns ;
    QScriptEngine * engine ;
    void rebuildAutoColumns() ;
public:
    QJsonTableModel(const QJsonArray &source, const QJsonObject &view, QScriptEngine * engine);
    int rowCount( const QModelIndex& parent ) const ;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;

    QJsonObject getCurrent(const QModelIndex &index) const ;
    bool isCurrent(const QModelIndex &index) const ;
    void replaceSource(const QJsonArray & source) ;
    void updateModel(const QModelIndex &index, const QJsonObject & newobj) ;
    void insertToModel(const QJsonObject & newobj) ;
    void deleteFromModel(const QModelIndex &index) ;
    // 1.0.1.2
    QJsonArray getSource() const ;
    QModelIndex getIndexByField(const QString & field, const QJsonValue & value) const ;

signals:
    void dataUpdated(const QJsonArray & data) ;
    void sendNoSelected(const QString & whatis) const ;
};

#endif // QJSONTABLEMODEL_H
