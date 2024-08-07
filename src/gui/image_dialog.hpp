#pragma once

#include "core/image.hpp"
#include "gui/image_label.hpp"

#include <QDialog>
#include <QLabel>
#include <functional>

class ImageDialog : public QDialog {
    Q_OBJECT
  public:
    ImageDialog(Image img, QWidget* parent = nullptr);

    void updateImageLabel() const;

  private:
    void addOption(QMenu* menu, const QString& name, std::function<void(Image&)> f);

    Image m_img;
    ImageLabel* m_img_label;
};