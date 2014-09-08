#include "imageprocessingwidget.h"
#include "dip.h"
#include "filterdialog.h"

ImageProcessingWidget::ImageProcessingWidget(QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize(800,600);

    FilterDialog *fd = new FilterDialog();
    fd->setMaximumHeight(50);
    filter.setFilterDialog(fd);

    connect(&noise, SIGNAL(updatePixmap(const QPixmap*)), fd, SLOT(setPixmap(const QPixmap*)));
    connect(fd, SIGNAL(updateParameters()), &filter, SLOT(updateParameters()));

    connect(fd, SIGNAL(open()), this, SLOT(open()));

    splitter = new QSplitter(Qt::Horizontal);
    QScrollArea *scroll;

    scroll= new QScrollArea();
    scroll->setWidget( &original );
    splitter->addWidget( scroll );

    scroll= new QScrollArea();
    scroll->setWidget( &noise );
    splitter->addWidget( scroll  );

    scroll= new QScrollArea();
    scroll->setWidget( &filter );
    splitter->addWidget( scroll );

    QVBoxLayout *l = new QVBoxLayout();
    l->addWidget(fd);
    l->addWidget(splitter);

    setLayout(l);
}

void ImageProcessingWidget::open()
{
    QString path = QDir::home().path() + "/images/t";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     path,
                                                     tr("Images (*.png *.xpm *.jpg)"));
    if( fileName.isEmpty() ) {
        return;
    }

    QPixmap pixmap(fileName);

    DIP::setParentWidget(this);

    original.setPixmap(pixmap);
    noise.setPixmap(*original.getGrayPixmap());
}

void ImageProcessingWidget::save()
{

}

void ImageProcessingWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}
