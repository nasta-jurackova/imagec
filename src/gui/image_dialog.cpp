#include "gui/image_dialog.hpp"
#include "algorithms/duplicate.hpp"
#include "algorithms/save.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QResizeEvent>
#include <QVBoxLayout>

ImageDialog::ImageDialog(Image img, const QString& name, QWidget* parent /* = nullptr */)
    : QDialog(parent), m_img(std::move(img)), m_name(name) {
    setWindowTitle(m_name);

    auto main_vbox = new QVBoxLayout();
    main_vbox->setAlignment(Qt::AlignCenter);

    // menu hbox
    {
        auto menu_hbox = new QHBoxLayout();

        {
            auto button = new QPushButton("File");
            connect(button, &QPushButton::clicked, button, [this, button]() {
                auto file_menu = new QMenu();
                addOption(file_menu, "Save image", algorithms::save_image);
                addOption(file_menu, "Duplicate", algorithms::duplicate);

                file_menu->exec(QCursor::pos());
            });

            menu_hbox->addWidget(button);
        }
        menu_hbox->addStretch();

        main_vbox->addLayout(menu_hbox);
    }

    // image label
    {
        m_img_label = new ImageLabel();
        m_img_label->setAlignment(Qt::AlignCenter);
        main_vbox->addWidget(m_img_label);
        updateImageLabel();
    }

    setLayout(main_vbox);
}

void ImageDialog::updateImageLabel() const {
    m_img_label->setPixmap(
        QPixmap::fromImage(m_img.toQImage()).scaled(QSize(512, 512), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ImageDialog::addOption(QMenu* menu, const QString& name, std::function<void(Image&, QString&)> f) {
    auto action = new QAction(name);
    connect(action, &QAction::triggered, this, [this, _f = std::move(f)]() {
        try {
            _f(m_img, m_name);
        } catch (const std::runtime_error& err) {
            QMessageBox::critical(this, "Error", err.what());
        }
        setWindowTitle(m_name);
        updateImageLabel();
    });
    menu->addAction(action);
}
