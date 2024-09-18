#include "core/image.hpp"

#include <stdexcept>
#include <vector>

namespace image {
namespace details {
class ImageData {
  public:
    ImageData(ImageType type, Size size)
        : type(type),
          size(size),
          image(size.width * size.height) {}
    ImageType type;
    Size size;
    std::vector<Pixel> image;
};
} // namespace details

Image::Image(Size size, ImageType type) { m_data = std::make_shared<details::ImageData>(type, size); }

Pixel Image::pixel(Coords coords) const { return m_data->image[linearizeIndex(coords)]; }

void Image::setPixel(Coords coords, Pixel pixel) {
    assertCorrectCoords(coords);
    assertCorrectType(pixel);
    m_data->image[linearizeIndex(coords)] = pixel;
}

void Image::fillWith(Pixel pixel) {
    assertCorrectType(pixel);
    for (auto& p : m_data->image)
        p = pixel;
}

Size Image::size() const { return m_data->size; }
ImageType Image::type() const { return m_data->type; }

Image Image::clone() const {
    auto cpy = *this;
    *cpy.m_data = *m_data;
    return cpy;
}

std::size_t Image::linearizeIndex(Coords coords) const { return coords.y * m_data->size.width + coords.x; }

void Image::assertCorrectType(Pixel pixel) const {
    if (pixel.index() != static_cast<int>(m_data->type))
        throw std::runtime_error("Image type is not correct");
}

void Image::assertCorrectCoords(Coords coords) const {
    if (coords.x >= m_data->size.width || coords.y >= m_data->size.height)
        throw std::runtime_error(std::format("Image coords out of range; trying to access {}x{} in image of size {}x{}",
                                             coords.x,
                                             coords.y,
                                             m_data->size.width,
                                             m_data->size.height));
}
} // namespace image