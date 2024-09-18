#pragma once

#include "core/image.hpp"

namespace algorithms {
void histogram_create(Image& img, QString& name);
void histogram_normalize(Image& img, QString& name);
void histogram_match(Image& img, QString& name);
} // namespace algorithms