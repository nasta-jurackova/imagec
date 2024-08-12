#include <iostream>

#include "main_window.hpp"

#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);


    auto wdg = new MainWindow();
    wdg->show();
    
    return app.exec();
}