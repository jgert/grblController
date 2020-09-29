//
// Created by Jakub Gert on 07/06/2020.
//

#include <QApplication>
#include <QDebug>
#include <QStyle>
#include "src/MainWindow.h"
#include "src/grbl/GRBL.h"
#include <QWindow>
#include <src/widgets/codeEditor/CodeEditorWidget.h>
#include <src/widgets/codeEditor/GCodeEditorWidget.h>
#include <src/widgets/render/Renderer2DWidget.h>

using namespace std;

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setStyle("Fusion");

    SerialPort serialPort;

    MainWindow mainWindow(&serialPort);

    mainWindow.show();

//    QMainWindow window;
//    auto layout = new QHBoxLayout;
//    auto widget1 = new GCodeEditorWidget();
//    auto widget2 = new Renderer2DWidget();
//    layout->addWidget(widget1, 50);
//    layout->addWidget(widget2, 50);
//    layout->update();
//    auto centralWidget = new QWidget();
//    centralWidget->setLayout(layout);
//    window.setCentralWidget(centralWidget);
//
//    window.show();

    return app.exec();
}
