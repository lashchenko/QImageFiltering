#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QtGui>

class FilterDialog : public QWidget
{
    Q_OBJECT
public:
    explicit FilterDialog(QWidget *parent = 0);

    const QPixmap* getPixmap();
    int getDemensionOfMatrix();
    double getFilterOrder();
    int getTruncatedMean();

signals:
    void updateParameters();
    void open();

public slots:
    void setPixmap(const QPixmap *qPixmap);

private slots:
    void calculate();

private:
    const QPixmap *pixmap;

    QSpinBox *demensionOfMatrix;
    QDoubleSpinBox *filterOrder;
    QSpinBox *truncatedMean;
};

#endif // FILTERDIALOG_H
