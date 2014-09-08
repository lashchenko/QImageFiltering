#include "original.h"
#include "dip.h"

Original::Original(QWidget *parent) :
    QWidget(parent)
{
    tabWidget = new QTabWidget;
    label = new QLabel;
    grayLabel = new QLabel;

    tabWidget->addTab(label, trUtf8("Исходное изображение"));
    tabWidget->addTab(grayLabel, trUtf8("Полутоновое изображение"));

    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(new QLabel(trUtf8("Изображение")));
    l->addWidget(tabWidget);
    setLayout(l);
}


void Original::setImage(QImage qImage)
{
    image = qImage;
    pixmap = QPixmap::fromImage(image);
    label->setPixmap(pixmap);
    resize(qImage.size());
}

void Original::setPixmap(QPixmap qPixmap)
{
    pixmap = qPixmap;
    grayPixmap = *DIP::transformPixmapToGray(qPixmap);

    image = pixmap.toImage();
    grayImage = *DIP::transformImageToGray(image);

    label->setPixmap(pixmap);
    grayLabel->setPixmap(grayPixmap);

    resize(qPixmap.size());
}

QImage* Original::getImage()
{
    return &image;
}

QPixmap* Original::getPixmap()
{
    return &pixmap;
}

QImage* Original::getGrayImage()
{
    return &grayImage;
}

QPixmap* Original::getGrayPixmap()
{
    return &grayPixmap;
}
