#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#include "imageprocessingwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void open();

private:
    QMdiArea *mdiArea;
//    QVector<ImageProcessingWidget*> ipWidgets;
    QVector<QLabel*> ipWidgets;
};

#endif // MAINWINDOW_H
