#include "algorithms/image_modifiers/Split.hpp"

#include "gui/AppManagerSingleton.hpp"

using namespace image;

namespace algorithms::img_modifiers {
QString SplitImage::getName() const { return "Split RGB"; }
bool SplitImage::isTypeSupported(ImageType type) const { return type == ImageType::RGB8; }

void SplitImage::apply(QString& name, Image& image) {
    auto [r, g, b] = splitRGB(image);

    gui::AppManagerSingleton::getInstance()->openImage(r, name + "_r");
    gui::AppManagerSingleton::getInstance()->openImage(g, name + "_g");
    gui::AppManagerSingleton::getInstance()->openImage(b, name + "_b");
}

/* static */ std::tuple<Image, Image, Image> SplitImage::splitRGB(const Image& image) {
    Image img_r(image.size(), ImageType::G8);
    Image img_g(image.size(), ImageType::G8);
    Image img_b(image.size(), ImageType::G8);

    auto typed = image.as_typed<Color>();

    for (std::size_t col = 0; col < image.size().width; ++col) {
        for (std::size_t row = 0; row < image.size().height; ++row) {
            Color pixel = typed.pixel(Coords(col, row));
            img_r.setPixel(Coords(col, row), pixel.r);
            img_g.setPixel(Coords(col, row), pixel.g);
            img_b.setPixel(Coords(col, row), pixel.b);
        }
    }

    return {img_r, img_g, img_b};
}
} // namespace algorithms::img_modifiers