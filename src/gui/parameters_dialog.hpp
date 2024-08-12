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

namespace parameters {
namespace fields {
struct Double {
    double min = std::numeric_limits<double>::lowest();
    double max = std::numeric_limits<double>::max();
    double value = 0.0;
};
struct Int {
    int min = std::numeric_limits<int>::lowest();
    int max = std::numeric_limits<int>::max();
    int value = 0;
};
struct String {
    std::string value = "";
};
struct Choice {
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
