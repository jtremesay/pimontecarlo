#include "RenderWidget.h"
#include <QtGui/QPainter>

RenderWidget::RenderWidget(QWidget * parent) :
    QWidget(parent),
    _circleBrush(Qt::blue, Qt::SolidPattern),
    _pointInBrush(Qt::green, Qt::SolidPattern),
    _pointOutBrush(Qt::red, Qt::SolidPattern)
{
    this->setPalette(QPalette(Qt::white));
    this->setAutoFillBackground(true);
}

void RenderWidget::reset()
{
    _points.clear();

    this->update();
}

void RenderWidget::addPoint(const QPair<QPointF, bool> & point)
{
    if (_points.length() == 5000) {
        _points.dequeue();
    }
    _points.enqueue(point);

    this->update();
}

void RenderWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    const int width = this->width();
    const int halfWidth = width / 2;
    const int height = this->height();
    const int halfHeight = height / 2;

    // draw target
    //painter.setBrush(_circleBrush);
    //painter.drawEllipse(0, 0, width, height);

    // Points
    for (const QPair<QPointF, bool> & point : _points) {
        if (point.second) {
            painter.setBrush(_pointInBrush);
        } else {
            painter.setBrush(_pointOutBrush);
        }

        const int x = halfWidth - halfWidth * point.first.x();
        const int y = halfHeight - halfHeight * point.first.y();
        painter.drawEllipse(x - (width / 128), y - (height / 128), width / 64, width / 64);
    }
}
