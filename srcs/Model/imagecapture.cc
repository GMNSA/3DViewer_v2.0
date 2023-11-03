#include "../../includes/Model/imagecapture.hpp"

#include <QDir>
#include <QMessageBox>

#define F 1000

namespace s21 {

ImageCapture::ImageCapture(QObject *parent)
    : QObject(parent), widget_(nullptr), gif_fps_(5) {
  if (!(gif_ = new GifCreator)) exit(-1);
  if (!(timer_gif_ = new QTimer)) exit(-1);
  if (!(label_gif_time_ = new QLabel)) exit(-1);

  label_gif_time_->setText("Piter pa");
  label_gif_time_->setAlignment(Qt::AlignTop);
  label_gif_time_->setAlignment(Qt::AlignLeft);
  label_gif_time_->move(40, 40);
  label_gif_time_->raise();
  QFont font = label_gif_time_->font();
  font.setPointSize(20);
  font.setBold(true);
  label_gif_time_->setFont(font);

  connect(timer_gif_, &QTimer::timeout, this, &ImageCapture::StartGif);
}

// ----------------------------------------------------------------------------

ImageCapture::~ImageCapture() {
  if (widget_ == nullptr)
    if (gif_) delete gif_;

  if (timer_gif_) delete timer_gif_;
  if (label_gif_time_) delete label_gif_time_;
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

    qDebug() << "YES";
    label_gif_time_->setText("Piter pa");
    label_gif_time_->setAlignment(Qt::AlignTop);
    label_gif_time_->setAlignment(Qt::AlignLeft);
    label_gif_time_->move(40, 40);
    label_gif_time_->raise();
    QFont font = label_gif_time_->font();
    font.setPointSize(20);
    font.setBold(true);
    label_gif_time_->setFont(font);
    // label_gif_time_->setText("HOOOOOOODIIII");
    // label_gif_time_->setStyleSheet("QLabel { color : white; }");
    // qDebug() << "OK STYLESHEET";
  }
}

// ----------------------------------------------------------------------------

QLabel *ImageCapture::get_label_gif_time() const { return label_gif_time_; }

// ----------------------------------------------------------------------------

void ImageCapture::DoGif() {
  if (!widget_) return;

  start_time_ = 0;
  end_time_ = F / gif_fps_;
  timer_gif_->start(F / gif_fps_);
  frame_num_ = 0;
}

// -------------------------------------------------------

void ImageCapture::ChangeColorGifTime(bool const &is_black) {
  Q_UNUSED(is_black);
  if (is_black)
    label_gif_time_->setStyleSheet("QLabel { color : black; }");
  else
    label_gif_time_->setStyleSheet("QLabel { color : white; }");
}

// -------------------------------------------------------

void ImageCapture::StartGif() {
  if (!widget_) return;

  if (start_time_ == end_time_) {
    float time = 0;
    QPixmap gif(widget_->size());
    widget_->render(&gif);
    gif.scaled(640, 480, Qt::IgnoreAspectRatio);

    if (!gif.save(gif_->imageFilePathMask().arg(frame_num_))) {
      // logging_line(ERROR_ANOTHER, "", __LINE__, "[ERROR] gif not save
      // image.", 1);
    }

    time = start_time_ / F;
    label_gif_time_->setText(QString::number(time));
    end_time_ += F / gif_fps_;
    ++frame_num_;
  }

  int gif_length = 5;

  if (start_time_ >= F * gif_length) {
    if (gif_->createGif(frame_num_, gif_fps_)) {
      qDebug() << "GIF OK";
    } else {
      qDebug() << "GIF FALSE";
    }

    timer_gif_->stop();
    qDebug() << "gif path: " << gif_->gifFilePath();
    label_gif_time_->setText("");
  }
  start_time_ += (float)F / gif_fps_;
}

// ----------------------------------------------------------------------------

// PRIATE --------------------------------------------------------------------

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

// -------------------------------------------------------

}  // namespace s21
