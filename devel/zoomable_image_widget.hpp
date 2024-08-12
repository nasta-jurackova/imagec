#pragma once
#include <QWidget>

#include <QLabel>
#include <QPixmap>
#include <QScrollArea>

class ZoomableImageWidget : public QScrollArea {
    Q_OBJECT
  public:
    ZoomableImageWidget(QPixmap img, QWidget* parent = nullptr);

  signals:
    void mousePositionChanged(QPoint coords);

  protected:
    void wheelEvent(QWheelEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

  private:
    void redrawPixmap();

    QPixmap m_img;
    double m_zoom = 1.0;
    QLabel* m_img_lbl;
};