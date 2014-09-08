#ifndef ORIGINAL_H
#define ORIGINAL_H

#include <QtGui>

class Original : public QWidget
{
    Q_OBJECT
public:
    explicit Original(QWidget *parent = 0);

    void setImage(QImage qImage);
    void setPixmap(QPixmap qPixmap);

    QImage* getImage();
    QPixmap* getPixmap();

    QImage* getGrayImage();
    QPixmap* getGrayPixmap();

signals:

public slots:

private:
    QLabel *label;
    QLabel *grayLabel;

    QImage image;
    QImage grayImage;

    QPixmap pixmap;
    QPixmap grayPixmap;

    QTabWidget *tabWidget;
};

#endif // ORIGINAL_H
