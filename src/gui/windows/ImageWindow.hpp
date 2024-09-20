#pragma once

#include "core/Image.hpp"
#include "gui/windows/ui_ImageWindow.h"
#include "gui/widgets/ImageWithInfoWidget.hpp"

#include <QString>
#include <QWidget>

namespace gui::windows {
class ImageWindow : public QWidget {
    Q_OBJECT
  public:
    ImageWindow(const QString& name, image::Image img);

  private:
    image::Image m_img;
    Ui::ImageWindow m_ui;
    widgets::ImageWithInfoWidget* m_img_widget;

};

} // namespace gui::windows