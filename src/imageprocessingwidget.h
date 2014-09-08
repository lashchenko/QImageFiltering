#ifndef IMAGEPROCESSINGWIDGET_H
#define IMAGEPROCESSINGWIDGET_H

#include <QtGui>

#include "noicewidget.h"
#include "filterwidget.h"
#include "original.h"

class ImageProcessingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageProcessingWidget(QWidget *parent = 0);

signals:

public slots:
    void open();
    void save();

protected:
    void resizeEvent(QResizeEvent *event);

protected:
    QSplitter *splitter;

    Original original;
    NoiseWidget noise;
    FilterWidget filter;
};

#endif // IMAGEPROCESSINGWIDGET_H
