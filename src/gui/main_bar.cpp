#include "gui/main_bar.hpp"
#include "gui/image_dialog.hpp"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QMenu>
#include <QPushButton>
#include <QString>

MainBarSingleton::MainBarSingleton() {
    setWindowTitle("Image C");

    auto hbox = new QHBoxLayout();
    hbox->setAlignment(Qt::AlignCenter);

    {
        auto button = new QPushButton("File");
        connect(button, &QPushButton::clicked, button, [this, button]() {
            auto file_menu = new QMenu();

            {
                auto action = new QAction("Open G8 image");
                connect(action, &QAction::triggered, this, &MainBarSingleton::onOpenGrayscaleImageAction);
                file_menu->addAction(action);
            }

            {
                auto action = new QAction("Open RGB image");
                connect(action, &QAction::triggered, this, &MainBarSingleton::onOpenRGBImageAction);
                file_menu->addAction(action);
            }

            file_menu->exec(QCursor::pos());
        });

        hbox->addWidget(button);
    }

    setLayout(hbox);
}

/* static */ MainBarSingleton* MainBarSingleton::sm_instance = nullptr;

MainBarSingleton* MainBarSingleton::getInstance() {
    if (sm_instance == nullptr)
        sm_instance = new MainBarSingleton();
    return sm_instance;
}

void MainBarSingleton::openImage(const std::filesystem::path& path, QImage::Format format) {
    openImage(QString::fromStdWString(path), format);
}

void MainBarSingleton::openImage(const QString& path, QImage::Format format) {
    QImage img(path);
    img.convertTo(format);
    openImage(img);
}

void MainBarSingleton::openImage(const Image& img) {
    auto img_dialog = new ImageDialog(img, this);
    img_dialog->show();
}

void MainBarSingleton::onOpenRGBImageAction() {
    QString path = QFileDialog::getOpenFileName(this);
    if (path.isEmpty())
        return;

    openImage(path, QImage::Format_RGB32);
}

void MainBarSingleton::onOpenGrayscaleImageAction() {
    QString path = QFileDialog::getOpenFileName(this);
    if (path.isEmpty())
        return;

    openImage(path, QImage::Format_Grayscale8);
}