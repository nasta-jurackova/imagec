#include "algorithms/flip.hpp"

namespace algorithms
{
void flip_h(Image& img, QString&) {
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

void flip_v(Image& img, QString&) {
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
} // namespace algorithms
