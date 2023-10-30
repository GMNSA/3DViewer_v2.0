#include "../../includes/Model/imagecapture.hpp"

#include <QDir>
#include <QMessageBox>

namespace s21 {

ImageCapture::ImageCapture() : widget_(nullptr) {}

// ----------------------------------------------------------------------------

ImageCapture::~ImageCapture() {}

// ----------------------------------------------------------------------------

void ImageCapture::ScreenshotJPEG() { Screenshot(); }

// ----------------------------------------------------------------------------

void ImageCapture::ScreenshotBMP() {
  Screenshot(ScreenshotType::SCREENSHOT_BPM);
}

// ----------------------------------------------------------------------------

void ImageCapture::set_widget(QWidget *my_widget) {
  if (widget_ != my_widget) widget_ = my_widget;
}

// PRIATE  --------------------------------------------------------------------

void ImageCapture::Screenshot(int const &is_jpeg) {
  if (!widget_) return;
  long ttime = time(0);
  QString current_time = ctime(&ttime);
  QString format;
  QPixmap pix(widget_->size() * 2);
  QMessageBox msg_box;

  QString path = QDir::currentPath() + "/screenshots/" + current_time;
  path.chop(1);
  path.replace(" ", "_");

  if (is_jpeg == ScreenshotType::SCREENSHOT_JPEG) {
    path += ".jpeg";
    format = "JPG";
  } else {
    path += ".bmp";
    format = "BMP";
  }

  pix.setDevicePixelRatio(2);
  widget_->render(&pix);

  if (pix.save(path, format.toLatin1(), 100)) {
    msg_box.setText("Screenshot OK (" + format + ").");
    msg_box.exec();
  } else {
    msg_box.setText("Screenshot ERROR (" + format + ").");
    msg_box.exec();
  }
}

}  // namespace s21
