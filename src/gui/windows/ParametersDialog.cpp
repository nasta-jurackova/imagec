#include "ParametersDialog.hpp"

#include <QFormLayout>
#include <QPushButton>
#include <string_view>

using namespace gui::windows;

namespace {
class FieldCreator {
  public:
    FieldCreator(std::string name,
                 QFormLayout* form,
                 std::map<std::string, ParametersDialog::FormWidget>& widgets)
        : m_name(std::move(name)),
          m_form(form),
          m_widgets(widgets) {}

    void operator()(const pf::Int& field) {
        auto wdg = new QSpinBox();
        wdg->setMinimum(field.min);
        wdg->setMaximum(field.max);
        wdg->setValue(field.value);
        m_form->addRow(QString::fromStdString(m_name), wdg);
        m_widgets[m_name] = wdg;
    }
    void operator()(const pf::Double& field) {
        auto wdg = new QDoubleSpinBox();
        wdg->setMinimum(field.min);
        wdg->setMaximum(field.max);
        wdg->setValue(field.value);
        m_form->addRow(QString::fromStdString(m_name), wdg);
        m_widgets[m_name] = wdg;
    }
    void operator()(const pf::String& field) {
        auto wdg = new QLineEdit();
        wdg->setText(QString::fromStdString(field.value));
        m_form->addRow(QString::fromStdString(m_name), wdg);
        m_widgets[m_name] = wdg;
    }
    void operator()(const pf::Choice& field) {
        auto wdg = new QComboBox();
        for (const auto& s : field.options)
            wdg->addItem(QString::fromStdString(s));

        m_form->addRow(QString::fromStdString(m_name), wdg);
        m_widgets[m_name] = wdg;
    }

  private:
    std::string m_name;
    QFormLayout* m_form;
    std::map<std::string, ParametersDialog::FormWidget>& m_widgets;
};

class FieldReader {
  public:
    FieldReader(const std::string& name, Values& values)
        : m_name(name),
          m_values(values) {}

    void operator()(QLineEdit* wdg) { m_values[m_name] = wdg->text().toStdString(); };
    void operator()(QSpinBox* wdg) { m_values[m_name] = wdg->value(); };
    void operator()(QDoubleSpinBox* wdg) { m_values[m_name] = wdg->value(); };
    void operator()(QComboBox* wdg) { m_values[m_name] = wdg->currentText().toStdString(); };

  private:
    std::string m_name;
    Values& m_values;
};

} // namespace

namespace gui::windows {
ParametersDialog::ParametersDialog(const Fields& fields, std::optional<Values>& values, QWidget* parent /* = nullptr */)
    : QDialog(parent),
      m_values(values) {

    m_values = std::nullopt;
    setWindowTitle("Operation parameters");
    auto form_layout = new QFormLayout();

    for (const auto& [name, field] : fields) {
        FieldCreator visitor(name, form_layout, m_form_widgets);
        std::visit(visitor, field);
    }

    auto button = new QPushButton("Ok");
    connect(button, &QPushButton::clicked, this, &ParametersDialog::onOkButtonClicked);
    form_layout->addRow("", button);

    setLayout(form_layout);
}

std::optional<Values> ParametersDialog::getValues(const Fields& fields, QWidget* parent /* nullptr */) {
    std::optional<Values> values;
    auto dialog = new ParametersDialog(fields, values, parent);
    dialog->exec();
    return values;
}

void ParametersDialog::onOkButtonClicked() {
    m_values = Values();
    for (const auto& [name, wdg] : m_form_widgets) {
        FieldReader visitor(name, m_values.value());
        std::visit(visitor, wdg);
    }

    close();
}
} // namespace gui::windows