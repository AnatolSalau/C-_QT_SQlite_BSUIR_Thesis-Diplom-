#include "qjsonsortproxymodel.h"
#include "qjsontablemodel.h"
#include <QJsonDocument>
#include <QDebug>

QJsonSortProxyModel::QJsonSortProxyModel(const QJsonObject &view, QScriptEngine * engine)
{
    this->view = view ;
    this->engine=engine ;
}

bool QJsonSortProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{    
    if (view["sortfunc"].isUndefined())
        return false ;
    else {
        QJsonObject leftObj = ((QJsonTableModel *)sourceModel())->getCurrent(left) ;
        QJsonObject rightObj = ((QJsonTableModel *)sourceModel())->getCurrent(right) ;

        QString sort = view["sortfunc"].toString() ;
        sort = sort.replace("<left>",QJsonDocument(leftObj).toJson()) ;
        sort = sort.replace("<right>",QJsonDocument(rightObj).toJson()) ;
        QScriptValue res = engine->evaluate(sort).toBool() ;
        if (res.isError())
            qDebug()<<res.toString() ;
        return res.toBool() ;
    }

    /*

    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    if ((left.column()==1)&&(right.column()==1)) {
        QDate leftDate = QDate::fromString(leftData.toString(),"dd.MM.yyyy") ;
        if (!leftDate.isValid()) leftDate = QDate::currentDate() ;
        QDate rightDate = QDate::fromString(rightData.toString(),"dd.MM.yyyy") ;
        if (!rightDate.isValid()) rightDate = QDate::currentDate() ;
        return leftDate<rightDate ;
    }
    else {
        return leftData<rightData ;
    }
    */
}

QVariant QJsonSortProxyModel::headerData(int section, Qt::Orientation orientation,
                                int role) const {
    return sourceModel()->headerData(section, orientation,
                                     role);
}

bool QJsonSortProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (view["filterfunc"].isUndefined())
        return true ;
    else {
        QJsonObject obj = ((QJsonTableModel *)sourceModel())->getCurrent(sourceModel()->index(source_row,0,source_parent)) ;

        QString filterfunc = view["filterfunc"].toString() ;
        filterfunc = filterfunc.replace("<obj>",QJsonDocument(obj).toJson()) ;
        filterfunc = filterfunc.replace("<filter>",QJsonDocument(filter).toJson()) ;
        QScriptValue res = engine->evaluate(filterfunc).toBool() ;
        if (res.isError())
            qDebug()<<res.toString() ;
        return res.toBool() ;
    }
}

void QJsonSortProxyModel::setFilterObject(const QJsonObject &filter)
{
    this->filter = filter ;
}
