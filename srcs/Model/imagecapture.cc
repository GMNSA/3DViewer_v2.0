#include "../../includes/Model/imagecapture.hpp"

#include <QDir>
#include <QMessageBox>

namespace s21 {

ImageCapture::ImageCapture(IFacadeModel *facade_model, QObject *parent)
    : QObject(parent),
      facade_model_(facade_model),
      widget_(nullptr),
      gif_fps_(10) {
  if (!(gif_ = new GifCreator)) exit(-1);
  if (!(timer_gif_ = new QTimer)) exit(-1);
  is_start_timer_ = false;

  connect(timer_gif_, &QTimer::timeout, this, &ImageCapture::StartGif);
}

// ----------------------------------------------------------------------------

ImageCapture::~ImageCapture() {
  if (widget_ == nullptr)
    if (gif_) delete gif_;

  if (timer_gif_) delete timer_gif_;
}

// ----------------------------------------------------------------------------

void ImageCapture::ScreenshotJPEG() { Screenshot(); }

// ----------------------------------------------------------------------------

void ImageCapture::ScreenshotBMP() {
  Screenshot(ScreenshotType::SCREENSHOT_BPM);
}

// ----------------------------------------------------------------------------

void ImageCapture::set_widget(QWidget *my_widget) {
  if (widget_ != my_widget) {
    widget_ = my_widget;
    gif_->setParent(widget_);
  }
}

bool ImageCapture::get_is_start_timer() const { return is_start_timer_; }

// ----------------------------------------------------------------------------

void ImageCapture::DoGif() {
  if (!widget_) return;

  start_time_ = 0;
  end_time_ = 1000 / gif_fps_;
  timer_gif_->start(1000 / gif_fps_);
  frame_num_ = 0;
}

// -------------------------------------------------------

void ImageCapture::StartGif() {
  if (!widget_) return;

  if (start_time_ == end_time_) {
    QPixmap gif(widget_->size());
    widget_->render(&gif);
    gif.scaled(640, 480, Qt::IgnoreAspectRatio);

    end_time_ += 1000 / gif_fps_;
    ++frame_num_;
  }

  int gif_length = 5;

  if (start_time_ >= 1000 * gif_length) {
    if (gif_->createGif(frame_num_, gif_fps_)) {
      qDebug() << "GIF OK";
      is_start_timer_ = false;
      facade_model_->NotifyMainWindow();
    } else {
      qDebug() << "GIF FALSE";
    }

    timer_gif_->stop();
    qDebug() << "gif path: " << gif_->gifFilePath();
  }
  start_time_ += 1000.0 / gif_fps_;
}

// PRIATE --------------------------------------------------------------------

void ImageCapture::Screenshot(int const &is_jpeg) {
  if (!widget_) return;
  long ttime = time(0);
  QString current_time = ctime(&ttime);
  QString format;
  QPixmap pix(widget_->size() * 2);
  QMessageBox msg_box;
  is_start_timer_ = true;

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

// -------------------------------------------------------

}  // namespace s21
