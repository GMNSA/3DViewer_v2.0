#ifndef INCLUDES_MODEL_IMAGECAPTURE_HPP_
#define INCLUDES_MODEL_IMAGECAPTURE_HPP_

#include <QLabel>
#include <QObject>
#include <QTimer>
#include <QWidget>

#include "../../includes/Model/customtypes.hpp"
#include "../lib/QtGifImage/includes/gifcreator.h"

namespace s21 {

class ImageCapture : public QObject {
 public:
  explicit ImageCapture(QObject *parent = nullptr);
  ImageCapture(ImageCapture const &other) = delete;
  ImageCapture &operator=(ImageCapture const &other) = delete;

  virtual ~ImageCapture();

  void set_widget(QWidget *my_widget);

  void ScreenshotJPEG();
  void ScreenshotBMP();

  void DoGif();
  void StartGif();

  void ChangeColorGifTime(bool const &is_black);
  QLabel *get_label_gif_time() const;

 private:
  void Screenshot(int const &is_jpeg = ScreenshotType::SCREENSHOT_JPEG);

 private:
  QWidget *widget_;
  int gif_fps_;
  double start_time_;
  int end_time_;
  // int count_frame_ = 0;
  int frame_num_ = 0;

  GifCreator *gif_;
  QTimer *timer_gif_;
  QLabel *label_gif_time_;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_IMAGECAPTURE_HPP_
