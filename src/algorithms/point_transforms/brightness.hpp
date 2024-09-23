#pragma once

#include "algorithms/AlgorithmBase.hpp"

namespace algorithms::point_transforms {
class Brightness : public NonStateAlgirthmBase {
  public:
      ~Brightness() override = default;

    [[nodiscard]] std::size_t partCount() const override;
    [[nodiscard]] QString getName(std::size_t part) const override;
    [[nodiscard]] bool isTypeSupported(std::size_t part, image::ImageType type) const override;
    void apply(std::size_t part, QString& name, image::Image& image) override;

    static void change(image::Image& img, int amount);

private:
    static std::optional<int> chooseFactor();
};
} // namespace algorithms::point_transforms

/*
void brightness_add_10(Image& img, QString& name);
void brightness_cut_10(Image& img, QString& name);
void brightness_by_custom(Image& img, QString& name);
*/