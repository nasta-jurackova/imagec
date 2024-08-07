#include "gui/image_dialog.hpp"
#include "algorithms/save.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QResizeEvent>
#include <QVBoxLayout>

ImageDialog::ImageDialog(Image img, QWidget* parent /* = nullptr */) : m_img(std::move(img)), QDialog(parent) {
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

void ImageDialog::addOption(QMenu* menu, const QString& name, std::function<void(Image&)> f) {
    auto action = new QAction(name);
    connect(action, &QAction::triggered, this, [this, _f = std::move(f)]() {
        _f(m_img);
        updateImageLabel();
    });
    menu->addAction(action);
}
