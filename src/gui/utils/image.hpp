#pragma once

#include "core/Image.hpp"

#include <QImage>

namespace gui::utils::image {
::image::Image imageFromQt(const QImage& img);
std::string stringFromPixel(const ::image::Pixel& pix);
QImage visualizationFromImage(const ::image::Image& img);
} // namespace gui::utils::image