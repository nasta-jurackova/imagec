#include "algorithms/split.hpp"

#include "core/image.hpp"
#include "gui/main_bar.hpp"

namespace algorithms {
void split_rgb(Image& img, QString& name){
    Image img_r(img.size(), ImageType::G8);
    Image img_g(img.size(), ImageType::G8);
    Image img_b(img.size(), ImageType::G8);

    for (std::size_t col = 0; col < img.size().width; ++col){
        for (std::size_t row = 0; row < img.size().height; ++row) {
            Color pixel = img.pixel<Color>(Coords(col, row));
            img_r.setPixel(Coords(col, row), pixel.r);
            img_g.setPixel(Coords(col, row), pixel.g);
            img_b.setPixel(Coords(col, row), pixel.b);
        }
    }

    MainBarSingleton::getInstance()->openImage(img_r, name + " _r");
    MainBarSingleton::getInstance()->openImage(img_g, name + " _g");
    MainBarSingleton::getInstance()->openImage(img_b, name + " _b");
}
} // namespace algorithms