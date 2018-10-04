#pragma once

#include <QtCore/QQueue>
#include <QtWidgets/QWidget>

class RenderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RenderWidget(QWidget * parent=nullptr);

    void reset();
    void addPoint(const QPair<QPointF, bool> & point);

protected:
    void paintEvent(QPaintEvent * event) override;

private:
    QQueue<QPair<QPointF, bool>> _points;
    const QBrush _circleBrush;
    const QBrush _pointInBrush;
    const QBrush _pointOutBrush;
};
