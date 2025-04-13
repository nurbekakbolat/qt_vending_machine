#include "BottleWidget.h"
#include <QPainter>

BottleWidget::BottleWidget(QWidget *parent) : QWidget(parent), fillLevel(0) {
    setFixedSize(80, 220);
}

void BottleWidget::setFillLevel(int level) {
    fillLevel = qBound(0, level, 100);
    update();
}

int BottleWidget::getFillLevel() const {
    return fillLevel;
}

void BottleWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);

    p.setPen(Qt::black);
    p.setBrush(Qt::white);
    p.drawRect(10, 10, 60, 200);

    if (fillLevel > 0) {
        p.setBrush(Qt::blue);
        int height = (200 * fillLevel) / 100;
        p.drawRect(10, 210 - height, 60, height);
    }
}

