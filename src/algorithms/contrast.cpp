#include "algorithms/contrast.hpp"

#include "core/image.hpp"
#include "gui/parameters_dialog.hpp"

namespace algorithms {
namespace details {
void contrast(Image& img, double by) {
    for (std::size_t col = 0; col < img.size().width; ++col) {
        for (std::size_t row = 0; row < img.size().height; ++row) {
            uint8_t pixel = img.pixel<uint8_t>(Coords(col, row));
            img.setPixel(Coords(col, row), uint8_t(std::clamp(std::lround(pixel * by), 0l, 255l)));
        }
    }
}
} // namespace details

void contrast_add_50(Image& img, QString&) { details::contrast(img, 1.5); }

void contrast_cut_50(Image& img, QString&) { details::contrast(img, 0.5); }

void contrast_by_custom(Image& img, QString&) {
    Fields fields;
    fields.emplace_back("Factor", pf::Double(0, 2, 1));
    auto values = ParametersDialog::getValues(fields);
    if (values.has_value()) {
        auto value = values.value()["Factor"];
        details::contrast(img, std::get<double>(value));
    }
}

void linear_stretch(Image&, QString&) {}
} // namespace algorithms