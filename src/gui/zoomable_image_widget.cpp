#include "gui/zoomable_image_widget.hpp"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>
#include <QScrollBar>
#include <QWheelEvent>

#include <iostream>

ZoomableImageWidget::ZoomableImageWidget(QPixmap img, QWidget* parent /* = nullptr */)
    : QWidget(parent),
      m_img(img) {
    m_ui.setupUi(this);

    m_ui.label->setPixmap(img);
    setFixedSize(524, 524);

    m_ui.horizontalScrollBar->setMinimum(0);
    m_ui.horizontalScrollBar->setValue(0);

    m_ui.verticalScrollBar->setMinimum(0);
    m_ui.verticalScrollBar->setValue(0);

    connect(m_ui.verticalScrollBar, &QScrollBar::valueChanged, this, &ZoomableImageWidget::redrawImage);
    connect(m_ui.horizontalScrollBar, &QScrollBar::valueChanged, this, &ZoomableImageWidget::redrawImage);

    setMouseTracking(true);
    m_ui.label->setMouseTracking(true);
    redrawImage();
}

void ZoomableImageWidget::setPixmap(QPixmap img) {
    m_img = img;
    redrawImage();
}

void ZoomableImageWidget::wheelEvent(QWheelEvent* event) {
    auto angle = event->angleDelta().y() / 8;
    if (event->modifiers() == Qt::ShiftModifier) {
        m_ui.horizontalScrollBar->setValue(m_ui.horizontalScrollBar->value() - angle);
    } else if (event->modifiers() == Qt::ControlModifier) {
        double shift = 1 + std::abs(angle) * 1e-2;
        if (angle > 0) {
            m_zoom = std::max(1.0, m_zoom * shift);
        } else {
            ;
            m_zoom = std::max(1.0, m_zoom / shift);
        }

    } else {
        m_ui.verticalScrollBar->setValue(m_ui.verticalScrollBar->value() - angle);
    }

    redrawImage();

    event->accept();
}

void ZoomableImageWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    redrawImage();
}

void ZoomableImageWidget::redrawImage() {
    QSize src_size = m_img.size();
    QSize viewport_size = src_size / m_zoom;
    m_ui.horizontalScrollBar->setMaximum(src_size.width() - viewport_size.width());
    m_ui.verticalScrollBar->setMaximum(src_size.height() - viewport_size.height());

    QRect vieport = getViewport();

    QPixmap cropped = m_img.copy(vieport);
    m_ui.label->setPixmap(cropped.scaled(m_ui.label->size(), Qt::KeepAspectRatio));
}

void ZoomableImageWidget::mouseMoveEvent(QMouseEvent* event) {
    auto pos = event->pos();
    auto label_pos = m_ui.label->mapFrom(this, pos);

    label_pos.rx() = std::clamp(label_pos.x(), 0, m_ui.label->width() - 1);
    label_pos.ry() = std::clamp(label_pos.y(), 0, m_ui.label->height() - 1);

    QRect viewport = getViewport();

    QPointF perc(qreal(label_pos.x()) / m_ui.label->width(), qreal(label_pos.y()) / m_ui.label->height());

    QPoint img_pos(int(perc.x() * viewport.width() + viewport.left()),
                   int(perc.y() * viewport.height() + viewport.top()));

    emit mousePositionChanged(img_pos);
}

QRect ZoomableImageWidget::getViewport() const {
    QSize src_size = m_img.size();

    QSize viewport_size = src_size / m_zoom;

    QPoint shift = {m_ui.horizontalScrollBar->value(), m_ui.verticalScrollBar->value()};

    return QRect(shift, viewport_size);
}
