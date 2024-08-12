#include "zoomable_image_widget.hpp"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>
#include <QScrollBar>
#include <QWheelEvent>

#include <iostream>

ZoomableImageWidget::ZoomableImageWidget(QPixmap img, QWidget* parent /* = nullptr */)
    : QScrollArea(parent),
      m_img_lbl(new QLabel()),
      m_img(img) {

    setMouseTracking(true);

    setAlignment(Qt::AlignCenter);

    setWidget(m_img_lbl);
    m_img_lbl->setScaledContents(true);
    m_img_lbl->setPixmap(m_img);
    m_img_lbl->setMouseTracking(true);
    redrawPixmap();
}

void ZoomableImageWidget::wheelEvent(QWheelEvent* event) {
    auto angle = event->angleDelta().y() / 8;
    if (event->modifiers() == Qt::ShiftModifier) {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - angle);
    } else if (event->modifiers() == Qt::ControlModifier) {
        if (angle > 0)
            m_zoom *= 1 + angle * 1e-2;
        else
            m_zoom /= 1 + -angle * 1e-2;
        redrawPixmap();
    } else {
        verticalScrollBar()->setValue(verticalScrollBar()->value() - angle);
    }

    event->accept();
}

void ZoomableImageWidget::mouseMoveEvent(QMouseEvent* event) {
    emit mousePositionChanged(event->pos());
    QScrollArea::mouseMoveEvent(event);

    int shift_x = horizontalScrollBar()->value();
    int shift_y = verticalScrollBar()->value();

    QPoint position = event->pos();
    QSize img_size = m_img.size();
}

void ZoomableImageWidget::redrawPixmap() {
    m_img_lbl->resize(std::lround(m_img.width() * m_zoom), std::lround(m_img.height() * m_zoom));
}
