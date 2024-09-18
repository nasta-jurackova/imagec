#include "gui/AppManagerSingleton.hpp"
#include "gui/windows/ImageWindow.hpp"

namespace gui {

AppManagerSingleton* AppManagerSingleton::getInstance() {
    if (sm_instance == nullptr)
        sm_instance = std::unique_ptr<AppManagerSingleton>(new AppManagerSingleton());
    return sm_instance.get();
}

void AppManagerSingleton::openImage(const image::Image& img, const QString& name) {
    auto window = new windows::ImageWindow(name, img.clone());
    window->show();
}

/* static */ std::unique_ptr<AppManagerSingleton> AppManagerSingleton::sm_instance = nullptr;

} // namespace gui
