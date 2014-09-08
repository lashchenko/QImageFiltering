#include "dip.h"

QWidget* DIP::parent = 0;

void DIP::setParentWidget(QWidget *p)
{
    parent = p;
}

DIP::DIP(QObject *parent) :
    QObject(parent)
{
}

QPixmap* DIP::processingImageWithTruncatedMeanFilter(const QPixmap *qPixmap, int iN, int iD)
{
    QImage out = qPixmap->toImage();

    ImageProcessor processor(out);

    int N = iN;
    processor.setN(N);

    int D = iD;

    int w = out.width();
    int h = out.height();

    QProgressDialog progress(trUtf8("processingImageWithTruncatedMeanFilter"),
                             trUtf8("Cancel"),
                             0, 0,
                             parent);
//    progress.setValue(1);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for( int x=0; x<w; ++x ) {
        for( int y=0; y<h; ++y ) {
            QVector<int> values = processor.valuesGxy(x,y);
            qSort(values);
            int dMin = D;
            while( dMin-- && !values.isEmpty()) {
                values.remove(0);
            }
            int dMax = D;
            while( dMax-- && !values.isEmpty()) {
                values.remove( values.size()-1 );
            }
            int value = 0;
            for( int i=0; i<values.size(); ++i ) {
                value += values.at(i);
            }
            value = value/(N*N-D);
            QColor color = QColor::fromHsv(0, 0, value);
            out.setPixel(x,y, qRgb(color.red(), color.green(), color.blue()));
        }

        if (progress.wasCanceled()) {
            break;
        }
    }

    progress.close();

    return new QPixmap(QPixmap::fromImage(out));
}

QPixmap* DIP::processingImageWithMediumPoinFilter(const QPixmap *qPixmap, int iN)
{
    QImage out = qPixmap->toImage();

    ImageProcessor processor(out);

    int N = iN;
    processor.setN(N);

    int w = out.width();
    int h = out.height();

    QProgressDialog progress(trUtf8("processingImageWithMediumPoinFilter"),
                             trUtf8("Cancel"),
                             0, 0,
                             parent);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for( int x=0; x<w; ++x ) {
        for( int y=0; y<h; ++y ) {
            QVector<int> values = processor.valuesGxy(x,y);
            qSort(values);
            int value = (values.first() + values.last()) / 2;
            QColor color = QColor::fromHsv(0, 0, value);
            out.setPixel(x,y, qRgb(color.red(), color.green(), color.blue()));
        }

        if (progress.wasCanceled()) {
            break;
        }
    }

    progress.close();

    return new QPixmap(QPixmap::fromImage(out));
}

QPixmap* DIP::processingImageWithMinimumFilter(const QPixmap *qPixmap, int iN)
{
    QImage out = qPixmap->toImage();

    ImageProcessor processor(out);

    int N = iN;
    processor.setN(N);

    int w = out.width();
    int h = out.height();

    QProgressDialog progress(trUtf8("processingImageWithMinimumFilter"),
                             trUtf8("Cancel"),
                             0, 0,
                             parent);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for( int x=0; x<w; ++x ) {
        for( int y=0; y<h; ++y ) {
            QVector<int> values = processor.valuesGxy(x,y);
            qSort(values);
            QColor color = QColor::fromHsv(0, 0, values.first());
            out.setPixel(x,y, qRgb(color.red(), color.green(), color.blue()));
        }

        if (progress.wasCanceled()) {
            break;
        }
    }

    progress.close();

    return new QPixmap(QPixmap::fromImage(out));
}

QPixmap* DIP::processingImageWithMaximumFilter(const QPixmap *qPixmap, int iN)
{
    QImage out = qPixmap->toImage();
    ImageProcessor processor(out);

    int N = iN;
    processor.setN(N);

    int w = out.width();
    int h = out.height();

    QProgressDialog progress(trUtf8("Изображение обрабаывается фильтром Максимума"),
                             trUtf8("Отменить"),
                             0, 0,
                             parent);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for( int x=0; x<w; ++x ) {
        for( int y=0; y<h; ++y ) {
            QVector<int> values = processor.valuesGxy(x,y);
            qSort(values);
            QColor color = QColor::fromHsv(0, 0, values.last());
            out.setPixel(x,y, qRgb(color.red(), color.green(), color.blue()));
        }

        if (progress.wasCanceled()) {
            break;
        }
    }

    progress.close();

    return new QPixmap(QPixmap::fromImage(out));
}

QPixmap* DIP::processingImageWithMedianFilter(const QPixmap *qPixmap, int iN)
{
    QImage out = qPixmap->toImage();

    ImageProcessor processor(out);

    int N = iN;
    processor.setN(N);

    int w = out.width();
    int h = out.height();

    QProgressDialog progress(trUtf8("Изображение обрабаывается Медианным фильтром"),
                             trUtf8("Отменить"),
                             0, 0,
                             parent);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for( int x=0; x<w; ++x ) {
        for( int y=0; y<h; ++y ) {
            QVector<int> values = processor.valuesGxy(x,y);
            qSort(values);
            QColor color = QColor::fromHsv(0, 0, values.at(values.size()/2));
            out.setPixel(x,y, qRgb(color.red(), color.green(), color.blue()));
        }

        if (progress.wasCanceled()) {
            break;
        }
    }

    progress.close();

    return new QPixmap(QPixmap::fromImage(out));
}

QPixmap* DIP::processingImageWithCounterHarmonicFilter(const QPixmap *qPixmap, int iN, double iQ)
{
    QImage out = qPixmap->toImage();

    ImageProcessor processor(out);

    int N = iN;
    processor.setN(N);

    double Q = iQ;
    processor.setQ(Q);

    int w = out.width();
    int h = out.height();

    QProgressDialog progress(trUtf8("Изображение обрабаывается Средним контргармоническим фильтром"),
                             trUtf8("Отменить"),
                             0, 0,
                             parent);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for( int x=0; x<w; ++x ) {
        for( int y=0; y<h; ++y ) {
            double A = processor.sumGxyInPowerQ(x,y, Q+1.0);
            double B = processor.sumGxyInPowerQ(x,y, Q);
            int value = qAbs(A / B);
            value = (value < 0) ? 0 : value;
            value = (value > 0xFF) ? 0xFF : value;

            QColor color = QColor::fromHsv(0, 0, value);
            out.setPixel(x,y, qRgb(color.red(), color.green(), color.blue()));
        }

        if (progress.wasCanceled()) {
            break;
        }
    }

    progress.close();

    return new QPixmap(QPixmap::fromImage(out));
}

QPixmap* DIP::processingImageWithHarmonicMeanFilter(const QPixmap *qPixmap, int iN)
{
    QImage out = qPixmap->toImage();

    ImageProcessor processor(out);

    int N = iN;
    processor.setN(N);

    int w = out.width();
    int h = out.height();

    QProgressDialog progress(trUtf8("Изображение обрабаывается Контр-гармоническим фильтром"),
                             trUtf8("Отменить"),
                             0, 0,
                             parent);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for( int x=0; x<w; ++x ) {
        for( int y=0; y<h; ++y ) {
            double value = double(N*N) / processor.sumOneToGxy(x,y) ;
            QColor color = QColor::fromHsv(0, 0, int(value));
            out.setPixel(x,y, qRgb(color.red(), color.green(), color.blue()));
        }

        if (progress.wasCanceled()) {
            break;
        }
    }

    progress.close();

    return new QPixmap(QPixmap::fromImage(out));
}

QPixmap* DIP::processingImageWithAveragingFilter(const QPixmap *qPixmap, int iN)
{
    QImage out = qPixmap->toImage();

    ImageProcessor processor(out);

    int N = iN;
    processor.setN(N);

    int w = out.width();
    int h = out.height();

    QProgressDialog progress(trUtf8("Изображение обрабаывается Среднеарифметическим фильтром"),
                             trUtf8("Отменить"),
                             0, 0,
                             parent);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for( int x=0; x<w; ++x ) {
        for( int y=0; y<h; ++y ) {
            int value = processor.sumGxy(x,y) / (N*N);
            QColor color = QColor::fromHsv(0, 0, value);
            out.setPixel(x,y, qRgb(color.red(), color.green(), color.blue()));
        }

        if (progress.wasCanceled()) {
            break;
        }
    }

    progress.close();

    return new QPixmap(QPixmap::fromImage(out));
}

QPixmap* DIP::processingImageWithGeometricMeanFilter(const QPixmap *qPixmap, int iN)
{
    QImage out = qPixmap->toImage();

    ImageProcessor processor(out);

    int N = iN;
    processor.setN(N);

    int w = out.width();
    int h = out.height();

    QProgressDialog progress(trUtf8("Изображение обрабаывается Среднегеометрическим фильтром"),
                             trUtf8("Отменить"),
                             0, 0,
                             parent);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for( int x=0; x<w; ++x ) {
        for( int y=0; y<h; ++y ) {
            double d = processor.mulGxy(x,y);
            int value = pow( d, 1.0/(N*N) ) * 1000;

            value = (value<0x0 || value>0xFF) ? 0xFF : value;
            QColor color = QColor::fromHsv(0, 0, value);
            out.setPixel(x,y, qRgb(color.red(), color.green(), color.blue()));
        }

        if (progress.wasCanceled()) {
            break;
        }
    }

    progress.close();

    return new QPixmap(QPixmap::fromImage(out));
}

QPixmap* DIP::createPixmapWithImpulseNoise(QPixmap &qPixmap)
{
    QImage out = qPixmap.toImage();

    int w = out.width();
    int h = out.height();

    int n = qrand()%((w*h)/5);

    while( n-- ) {
        int x = qrand() % w;
        int y = qrand() % h;
        QColor color = QColor::fromHsv(0,0,(qrand() % 3) ? 255 : 0);
        out.setPixel(x,y, qRgb(color.red(), color.green(), color.blue()));
    }

    return new QPixmap(QPixmap::fromImage(out));
}

QPixmap* DIP::createPixmapWithAdditiveNoise(QPixmap &qPixmap)
{
    QImage out = qPixmap.toImage();

    int w = out.width();
    int h = out.height();

    for( int x=0; x<w; ++x ) {
        for( int y=0; y<h; ++y ) {
            if( qrand()%3 == 0 ) {
                continue;
            }
            int random = qAbs(qrand()%0xFF);


            QColor color = out.pixel(x,y);
            int value = color.value()+random;
            if( value < 0 ) {
                value = 0;
            }
            else if( value > 0xFF ){
                value = 0xFF;
            }
            color.setHsv(0,0, value);

            out.setPixel(x,y, qRgb(color.red(), color.green(), color.blue()));
        }
    }

    return new QPixmap(QPixmap::fromImage(out));
}

QPixmap* DIP::createPixmapWithMultiplicativeNoise(QPixmap &qPixmap)
{
    QImage out = qPixmap.toImage();

    int w = out.width();
    int h = out.height();

    for( int x=0; x<w; ++x ) {
        for( int y=0; y<h; ++y ) {
            if( qrand() % 2 == 0 ) {
                continue;
            } else if( qrand()%3 == 0 ) {
                continue;
            }

            double random = qrand()%100 * 0.01;

            QColor color = out.pixel(x,y);
            color.setHsvF(0,0, color.valueF()*random);

            out.setPixel(x,y, qRgb(color.red(), color.green(), color.blue()));
        }
    }

    return new QPixmap(QPixmap::fromImage(out));
}

QImage* DIP::transformImageToGray(QImage &qImage)
{
    QImage *image = new QImage(qImage.size(), QImage::Format_ARGB32);

    Q_ASSERT(image->size() == qImage.size() );

    for( int x=0; x<qImage.width(); ++x ) {
        for( int y=0; y<qImage.height(); ++y ) {
            QColor color = qImage.pixel(x,y);
            color.setHsv( 0, 0, color.value());

            QRgb pixel = qRgb(color.red(),color.green(), color.blue());
            image->setPixel(x,y, pixel);
        }
    }

    return image;
}

QPixmap* DIP::transformPixmapToGray(QPixmap &qPixmap)
{
    QImage image = qPixmap.toImage();
    QPixmap *pixmap = new QPixmap( QPixmap::fromImage( *DIP::transformImageToGray(image) ) );

    return pixmap;
}
