#pragma once

#include <QImage>
#include <cstddef>

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

class Image {
  public:
    enum class Type { G8, RGB8 };

    Image(Size size, Type type);
    Image(QImage img);

    QImage toQImage() const;

    uint8_t pixel(Coords coords) const;
    Color pixelRGB(Coords coords) const;
    void setPixel(Coords coords, uint8_t value);
    void setPixel(Coords coords, Color color);
    void setPixelRGB(Coords coords, Color color);

    Size size() const;
    Type type() const;

  private:
    void assertCorrectType(Type expected) const;
    void assertCorrectCoords(Coords coords) const;
    static QImage::Format qtFormatFromType(Type type);
    static Type typeFromQtFormat(QImage::Format);

    Type m_type;
    QImage m_image;
};