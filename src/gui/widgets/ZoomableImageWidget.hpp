#pragma once


#include "ui_zoomableImageWidget.h"

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>

class ZoomableImageWidget : public QWidget {
    Q_OBJECT
  public:
    ZoomableImageWidget(QPixmap img, QWidget* parent = nullptr);
    void setPixmap(QPixmap img);

  protected:
    void wheelEvent(QWheelEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

  signals:
    void mousePositionChanged(QPoint coords);

  private slots:
    void redrawImage();

  private:
    QRect getViewport() const;

    Ui::ZoomableImageWidget m_ui;
    double m_zoom = 1.0;
    QPixmap m_img;
};