#include <QApplication>
#include "MainWindow.h"
#include "VendingFSM.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    VendingFSM fsm(&window);
    fsm.start();

    window.show();
    return app.exec();
}
