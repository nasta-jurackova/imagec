#pragma once

#include "core/image.hpp"

namespace algorithms {
void contrast_add_50(Image& img, QString& name);
void contrast_cut_50(Image& img, QString& name);
void contrast_by_custom(Image& img, QString& name);
void linear_stretch(Image& img, QString& name);
} // namespace algorithms