#pragma once

#include "algorithms/AlgorithmBase.hpp"


namespace algorithms::img_modifiers {
class SaveImage : public SimpleAlgorithmBase {
  public:
      ~SaveImage() override = default;

    [[nodiscard]] QString getName() const override;
    [[nodiscard]] bool isTypeSupported(image::ImageType type) const override;
    void apply(QString& name, image::Image& image) override;
};

}