#include "algorithms/image_modifiers/Save.hpp"

#include "gui/utils/image.hpp"
#include <QFileDialog>

namespace algorithms {
QString img_modifiers::SaveImage::getName() const { return "Save image"; }
bool img_modifiers::SaveImage::isHighlighted() const { return false; }
bool img_modifiers::SaveImage::isEnabled() const { return true; }

bool img_modifiers::SaveImage::isTypeSupported(image::ImageType type) const {
    switch (type) {
    case image::ImageType::BINARY:
    case image::ImageType::G8:
    case image::ImageType::RGB8:
        return true;
    default:
        return false;
    }
}

void img_modifiers::SaveImage::apply(QString&, image::Image& image) {
    QString dest = QFileDialog::getSaveFileName(nullptr, "Select save destination", "", "Image (*.png)");
    if (dest.isEmpty())
        return;

    if (!gui::utils::image::visualizationFromImage(image).save(dest))
        throw std::runtime_error("Image save failed!");
}
} // namespace algorithms