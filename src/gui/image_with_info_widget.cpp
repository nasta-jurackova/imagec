#include "gui/image_with_info_widget.hpp"

#include <QFileDialog>
#include <QPixmap>
#include <QVBoxLayout>
#include <iostream>

ImageWithInfoWidget::ImageWithInfoWidget(const Image& img, QWidget* parent /* = nullptr */)
    : m_img(img),
      QWidget(parent) {

    auto layout = new QVBoxLayout();

    m_img_wdg = new ZoomableImageWidget(QPixmap::fromImage(img.toQImage()));
    connect(m_img_wdg, &ZoomableImageWidget::mousePositionChanged, this, [this](QPoint coords) {
        updateInfoLabel(coords,
                        QString::fromStdString(
                            stringFromPixel(m_img.pixel(Coords{std::size_t(coords.x()), std::size_t(coords.y())}))));
    });
    layout->addWidget(m_img_wdg);

    m_info_label = new QLabel();
    layout->addWidget(m_info_label);
    updateInfoLabel({0, 0}, "NaN");

    setLayout(layout);
}

void ImageWithInfoWidget::setImage(const Image& img) {
    m_img = img;
    m_img_wdg->setPixmap(QPixmap::fromImage(img.toQImage()));
}

void ImageWithInfoWidget::updateInfoLabel(const QPoint& coords, const QString& color) {
    m_info_label->setText(QString("X: %1 Y: %2 Color: %3").arg(coords.x()).arg(coords.y()).arg(color));
}
