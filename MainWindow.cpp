#include "MainWindow.h"
#include "BottleWidget.h"

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    inputMoney = new QLineEdit;
    inputMoney->setPlaceholderText("Enter money...");

    fillBtn = new QPushButton("Fill");
    stopBtn = new QPushButton("Stop");
    abortBtn = new QPushButton("Abort");
    QString buttonStyle = R"(
        QPushButton {
            background-color: rgba(255, 255, 255, 180);
            border: 2px solid #0077be;
            border-radius: 8px;
            padding: 6px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: rgba(0, 119, 190, 0.8);
            color: white;
        }
    )";
    fillBtn->setStyleSheet(buttonStyle);
    stopBtn->setStyleSheet(buttonStyle);
    abortBtn->setStyleSheet(buttonStyle);
    
    stateLabel = new QLabel("State: Idle");
    stateLabel->setStyleSheet("color: black; font-size: 16px; font-weight: bold;");

    bottle = new BottleWidget;

    fillTimer = new QTimer(this);
    fillTimer->setInterval(100);

    totalLabel = new QLabel("Total Earned: ₸0");
    totalLabel->setStyleSheet("color: black; font-weight: bold; font-size: 14px;");
    
    auto *layout = new QVBoxLayout;

    layout->addWidget(totalLabel);
    layout->addWidget(inputMoney);
    layout->addWidget(fillBtn);
    layout->addWidget(stopBtn);
    layout->addWidget(abortBtn);
    layout->addWidget(stateLabel);
    
    auto *tankLayout = new QVBoxLayout;
    tankLayout->setAlignment(Qt::AlignHCenter);
    
    QLabel *tankLabel = new QLabel("Water Tank");
    tankLabel->setStyleSheet("color: black; font-weight: bold;");
    tankLabel->setAlignment(Qt::AlignCenter);

    tankInfoLabel = new QLabel("0 Liters (₸10/L)");
    tankInfoLabel->setStyleSheet("color: black; font-weight: bold;");
    tankInfoLabel->setAlignment(Qt::AlignCenter);

    tankLayout->addWidget(tankLabel);
    tankLayout->addWidget(tankInfoLabel);
    tankLayout->addWidget(bottle);
    
    QWidget *tankContainer = new QWidget;
    tankContainer->setLayout(tankLayout);
    
    layout->addStretch();
    layout->addWidget(tankContainer);
    layout->addStretch(); 
    
    setLayout(layout);
    
    setFixedSize(400, 600);
    setWindowTitle("NU Vodomat");

    QPixmap bg("public/water_bg.jpg"); 
    QPixmap scaledBg = bg.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(scaledBg));
    
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}
