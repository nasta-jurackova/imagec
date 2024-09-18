#include "algorithms/duplicate.hpp"

#include "gui/main_bar.hpp"

namespace algorithms {
void duplicate(Image& img, QString& name) { MainBarSingleton::getInstance()->openImage(img, name + " dup"); }
} // namespace algorithms