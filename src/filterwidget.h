#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include <QtGui>

#include "filterdialog.h"

namespace Filter {
    enum {
        Averaging,
        GeometricMean,
        HarmonicMean,
        CounterHarmonic,
        Median,
        Minimum,
        Maximum,
        MediumPoint,
        TruncatedMean
    };
}

class FilterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FilterWidget(QWidget *parent = 0);
    void setFilterDialog(FilterDialog *f);

signals:

public slots:
    void updateParameters();

private slots:
    void updateText(int index);

private:
    void processPixmap(const QPixmap *qPixmap);

    FilterDialog *fd;

//    QToolBox *toolBox;
    QTabWidget *tabWidget;
    QMap<int, QLabel*> map;
    QLabel *topLabel;
};

#endif // FILTERWIDGET_H
