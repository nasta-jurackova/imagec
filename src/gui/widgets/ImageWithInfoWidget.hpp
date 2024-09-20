#pragma once

#include "core/image.hpp"
#include "gui/widgets/ZoomableImageWidget.hpp"

#include <QWidget>

namespace gui::widgets {
class ImageWithInfoWidget : public QWidget {
    Q_OBJECT
  public:
    ImageWithInfoWidget(image::Image img, QWidget* parent = nullptr);

    void setImage(image::Image img);

  private:
    void updateInfoLabel(const QPoint& coords, const QString& color);

    ZoomableImageWidget* m_img_wdg;
    QLabel* m_info_label;
    image::Image m_img;
};
} // namespace gui::widgets