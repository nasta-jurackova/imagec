#include "main_window.hpp"

#include "image_with_info_widget.hpp"

MainWindow::MainWindow() { 
    auto wdg = new ImageWithInfoWidget();
    setCentralWidget(wdg);
}
