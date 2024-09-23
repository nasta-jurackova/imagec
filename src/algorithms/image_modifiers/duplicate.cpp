#include "algorithms/image_modifiers/Duplicate.hpp"

#include "gui/AppManagerSingleton.hpp"

using namespace image;

namespace algorithms::img_modifiers {

QString Duplicate::getName() const { return "Duplicate"; }
bool Duplicate::isTypeSupported(image::ImageType) const { return true; }
void Duplicate::apply(QString& name, Image& image) {
    gui::AppManagerSingleton::getInstance()->openImage(image.clone(), name + " dup");
}
} // namespace algorithms::img_modifiers