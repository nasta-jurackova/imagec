#pragma once
#include "core/image.hpp"

#include <QWidget>
#include <filesystem>
#include <QString>

class MainBarSingleton : public QWidget {
  private:
    MainBarSingleton();

    Q_OBJECT
  public:
    static MainBarSingleton* getInstance();
    void openImage(const std::filesystem::path& path, QImage::Format format);
    void openImage(const QString& path, QImage::Format format);
    void openImage(const Image& img);

  private slots:
    void onOpenGrayscaleImageAction();
    void onOpenRGBImageAction();

  private:
    static MainBarSingleton* sm_instance;
};