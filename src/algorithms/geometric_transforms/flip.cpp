#include "algorithms/geometric_transforms/Flip.hpp"

using namespace image;

namespace algorithms::geometric_trans {

std::size_t Flip::partCount() const { return 2; }
QString Flip::getName(std::size_t part) const {
    switch (part) {
    case 0:
        return "Horizontal";
    case 1:
        return "Vertical";
    }
    std::unreachable();
}

bool Flip::isTypeSupported(std::size_t, ImageType) const { return true; }
void Flip::apply(std::size_t part, QString&, Image& image) {
    switch (part) {
    case 0:
        horizontal(image);
        break;
    case 1:
        vertical(image);
        break;
    }
}

void Flip::horizontal(Image& img) {
    std::size_t cols = img.size().width;
    std::size_t rows = img.size().height;
    for (std::size_t col = 0; col < cols / 2; ++col) {
        for (std::size_t row = 0; row < rows; ++row) {
            auto coords_l = Coords(col, row);
            auto pixel_l = img.pixel(coords_l);
            auto coords_r = Coords(cols - col - 1, row);
            auto pixel_r = img.pixel(coords_r);
            img.setPixel(coords_l, pixel_r);
            img.setPixel(coords_r, pixel_l);
        }
    }
}

void Flip::vertical(Image& img) {
    std::size_t cols = img.size().width;
    std::size_t rows = img.size().height;
    for (std::size_t col = 0; col < cols; ++col) {
        for (std::size_t row = 0; row < rows / 2; ++row) {
            Coords coords_l(col, row);
            auto pixel_l = img.pixel(coords_l);
            auto coords_r = Coords(col, rows - row - 1);
            auto pixel_r = img.pixel(coords_r);
            img.setPixel(coords_l, pixel_r);
            img.setPixel(coords_r, pixel_l);
        }
    }
}
} // namespace algorithms::geometric_trans
