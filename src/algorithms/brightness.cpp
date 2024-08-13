#include "algorithms/brightness.hpp"
#include "gui/parameters_dialog.hpp"
#include "core/image.hpp"

namespace algorithms {
namespace details {
    void brightness(Image& img, int by) {
    for (std::size_t col = 0; col < img.size().width; ++col) {
        for (std::size_t row = 0; row < img.size().height; ++row) {
            uint8_t pixel = img.pixel<uint8_t>(Coords(col, row));
            img.setPixel(Coords(col, row), uint8_t(std::clamp(pixel + by, 0, 255)));
        }
    }
}
}

void brightness_add_10(Image& img, QString&) { details::brightness(img, 10); }

void brightness_cut_10(Image& img, QString&) { details::brightness(img, -10); }

void brightness_by_custom(Image& img, QString&){
    Fields fields;
    fields.emplace_back("Factor", pf::Int(-255, 255, 0));
    auto values = ParametersDialog::getValues(fields);
    if (values.has_value()) {
        auto value = values.value()["Factor"];
        details::brightness(img, std::get<int>(value));
    }
}
} // namespace algorithms