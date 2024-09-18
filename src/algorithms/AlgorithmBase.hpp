#pragma once

#include "algorithms/IAlgorithm.hpp"

namespace algorithms {
class SimpleAlgorithmBase : public IAlgorithm {
  public:
    ~SimpleAlgorithmBase() override = default;

    [[nodiscard]] std::size_t partCount() const final;
    [[nodiscard]] QString getName(std::size_t part) const final;
    [[nodiscard]] bool isHighlighted(std::size_t part) const final;
    [[nodiscard]] bool isEnabled(std::size_t part) const final;
    [[nodiscard]] bool isTypeSupported(std::size_t part, image::ImageType type) const final;
    void apply(std::size_t part, QString& name, image::Image& image) final;

  protected:
    [[nodiscard]] virtual QString getName() const = 0;
    [[nodiscard]] virtual bool isHighlighted() const = 0;
    [[nodiscard]] virtual bool isEnabled() const = 0;
    [[nodiscard]] virtual bool isTypeSupported(image::ImageType type) const = 0;
    virtual void apply(QString& name, image::Image& image) = 0;
};
} // namespace algorithms
