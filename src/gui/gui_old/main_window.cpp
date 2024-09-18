#include "main_window.hpp"

#include "gui/main_bar.hpp"

MainWindow::MainWindow() {
    setCentralWidget(MainBarSingleton::getInstance());
}
