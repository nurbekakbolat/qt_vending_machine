#include "VendingFSM.h"
#include "MainWindow.h"
#include "BottleWidget.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QEventTransition>

#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QTimer>
#include <QEvent>

#include <QDebug>

VendingFSM::VendingFSM(MainWindow *ui, QObject *parent) : QObject(parent), ui(ui) {
    machine = new QStateMachine(this);

    auto *idle = new QState();
    auto *filling = new QState();
    auto *stopped = new QState();
    auto *aborted = new QState();
    auto *completed = new QState();

    idle->assignProperty(ui->stateLabel, "text", "State: Idle");
    QObject::connect(idle, &QState::entered, [=]() {
        ui->fillBtn->setEnabled(true);
    });
    QObject::connect(ui->fillBtn, &QPushButton::clicked, [=]() {
        bool ok;
        int money = ui->inputMoney->text().toInt(&ok); 
    
        if (ok && money > 0 && money <= 100) {
            ui->stateLabel->setStyleSheet("");
            ui->totalEarned += money;
            ui->totalLabel->setText(QString("Total Earned: ₸%1").arg(ui->totalEarned));
            float liters = money / 10.0f;
            ui->tankInfoLabel->setText(QString("%1 Liters (₸10/L)").arg(liters, 0, 'f', 2));
            emit startFilling();  // Valid input, start filling
        } else {
            ui->inputMoney->clear();  // Clear invalid input
            ui->stateLabel->setStyleSheet("color: red;");
            ui->stateLabel->setText("Invalid input! Please enter a number between 1 and 100.");
        }
    });
    idle->addTransition(this, SIGNAL(startFilling()), filling);
    
    filling->assignProperty(ui->stateLabel, "text", "State: Filling");
    QObject::connect(filling, &QState::entered, [=]() mutable {
        ui->fillBtn->setEnabled(false);
        ui->inputMoney->setEnabled(false);
        
        if (currentStep == 0) {
            ui->bottle->setFillLevel(0);
        }
    
        bool ok;
        int money = ui->inputMoney->text().toInt(&ok);
        if (ok && money > 0) {
            totalSteps = (money * 100) / 100; 
            ui->fillTimer->start(500);
        } else {
            totalSteps = 0;
        }
    });
    
    QObject::connect(filling, &QState::exited, ui->fillTimer, &QTimer::stop);
    QObject::connect(ui->fillTimer, &QTimer::timeout, [=]() mutable {
        qDebug() << "Step:" << currentStep << "of" << totalSteps;
    
        if (currentStep < totalSteps) {
            currentStep++;
            int fillPercent = (currentStep * 100) / totalSteps;
            ui->bottle->setFillLevel(fillPercent);
        } else {
            qDebug() << "Filling done, emitting finishedFilling()";
            ui->fillTimer->stop();
            emit finishedFilling();
        }
    });
    
    

    filling->addTransition(ui->stopBtn, &QPushButton::clicked, stopped);
    filling->addTransition(ui->abortBtn, &QPushButton::clicked, aborted);
    filling->addTransition(this, SIGNAL(finishedFilling()), completed);

    stopped->assignProperty(ui->stateLabel, "text", "State: Stopped");
    QObject::connect(stopped, &QState::entered, [=]() {
        ui->fillBtn->setEnabled(true);
        ui->inputMoney->setEnabled(false);
        ui->fillTimer->stop();
    });
    QObject::connect(stopped, &QState::entered, ui->fillTimer, &QTimer::stop);
    stopped->addTransition(ui->fillBtn, &QPushButton::clicked, filling);
    stopped->addTransition(ui->abortBtn, &QPushButton::clicked, aborted);

    aborted->assignProperty(ui->stateLabel, "text", "State: Aborted");
    QObject::connect(aborted, &QState::entered, [=]() {
        ui->fillBtn->setEnabled(true);
        ui->inputMoney->setEnabled(true);
        ui->tankInfoLabel->setText("0 Liters (₸10/L)");
        ui->bottle->setFillLevel(0);
        currentStep = 0;
        totalSteps = 0;
        ui->fillTimer->stop();
    });

    aborted->addTransition(idle);

    QObject::connect(completed, &QState::entered, [=]() {
        ui->stateLabel->setText("State: Completed. Thank you!");
        
        ui->fillBtn->setEnabled(false);
        ui->inputMoney->setEnabled(false);
    
        QTimer::singleShot(5000, [=]() {
            ui->stateLabel->setText("State: Idle");
            ui->tankInfoLabel->setText("0 Liters (₸10/L)");
            ui->fillBtn->setEnabled(true);
            ui->inputMoney->setEnabled(true);
            ui->inputMoney->clear();
            ui->bottle->setFillLevel(0);
            currentStep = 0;
            totalSteps = 0;
        
            emit resetToIdle();
        });
        
    });

    completed->addTransition(this, SIGNAL(resetToIdle()), idle);

    machine->addState(idle);
    machine->addState(filling);
    machine->addState(stopped);
    machine->addState(aborted);
    machine->addState(completed);
    machine->setInitialState(idle);
}

void VendingFSM::start() {
    machine->start();
}
