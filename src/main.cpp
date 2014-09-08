#include <QtGui/QApplication>

#include "imageprocessingwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ImageProcessingWidget w;
    w.setBackgroundRole(QPalette::Dark);
    w.setPalette(Qt::darkGray);
//    w.showMaximized();
    w.showFullScreen();

//    QMessageBox::aboutQt(&w, "afa");

    QApplication::setStyle(new QPlastiqueStyle());
    return a.exec();
}
