#include "change_name.hpp"
#include "gui/parameters_dialog.hpp"

void algorithms::change_name(Image&, QString& name) {

    Fields fields;
    fields.emplace_back("New name", pf::String(name.toStdString()));

    auto values = ParametersDialog::getValues(fields);
    if (values.has_value())
        name = QString::fromStdString(std::get<std::string>(values->at("New name")));
}
