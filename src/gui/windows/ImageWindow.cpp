#include "gui/windows/ImageWindow.hpp"

#include "gui/widgets/ImageWithInfoWidget.hpp"

namespace gui::windows {
ImageWindow::ImageWindow(const QString& name, image::Image img)
    : m_img(std::move(img)),
      m_img_widget(new widgets::ImageWithInfoWidget(m_img)) {
    m_ui.setupUi(this);

    setWindowTitle(name);
    m_ui.verticalLayout->addWidget(m_img_widget);
}
} // namespace gui::windows