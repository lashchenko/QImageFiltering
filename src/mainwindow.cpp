#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    QAction *open = new QAction(tr("OPEN IMAGE FILE"), this);
    connect(open, SIGNAL(triggered()), this, SLOT(open()));

    QToolBar *fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(open);

    for( int i=0; i<10; ++i) {
        mdiArea->addSubWindow(new QLabel(tr("%1").arg(i)));
    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "/home",
                                                     tr("Images (*.png *.xpm *.jpg)"));

}
