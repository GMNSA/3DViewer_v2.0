#ifndef INCLUDES_MODEL_IMAGECAPTURE_HPP_
#define INCLUDES_MODEL_IMAGECAPTURE_HPP_

#include <QWidget>

#include "../../includes/Model/customtypes.hpp"
// #include "../lib/QtGifImage/includes/gifcreator.h"

namespace s21 {

class ImageCapture {
 public:
  ImageCapture();
  ImageCapture(ImageCapture const &other) = delete;
  ImageCapture &operator=(ImageCapture const &other) = delete;

  virtual ~ImageCapture();

  void set_widget(QWidget *my_widget);

  void ScreenshotJPEG();
  void ScreenshotBMP();

 private:
  void Screenshot(int const &is_jpeg = ScreenshotType::SCREENSHOT_JPEG);

 private:
  QWidget *widget_;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_IMAGECAPTURE_HPP_
