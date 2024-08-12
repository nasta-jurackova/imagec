#include "image_with_info_widget.hpp"

#include <QFileDialog>
#include <QPixmap>
#include <QVBoxLayout>
#include <iostream>

ImageWithInfoWidget::ImageWithInfoWidget(QWidget* parent /* = nullptr */)
    : QWidget(parent) {

    auto path = QFileDialog::getOpenFileName(this);

    QPixmap img(path);

    auto layout = new QVBoxLayout();

    m_img_wdg = new ZoomableImageWidget(img);
    connect(m_img_wdg, &ZoomableImageWidget::mousePositionChanged, this, [this](QPoint coords) {
        updateInfoLabel(coords, "color");
    });
    layout->addWidget(m_img_wdg);

    m_info_label = new QLabel();
    layout->addWidget(m_info_label);
    updateInfoLabel({0, 0}, "color");

    setLayout(layout);
    
}

void ImageWithInfoWidget::updateInfoLabel(const QPoint& coords, const QString& color) {
    m_info_label->setText(QString("X: %1 Y: %2 Color: %3").arg(coords.x()).arg(coords.y()).arg(color));
}
