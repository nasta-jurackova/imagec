#pragma once

#include "core/image.hpp"

#include <QString>

namespace algorithms {
class IAlgorithm {
  public:
    virtual ~IAlgorithm() = default;
    [[nodiscard]] virtual std::size_t partCount() const = 0;
    [[nodiscard]] virtual QString getName(std::size_t part) const = 0;
    [[nodiscard]] virtual bool isHighlighted(std::size_t part) const = 0;
    [[nodiscard]] virtual bool isEnabled(std::size_t part) const = 0;
    [[nodiscard]] virtual bool isTypeSupported(std::size_t part, image::ImageType type) const = 0;
    virtual void apply(std::size_t part, QString& name, image::Image& image) = 0;
};
} // namespace algorithms