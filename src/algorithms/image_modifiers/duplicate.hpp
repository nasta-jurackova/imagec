#pragma once

#include "algorithms/AlgorithmBase.hpp"

namespace algorithms::img_modifiers {

class Duplicate : public SimpleAlgorithmBase {
  public:
    ~Duplicate() override = default;

    [[nodiscard]] QString getName() const override;
    [[nodiscard]] bool isTypeSupported(image::ImageType type) const override;
    void apply(QString& name, image::Image& image) override;
};

} // namespace algorithms::img_modifiers