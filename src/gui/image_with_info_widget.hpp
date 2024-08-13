#pragma once

#include "gui/zoomable_image_widget.hpp"
#include "core/image.hpp"

#include <QWidget>

class ImageWithInfoWidget : public QWidget {
    Q_OBJECT
  public:
    ImageWithInfoWidget(const Image& img, QWidget* parent = nullptr);

    void setImage(const Image& img);

  private:
    void updateInfoLabel(const QPoint& coords, const QString& color);

    ZoomableImageWidget* m_img_wdg;
    QLabel* m_info_label;
    Image m_img;
};