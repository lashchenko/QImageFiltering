#include "filterwidget.h"
#include "dip.h"

FilterWidget::FilterWidget(QWidget *parent) :
    QWidget(parent)
{
    map.insert(Filter::Averaging, new QLabel());
    map.insert(Filter::GeometricMean, new QLabel());
    map.insert(Filter::HarmonicMean, new QLabel());
    map.insert(Filter::CounterHarmonic, new QLabel());
    map.insert(Filter::Median, new QLabel());
    map.insert(Filter::Minimum, new QLabel());
    map.insert(Filter::Maximum, new QLabel());
    map.insert(Filter::MediumPoint, new QLabel());
    map.insert(Filter::TruncatedMean, new QLabel());

    tabWidget = new QTabWidget();
    tabWidget->addTab(map.value(Filter::Averaging), trUtf8("Среднеарифметический"));
    tabWidget->addTab(map.value(Filter::GeometricMean), trUtf8("Среднегеометрический"));
    tabWidget->addTab(map.value(Filter::HarmonicMean), trUtf8("Среднегармонический"));
    tabWidget->addTab(map.value(Filter::CounterHarmonic), trUtf8("Контргармонический"));
    tabWidget->addTab(map.value(Filter::Median), trUtf8("Медианный"));
    tabWidget->addTab(map.value(Filter::Minimum), trUtf8("Минимум"));
    tabWidget->addTab(map.value(Filter::Maximum), trUtf8("Максимум"));
    tabWidget->addTab(map.value(Filter::MediumPoint), trUtf8("Серединной точки"));
    tabWidget->addTab(map.value(Filter::TruncatedMean), trUtf8("Усеченного среднего"));
    tabWidget->setCurrentIndex(tabWidget->count()-1);

//    toolBox = new QToolBox();
//    toolBox->addItem(map.value(Filter::Averaging), trUtf8("Среднеарифметический"));
//    toolBox->addItem(map.value(Filter::GeometricMean), trUtf8("Среднегеометрический"));
//    toolBox->addItem(map.value(Filter::HarmonicMean), trUtf8("Среднегармонический"));
//    toolBox->addItem(map.value(Filter::CounterHarmonic), trUtf8("Контргармонический"));
//    toolBox->addItem(map.value(Filter::Median), trUtf8("Медианный"));
//    toolBox->addItem(map.value(Filter::Minimum), trUtf8("Минимум"));
//    toolBox->addItem(map.value(Filter::Maximum), trUtf8("Максимум"));
//    toolBox->addItem(map.value(Filter::MediumPoint), trUtf8("Серединной точки"));
//    toolBox->addItem(map.value(Filter::TruncatedMean), trUtf8("Усеченного среднего"));
//    toolBox->setCurrentIndex(toolBox->count()-1);

    setMinimumWidth(1100);//tabWidget->width());
//    setMinimumWidth(toolBox->width());

    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(updateText(int)));
//    connect(toolBox, SIGNAL(currentChanged(int)), this, SLOT(updateText(int)));

    topLabel = new QLabel(trUtf8("Фильтры [Усеченного среднего]"));

    QVBoxLayout *l = new QVBoxLayout();
    l->addWidget(topLabel);
    l->addWidget(tabWidget);//toolBox);
    setLayout(l);
}

void FilterWidget::setFilterDialog(FilterDialog *f)
{
    fd = f;
}

void FilterWidget::updateParameters()
{
    if( fd == 0 ) {
        return;
    }
    if( fd->getPixmap() == 0 ) {
        return;
    }
    processPixmap(fd->getPixmap());
}


void FilterWidget::processPixmap(const QPixmap *qPixmap)
{
    int n = fd->getDemensionOfMatrix();
    int q = fd->getFilterOrder();
    int d = fd->getTruncatedMean();

    map.value(Filter::Averaging)->setPixmap(
            *DIP::processingImageWithAveragingFilter( qPixmap, n ) );

    map.value(Filter::GeometricMean)->setPixmap(
            *DIP::processingImageWithGeometricMeanFilter( qPixmap, n ) );

    map.value(Filter::HarmonicMean)->setPixmap(
            *DIP::processingImageWithHarmonicMeanFilter( qPixmap, n ) );

    map.value(Filter::CounterHarmonic)->setPixmap(
            *DIP::processingImageWithCounterHarmonicFilter( qPixmap, n, q ) );

    map.value(Filter::Median)->setPixmap(
            *DIP::processingImageWithMedianFilter( qPixmap, n ) );

    map.value(Filter::Minimum)->setPixmap(
            *DIP::processingImageWithMinimumFilter( qPixmap, n ) );

    map.value(Filter::Maximum)->setPixmap(
            *DIP::processingImageWithMaximumFilter( qPixmap, n ) );

    map.value(Filter::MediumPoint)->setPixmap(
            *DIP::processingImageWithMediumPoinFilter( qPixmap, n ) );

    map.value(Filter::TruncatedMean)->setPixmap(
            *DIP::processingImageWithTruncatedMeanFilter( qPixmap, n, d ) );

//    if( qPixmap->width() >= tabWidget->width() ) {
//        setMinimumWidth(qPixmap->width());
//    }
    resize(minimumWidth(),qPixmap->height());
}

void FilterWidget::updateText(int index)
{
    topLabel->setText(trUtf8("Фильтры [%1]").arg(tabWidget->tabText(index)) );
//    topLabel->setText(trUtf8("Фильтры [%1]").arg(toolBox->itemText(index) ));
}

