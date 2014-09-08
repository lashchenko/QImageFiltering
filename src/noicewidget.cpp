#include "noicewidget.h"
#include "dip.h"

NoiseWidget::NoiseWidget(QWidget *parent) :
    QWidget(parent)
{
    map.insert(Noise::IMPULSE, new QLabel());
    map.insert(Noise::ADDITIVE, new QLabel());
    map.insert(Noise::MULTIPLICATIVE, new QLabel());
    map.insert(Noise::WITHOUT_NOISE, new QLabel());

    tabWidget = new QTabWidget();
    tabWidget->addTab(map.value(Noise::IMPULSE), trUtf8("Импульсный"));
    tabWidget->addTab(map.value(Noise::MULTIPLICATIVE), trUtf8("Мльтипликативный"));
    tabWidget->addTab(map.value(Noise::ADDITIVE), trUtf8("Аддитивный"));
    tabWidget->addTab(map.value(Noise::WITHOUT_NOISE), trUtf8("Без шума"));

    setMinimumWidth(400);

    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged(int)));

    topLabel = new QLabel(trUtf8("Шумы [Импульсный]"));

    QVBoxLayout *l = new QVBoxLayout();
    l->addWidget(topLabel);//new QLabel(trUtf8("Шумы")));
    l->addWidget(tabWidget);
    setLayout(l);
}

void NoiseWidget::setPixmap(QPixmap qPixmap)
{
    QImage *image = new QImage(qPixmap.toImage());
    QPixmap pixmap = QPixmap::fromImage(*image);

    map.value(Noise::IMPULSE)->setPixmap(*DIP::createPixmapWithImpulseNoise(pixmap));

    map.value(Noise::MULTIPLICATIVE)->setPixmap(*DIP::createPixmapWithMultiplicativeNoise(pixmap));

    map.value(Noise::ADDITIVE)->setPixmap(*DIP::createPixmapWithAdditiveNoise(pixmap));

    map.value(Noise::WITHOUT_NOISE)->setPixmap(pixmap);

    resize(qPixmap.size());
    if( qPixmap.width() < 400 ) {
        resize(400,qPixmap.height());
    }

    currentTabChanged(tabWidget->currentIndex());
}

void NoiseWidget::currentTabChanged(int index)
{
    topLabel->setText(trUtf8("Шумы [%1]").arg( tabWidget->tabText(index)) );
    QLabel *label = (QLabel*)tabWidget->widget(index);
    if( label == 0 ) {
        return;
    }
    emit(updatePixmap(label->pixmap()));
}

