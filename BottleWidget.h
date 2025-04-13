#pragma once
#include <QWidget>

class BottleWidget : public QWidget {
    Q_OBJECT
public:
    explicit BottleWidget(QWidget *parent = nullptr);
    void setFillLevel(int level);
    int getFillLevel() const;

protected:
    void paintEvent(QPaintEvent *) override;

private:
    int fillLevel;
};
