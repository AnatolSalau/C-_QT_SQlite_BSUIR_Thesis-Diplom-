#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include "helper.h"
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>
#include "qjsonutils.h"
#include "all_qjson.h"
#include "dialogviewlist.h"
#include "dialogsellist.h"
#include "qjsonsearchinobject.h"
#include "Consts.h"
#include "dialogloader.h"
#include "formbuilder.h"
#include <QSqlError>
#include "dialogeditobject.h"
#include "dialogrefedit.h"
#include <QRandomGenerator>
#include "dialogviewdiag.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDir::setCurrent("../data") ;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("childcenter.db");
    if (!db.open())
        QMessageBox::information(this,"Ошибка открытия базы данных: ",db.lastError().text()) ;
    if (!db.tables().contains("USERS")) {
    }

    ui->tableClients->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents) ;
    ui->tableClients->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents) ;
    ui->tableClients->setSelectionBehavior(QAbstractItemView::SelectRows) ;
    ui->tableClients->setSelectionMode(QAbstractItemView::SingleSelection) ;

    ui->tableChildrens->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents) ;
    ui->tableChildrens->setSelectionBehavior(QAbstractItemView::SelectRows) ;
    ui->tableChildrens->setSelectionMode(QAbstractItemView::SingleSelection) ;

    qApp->setStyleSheet(Helper::readAllText("style.css"));

    connect(QJsonUtils::getGlobalUtils(),
            SIGNAL(sendParseError(const QString &, const QString &)),
            this,
            SLOT(getParseError(const QString &, const QString &))) ;

    QJsonArray clients ;//loadClients() ;

    loadCities() ;
    loadCategories() ;

    view_client = QJsonUtils::getGlobalUtils()->loadObjectFromFile("view_client.json") ;
    view_children = QJsonUtils::getGlobalUtils()->loadObjectFromFile("view_children.json") ;

    editor_client = QJsonUtils::getGlobalUtils()->loadObjectFromFile("editor_client.json") ;
    editor_child = QJsonUtils::getGlobalUtils()->loadObjectFromFile("editor_child.json") ;

    engine = new MainEngine(new QScriptEngine()) ;
    engine->getEngine()->evaluate(Helper::readAllText("userfunc.js")) ;
    engine->getEngine()->evaluate("var list_cities = "+QJsonDocument(cities).toJson()+";") ;

    modelclientsorted = new QJsonSortProxyModel(view_client,engine->getEngine()) ;
    modelclientsorted->setSourceModel(modelclient = new QJsonTableModel(clients,view_client,engine->getEngine())) ;
    modelclientsorted->setDynamicSortFilter(true) ;
    ui->tableClients->setModel(modelclientsorted) ;

    modelchildren = new QJsonTableModel(QJsonArray(),view_children,engine->getEngine()) ;
    ui->tableChildrens->setModel(modelchildren) ;

    ui->tableClients->sortByColumn(0, Qt::AscendingOrder);

    connect(ui->tableClients->selectionModel(),SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)),
            this,SLOT(on_row_select(const QItemSelection&,const QItemSelection&))) ;
    connect(modelclient,SIGNAL(sendNoSelected(const QString &)),
            this,SLOT(messageNoSelected(const QString &))) ;
    connect(modelclient,SIGNAL(dataChanged(const QModelIndex &,const QModelIndex &,const QVector<int> &)),
            this,SLOT(dataChangedClients(const QModelIndex &,const QModelIndex &,const QVector<int> &))) ;
    connect(modelclient,SIGNAL(dataUpdated(const QJsonArray &)),
            this,SLOT(updateInfo(const QJsonArray &))) ;

    connect(modelchildren,SIGNAL(sendNoSelected(const QString &)),
            this,SLOT(messageNoSelected(const QString &))) ;

    QTimer::singleShot(1000,this,SLOT(doAuth())) ;
}

void MainWindow::updateInfo(const QJsonArray & data)
{
    ui->labInfo->setText("Всего записей: "+QString::number(data.count()));
}

void MainWindow::UpdatePanel(const QModelIndex &index)
{
    if (!modelclient->isCurrent(index)) return ;
    QJsonObject obj = modelclient->getCurrent(index) ;

    // Заполнение пар "поле-заголовок" из редактора
    QMap<QString,QString> fieldcaptions ;
    foreach (auto obj, editor_client["inputs"].toArray())
        fieldcaptions.insert(obj.toObject()["field"].toString(),
                obj.toObject()["caption"].toString()) ;
    foreach (auto obj, editor_child["inputs"].toArray())
        fieldcaptions.insert("Childrens_"+obj.toObject()["field"].toString(),
                "Ребенок "+obj.toObject()["caption"].toString()) ;

    QStringList list ;
    list.append("Код в базе:"+QString::number(obj["id"].toInt())) ;
    foreach(auto key, obj.keys()) {
        QString caption = key ;
        if (fieldcaptions.contains(key)) caption = fieldcaptions[key] ;
        if (obj[key].isString())
            if (obj[key].toString().length()>0)
                list.append(caption+": "+obj[key].toString()) ;
        if (obj[key].isDouble())
            list.append(caption+": "+QString::number(obj[key].toInt())) ;
    }
    ui->textInfo->setText(list.join("\n")) ;

    modelchildren->replaceSource(obj["Childrens"].toArray()) ;

}

void MainWindow::reloadClients()
{
    QJsonArray clients ;
    QSqlQuery query("SELECT id, jsondata FROM clients") ;
    QSqlQuery query2 ;
    query.exec() ;
    while (query.next()) {
        QJsonDocument doc = QJsonDocument::fromJson(query.value("jsondata").toByteArray()) ;
        QJsonObject obj = doc.object() ;
        obj["id"]=query.value("id").toInt() ;
        query2.prepare("SELECT id, jsondata FROM childs WHERE client_id=:id") ;
        query2.bindValue(":id",query.value("id").toInt()) ;
        query2.exec() ;
        QJsonArray childs ;
        while (query2.next()) {
            QJsonDocument doc2 = QJsonDocument::fromJson(query2.value("jsondata").toByteArray()) ;
            QJsonObject obj2 = doc2.object() ;
            obj2["id"]=query2.value("id").toInt() ;
            childs.append(obj2) ;
        }
        obj["Childrens"]=childs ;
        clients.append(obj) ;
    }
    modelclient->replaceSource(clients) ;
    updateInfo(clients) ;
}

void MainWindow::doAuth()
{
    /* Отладочный код для входа без пароля
    user_id=1 ;
    reloadClients() ;
    return ;
    */

    FormBuilder builder(this,"Авторизация") ;

    QFormLayout * layout = builder.addFormLayout() ;

    QLineEdit * eduser = new QLineEdit() ;
    QLineEdit * edpass = new QLineEdit() ;
    edpass->setEchoMode(QLineEdit::EchoMode::Password) ;

    layout->addRow(new QLabel("Логин"),eduser) ;
    layout->addRow(new QLabel("Пароль"),edpass) ;
    eduser->setFocus() ;

    if (builder.exec()) {
        QSqlQuery query ;
        query.prepare("SELECT ID,USERNAME FROM USERS WHERE USERLOGIN=:userlogin AND USERPASS=:userpass") ;
        query.bindValue(":userlogin",eduser->text().trimmed()) ;
        query.bindValue(":userpass",edpass->text().trimmed()) ;
        query.exec() ;
        if (query.next()) {
            user_id = query.value("id").toInt() ;
            setWindowTitle("Вход выполнен :: "+query.value("username").toString()) ;
            reloadClients() ;
        }
        else {
            QMessageBox::information(this,"Ошибка авторизации","Неправильный логин или пароль") ;
            QTimer::singleShot(1000,this,SLOT(doAuth())) ;
        }
    }
    else
        this->close() ;
}

void MainWindow::dataChangedClients(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    UpdatePanel(topLeft) ;
}

void MainWindow::on_row_select(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected) ;

    if (selected.indexes().size()==0) return ;

    QModelIndex index = modelclientsorted->mapToSource(selected.indexes()[0]) ;
    UpdatePanel(index) ;
}

void MainWindow::messageNoSelected(const QString &whatis)
{
    QMessageBox::information(this,"Ошибка","Не выбрана запись: "+whatis) ;
}

void MainWindow::getParseError(const QString &filename, const QString &error)
{
    QMessageBox::information(this,"Ошибка","В файле "+filename+" ошибка "+error) ;
}

MainWindow::~MainWindow()
{
    delete modelclientsorted ;
    delete engine ;

    delete ui;
}

void MainWindow::on_ButList_clicked()
{
    QJsonArray files ;
    QDir dir ;
    foreach(auto fi, dir.entryInfoList())
        if (fi.fileName().startsWith("list_")) {            
            QJsonObject cont = QJsonUtils::getGlobalUtils()->loadObjectFromFile(fi.fileName()) ;
            files.append(QJsonUtils::createObjectWith2Field("filename",fi.fileName(),
                                                            "caption",cont["viewname"].toString())) ;
        }    

    DialogSelList dsel(files,QJsonUtils::createObjectWith2Field("title","Выбор шаблона","itemcaption","caption"),this) ;
    if (dsel.exec()!=QDialog::Accepted) return ;

    QJsonObject list_info = QJsonUtils::getGlobalUtils()->loadObjectFromFile(dsel.getSelected()["filename"].toString()) ;

    QJsonObject filter ;
    //qDebug()<<list_info ;
    if (list_info.contains("filter")) {
        FormBuilder builder(this,"Параметры списка") ;

        QFormLayout * layout = builder.addFormLayout() ;
        foreach(auto item, list_info["filter"].toArray()) {
            QJsonObject filterelem = item.toObject() ;
            QLabel * lab = new QLabel(filterelem["caption"].toString()) ;
            QLineEdit * ed = new QLineEdit() ;
            ed->setProperty("filtername",filterelem["name"].toString()) ;
            layout->addRow(lab,ed) ;
        }

        if (builder.exec())
            for (int i=0; i<layout->rowCount(); i++) {
                auto * item = (QLineEdit*)layout->itemAt(i,QFormLayout::ItemRole::FieldRole)->widget() ;
                filter[item->property("filtername").toString()]=item->text().trimmed() ;                
            }
        else
            return ;        
    }

    QJsonArray list_source ;

    if (list_info.contains("source")) {
        if (list_info["source"].toString()=="join") {
            // Строим комбинированный список
            foreach(auto client, modelclient->getSource()) {
                QJsonObject row = client.toObject() ;
                foreach(auto child, client.toObject()["Childrens"].toArray()) {
                    QJsonObject row1 = child.toObject() ;
                    foreach(auto key, row.keys())
                        row1.insert(key,row[key]) ;
                    list_source.append(row1) ;
                }
            }
        }
        else
            list_source = modelclient->getSource() ;
    }
    else
        list_source = modelclient->getSource() ;

    auto modellist = new QJsonTableModel(list_source,list_info,engine->getEngine()) ;

    QJsonSortProxyModel * model = new QJsonSortProxyModel(list_info,engine->getEngine()) ;
    model->setDynamicSortFilter(true) ;
    model->setFilterObject(filter) ;
    model->setSourceModel(modellist) ;

    DialogViewList d(this) ;
    d.setWindowTitle(list_info["viewname"].toString()) ;
    d.setModel(model) ;
    d.exec() ;

    delete model ;
}

void MainWindow::on_ButFind_clicked()
{
    QJsonArray clients = modelclient->getSource() ;

    QString str = QInputDialog::getText(this,"Поиск","Введите строку") ;
    if (str.length()==0) return ;

    // Заполнение пар "поле-заголовок" из редактора
    QMap<QString,QString> fieldcaptions ;
    foreach (auto obj, editor_client["inputs"].toArray())
        fieldcaptions.insert(obj.toObject()["field"].toString(),
                obj.toObject()["caption"].toString()) ;
    foreach (auto obj, editor_child["inputs"].toArray())
        fieldcaptions.insert("Childrens_"+obj.toObject()["field"].toString(),
                "Ребенок "+obj.toObject()["caption"].toString()) ;

    QJsonArray searchres ;

    QJsonSearchInObject search(str) ;
    foreach(auto item, clients) {
        search.findInObject(item.toObject()) ;
        foreach(auto key, search.getWhereFind().keys()) {
            QJsonObject found = item.toObject() ;
            if (fieldcaptions.contains(key))
                found["fieldname"]=fieldcaptions[key] ;
            else
                found["fieldname"]=key ;
            found["fieldvalue"]=search.getWhereFind()[key] ;
            searchres.append(found) ;
        }
    }

    if (searchres.count()==0) {
        QMessageBox::information(this,"Ошибка","По тексту <"+str+"> ничего не найдено") ;
        return ;
    }

    QJsonObject list_info = QJsonUtils::getGlobalUtils()->loadObjectFromFile("view_search.json") ;

    auto modelsearch = new QJsonTableModel(searchres,list_info,engine->getEngine()) ;

    QJsonSortProxyModel * model = new QJsonSortProxyModel(list_info,engine->getEngine()) ;
    model->setDynamicSortFilter(true) ;
    model->setSourceModel(modelsearch) ;

    DialogViewList d(this) ;
    d.setWindowTitle(list_info["viewname"].toString()) ;
    d.setModel(model) ;
    d.exec() ;

    delete model ;
}

int MainWindow::getFirstIntFromSQL(const QString &sql)
{
    QSqlQuery query(sql) ;
    if (!query.exec()) return 0;
    if (!query.next()) return 0 ;
    return query.value(0).toInt() ;
}

void MainWindow::loadCities()
{
    QSqlQuery query ;
    query.prepare("SELECT id,cityname FROM cities") ;
    query.exec() ;
    cities = QJsonArray() ;
    while (query.next())
        cities.append(QJsonUtils::createObjectWith2Field(
                          "id",query.value(0).toInt(),
                          "cityname",query.value(1).toString())) ;
}

void MainWindow::loadCategories()
{
    QSqlQuery query ;
    query.prepare("SELECT id,catname FROM categories") ;
    query.exec() ;
    categories = QJsonArray() ;
    while (query.next())
        categories.append(QJsonUtils::createObjectWith2Field(
                          "id",query.value(0).toInt(),
                              "catname",query.value(1).toString())) ;
}

bool MainWindow::fillFilterData(QJsonObject &filter, const QJsonArray &filter_array)
{
    FormBuilder builder(this,"Параметры списка") ;

    QFormLayout * layout = builder.addFormLayout() ;
    foreach(auto item, filter_array) {
        QJsonObject filterelem = item.toObject() ;
        QLabel * lab = new QLabel(filterelem["caption"].toString()) ;
        QLineEdit * ed = new QLineEdit() ;
        ed->setProperty("filtername",filterelem["name"].toString()) ;
        layout->addRow(lab,ed) ;
    }

    if (builder.exec()) {
        for (int i=0; i<layout->rowCount(); i++) {
            auto * item = (QLineEdit*)layout->itemAt(i,QFormLayout::ItemRole::FieldRole)->widget() ;
            filter[item->property("filtername").toString()]=item->text().trimmed() ;
        }
        return true ;
    }
    else
        return false ;
}

QJsonArray MainWindow::buildJoinedSource()
{
    QJsonArray list_source ;
    // Строим комбинированный список
    foreach(auto client, modelclient->getSource()) {
        QJsonObject row = client.toObject() ;
        foreach(auto child, client.toObject()["Childrens"].toArray()) {
            QJsonObject row1 = child.toObject() ;
            foreach(auto key, row.keys())
                row1.insert(key,row[key]) ;
            list_source.append(row1) ;
        }
    }
    return list_source ;
}

QJsonArray MainWindow::buildDiagData(const QJsonArray &source, const QJsonObject &diag_info, const QJsonObject &filter)
{
    QMap<QString,QList<QVariant>> map ;

    foreach(auto rowobj, source) {

        if (diag_info.contains("filter")) {
            QString filterfunc = diag_info["filterfunc"].toString() ;
            filterfunc = filterfunc.replace("<obj>",QJsonDocument(rowobj.toObject()).toJson()) ;
            filterfunc = filterfunc.replace("<filter>",QJsonDocument(filter).toJson()) ;
            QScriptValue res = engine->getEngine()->evaluate(filterfunc).toBool() ;
            if (res.isError()) continue ;
            if (!res.toBool()) continue ;
        }

        QString group = "" ;
        QJsonObject groupcolumn = diag_info["groupcolumn"].toObject() ;
        if (groupcolumn["field"].toString()=="[calc]") {
            QString calc = groupcolumn["func"].toString() ;
            calc = calc.replace("<current>",QJsonDocument(rowobj.toObject()).toJson()) ;
            group = engine->getEngine()->evaluate(calc).toString() ;
        }
        else {
            auto val = rowobj.toObject()[groupcolumn["field"].toString()] ;
            group = QJsonUtils::getGlobalUtils()->getJsonValueAsString(val) ;
        }

        QVariant value ;
        QJsonObject calccolumn = diag_info["calccolumn"].toObject() ;
        if (calccolumn["field"].toString()=="[calc]") {
            QString calc = calccolumn["func"].toString() ;
            calc = calc.replace("<current>",QJsonDocument(rowobj.toObject()).toJson()) ;
            value = engine->getEngine()->evaluate(calc).toVariant() ;
        }
        else {
            value = rowobj.toObject()[groupcolumn["field"].toString()].toVariant() ;
        }

        if (!map.contains(group)) map.insert(group,QList<QVariant>()) ;
        map[group].append(value) ;
    }

    QJsonArray res ;
    foreach(auto group, map.keys()) {
        if (diag_info["groupfunc"].toString()=="count")
            res.append(QJsonUtils::createObjectWith2Field("group",group,"value",map[group].count())) ;
        else
            res.append(QJsonUtils::createObjectWith2Field("group",group,"value",0)) ;
    }

    return res ;
}

void MainWindow::on_butAddClient_clicked()
{
    QJsonObject new_client ;
    new_client["Childrens"]=QJsonArray() ;
    new_client["Categories"]=QJsonArray() ;
    DialogEditObject d(new_client,editor_client,engine->getEngine(),this) ;
    if (d.exec()==QDialog::Accepted) {
        QJsonObject obj = d.getObject() ;
        QSqlQuery query ;
        query.prepare("INSERT INTO CLIENTS (JSONDATA) VALUES (:jsondata)") ;
        query.bindValue(":jsondata",QJsonDocument(obj).toJson()) ;
        query.exec() ;
        obj["id"]=getFirstIntFromSQL("SELECT id FROM CLIENTS WHERE rowid=last_insert_rowid()") ;
        modelclient->insertToModel(obj);
    }
}

void MainWindow::on_butEditClient_clicked()
{
    QModelIndex index = modelclientsorted->mapToSource(ui->tableClients->currentIndex()) ;
    // Здесь не нужно сообщение, мы его кидаем в сигнале модели
    if (!modelclient->isCurrent(index)) return ;

    DialogEditObject d(modelclient->getCurrent(index),editor_client,engine->getEngine(),this) ;
    if (d.exec()==QDialog::Accepted) {
        QJsonObject obj = d.getObject() ;
        modelclient->updateModel(index,obj);
        int id = obj["id"].toInt() ;
        obj.remove("id") ;
        obj.remove("Childrens") ;
        QSqlQuery query ;
        query.prepare("UPDATE CLIENTS SET JSONDATA=:jsondata WHERE id=:id") ;
        query.bindValue(":id",id) ;
        query.bindValue(":jsondata",QJsonDocument(obj).toJson()) ;
        query.exec() ;
    }
}

void MainWindow::on_butDelClient_clicked()
{
    QModelIndex index = modelclientsorted->mapToSource(ui->tableClients->currentIndex()) ;
    // Здесь не нужно сообщение, мы его кидаем в сигнале модели
    if (!modelclient->isCurrent(index)) return ;

    QJsonObject obj = modelclient->getCurrent(index) ;
    if (Helper::confirm(this,"Удалить запись "+obj["FamilyM"].toString()+"?",
                        "Подтверждение")) {
        modelclient->deleteFromModel(index) ;
        QSqlQuery query ;
        query.prepare("DELETE FROM CLIENTS WHERE id=:id") ;
        query.bindValue(":id",obj["id"].toInt()) ;
        query.exec() ;
    }
}

void MainWindow::on_butEditChild_clicked()
{
    QModelIndex index = ui->tableChildrens->currentIndex() ;
    // Здесь не нужно сообщение, мы его кидаем в сигнале модели
    if (!modelchildren->isCurrent(index)) return ;

    DialogEditObject d(modelchildren->getCurrent(index),editor_child,engine->getEngine(),this) ;
    if (d.exec()==QDialog::Accepted) {
        QJsonObject obj = d.getObject() ;

        QModelIndex clientindex = modelclientsorted->mapToSource(ui->tableClients->currentIndex()) ;
        QJsonObject clientobj = modelclient->getCurrent(clientindex) ;
        QJsonArray childs = clientobj["Childrens"].toArray() ;
        childs.replace(index.row(),obj) ;
        clientobj["Childrens"]=childs ;

        modelclient->updateModel(clientindex,clientobj) ;

        int id = obj["id"].toInt() ;
        obj.remove("id") ;
        QSqlQuery query ;
        query.prepare("UPDATE CHILDS SET JSONDATA=:jsondata WHERE id=:id") ;
        query.bindValue(":id",id) ;
        query.bindValue(":jsondata",QJsonDocument(obj).toJson()) ;
        query.exec() ;
    }
}

void MainWindow::on_butAddChild_clicked()
{
    QModelIndex clientindex = modelclientsorted->mapToSource(ui->tableClients->currentIndex()) ;
    // Здесь не нужно сообщение, мы его кидаем в сигнале модели
    if (!modelclient->isCurrent(clientindex)) return ;

    QJsonObject new_child ;
    DialogEditObject d(new_child,editor_child,engine->getEngine(),this) ;
    if (d.exec()==QDialog::Accepted) {
        QJsonObject obj = d.getObject() ;

        QJsonObject clientobj = modelclient->getCurrent(clientindex) ;

        QSqlQuery query ;
        query.prepare("INSERT INTO CHILDS (CLIENT_ID,JSONDATA) VALUES (:client_id,:jsondata)") ;
        query.bindValue(":jsondata",QJsonDocument(obj).toJson()) ;
        query.bindValue(":client_id",clientobj["id"].toInt()) ;
        query.exec() ;
        obj["id"]=getFirstIntFromSQL("SELECT id FROM CHILDS WHERE rowid=last_insert_rowid()") ;

        QJsonArray childs = clientobj["Childrens"].toArray() ;
        childs.append(obj) ;
        clientobj["Childrens"]=childs ;

        modelclient->updateModel(clientindex,clientobj) ;
    }

}

void MainWindow::on_butDelChild_clicked()
{
    QModelIndex index = modelclientsorted->mapToSource(ui->tableClients->currentIndex()) ;
    // Здесь не нужно сообщение, мы его кидаем в сигнале модели
    if (!modelclient->isCurrent(index)) return ;

    QJsonObject obj = modelclient->getCurrent(index) ;
    if (Helper::confirm(this,"Удалить запись "+obj["Family"].toString()+"?",
                        "Подтверждение")) {

        QModelIndex clientindex = modelclientsorted->mapToSource(ui->tableClients->currentIndex()) ;
        QJsonObject clientobj = modelclient->getCurrent(clientindex) ;
        QJsonArray childs = clientobj["Childrens"].toArray() ;
        childs.removeAt(index.row()) ;
        clientobj["Childrens"]=childs ;
        modelclient->updateModel(clientindex,clientobj) ;

        QSqlQuery query ;
        query.prepare("DELETE FROM CHILDS WHERE id=:id") ;
        query.bindValue(":id",obj["id"].toInt()) ;
        query.exec() ;
    }
}

void MainWindow::on_butSetCats_clicked()
{
    QModelIndex index = modelclientsorted->mapToSource(ui->tableClients->currentIndex()) ;
    // Здесь не нужно сообщение, мы его кидаем в сигнале модели
    if (!modelclient->isCurrent(index)) return ;

    QJsonObject view = QJsonUtils::createObjectWith2Field(
                "title","Выбор категорий","itemcaption","catname") ;
    view["multiselect"]=true ;
    DialogSelList dsel(categories,view,this) ;
    QJsonObject obj = modelclient->getCurrent(index) ;
    dsel.setChecked(obj["Categories"].toArray(),"catname") ;
    if (dsel.exec()==QDialog::Accepted) {
        obj["Categories"]=dsel.getChecked("catname") ;
        modelclient->updateModel(index,obj);
        int id = obj["id"].toInt() ;
        obj.remove("id") ;
        obj.remove("Childrens") ;
        QSqlQuery query ;
        query.prepare("UPDATE CLIENTS SET JSONDATA=:jsondata WHERE id=:id") ;
        query.bindValue(":id",id) ;
        query.bindValue(":jsondata",QJsonDocument(obj).toJson()) ;
        query.exec() ;
    }
}

void MainWindow::on_butRefs_clicked()
{
    QJsonArray refs ;
    refs.append(QJsonUtils::createObjectWith1Field("caption","Города")) ;
    refs.append(QJsonUtils::createObjectWith1Field("caption","Категории")) ;
    DialogSelList dsel(refs,QJsonUtils::createObjectWith2Field("title","Выбор справочника","itemcaption","caption"),this) ;
    if (dsel.exec()!=QDialog::Accepted) return ;

    if (dsel.getSelected()["caption"].toString()=="Города") {
        DialogRefEdit dlg(this) ;
        dlg.setWindowTitle("Справочник городов") ;
        dlg.setRefer("cities","cityname") ;
        dlg.exec() ;
        loadCities() ;
        engine->getEngine()->evaluate("var list_cities = "+QJsonDocument(cities).toJson()+";") ;
    }
    if (dsel.getSelected()["caption"].toString()=="Категории") {
        DialogRefEdit dlg(this) ;
        dlg.setWindowTitle("Справочник категорий") ;
        dlg.setRefer("categories","catname") ;
        dlg.exec() ;
        loadCategories() ;
    }
}

void MainWindow::on_butDiag_clicked()
{
    QJsonArray files ;
    QDir dir ;
    foreach(auto fi, dir.entryInfoList())
        if (fi.fileName().startsWith("diag_")) {
            QJsonObject cont = QJsonUtils::getGlobalUtils()->loadObjectFromFile(fi.fileName()) ;
            files.append(QJsonUtils::createObjectWith2Field("filename",fi.fileName(),
                                                            "caption",cont["diagname"].toString())) ;
        }

    DialogSelList dsel(files,QJsonUtils::createObjectWith2Field("title","Выбор шаблона","itemcaption","caption"),this) ;
    if (dsel.exec()!=QDialog::Accepted) return ;

    QJsonObject diag_info = QJsonUtils::getGlobalUtils()->loadObjectFromFile(dsel.getSelected()["filename"].toString()) ;

    QJsonObject filter ;
    //qDebug()<<list_info ;
    if (diag_info.contains("filter"))
        if (!fillFilterData(filter,diag_info["filter"].toArray())) return ;

    QJsonArray diag_source ;

    if (QJsonUtils::getValue(diag_info,"source","").toString()=="join")
        diag_source = buildJoinedSource() ;
    else
        diag_source = modelclient->getSource() ;

    auto diag_data = buildDiagData(diag_source,diag_info,filter) ;

    DialogViewDiag d(this) ;
    d.setWindowTitle(diag_info["viewname"].toString()) ;
    d.setDiag(diag_data,diag_info) ;
    d.exec() ;
}
