#pragma once

#include "algorithms/AlgorithmBase.hpp"

#include <optional>

namespace algorithms::point_transforms {
class Contrast : public NonStateAlgirthmBase {
  public:
    ~Contrast() override = default;

    [[nodiscard]] std::size_t partCount() const override;
    [[nodiscard]] QString getName(std::size_t part) const override;
    [[nodiscard]] bool isTypeSupported(std::size_t part, image::ImageType type) const override;
    void apply(std::size_t part, QString& name, image::Image& image) override;

    static void change(image::Image& image, double multiplier);
    static void linearStretch(image::Image& image);

private:
    static std::optional<double> chooseMultiplier();
};

/*
void contrast_add_50(Image& img, QString& name);
void contrast_cut_50(Image& img, QString& name);
void contrast_by_custom(Image& img, QString& name);
void linearStretch(Image& img, QString& name);
*/
} // namespace algorithms::point_transforms