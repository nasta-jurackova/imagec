#include "algorithms/AlgorithmBase.hpp"

#include <cassert>

namespace algorithms {

std::size_t SimpleAlgorithmBase::partCount() const /* final */ { return 1; }

QString SimpleAlgorithmBase::getName(std::size_t part) const /* final */ {
    assert(partCount() == 1);
    assert(part == 0);
    return getName();
}

bool SimpleAlgorithmBase::isHighlighted(std::size_t part) const /* final */ {
    assert(partCount() == 1);
    assert(part == 0);
    return isHighlighted();
}

bool SimpleAlgorithmBase::isEnabled(std::size_t part) const /* final */ {
    assert(partCount() == 1);
    assert(part == 0);
    return isEnabled();
}

bool SimpleAlgorithmBase::isTypeSupported(std::size_t part, image::ImageType type) const /* final */ {
    assert(partCount() == 1);
    assert(part == 0);
    return isTypeSupported(type);
}

void SimpleAlgorithmBase::apply(std::size_t part, QString& name, image::Image& image) /* final */ {
    assert(partCount() == 1);
    assert(part == 0);
    return apply(name, image);
}
} // namespace algorithms