#include "Widget.h"
#include <cmath>
#include <QtCore/QTimer>
#include "ui_Widget.h"

constexpr qreal lerp(qreal val, qreal x0, qreal y0, qreal x1, qreal y1)
{
    return ((y0 * (x1 - val)) + (y1 * (val - x0))) / (x1 - x0);
}

Widget::Widget(QWidget * parent) :
    QWidget(parent),
    _ui(new Ui::Widget),
    _timer(new QTimer(this))
{
    connect(_timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));

    _ui->setupUi(this);

    connect(_ui->runButton, SIGNAL(clicked()), this, SLOT(onRunButtonClicked()));
    connect(_ui->stopButton, SIGNAL(clicked()), this, SLOT(onStopButtonClicked()));
    connect(_ui->addButton, SIGNAL(clicked()), this, SLOT(onAddButtonClicked()));
    connect(_ui->resetButton, SIGNAL(clicked()), this, SLOT(onResetButtonClicked()));

    this->reset();
    this->updateUi();
}

Widget::~Widget()
{
    delete _ui;
}

void Widget::run()
{
    _timer->start();
}

void Widget::stop()
{
    _timer->stop();
}


void Widget::add()
{
    _totalPoints++;

    const qreal x = lerp(rand(), 0, -1, RAND_MAX, 1);
    const qreal y = lerp(rand(), 0, -1, RAND_MAX, 1);
    const qreal distance = sqrt(x * x + y * y);
    const bool isInCircle = distance < 1.0;
    if (isInCircle) {
        _pointsInCircle++;
    }

    _ui->renderWidget->addPoint(QPair<QPointF, bool>(QPointF(x, y), isInCircle));
}

void Widget::reset()
{
    _totalPoints = 0;
    _pointsInCircle = 0;

    _ui->renderWidget->reset();
}

void Widget::updateStats()
{
    _ui->totalPointsEdit->setText(QString::number(_totalPoints));
    _ui->pointsInCircleEdit->setText(QString::number(_pointsInCircle));

    const qreal pi = 4.0 * _pointsInCircle / _totalPoints;
    _ui->piEdit->setText(QString::number(pi));

    const qreal error = pi - M_PI;
    _ui->errorEdit->setText(QString::number(error));

    const qreal errorRelative = error / M_PI * 100.0;
    _ui->errorRelativeEdit->setText(QString::number(errorRelative));
}

void Widget::updateControls()
{
    const bool isRunning = _timer->isActive();
    _ui->runButton->setEnabled(!isRunning);
    _ui->stopButton->setEnabled(isRunning);
}

void Widget::updateUi()
{
    this->updateControls();
    this->updateStats();
}

void Widget::onTimerTimeout()
{
    for (int i = 0; i < 1000; ++i) {
        this->add();
    }
    this->updateStats();
}

void Widget::onRunButtonClicked()
{
    this->run();
    this->updateControls();
}

void Widget::onStopButtonClicked()
{
    this->stop();
    this->updateControls();
}

void Widget::onAddButtonClicked()
{
    this->add();
    this->updateStats();
}

void Widget::onResetButtonClicked()
{
    this->reset();
    this->updateStats();
}
