#include "algorithms/histogram.hpp"
#include "core/image.hpp"
#include "gui/main_bar.hpp"
#include <array>

namespace algorithms {
namespace details {
std::array<std::size_t, 256> count_intensities(Image& img) {
    std::array<std::size_t, 256> hist = {0};
    for (std::size_t col = 0; col < img.size().width; ++col) {
        for (std::size_t row = 0; row < img.size().height; ++row) {
            auto pixel = img.pixel<uint8_t>(Coords(col, row));
            ++hist[pixel];
        }
    }
    return hist;
}

std::array<std::size_t, 256> create_uniform_cummulative_hist(std::size_t num_of_pixels) { 
    std::array<std::size_t, 256> hist = {0};
    std::size_t to_add = num_of_pixels / 256;
    for (std::size_t i = 0; i < 256; ++i) {
        hist[i] = (i + 1) * to_add;
    }
    std::size_t rest = num_of_pixels - (to_add * 256);
    hist[0] += rest;
    return hist;
}

std::array<std::size_t, 256> count_cummulative_intensities(std::array<std::size_t, 256> orig) {
    std::array<std::size_t, 256> hist = orig;
    std::size_t to_add = 0;
    for (std::size_t i = 0; i < 256; ++i) {
        hist[i] += to_add;
        to_add = hist[i];
    }
    return hist;
}
void make_histogram_picture(std::array<std::size_t, 256> hist, QString& name) {
    std::size_t max = *std::ranges::max_element(hist);
    auto histogram = Image(Size(256, 256), ImageType::G8);
    histogram.fillWith(uint8_t(0));
    for (std::size_t h = 0; h < 256; ++h) {
        for (std::size_t i = 0; i < std::size_t(double(hist[h]) / max * 256); ++i) {
            histogram.setPixel(Coords(h, 256 - i - 1), uint8_t(255));
        }
    }
    MainBarSingleton::getInstance()->openImage(histogram, name + "_histogram");
}
} // namespace details

void histogram_create(Image& img, QString& name) {
    auto hist = details::count_intensities(img);
    details::make_histogram_picture(hist, name);
}

void histogram_equalize(Image& img, QString&) {
    std::size_t pixels = img.size().width * img.size().height;
    std::array<std::size_t, 256> wanted_hist = details::create_uniform_cummulative_hist(pixels);
    std::array<std::size_t, 256> orig_hist = details::count_intensities(img);
    std::array<uint8_t, 256> intensity_map = {0};
    for (std::size_t j = 0; j < 256; ++j) {
        for (std::size_t i = 0; i < 256; ++i) {
            if (orig_hist[j] <= wanted_hist[i]) {
                intensity_map[j] = i;
                wanted_hist[i] = 0;
                break;
            }
        }
    }
    for (std::size_t col = 0; col < img.size().width; ++col) {
        for (std::size_t row = 0; row < img.size().height; ++row) {
            auto coord = Coords(col, row);
            auto pixel = img.pixel<uint8_t>(coord);
            img.setPixel(coord, intensity_map[pixel]);
        }
    }
}

void histogram_match(Image&, QString&) {}
} // namespace algorithms