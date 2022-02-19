#ifndef SORTORGS_H
#define SORTORGS_H
#include <QSortFilterProxyModel>
#include <QObject>
#include "mainengine.h"
#include <QScriptEngine>
#include <QJsonObject>

class QJsonSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
private:
    QScriptEngine * engine ;
    QJsonObject view ;
    QJsonObject filter ;
public:
    QJsonSortProxyModel(const QJsonObject &view, QScriptEngine *engine);
    bool lessThan(const QModelIndex &left,
                  const QModelIndex &right) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                                    int role) const ;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const ;

    void setFilterObject(const QJsonObject & filter) ;
};

#endif // SORTORGS_H
