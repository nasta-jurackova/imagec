#pragma once

#include "gui/windows/ui_MainWindow.h"

#include <QWidget>

namespace gui::windows {
class MainWindow : public QWidget {
    Q_OBJECT
  public:
    MainWindow();

  private slots:
    void onOpenGrayscaleImageAction();
    void onOpenRGBImageAction();

  private:
    void openImage(QImage::Format format);

    Ui::MainWindow m_ui;
};
} // namespace gui::windows