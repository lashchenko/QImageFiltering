#include "filterdialog.h"

FilterDialog::FilterDialog(QWidget *parent) :
    QWidget(parent)
{

    setMinimumHeight(40);

    QHBoxLayout *l = new QHBoxLayout;
    QHBoxLayout *hl;

    QPushButton *button = new QPushButton(trUtf8("Открыть изображение"));
    connect(button, SIGNAL(clicked()), this, SIGNAL(open()));
    hl = new QHBoxLayout();
    hl->addWidget(button);
    l->addLayout(hl);

    l->addSpacing(10);

    demensionOfMatrix = new QSpinBox();
    demensionOfMatrix->setRange(3,11);
    demensionOfMatrix->setSingleStep(2);
    demensionOfMatrix->setValue(3);
    connect(demensionOfMatrix, SIGNAL(valueChanged(int)), this, SLOT(calculate()));

    hl = new QHBoxLayout();
    hl->addWidget(new QLabel(trUtf8("Размерность матрицы <b>[N x N]</b> :<br/>"
                                    "Все виды фильтрации. ")));
    hl->addWidget(demensionOfMatrix);
    l->addLayout(hl);

    l->addSpacing(10);

    filterOrder = new QDoubleSpinBox();
    filterOrder->setRange(-10.0, +10.0);
    filterOrder->setSingleStep(0.1);
    filterOrder->setValue(1.5);

    hl = new QHBoxLayout();
    hl->addWidget(new QLabel(trUtf8("Порядок фильтра [Q] : <br/>"
                                    "Контр-среднегармонический фильтр.")));
    hl->addWidget(filterOrder);
    l->addLayout(hl);

    l->addSpacing(10);

    truncatedMean = new QSpinBox();
    truncatedMean->setRange(0,9-1);
    truncatedMean->setValue(2);
    connect(truncatedMean, SIGNAL(valueChanged(int)), this, SLOT(calculate()));
    hl = new QHBoxLayout();
    hl->addWidget(new QLabel(trUtf8("Усеченное среднее <br/>"
                                    "[d : 0 .. NxN-1] :")));
    hl->addWidget(truncatedMean);
    l->addLayout(hl);

    l->addSpacing(10);

    button = new QPushButton(trUtf8("Начать обработку"));
    button->setPalette(Qt::darkGreen);
//    button->setStyleSheet("color: #FF5500; font: bold 14px;");
    connect(button, SIGNAL(clicked()), this, SIGNAL(updateParameters()));
    hl = new QHBoxLayout();
    hl->addWidget(button);
    l->addLayout(hl);

    l->addStretch();

    button = new QPushButton(trUtf8("Выйти"));
    button->setPalette(Qt::darkRed);
//    button->setStyleSheet("color: #FF5500; font: bold 14px;");
    connect(button, SIGNAL(clicked()), qApp, SLOT(quit()));
    hl = new QHBoxLayout();
    hl->addWidget(button);
    l->addLayout(hl);

    setLayout(l);
}

void FilterDialog::calculate()
{
    int N = demensionOfMatrix->value();
    N = (N%2 == 0) ? 1 : N;
    demensionOfMatrix->setValue(N);
    truncatedMean->setRange(0, N*N-1);
}

int FilterDialog::getTruncatedMean()
{
    return truncatedMean->value();
}

const QPixmap* FilterDialog::getPixmap()
{
    return pixmap;
}

int FilterDialog::getDemensionOfMatrix()
{
    return demensionOfMatrix->value();
}

double FilterDialog::getFilterOrder()
{
    return filterOrder->value();
}

void FilterDialog::setPixmap(const QPixmap *qPixmap)
{
    pixmap = qPixmap;
    emit( updateParameters() );
}
