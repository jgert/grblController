//
// Created by Jakub Gert on 07/06/2020.
//

#include <QApplication>
#include <QDebug>
#include <QStyle>
#include "src/MainWindow.h"
#include "src/grbl/GRBL.h"

using namespace std;

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setStyle("Fusion");

    SerialPort serialPort;

    MainWindow mainWindow(&serialPort);

    mainWindow.show();

    return app.exec();
}