#pragma once

#include "core/Image.hpp"

#include <QImage>
#include <QObject>
#include <QString>
#include <filesystem>
#include <memory>

namespace gui {

class AppManagerSingleton {
  private:
    AppManagerSingleton() = default;

  public:
    static AppManagerSingleton* getInstance();
    void openImage(const image::Image& img, const QString& name);

  private:
    static std::unique_ptr<AppManagerSingleton> sm_instance;
};
} // namespace gui