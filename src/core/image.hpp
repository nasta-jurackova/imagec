#pragma once

#include "core/utils.hpp"

#include <QImage>
#include <cstddef>
#include <format>
#include <tuple>
#include <type_traits>
#include <variant>

class ImageDialog;

struct Size {
    std::size_t width;
    std::size_t height;
};

struct Coords {
    std::size_t x;
    std::size_t y;
};

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
enum class ImageType { G8 = 0, RGB8, DOUBLE };
using Pixel = std::variant<uint8_t, Color, double>;

std::string stringFromPixel(Pixel pix);

class Image {
  public:
    Image(Size size, ImageType type);
    Image(QImage img);

    QImage toQImage() const;

    Pixel pixel(Coords coords) const;
    template <typename T>
    T pixel(Coords coords) const {
        assertCorrectCoords(coords);
        assertCorrectType(static_cast<ImageType>(utils::idx_of_variant_v<T, Pixel>));

        return std::get<T>(m_image[linearizeIndex(coords)]);
    }

    template <ImageType type>
    std::tuple_element_t<static_cast<std::size_t>(type), Pixel> pixel(Coords coords) const {
        return pixel<std::tuple_element_t<static_cast<std::size_t>(type), Pixel>>(coords);
    }

    void setPixel(Coords coords, Pixel pixel);
    void fillWith(Pixel pixel);

    Size size() const;
    ImageType type() const;

  private:
    std::size_t linearizeIndex(Coords coords) const;

    void assertCorrectType(ImageType expected) const;
    void assertCorrectCoords(Coords coords) const;
    static QImage::Format qtFormatFromType(ImageType type);
    static ImageType typeFromQtFormat(QImage::Format);

    ImageType m_type;
    Size m_size;
    std::vector<Pixel> m_image;
};