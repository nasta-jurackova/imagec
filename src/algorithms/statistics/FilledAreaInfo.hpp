#pragma once

#include "algorithms/AlgorithmBase.hpp"

namespace algorithms::statistics {
class FilledAreaInfo : public SimpleAlgorithmBase {
  public:
    struct AreaInfo {
        unsigned area_px = 0;
        // unsigned in_perimeter_px = 0;
        // unsigned out_perimeter_px = 0;
    };
    enum class NeighbourRule {
        N4, N8
    };

    ~FilledAreaInfo() override = default;

    [[nodiscard]] QString getName() const override;
    [[nodiscard]] bool isTypeSupported(image::ImageType type) const override;
    void apply(QString& name, image::Image& image) override;

    AreaInfo getAreaInfo(image::Image& image, image::Coords coords, NeighbourRule neighbour) const;
};

} // namespace algorithms::statistics