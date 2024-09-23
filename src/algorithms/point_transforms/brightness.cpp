#include "algorithms/point_transforms/Brightness.hpp"
#include "gui/windows/ParametersDialog.hpp"

using namespace image;
using namespace gui::windows;

namespace algorithms::point_transforms {
std::size_t Brightness::partCount() const { return 3; }

QString Brightness::getName(std::size_t part) const {
    switch (part) {
    case 0:
        return "+10";
    case 1:
        return "-10";
    case 2:
        return "Custom";
    }
    std::unreachable();
}

bool Brightness::isTypeSupported(std::size_t, ImageType type) const { return type == ImageType::G8; }

void Brightness::apply(std::size_t part, QString&, Image& image) {
    switch (part) {
    case 0:
        change(image, 10);
        break;
    case 1:
        change(image, -10);
        break;
    case 2: {
        auto amount = chooseFactor();
        if (amount.has_value())
            change(image, amount.value());
        break;
    }
    }
}

void Brightness::change(Image& img, int amount) {
    auto typed = img.as_typed<uint8_t>();

    for (std::size_t col = 0; col < img.size().width; ++col) {
        for (std::size_t row = 0; row < img.size().height; ++row) {
            uint8_t pixel = typed.pixel(Coords(col, row));
            img.setPixel(Coords(col, row), uint8_t(std::clamp(pixel + amount, 0, 255)));
        }
    }
}

std::optional<int> Brightness::chooseFactor() {
    Fields fields;
    fields.emplace_back("Factor", pf::Int(-255, 255, 0));
    auto values = ParametersDialog::getValues(fields);
    if (values.has_value()) {
        auto value = values.value()["Factor"];
        return std::get<int>(value);
    }
    return std::nullopt;
}
} // namespace algorithms::point_transforms