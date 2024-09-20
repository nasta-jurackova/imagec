#pragma once

#include "core/Image.hpp"
#include "gui/windows/ui_ImageWindow.h"
#include "gui/widgets/ImageWithInfoWidget.hpp"
#include "algorithms/IAlgorithm.hpp"

#include <QString>
#include <QWidget>

namespace gui::windows {
class ImageWindow : public QWidget {
    Q_OBJECT
  public:
    ImageWindow(const QString& name, image::Image img);

  private:
    void addToMenu(algorithms::IAlgorithm* algo, QMenu* menu);
    QMenu* buildMenu(const std::map<QString, std::vector<std::unique_ptr<algorithms::IAlgorithm>>>& algos);

    std::map<QString, std::vector<std::unique_ptr<algorithms::IAlgorithm>>> m_image_algos;
    std::map<QString, std::vector<std::unique_ptr<algorithms::IAlgorithm>>> m_trans_algos;
    std::map<QString, std::vector<std::unique_ptr<algorithms::IAlgorithm>>> m_stats_algos;

    image::Image m_img;
    Ui::ImageWindow m_ui;
    widgets::ImageWithInfoWidget* m_img_widget;

};

} // namespace gui::windows