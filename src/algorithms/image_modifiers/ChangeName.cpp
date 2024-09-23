#include "algorithms/image_modifiers/ChangeName.hpp"

#include "gui/windows/ParametersDialog.hpp"

using namespace image;
using namespace gui::windows;

namespace algorithms::img_modifiers {
QString ChangeName::getName() const { return "Change name"; }
bool ChangeName::isTypeSupported(ImageType) const { return true; }
void ChangeName::apply(QString& name, Image&) {
    Fields fields;
    fields.emplace_back("New name", pf::String(name.toStdString()));

    auto values = ParametersDialog::getValues(fields);
    if (values.has_value())
        name = QString::fromStdString(std::get<std::string>(values->at("New name")));
}
} // namespace algorithms::img_modifiers
