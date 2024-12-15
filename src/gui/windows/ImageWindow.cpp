#include "gui/windows/ImageWindow.hpp"

#include "gui/widgets/ImageWithInfoWidget.hpp"

#include "algorithms/image_modifiers/ChangeName.hpp"
#include "algorithms/image_modifiers/Duplicate.hpp"
#include "algorithms/image_modifiers/Save.hpp"
#include "algorithms/image_modifiers/Split.hpp"

#include "algorithms/geometric_transforms/Flip.hpp"
#include "algorithms/geometric_transforms/Rotate.hpp"

#include "algorithms/point_transforms/Brightness.hpp"
#include "algorithms/point_transforms/Contrast.hpp"

#include "algorithms/statistics/Histogram.hpp"
#include "algorithms/statistics/FilledAreaInfo.hpp"

#include <QMenu>

namespace gui::windows {
ImageWindow::ImageWindow(const QString& name, image::Image img)
    : m_img(std::move(img)),
      m_img_widget(new widgets::ImageWithInfoWidget(m_img)) {
    m_ui.setupUi(this);

    setWindowTitle(name);
    m_ui.verticalLayout->addWidget(m_img_widget);

    connect(m_ui.image_button, &QPushButton::clicked, this, [this]() {
        auto menu = buildMenu(m_image_algos);
        menu->exec(QCursor::pos());
    });
    connect(m_ui.transform_button, &QPushButton::clicked, this, [this]() {
        auto point_trans = buildMenu(m_point_trans_algos);
        point_trans->setTitle("Point");

        auto geom_trans = buildMenu(m_geom_trans_algos);
        geom_trans->setTitle("Geometric");

        auto menu = new QMenu();
        menu->addMenu(point_trans);
        menu->addMenu(geom_trans);
        menu->exec(QCursor::pos());
    });
    connect(m_ui.statistics_button, &QPushButton::clicked, this, [this]() {
        auto menu = buildMenu(m_stats_algos);
        menu->exec(QCursor::pos());
    });

    m_image_algos[""].push_back(std::make_unique<algorithms::img_modifiers::Duplicate>());
    m_image_algos[""].push_back(std::make_unique<algorithms::img_modifiers::ChangeName>());
    m_image_algos[""].push_back(std::make_unique<algorithms::img_modifiers::SaveImage>());
    m_image_algos[""].push_back(std::make_unique<algorithms::img_modifiers::SplitImage>());

    m_point_trans_algos["Brightness"].push_back(std::make_unique<algorithms::point_transforms::Brightness>());
    m_point_trans_algos["Contrast"].push_back(std::make_unique<algorithms::point_transforms::Contrast>());

    m_geom_trans_algos["Flip"].push_back(std::make_unique<algorithms::geometric_trans::Flip>());
    m_geom_trans_algos["Rotate"].push_back(std::make_unique<algorithms::geometric_trans::Rotate>());

    m_stats_algos[""].push_back(std::make_unique<algorithms::statistics::FilledAreaInfo>());
    m_stats_algos["Histogram"].push_back(std::make_unique<algorithms::statistics::Histogram>());
}

void ImageWindow::addToMenu(algorithms::IAlgorithm* algo, QMenu* menu) {
    std::size_t count = algo->partCount();
    for (std::size_t i = 0; i < count; ++i) {
        auto action = new QAction(algo->getName(i));
        bool enabled = true;
        enabled = enabled && algo->isEnabled(i);
        enabled = enabled && algo->isTypeSupported(i, m_img.type());
        action->setEnabled(enabled);
        if (algo->isHighlighted(i)) {
            auto f = action->font();
            f.setItalic(true);
            action->setFont(f);
        }
        connect(action, &QAction::triggered, this, [algo, this, i]() {
            QString title = windowTitle();
            algo->apply(i, title, m_img);
            setWindowTitle(title);
            m_img_widget->setImage(m_img);
        });
        menu->addAction(action);
    }
}

QMenu* ImageWindow::buildMenu(const std::map<QString, std::vector<std::unique_ptr<algorithms::IAlgorithm>>>& algos) {
    QMenu* menu = new QMenu();

    for (auto& [group, algs] : algos) {
        QMenu* submenu = menu;
        if (group != "")
            submenu = menu->addMenu(group);
        for (auto& alg : algs) {
            addToMenu(alg.get(), submenu);
        }
    }

    return menu;
}

} // namespace gui::windows