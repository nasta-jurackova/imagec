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

    auto operator<=>(const Coords&) const = default;
};

struct Offset {
    Offset(int dx, int dy)
        : dx(dx),
          dy(dy) {}

    int dx;
    int dy;
    bool operator==(const Offset&) const = default;
};
inline Coords& operator+=(Coords& coords, const Offset& off) {
    coords.x += off.dx;
    coords.y += off.dy;
    return coords;
}
inline Coords operator+(const Coords& coords, const Offset& off) {
    auto cpy = coords;
    cpy += off;
    return cpy;
}

struct Color {
    Color(uint8_t r, uint8_t g, uint8_t b)
        : r(r),
          g(g),
          b(b) {}
    bool operator==(const Color&) const = default;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
enum class ImageType { BINARY = 0, G8, RGB8, DOUBLE, COMPLEX };
using Pixel = std::variant<bool, uint8_t, Color, double, std::complex<double>>;

template <typename T>
concept PixelType = requires(T) { utils::traits::any_of_variant_v<T, Pixel>; };
} // namespace image