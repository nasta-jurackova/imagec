#include "algorithms/point_transforms/Contrast.hpp"
#include "gui/windows/ParametersDialog.hpp"

using namespace image;
using namespace gui::windows;

namespace algorithms::point_transforms {
std::size_t Contrast::partCount() const { return 4; }

QString Contrast::getName(std::size_t part) const {
    switch (part) {
    case 0:
        return "+50 %";
    case 1:
        return "-50 %";
    case 2:
        return "Custom";
    case 3:
        return "Linear stretch";
    }

    std::unreachable();
}

bool Contrast::isTypeSupported(std::size_t, ImageType type) const { return type == ImageType::G8; }

void Contrast::apply(std::size_t part, QString&, Image& image) {
    switch (part) {
    case 0:
        change(image, 1.5);
        break;
    case 1:
        change(image, 0.5);
        break;
    case 2: {
        auto mult = chooseMultiplier();
        if (mult.has_value())
            change(image, mult.value());
    } break;
    case 3:
        linearStretch(image);
        break;
    }
}

void Contrast::change(Image& image, double multiplier) {
    auto typed = image.as_typed<uint8_t>();

    for (std::size_t col = 0; col < typed.size().width; ++col) {
        for (std::size_t row = 0; row < typed.size().height; ++row) {
            uint8_t pixel = typed.pixel(Coords(col, row));
            typed.setPixel(Coords(col, row), uint8_t(std::clamp(std::lround(pixel * multiplier), 0l, 255l)));
        }
    }
}

void Contrast::linearStretch(Image& image) {
    auto typed = image.as_typed<uint8_t>();

    uint8_t min = 255;
    uint8_t max = 0;
    for (std::size_t col = 0; col < typed.size().width; ++col) {
        for (std::size_t row = 0; row < typed.size().height; ++row) {
            auto pixel = typed.pixel(Coords(col, row));
            min = std::min(min, pixel);
            max = std::max(max, pixel);
        }
    }

    double factor = 255.0 / (max - min);
    for (std::size_t col = 0; col < typed.size().width; ++col) {
        for (std::size_t row = 0; row < typed.size().height; ++row) {
            auto pixel = typed.pixel(Coords(col, row));
            typed.setPixel(Coords(col, row), uint8_t(std::lround(double(pixel - min) * factor)));
        }
    }
}

std::optional<double> Contrast::chooseMultiplier() {
    Fields fields;
    fields.emplace_back("Factor", pf::Double(0, 2, 1));
    auto values = ParametersDialog::getValues(fields);
    if (values.has_value()) {
        auto value = values.value()["Factor"];
        return std::get<double>(value);
    }
    return std::nullopt;
}
} // namespace algorithms::point_transforms