
#include "core/image.hpp"
#include "gui/windows/MainWindow.hpp"

#include <QApplication>
#include <iostream>

int main(int argc, char** argv) {
 
    QApplication app(argc, argv);

    auto window = new gui::windows::MainWindow();
    window->show();

    return app.exec();
}