#ifndef DIP_H
#define DIP_H

#include <QObject>
#include <QtCore>
#include <QtGui>

#include <QDebug>

class DIP : public QObject
{
    Q_OBJECT
public:
    explicit DIP(QObject *parent = 0);

    static QImage* transformImageToGray(QImage &qImage);
    static QPixmap* transformPixmapToGray(QPixmap &qPixmap);

    static QPixmap* createPixmapWithImpulseNoise(QPixmap &qPixmap);
    static QPixmap* createPixmapWithAdditiveNoise(QPixmap &qPixmap);
    static QPixmap* createPixmapWithMultiplicativeNoise(QPixmap &qPixmap);

    // Arithmetical average
    static QPixmap* processingImageWithAveragingFilter(const QPixmap *qPixmap, int iN=3);
    // Geometric mean
    static QPixmap* processingImageWithGeometricMeanFilter(const QPixmap *qPixmap, int iN=3);
    // Harmonic mean
    static QPixmap* processingImageWithHarmonicMeanFilter(const QPixmap *qPixmap, int iN=3);
    // counter harmonic
    static QPixmap* processingImageWithCounterHarmonicFilter(const QPixmap *qPixmap, int iN=3, double iQ=1.5);
    // Median filter
    static QPixmap* processingImageWithMedianFilter(const QPixmap *qPixmap, int iN=3);
    // Minimum filter
    static QPixmap* processingImageWithMinimumFilter(const QPixmap *qPixmap, int iN=3);
    // Maximum filter
    static QPixmap* processingImageWithMaximumFilter(const QPixmap *qPixmap, int iN=3);
    // Medium point filter
    static QPixmap* processingImageWithMediumPoinFilter(const QPixmap *qPixmap, int iN=3);
    // Truncated mean filter
    static QPixmap* processingImageWithTruncatedMeanFilter(const QPixmap *qPixmap, int iN=3, int iD=0);


    static void setParentWidget(QWidget *p);

private:
    static QWidget *parent;
};

class ImageProcessor {
public:
    ImageProcessor(QImage qImage)
    {
        image = qImage;
        n = 3;
        q = 1.5;
    }

    void setN(int iN=3 )
    { // only NxN matrix
        n = iN;
    }

    void setQ(double iQ=1.5)
    {
        q = iQ;
    }

    int g(int s, int t)
    {
        QColor color = image.pixel(s,t);
        return color.value();
    }

    QVector<int> valuesGxy(int x, int y )
    {
        QVector<int> values;

        int c = (n-1)/2;
        for( int s=x-c; s<=x+c; ++s ) {
            for( int t=y-c; t<=y+c; ++t ) {
                if( checkPosition(s,t) ) {
                    values.append(g(s,t));
                }
            }
        }

        return values;
    }

    double sumGxyInPowerQ(int x, int y, double iQ=1.5)
    {
        q = iQ;

        double result = 0;

        int c = (n-1)/2;
        for( int s=x-c; s<=x+c; ++s ) {
            for( int t=y-c; t<=y+c; ++t ) {
                if( checkPosition(s,t) ) {
                    double G = double(g(s,t));
                    double value =  pow(G, q);
                    value = (G == 0) ? 0 : value;
                    result += value;
                }
            }
        }
        return result;
    }

    double sumOneToGxy(int x, int y)
    {
        double result = 0;

        int c = (n-1)/2;
        for( int s=x-c; s<=x+c; ++s ) {
            for( int t=y-c; t<=y+c; ++t ) {
                if( checkPosition(s,t) ) {
                    double value =  g(s,t);
                    if( value == 0 ) {
                        value = 255.0;
                    }
                    result += (1.0 / value );
                } else {
                    result += (1.0 / 255.0);
                }
            }
        }

        if( result == 0.0 ) {
            return 1.0;
        }
        return result;
    }

    int sumGxy(int x, int y)
    {
        int result = 0;

        int c = (n-1)/2;
        for( int s=x-c; s<=x+c; ++s ) {
            for( int t=y-c; t<=y+c; ++t ) {
                if( checkPosition(s,t) ) {
                    result += g(s,t);
                }
            }
        }

        return result;
    }

    double mulGxy(int x, int y)
    {
        double result = 1.0;

        int c = (n-1)/2;
        for( int s=x-c; s<=x+c; ++s ) {
            for( int t=y-c; t<=y+c; ++t ) {
                if( checkPosition(s,t) ) {
                    result *= ((g(s,t) > 0 ) ? g(s,t) / 1000.0 : 1.0);
                }
            }
        }
        return result;
    }

    bool checkPosition(int x, int y)
    {
        if( x < 0 ) {
            return false;
        }
        if( x >= image.width() ) {
            return false;
        }
        if( y < 0 ) {
            return false;
        }
        if( y >= image.height() ) {
            return false;
        }
        return true;
    }

private:
    int n;
    double q;
    QImage image;
};

#endif // DIP_H
