#include "gui/image_dialog.hpp"

#include "algorithms/duplicate.hpp"
#include "algorithms/save.hpp"
#include "algorithms/change_name.hpp"
#include "algorithms/flip.hpp"
#include "algorithms/rotate.hpp"
#include "algorithms/split.hpp"
#include "algorithms/brightness.hpp"
#include "algorithms/contrast.hpp"
#include "algorithms/histogram.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QResizeEvent>
#include <QVBoxLayout>

namespace {
void algo_noop(Image&, QString&) {}
} // namespace

ImageDialog::ImageDialog(Image img, const QString& name, QWidget* parent /* = nullptr */)
    : QDialog(parent),
      m_img(std::move(img)),
      m_name(name) {
    setWindowTitle(m_name);

    auto main_vbox = new QVBoxLayout();
    main_vbox->setAlignment(Qt::AlignCenter);

    // menu hbox
    {
        auto menu_hbox = new QHBoxLayout();

        {
            auto button = new QPushButton("File");
            connect(button, &QPushButton::clicked, button, [this, button]() {
                auto menu = new QMenu();
                addOption(menu, "Save image", algorithms::save_image);
                addOption(menu, "Duplicate", algorithms::duplicate);
                addOption(menu, "Change name", algorithms::change_name);

                menu->exec(QCursor::pos());
            });

            menu_hbox->addWidget(button);
        }
        {
            auto button = new QPushButton("Transformations");
            connect(button, &QPushButton::clicked, button, [this, button]() {
                auto main_menu = new QMenu();
                {
                    auto menu = main_menu->addMenu("Rotate");
                    addOption(menu, "Right", algorithms::rotate_r);
                    addOption(menu, "Left", algorithms::rotate_l);
                    addOption(menu, "180 degrees", algorithms::rotate_180);
                }
                {
                    auto menu = main_menu->addMenu("Flip");
                    addOption(menu, "Horizontal", algorithms::flip_h);
                    addOption(menu, "Vertical", algorithms::flip_v);
                }

                main_menu->exec(QCursor::pos());
            });

            menu_hbox->addWidget(button);
        }
        {
            auto button = new QPushButton("Intensities");
            connect(button, &QPushButton::clicked, button, [this, button]() {
                auto main_menu = new QMenu();
                addOption(main_menu, "Split RGB", algorithms::split_rgb);
                {
                    auto menu = main_menu->addMenu("Brightness");
                    addOption(menu, "+10", algorithms::brightness_add_10);
                    addOption(menu, "-10", algorithms::brightness_cut_10);
                    addOption(menu, "By custom value", algorithms::brightness_by_custom);
                }
                {
                    auto menu = main_menu->addMenu("Contrast");
                    addOption(menu, "+50 %", algorithms::contrast_add_50);
                    addOption(menu, "-50 %", algorithms::contrast_cut_50);
                    addOption(menu, "By custom value", algorithms::contrast_by_custom);
                    addOption(menu, "Linear stretch", algorithms::linear_stretch);
                }
                {
                    auto menu = main_menu->addMenu("Histrogram");
                    addOption(menu, "Create", algorithms::histogram_create);
                    addOption(menu, "Normalize", algorithms::histogram_normalize);

                    auto match_menu = menu->addMenu("Match");
                    addOption(match_menu, "Select source image (first)", algo_noop);
                    addOption(match_menu, "Select source histogram (first)", algo_noop);
                    addOption(match_menu, "Compute (second)", algo_noop);
                }


                main_menu->exec(QCursor::pos());
            });

            menu_hbox->addWidget(button);
        }
        menu_hbox->addStretch();
        main_vbox->addLayout(menu_hbox);
    }

    // image label
    {
        m_img_label = new ImageWithInfoWidget(m_img);
        main_vbox->addWidget(m_img_label);
    }

    setLayout(main_vbox);
}

void ImageDialog::updateImageLabel() const {
    m_img_label->setImage(m_img);
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
