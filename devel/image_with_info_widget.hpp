#pragma once

#include "zoomable_image_widget.hpp"

#include <QWidget>

class ImageWithInfoWidget : public QWidget {
    Q_OBJECT
  public:
    explicit ImageWithInfoWidget(QWidget* parent = nullptr);

  private:
    void updateInfoLabel(const QPoint& coords, const QString& color);

    ZoomableImageWidget* m_img_wdg;
    QLabel* m_info_label;
};