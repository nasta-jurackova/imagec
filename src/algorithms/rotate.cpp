#include "algorithms/rotate.hpp"

#include "core/image.hpp"
#include "gui/main_bar.hpp"

namespace algorithms
{
void rotate_l(Image& img, QString&) { 
    std::size_t cols = img.size().width;
    std::size_t rows = img.size().height;
    Image new_image(Size(rows, cols), img.type());
    for (std::size_t col = 0; col < rows; ++col) {
        for (std::size_t row = 0; row < cols; ++row) {
            new_image.setPixel(Coords(col, row), img.pixel(Coords(cols - row - 1, col)));
        }
    }
    img = new_image;
}

void rotate_r(Image& img, QString&) {
    std::size_t cols = img.size().width;
    std::size_t rows = img.size().height;
    Image new_image(Size(rows, cols), img.type());
    for (std::size_t col = 0; col < rows; ++col) {
        for (std::size_t row = 0; row < cols; ++row) {
            new_image.setPixel(Coords(col, row), img.pixel(Coords(row, rows - col - 1)));
        }
    }
    img = new_image;
}

void rotate_180(Image& img, QString&) {
    std::size_t cols = img.size().width;
    std::size_t rows = img.size().height;
    Image new_image(Size(cols, rows), img.type());
    for (std::size_t col = 0; col < cols; ++col) {
        for (std::size_t row = 0; row < rows; ++row) {
            new_image.setPixel(Coords(col, row), img.pixel(Coords(cols - col - 1, rows - row - 1)));
        }
    }
    img = new_image;
}
} // namespace algorithms
