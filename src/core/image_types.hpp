#pragma once

#include "core/utils/traits.hpp"

#include <complex>
#include <cstddef>
#include <variant>

namespace image {

struct Size {
    Size(std::size_t width, std::size_t height)
        : width(width),
          height(height) {}

    bool operator==(const Size&) const = default;

    std::size_t width;
    std::size_t height;
};

struct Coords {
    Coords(std::size_t x, std::size_t y)
        : x(x),
          y(y) {}
    std::size_t x;
    std::size_t y;
};

struct Color {
    Color(uint8_t r, uint8_t g, uint8_t b)
        : r(r),
          g(g),
          b(b) {}
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
enum class ImageType { BINARY = 0, G8, RGB8, DOUBLE, COMPLEX };
using Pixel = std::variant<bool, uint8_t, Color, double, std::complex<double>>;

template <typename T>
concept PixelType = requires(T) { utils::traits::any_of_variant_v<T, Pixel>; };
} // namespace image