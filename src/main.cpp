
#include "core/image.hpp"
#include "gui/main_bar.hpp"
#include "gui/image_dialog.hpp"

#include <QApplication>
#include <iostream>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainBarSingleton* bar = MainBarSingleton::getInstance();
    bar->show();

    return app.exec();
}