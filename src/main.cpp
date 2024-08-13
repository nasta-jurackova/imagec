
#include "core/image.hpp"
#include "gui/main_window.hpp"
#include "gui/image_dialog.hpp"

#include <QApplication>
#include <iostream>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    auto window = new MainWindow();
    window->show();

    return app.exec();
}