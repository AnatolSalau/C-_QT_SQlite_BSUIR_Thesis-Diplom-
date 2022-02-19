#include "dialogviewdiag.h"
#include "ui_dialogviewdiag.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

using namespace QtCharts ;

DialogViewDiag::DialogViewDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogViewDiag)
{
    ui->setupUi(this);
}

DialogViewDiag::~DialogViewDiag()
{
    delete ui;
}

void DialogViewDiag::setDiag(const QJsonArray &diag_data, const QJsonObject &diag_info)
{
    QList<QColor> colors ;
    colors.append(QColor::fromRgb(255,196,196)) ;
    colors.append(QColor::fromRgb(255,128,128)) ;
    colors.append(QColor::fromRgb(255,64,64)) ;
    colors.append(QColor::fromRgb(196,255,196)) ;
    colors.append(QColor::fromRgb(128,255,128)) ;
    colors.append(QColor::fromRgb(64,255,64)) ;
    colors.append(QColor::fromRgb(196,196,255)) ;
    colors.append(QColor::fromRgb(128,128,255)) ;
    colors.append(QColor::fromRgb(64,64,255)) ;
    colors.append(QColor::fromRgb(196,255,255)) ;
    colors.append(QColor::fromRgb(128,255,255)) ;
    colors.append(QColor::fromRgb(64,255,255)) ;
    colors.append(QColor::fromRgb(255,196,255)) ;
    colors.append(QColor::fromRgb(255,128,255)) ;
    colors.append(QColor::fromRgb(255,64,255)) ;
    colors.append(QColor::fromRgb(255,255,196)) ;
    colors.append(QColor::fromRgb(255,255,128)) ;
    colors.append(QColor::fromRgb(255,255,64)) ;

    QPieSeries *series = new QPieSeries();
    foreach(auto row, diag_data)
        series->append(row.toObject()["group"].toString(), row.toObject()["value"].toInt());

    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);
    int k = 0 ;
    for(auto slice : series->slices()) {
        slice->setLabel(QString("%1: %2").arg(slice->label()).arg(slice->value()));
        slice->setColor(colors[k]) ;
        k++ ;
        if (k>=colors.count()) k=0 ;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(diag_info["diagname"].toString());

    QChartView *chartView = new QChartView(chart,this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setGeometry(0,0,this->width(),this->height()) ;

    this->setWindowTitle("Диаграмма") ;
}
