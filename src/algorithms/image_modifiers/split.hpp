#pragma once

#include "algorithms/AlgorithmBase.hpp"

namespace algorithms::img_modifiers {
class SplitImage : public SimpleAlgorithmBase {
  public:
      ~SplitImage() override = default;

    [[nodiscard]] QString getName() const override;
    [[nodiscard]] bool isTypeSupported(image::ImageType type) const override;
    void apply(QString& name, image::Image& image) override;

    [[nodiscard]] static std::tuple<image::Image, image::Image, image::Image> splitRGB(const image::Image& image);
};
} // namespace algorithms