#include "gui/windows/MainWindow.hpp"
#include "gui/AppManagerSingleton.hpp"
#include "gui/utils/image.hpp"

#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>

namespace gui::windows {
MainWindow::MainWindow() {
    m_ui.setupUi(this);

    connect(m_ui.pushButton, &QPushButton::clicked, m_ui.pushButton, [this]() {
        auto file_menu = new QMenu();

        {
            auto action = new QAction("Open G8 image");
            connect(action, &QAction::triggered, this, &MainWindow::onOpenGrayscaleImageAction);
            file_menu->addAction(action);
        }

        {
            auto action = new QAction("Open RGB image");
            connect(action, &QAction::triggered, this, &MainWindow::onOpenRGBImageAction);
            file_menu->addAction(action);
        }

        file_menu->exec(QCursor::pos());
    });
}

void MainWindow::onOpenGrayscaleImageAction() { openImage(QImage::Format_Grayscale8); }
void MainWindow::onOpenRGBImageAction() { openImage(QImage::Format_RGB32); }

void MainWindow::openImage(QImage::Format format) {
    QString path = QFileDialog::getOpenFileName(this);
    if (path.isEmpty())
        return;

    try {
        QImage img(path);
        img.convertTo(format);

        QFileInfo pinfo(path);
        AppManagerSingleton::getInstance()->openImage(utils::image::imageFromQt(img), pinfo.baseName());
    } catch (const std::runtime_error& err) {
        QMessageBox::critical(this, "Error", err.what());
    }
}
} // namespace gui::windows