#include "gui/utils/image.hpp"
#include "core/utils/traits.hpp"
#include "image.hpp"

namespace gui::utils::image {
namespace details {
template <::image::ImageType type>
::image::Image imageFromQtHelp(const QImage& qimg) {
    ::image::Image img(::image::Size(qimg.width(), qimg.height()), type);

    for (std::size_t x = 0; x < img.size().width; ++x)
        for (std::size_t y = 0; y < img.size().height; ++y) {
            switch (type) {
            case ::image::ImageType::G8:
                img.setPixel(::image::Coords(x, y), uint8_t(qGray(qimg.pixel(int(x), int(y)))));
                break;
            case ::image::ImageType::RGB8: {
                QRgb rgb = qimg.pixel(int(x), int(y));
                img.setPixel(::image::Coords(x, y),
                             ::image::Color{uint8_t(qRed(rgb)), uint8_t(qGreen(rgb)), uint8_t(qBlue(rgb))});
            } break;
            default:
                throw std::runtime_error("Unsupported image format");
            }
        }

    return img;
}

} // namespace details

::image::Image imageFromQt(const QImage& img) {
    if (img.format() == QImage::Format_Grayscale8)
        return details::imageFromQtHelp<::image::ImageType::G8>(img);
    if (img.format() == QImage::Format_RGB32)
        return details::imageFromQtHelp<::image::ImageType::RGB8>(img);

    throw std::runtime_error("Unsupported image format");
}

std::string stringFromPixel(::image::Pixel& pix) {
    class Visitor {
      public:
        std::string operator()(bool val) const { return val ? "1" : "0"; }
        std::string operator()(uint8_t val) const { return std::to_string(val); }
        std::string operator()(double val) const { return std::to_string(val); }
        std::string operator()(std::complex<double> val) const {
            return std::format("(r: {}, i: {})", val.real(), val.imag());
        }
        std::string operator()(::image::Color val) const {
            return std::format("(r: {}, g: {}, b: {})", val.r, val.g, val.b);
        }
    };

    return std::visit(Visitor{}, pix);
}

QImage visualizationFromImage(const ::image::Image& img) {
    QImage qimg(int(img.size().width), int(img.size().height), QImage::Format_RGB32);

    double min, max;
    bool first = false;
    for (std::size_t x = 0; x < img.size().width; ++x)
        for (std::size_t y = 0; y < img.size().height; ++y)
            std::visit(
                [&min, &max, &first]<typename T>(T x) {
                    if constexpr (std::is_same_v<T, double>) {
                        if (first) {
                            min = x;
                            max = x;
                            first = false;
                        } else {
                            min = std::min(min, x);
                            max = std::max(max, x);
                        }
                    }
                    if constexpr (std::is_same_v<T, std::complex<double>>) {
                        double val = std::abs(x);
                        if (first) {
                            min = val;
                            max = val;
                            first = false;
                        } else {
                            min = std::min(min, val);
                            max = std::max(max, val);
                        }
                    }
                },
                img.pixel(::image::Coords(x, y)));

    class ToRGBVisitor {
    public:
        ToRGBVisitor(double min, double max) : m_min(min), m_max(max) {}
        QColor operator()(bool val) const { return val ? QColorConstants::Black: QColorConstants::White; }
        QColor operator()(uint8_t val) const { return {val, val, val}; }
        QColor operator()(double val) const {
            // TODO
            return QColor();
        }
        QColor operator()(std::complex<double> val) const {
            return (*this)(std::abs(val));
        }
        QColor operator()(::image::Color val) const {
            return {val.r, val.g, val.b};
        }
    private:
        double m_min, m_max;
    };

    ToRGBVisitor visitor(min, max); 

    for (std::size_t x = 0; x < img.size().width; ++x)
        for (std::size_t y = 0; y < img.size().height; ++y)
            qimg.setPixelColor(int(x), int(y), std::visit(visitor, img.pixel({x, y})));

}
} // namespace gui::utils::image
