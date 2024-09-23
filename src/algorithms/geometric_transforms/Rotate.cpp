#include "algorithms/geometric_transforms/Rotate.hpp"

using namespace image;

namespace algorithms::geometric_trans {
std::size_t Rotate::partCount() const { return 3; }
QString Rotate::getName(std::size_t part) const {
    switch (part) {
    case 0:
        return "Left";
    case 1:
        return "Right";
    case 2:
        return "180";
    }
    std::unreachable();
}
bool Rotate::isTypeSupported(std::size_t, ImageType) const { return true; }

void Rotate::apply(std::size_t part, QString&, Image& image) {
    switch (part) {
    case 0:
        left(image);
        break;
    case 1:
        right(image);
        break;
    case 2:
        r180(image);
    }
}

void Rotate::left(Image& img) {
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

void Rotate::right(Image& img) {
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

void Rotate::r180(Image& img) {
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
} // namespace algorithms::geometric_trans
