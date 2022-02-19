#include "qjsontablemodel.h"
#include "qjsonutils.h"
#include "mainengine.h"
#include <QJsonDocument>
#include <QColor>

void QJsonTableModel::rebuildAutoColumns()
{
    autocolumns.clear() ;
    for (int i=0; i<array.count(); i++) {
        QJsonObject row = array.at(i).toObject() ;
        foreach (QString key, row.keys())
            if (row[key].isBool()||row[key].isString()||row[key].isDouble())
                if (!autocolumns.contains(key)) autocolumns.append(key);
    }
}

QJsonTableModel::QJsonTableModel(const QJsonArray &source, const QJsonObject &view,
                                 QScriptEngine * engine)
{
    this->array = source ;
    this->view = view ;
    columns = view["columns"].toArray() ;
    useautocolumns = columns.count()==0 ;
    rebuildAutoColumns() ;

    this->engine = engine ;
}

int QJsonTableModel::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED(parent) ;
    return array.count() ;
}

int QJsonTableModel::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED(parent) ;

    return useautocolumns?autocolumns.count():columns.count() ;
}

QVariant QJsonTableModel::data( const QModelIndex& index, int role ) const {
    if(
        !index.isValid() ||
        array.count() <= index.row())
        return QVariant();

    if (role == Qt::BackgroundRole) {
        if (array.at(index.row()).toObject().contains("inbox_id"))
            return QColor::fromRgb(200,200,255) ;
        else
            return QVariant() ;
    }

    if (( role != Qt::DisplayRole && role != Qt::EditRole ))
        return QVariant();

    QJsonObject rowobj = array.at(index.row()).toObject() ;
    QJsonValue val ;
    if (useautocolumns) {
        val = rowobj.value(autocolumns[index.column()]) ;
        return QJsonUtils::getGlobalUtils()->getJsonValueAsString(val) ;
    }
    else {
        QJsonObject rowparam = columns.at(index.column()).toObject() ;
        if (rowparam["field"].toString()=="[calc]") {
            QString calc = rowparam["func"].toString() ;
            calc = calc.replace("<current>",QJsonDocument(rowobj).toJson()) ;
            return engine->evaluate(calc).toString() ;
        }
        else {
            val = rowobj[rowparam["field"].toString()] ;
            return QJsonUtils::getGlobalUtils()->getJsonValueAsString(val) ;
        }
    }

    return QVariant() ;
}

bool QJsonTableModel::setData( const QModelIndex& index, const QVariant& value, int role ) {
    return false ;
    /*

    if( !index.isValid() || role != Qt::EditRole || list->count() <= index.row() )
        return false;

    bool isok = false;
    int n = value.toInt(&isok) ;
    if (index.column()==PLACECOUNT) {
        if (!isok) return false ;
        if (!tickets->at(index.row())->canSetPlaceCount(n)) return false ;
        tickets->at(index.row())->updatePlaceCount(n) ;
        emit dataChanged(index, index.sibling(index.row(),index.column()+1));
    }

    return true ;
    */
}

QVariant QJsonTableModel::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole )
        return QVariant() ;

    if( orientation == Qt::Vertical )
        return section+1;

    if (useautocolumns)
        return autocolumns[section] ;
    else
        return columns.at(section).toObject().value("caption") ;

}

Qt::ItemFlags QJsonTableModel::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    /*if( index.isValid() ) {
        if( index.column() == PLACECOUNT ) {
            flags |= Qt::ItemIsEditable;
        }
    }
*/
    return flags;
}

bool QJsonTableModel::isCurrent(const QModelIndex &index) const
{
    if (index.isValid() && (array.size() > index.row()))
        return true ;
    else {
        emit sendNoSelected(view.value("viewname").toString());
        return false ;
    }
}

QJsonObject QJsonTableModel::getCurrent(const QModelIndex &index) const {
    QJsonObject obj ;
    if (index.isValid() && (array.size() > index.row()))
        obj = array.at(index.row()).toObject() ;
    return obj ;
}

void QJsonTableModel::replaceSource(const QJsonArray &source)
{
    this->array = source ;
    beginResetModel();    
    rebuildAutoColumns() ;
    endResetModel();
}

void QJsonTableModel::updateModel(const QModelIndex &index, const QJsonObject & newobj) {
    if (index.isValid() && (array.size() > index.row())) {
        array.replace(index.row(),newobj) ;
        emit dataUpdated(array) ;
        emit dataChanged(index.sibling(index.row(),0),
                         index.sibling(index.row(),columnCount(index)-1));
    }
}

void QJsonTableModel::insertToModel(const QJsonObject & newobj) {
    array.append(newobj) ;
    emit dataUpdated(array) ;    
    beginResetModel();
    rebuildAutoColumns() ;
    endResetModel();
}

void QJsonTableModel::deleteFromModel(const QModelIndex &index)
{
    if (index.isValid() && (array.size() > index.row())) {
        array.removeAt(index.row()) ;
        emit dataUpdated(array) ;
        beginResetModel();
        rebuildAutoColumns() ;
        endResetModel();
    }
}

QJsonArray QJsonTableModel::getSource() const
{
    return array ;
}

QModelIndex QJsonTableModel::getIndexByField(const QString &field, const QJsonValue &value) const
{
    for (int i=0; i<array.count(); i++)
        if (array[i].toObject().contains(field))
            if (array[i].toObject()[field]==value)
                return index(i,0) ;
}

