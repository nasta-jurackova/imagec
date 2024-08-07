#include "algorithms/duplicate.hpp"

#include "gui/main_bar.hpp"

namespace algorithms {
void duplicate(Image& img) { MainBarSingleton::getInstance()->openImage(img); }
} // namespace algorithms