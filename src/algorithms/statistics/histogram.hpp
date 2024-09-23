#pragma once

#include "algorithms/IAlgorithm.hpp"

#include <optional>

namespace algorithms::statistics {
class Histogram : public IAlgorithm {
    using HistValues = std::array<std::size_t, 256>;
  public:
    ~Histogram() override = default;
    [[nodiscard]] std::size_t partCount() const override;
    [[nodiscard]] QString getName(std::size_t part) const override;
    [[nodiscard]] bool isHighlighted(std::size_t part) const override;
    [[nodiscard]] bool isEnabled(std::size_t part) const override;
    [[nodiscard]] bool isTypeSupported(std::size_t part, image::ImageType type) const override;
    void apply(std::size_t part, QString& name, image::Image& image) override;

    static [[nodiscard]] HistValues create(const image::Image& img);
    static [[nodiscard]] HistValues createCumulative(const image::Image& img);
    static void normalize(image::Image& img);
    static void match(const image::Image& source, image::Image& dest);
    static void match(image::Image& image, const HistValues& hist);

  private:
    static void showHistogram(const HistValues& hist, const QString& name);

    std::optional<image::Image> m_match_source;
};
/*
void histogram_create(Image& img, QString& name);
void histogram_normalize(Image& img, QString& name);
void histogram_match(Image& img, QString& name);
*/
} // namespace algorithms::statistics