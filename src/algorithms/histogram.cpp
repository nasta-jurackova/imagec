#include "algorithms/histogram.hpp"
#include "gui/main_bar.hpp"
#include "core/image.hpp"
#include <array>

namespace algorithms {
void histogram_create(Image& img, QString& name) { 
	std::array<std::size_t, 256> hist = {0};
    for (std::size_t col = 0; col < img.size().width; ++col) {
        for (std::size_t row = 0; row < img.size().height; ++row) {
            auto pixel = img.pixel<uint8_t>(Coords(col, row));
            ++hist[pixel];
        }
    }
    std::size_t max = *std::ranges::max_element(hist);
    auto histogram = Image(Size(256, max), ImageType::G8);
    histogram.fillWith(uint8_t(0));
    for (std::size_t h = 0; h < 256; ++h) {
        for (std::size_t i = 0; i < hist[h]; ++i) {
            histogram.setPixel(Coords(h, max - i - 1), uint8_t(255));
        }
    }
    MainBarSingleton::getInstance()->openImage(histogram, name + "_histogram");
}

void histogram_equalize(Image&, QString&) {}

void histogram_match(Image&, QString&) {}
} // namespace algorithms