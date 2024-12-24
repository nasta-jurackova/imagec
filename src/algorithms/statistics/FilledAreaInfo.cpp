#include "algorithms/statistics/FilledAreaInfo.hpp"

#include "gui/windows/ParametersDialog.hpp"
#include <QMessageBox>
#include <queue>
#include <set>
#include <algorithm>

using namespace gui::windows;

namespace algorithms::statistics {
QString FilledAreaInfo::getName() const { return "Filled area information"; }
bool FilledAreaInfo::isTypeSupported(image::ImageType) const { return true; }
void FilledAreaInfo::apply(QString&, image::Image& image) {
    Fields fields;
    fields.emplace_back("Coords:", pf::Empty());
    fields.emplace_back("X", pf::Int(0, int(image.size().width - 1), 0));
    fields.emplace_back("Y", pf::Int(0, int(image.size().height - 1), 0));
    fields.emplace_back("", pf::Empty());
    fields.emplace_back("Neighbour rule", pf::Choice({"N4", "N8"}));

    auto values = ParametersDialog::getValues(fields);
    if (!values.has_value())
        return;

    NeighbourRule rule =
        std::get<std::string>(values->at("Neighbour rule")) == "N4" ? NeighbourRule::N4 : NeighbourRule::N8;
    image::Coords start_coords(0, 0);
    start_coords.x = std::get<int>(values->at("X"));
    start_coords.y = std::get<int>(values->at("Y"));

    auto info = getAreaInfo(image, start_coords, rule);

    QMessageBox::information(
        nullptr,
        "Filled area stats",
        QString("Area: %1 px\nWidth: %2 px\nHeight: %3 px").arg(info.area_px).arg(info.width).arg(info.height));
}
FilledAreaInfo::AreaInfo
FilledAreaInfo::getAreaInfo(image::Image& image, image::Coords coords, NeighbourRule neighbour) const {
    std::vector<image::Offset> offsets;
    switch (neighbour) {
    case NeighbourRule::N4:
        offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        break;
    case NeighbourRule::N8:
        offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
        break;
    }

    // `visited` also measures the area
    std::set<image::Coords> visited{coords};
    std::queue<image::Coords> queue;
    queue.push(coords);

    // bfs
    auto pixel_value = image.pixel(coords);
    while (!queue.empty()) {
        auto curr_coords = queue.front();
        queue.pop();

        for (auto off : offsets) {
            auto new_coords = curr_coords + off;
            // out of bounds
            if (new_coords.x >= image.size().width || new_coords.y >= image.size().height)
                continue;
            // different value
            if (image.pixel(new_coords) != pixel_value)
                continue;
            // already found
            if (visited.contains(new_coords))
                continue;

            visited.insert(new_coords);
            queue.push(new_coords);
        }
    }

    return getAreaInfoFromCoords(visited);
}

FilledAreaInfo::AreaInfo FilledAreaInfo::getAreaInfoFromCoords(const std::set<image::Coords>& coords) const {
    AreaInfo out;
    out.area_px = coords.size();

    if (out.area_px == 0)
        return out;

    image::Coords min = *coords.begin();
    image::Coords max = *coords.begin();

    for (const auto& coord : coords) {
        min.x = std::min(min.x, coord.x);
        min.y = std::min(min.y, coord.y);
        max.x = std::max(max.x, coord.x);
        max.y = std::max(max.y, coord.y);
    }

    out.height = max.y - min.y;
    out.width = max.x - min.x;

    return out;
}
} // namespace algorithms::statistics