#pragma once

#include <QComboBox>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QSpinBox>
#include <limits>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace gui::windows{
namespace parameters {
namespace fields {
struct Double {
    Double() = default;
    Double(double min, double max, double value)
        : min(min),
          max(max),
          value(value) {}
    double min = std::numeric_limits<double>::lowest();
    double max = std::numeric_limits<double>::max();
    double value = 0.0;
};
struct Int {
    Int() = default;
    Int(int min, int max, int value)
        : min(min),
          max(max),
          value(value) {}
    int min = std::numeric_limits<int>::lowest();
    int max = std::numeric_limits<int>::max();
    int value = 0;
};
struct String {
    String() = default;
    String(std::string value)
        : value(std::move(value)) {}
    std::string value = "";
};
struct Choice {
    Choice() = default;
    Choice(std::vector<std::string> options)
        : options(std::move(options)) {}
    // The first option is the default one
    std::vector<std::string> options;
};
} // namespace fields
using ParamField = std::variant<fields::Double, fields::Int, fields::String, fields::Choice>;
using ResultValue = std::variant<double, int, std::string>;
} // namespace parameters

namespace pf = parameters::fields;

using Fields = std::vector<std::pair<std::string, parameters::ParamField>>;
using Values = std::map<std::string, parameters::ResultValue>;

class ParametersDialog : public QDialog {
    Q_OBJECT
  public:
    using FormWidget = std::variant<QLineEdit*, QSpinBox*, QDoubleSpinBox*, QComboBox*>;
    ParametersDialog(const Fields& fields, std::optional<Values>& values, QWidget* parent = nullptr);

    static std::optional<Values> getValues(const Fields& fields, QWidget* parent = nullptr);

  private slots:
    void onOkButtonClicked();

  private:
    std::optional<Values>& m_values;
    std::map<std::string, FormWidget> m_form_widgets;
};
}}