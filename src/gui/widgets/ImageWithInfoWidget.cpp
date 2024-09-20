#include "gui/widgets/ImageWithInfoWidget.hpp"
#include "gui/utils/image.hpp"

#include <QFileDialog>
#include <QPixmap>
#include <QVBoxLayout>
#include <iostream>

namespace gui::widgets {

ImageWithInfoWidget::ImageWithInfoWidget(image::Image img, QWidget* parent /* = nullptr */)
    : QWidget(parent),
      m_img(std::move(img)) {

    auto layout = new QVBoxLayout();

    m_img_wdg = new ZoomableImageWidget(QPixmap::fromImage(gui::utils::image::visualizationFromImage(m_img)));
    connect(m_img_wdg, &ZoomableImageWidget::mousePositionChanged, this, [this](QPoint coords) {
        updateInfoLabel(coords,
                        QString::fromStdString(gui::utils::image::stringFromPixel(
                            m_img.pixel(image::Coords{std::size_t(coords.x()), std::size_t(coords.y())}))));
    });
    layout->addWidget(m_img_wdg);

    m_info_label = new QLabel();
    layout->addWidget(m_info_label);
    updateInfoLabel({0, 0}, "NaN");

    setLayout(layout);
}

void ImageWithInfoWidget::setImage(image::Image img) {
    m_img = img;
    m_img_wdg->setPixmap(QPixmap::fromImage(gui::utils::image::visualizationFromImage(img)));
}

void ImageWithInfoWidget::updateInfoLabel(const QPoint& coords, const QString& color) {
    m_info_label->setText(QString("X: %1 Y: %2 Color: %3").arg(coords.x()).arg(coords.y()).arg(color));
}
} // namespace gui::widgets