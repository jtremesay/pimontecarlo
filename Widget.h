#pragma once

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget * parent=nullptr);
    ~Widget();

private:
    void run();
    void stop();
    void add();
    void reset();

    void updateStats();
    void updateControls();
    void updateUi();

private slots:
    void onTimerTimeout();
    void onRunButtonClicked();
    void onStopButtonClicked();
    void onAddButtonClicked();
    void onResetButtonClicked();

private:
    Ui::Widget * _ui;
    quint64 _totalPoints;
    quint64 _pointsInCircle;
    QTimer * _timer;
};
