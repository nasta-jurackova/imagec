#include "core/image.hpp"

#include <stdexcept>

std::string stringFromPixel(Pixel pix) {
    class Visitor {
      public:
        std::string operator()(uint8_t val) { return std::to_string(val); }
        std::string operator()(double val) { return std::to_string(val); }
        std::string operator()(Color val) { return std::format("(r: {}, g: {}, b: {})", val.r, val.g, val.b); }
    };

    return std::visit(Visitor{}, pix);
}

Image::Image(Size size, ImageType type)
    : m_type(type),
      m_size(size),
      m_image(size.width * size.height) {}

Image::Image(QImage img)
    : Image({std::size_t(img.width()), std::size_t(img.height())}, typeFromQtFormat(img.format())) {

    for (std::size_t x = 0; x < m_size.width; ++x)
        for (std::size_t y = 0; y < m_size.height; ++y) {
            std::size_t idx = linearizeIndex(Coords(x, y));
            switch (m_type) {
            case ImageType::G8:
                m_image[idx] = uint8_t(qGray(img.pixel(int(x), int(y))));
                break;
            case ImageType::RGB8: {
                QRgb rgb = img.pixel(int(x), int(y));
                m_image[idx] = Color{uint8_t(qRed(rgb)), uint8_t(qGreen(rgb)), uint8_t(qBlue(rgb))};
            } break;
            case ImageType::DOUBLE:
                break;
            }
        }
}

QImage Image::toQImage() const {
    QImage img(int(m_size.width), int(m_size.height), qtFormatFromType(type()));

    double min = 0, max = 0;
    if (type() == ImageType::DOUBLE) {
        bool first = true;
        for (const auto& p : m_image) {
            double value = std::get<double>(p);
            if (first) {
                min = value;
                max = value;
                first = false;
                continue;
            }
            min = std::min(value, min);
            max = std::max(value, max);
        }
    }

    for (std::size_t x = 0; x < m_size.width; ++x)
        for (std::size_t y = 0; y < m_size.height; ++y) {
            std::size_t idx = linearizeIndex(Coords(x, y));
            QColor color;

            switch (m_type) {
            case ImageType::G8: {
                uint8_t val = std::get<uint8_t>(m_image[idx]);
                color = QColor(val, val, val);
            } break;
            case ImageType::RGB8: {
                Color val = std::get<Color>(m_image[idx]);
                color = QColor(val.r, val.g, val.b);
            } break;
            case ImageType::DOUBLE: {
                double val = std::get<double>(m_image[idx]);
                uint8_t g8_val = uint8_t((val - min) * (255.0 / (max - min)));
                color = QColor(g8_val, g8_val, g8_val);
            } break;
            }

            img.setPixelColor(int(x), int(y), color);
        }

    return img;
}
Pixel Image::pixel(Coords coords) const { return m_image[linearizeIndex(coords)]; }

void Image::setPixel(Coords coords, Pixel pixel) {
    assertCorrectCoords(coords);
    assertCorrectType(static_cast<ImageType>(pixel.index()));
    m_image[linearizeIndex(coords)] = pixel;
}

void Image::fillWith(Pixel pixel) {
    assertCorrectType(static_cast<ImageType>(pixel.index()));
    for (auto& p : m_image)
        p = pixel;
}

Size Image::size() const { return m_size; }
ImageType Image::type() const { return m_type; }
std::size_t Image::linearizeIndex(Coords coords) const { return coords.y * m_size.width + coords.x; }

void Image::assertCorrectType(ImageType expected) const {
    if (expected != type())
        throw std::runtime_error("Image type is not correct");
}

void Image::assertCorrectCoords(Coords coords) const {
    if (coords.x >= m_size.width || coords.y >= m_size.height)
        throw std::runtime_error(std::format("Image coords out of range; trying to access {}x{} in image of size {}x{}",
                                             coords.x,
                                             coords.y,
                                             m_size.width,
                                             m_size.height));
}

QImage::Format Image::qtFormatFromType(ImageType type) {
    switch (type) {
    case ImageType::G8:
    case ImageType::DOUBLE:
        return QImage::Format_Grayscale8;
    case ImageType::RGB8:
        return QImage::Format_RGB32;
    }

    return QImage::Format_Invalid;
}

ImageType Image::typeFromQtFormat(QImage::Format format) {
    switch (format) {
    case QImage::Format_Grayscale8:
        return ImageType::G8;
    case QImage::Format_RGB32:
        return ImageType::RGB8;
    }

    throw std::runtime_error("Invalid format");
}
