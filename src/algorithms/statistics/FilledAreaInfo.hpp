#pragma once

#include "algorithms/AlgorithmBase.hpp"

#include <set>

namespace algorithms::statistics {
class FilledAreaInfo : public SimpleAlgorithmBase {
  public:
    struct AreaInfo {
        std::size_t area_px = 0;
        std::size_t width = 0;
        std::size_t height = 0;
    };
    enum class NeighbourRule { N4, N8 };

    ~FilledAreaInfo() override = default;

    [[nodiscard]] QString getName() const override;
    [[nodiscard]] bool isTypeSupported(image::ImageType type) const override;
    void apply(QString& name, image::Image& image) override;

    AreaInfo getAreaInfo(image::Image& image, image::Coords coords, NeighbourRule neighbour) const;

  private:
    AreaInfo getAreaInfoFromCoords(const std::set<image::Coords>&) const;
};

} // namespace algorithms::statistics