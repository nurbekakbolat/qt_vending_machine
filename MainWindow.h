#pragma once

#include <QWidget>

class QLineEdit;
class QPushButton;
class QLabel;
class QTimer;
class BottleWidget;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    QLabel *totalLabel;
    int totalEarned = 0;
    QLabel *tankInfoLabel;
    QLineEdit *inputMoney;
    QPushButton *fillBtn;
    QPushButton *stopBtn;
    QPushButton *abortBtn;
    QLabel *stateLabel;
    BottleWidget *bottle;
    QTimer *fillTimer;
};
