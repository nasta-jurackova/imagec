#include "core/image.hpp"

#include <stdexcept>

Image::Image(Size size, Type type)
    : m_type(type), m_image(QSize(int(size.width), int(size.height)), qtFormatFromType(type)) {}

Image::Image(QImage img) : m_type(typeFromQtFormat(img.format())), m_image(std::move(img)) {}

QImage Image::toQImage() const { return m_image; }

uint8_t Image::pixel(Coords coords) const {
    assertCorrectType(Type::G8);
    assertCorrectCoords(coords);

    return m_image.pixelColor(int(coords.x), int(coords.y)).black();
}

Color Image::pixelRGB(Coords coords) const {
    assertCorrectType(Type::RGB8);
    assertCorrectCoords(coords);

    auto col = m_image.pixelColor(int(coords.x), int(coords.y));

    return {uint8_t(col.red()), uint8_t(col.green()), uint8_t(col.blue())};
}

void Image::setPixel(Coords coords, uint8_t value) {
    assertCorrectType(Type::G8);
    assertCorrectCoords(coords);

    m_image.setPixelColor(int(coords.x), int(coords.y), QColor(value, value, value));
}

void Image::setPixel(Coords coords, Color color) {
    assertCorrectType(Type::RGB8);
    assertCorrectCoords(coords);

    m_image.setPixelColor(int(coords.x), int(coords.y), QColor(color.r, color.g, color.b));
}

void Image::setPixelRGB(Coords coords, Color color) { setPixel(coords, color); }

Size Image::size() const {
    auto qsize = m_image.size();
    return {std::size_t(qsize.width()), std::size_t(qsize.height())};
}

Image::Type Image::type() const { return m_type; }

void Image::assertCorrectType(Type expected) const {
    if (expected != type())
        throw std::runtime_error("Image type is not correct");
}

void Image::assertCorrectCoords(Coords coords) const {
    if (coords.x >= m_image.width() || coords.y >= m_image.height())
        throw std::runtime_error("Image coords out of range");
}

QImage::Format Image::qtFormatFromType(Type type) {
    switch (type) {
    case Type::G8:
        return QImage::Format_Grayscale8;
    case Type::RGB8:
        return QImage::Format_RGB32;
    }

    return QImage::Format_Invalid;
}

Image::Type Image::typeFromQtFormat(QImage::Format format) {
    switch (format) {
    case QImage::Format_Grayscale8:
        return Type::G8;
    case QImage::Format_RGB32:
        return Type::RGB8;
    }

    throw std::runtime_error("Invalid format");
}
