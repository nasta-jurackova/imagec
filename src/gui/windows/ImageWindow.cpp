#include "gui/windows/ImageWindow.hpp"

namespace gui::windows {
ImageWindow::ImageWindow(const QString& name, image::Image img)
    : m_img(std::move(img)) {
    setWindowTitle(name);
}
} // namespace gui::windows