#ifndef NOICEWIDGET_H
#define NOICEWIDGET_H

#include <QtGui>

namespace Noise {
    enum {
        IMPULSE,
        ADDITIVE,
        MULTIPLICATIVE,
        WITHOUT_NOISE
    };
}

class NoiseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NoiseWidget(QWidget *parent = 0);

    void setPixmap(QPixmap qPixmap);

signals:
    void updatePixmap(const QPixmap *pixmap);
private slots:
    void currentTabChanged(int index);

private:
    QMap< int, QLabel* > map;
    QTabWidget *tabWidget;
    QLabel *topLabel;
};

#endif // NOICEWIDGET_H
