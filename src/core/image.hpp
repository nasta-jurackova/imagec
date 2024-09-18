#pragma once

#include "core/image_types.hpp"

#include <memory>

namespace image {
namespace details {
class ImageData;
}

class Image;

template <PixelType T>
class TypedImage {
  public:
    explicit(false) TypedImage(Image img)
        : m_image(std::move(img)) {
        if (m_image.type() != static_cast<ImageType>(utils::traits::idx_of_variant_v<T, Pixel>))
            throw std::runtime_error("Image is in incorrect format");
    }

    void setPixel(Coords coords, T pixel) { m_image.setPixel(coords, pixel); }
    void fillWith(T pixel) { m_image.fillWith(pixel); }
    [[nodiscard]] T pixel(Coords coords) const { return std::get<T>(m_image.pixel(coords)); }
    [[nodiscard]] Size size() const { return m_image.size(); }
    [[nodiscard]] ImageType type() const { return m_image.type(); }
    [[nodiscard]] TypedImage clone() const { return TypedImage(m_image.clone()); }

  private:
    Image m_image;
};

class Image {
  public:
    Image(Size size, ImageType type);

    void setPixel(Coords coords, Pixel pixel);
    void fillWith(Pixel pixel);
    [[nodiscard]] Pixel pixel(Coords coords) const;
    [[nodiscard]] Size size() const;
    [[nodiscard]] ImageType type() const;
    [[nodiscard]] Image clone() const;
    template <PixelType T>
    TypedImage<T> as_typed() {
        return TypedImage<T>(*this);
    }

  private:
    std::size_t linearizeIndex(Coords coords) const;

    void assertCorrectType(Pixel pixel) const;
    void assertCorrectCoords(Coords coords) const;

    std::shared_ptr<details::ImageData> m_data;
};

} // namespace image