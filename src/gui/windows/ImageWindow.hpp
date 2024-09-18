#pragma once

#include "core/Image.hpp"
// #include "gui/windows/ui_ImageWindow.h"

#include <QString>
#include <QWidget>

namespace gui::windows {
class ImageWindow : public QWidget {
    Q_OBJECT
  public:
    ImageWindow(const QString& name, image::Image img);

  private:
    image::Image m_img;
};

} // namespace gui::windows