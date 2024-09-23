#include "algorithms/statistics/Histogram.hpp"

#include "gui/AppManagerSingleton.hpp"
#include <array>

using namespace image;

namespace algorithms::statistics {
std::size_t Histogram::partCount() const { return 5; }

QString Histogram::getName(std::size_t part) const {
    switch (part) {
    case 0:
        return "Create";
    case 1:
        return "Create cumulative";
    case 2:
        return "Normalize";
    case 3:
        return "Match (select source)";
    case 4:
        return "Match (apply)";
    }
    std::unreachable();
}

bool Histogram::isHighlighted(std::size_t part) const {
    if (part == 3)
        return m_match_source.has_value();
    return false;
}

bool Histogram::isEnabled(std::size_t part) const {
    if (part == 4)
        return m_match_source.has_value();
    return true;
}

bool Histogram::isTypeSupported(std::size_t, ImageType type) const { return type == ImageType::G8; }

void Histogram::apply(std::size_t part, QString& name, Image& image) {
    switch (part) {
    case 0:
        showHistogram(create(image), name);
        break;
    case 1:
        showHistogram(createCumulative(image), name);
        break;
    case 2:
        normalize(image);
        break;
    case 3:
        m_match_source = image.clone();
        break;
    case 4:
        match(m_match_source.value(), image);
        break;
    }
}

Histogram::HistValues Histogram::create(const Image& img) {
    auto typed = img.as_typed<uint8_t>();

    HistValues hist{};
    for (std::size_t col = 0; col < img.size().width; ++col) {
        for (std::size_t row = 0; row < img.size().height; ++row) {
            auto pixel = typed.pixel(Coords(col, row));
            ++hist[pixel];
        }
    }
    return hist;
}

Histogram::HistValues Histogram::createCumulative(const Image& img) {
    auto values = create(img);
    std::partial_sum(values.begin(), values.end(), values.begin());
    return values;
}

void Histogram::normalize(Image& img) {
    std::size_t num_of_pixels = img.size().width * img.size().height;
    HistValues hist{};
    std::size_t to_add = num_of_pixels / 256;
    for (std::size_t i = 0; i < 256; ++i) {
        hist[i] = (i + 1) * to_add;
    }
    std::size_t rest = num_of_pixels - (to_add * 256);
    hist[0] += rest;

    match(img, hist);
}

void Histogram::match(const Image& source, Image& dest) {
    if (source.size() != dest.size())
        throw std::runtime_error("Sizes of source and destination image for histogram matching must be the same.");
    auto cum_hist = createCumulative(source);
    match(dest, cum_hist);
}

void Histogram::match(Image& image, const HistValues& hist) {
    if (image.size().height * image.size().width != hist[255])
        throw std::runtime_error("Image histogram can not be matched to provided histogram");
    std::array<std::size_t, 256> orig_hist = create(image);
    std::array<uint8_t, 256> intensity_map = {0};

    std::size_t accumulator = 0;
    uint8_t dest_int = 0;
    for (std::size_t i = 0; i < 256; ++i) {
        while (accumulator + orig_hist[i] > hist[dest_int])
            ++dest_int;

        intensity_map[i] = dest_int;
        accumulator += orig_hist[i];
    }

    auto typed = image.as_typed<uint8_t>();
    for (std::size_t col = 0; col < image.size().width; ++col) {
        for (std::size_t row = 0; row < image.size().height; ++row) {
            auto coord = Coords(col, row);
            auto pixel = typed.pixel(coord);
            typed.setPixel(coord, intensity_map[pixel]);
        }
    }
}

void Histogram::showHistogram(const HistValues& hist, const QString& name) {
    std::size_t max = *std::ranges::max_element(hist);
    auto histogram = Image(Size(256, 256), ImageType::G8);
    histogram.fillWith(uint8_t(0));
    for (std::size_t h = 0; h < 256; ++h) {
        for (std::size_t i = 0; i < std::size_t(double(hist[h]) / max * 256); ++i) {
            histogram.setPixel(Coords(h, 256 - i - 1), uint8_t(255));
        }
    }
    gui::AppManagerSingleton::getInstance()->openImage(histogram, name + "_histogram");
}
} // namespace algorithms::statistics