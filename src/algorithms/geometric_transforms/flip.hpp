#pragma once
#include "algorithms/AlgorithmBase.hpp"

namespace algorithms::geometric_trans {
class Flip : public NonStateAlgirthmBase {
  public:
    ~Flip() override = default;

    [[nodiscard]] std::size_t partCount() const override;
    [[nodiscard]] QString getName(std::size_t part) const override;
    [[nodiscard]] bool isTypeSupported(std::size_t part, image::ImageType type) const override;
    void apply(std::size_t part, QString& name, image::Image& image) override;

    static void horizontal(image::Image& img);
    static void vertical(image::Image& img);
};
} // namespace algorithms::geometric_trans