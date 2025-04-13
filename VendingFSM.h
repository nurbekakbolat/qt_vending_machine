#pragma once

#include <QObject>

class QStateMachine;
class MainWindow;

class VendingFSM : public QObject {
    Q_OBJECT

public:
    explicit VendingFSM(MainWindow *ui, QObject *parent = nullptr);
    void start();

signals:
    void startFilling();
    void finishedFilling();
    void resetToIdle();

private:
    int totalSteps = 0;
    int currentStep = 0;
    MainWindow *ui;
    QStateMachine *machine;
};

