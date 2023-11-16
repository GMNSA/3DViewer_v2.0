#ifndef INCLUDES_MODEL_IMAGECAPTURE_HPP_
#define INCLUDES_MODEL_IMAGECAPTURE_HPP_

#include <QLabel>
#include <QObject>
#include <QTimer>
#include <QWidget>

#include "../../includes/Model/customtypes.hpp"
#include "../../includes/Model/ifacademodel.hpp"
#include "../lib/QtGifImage/includes/gifcreator.h"

namespace s21 {

class ImageCapture : public QObject {
 public:
  explicit ImageCapture(IFacadeModel *facade_model, QObject *parent = nullptr);
  ImageCapture(ImageCapture const &other) = delete;
  ImageCapture &operator=(ImageCapture const &other) = delete;

  virtual ~ImageCapture();

  void set_widget(QWidget *my_widget);
  bool get_is_start_timer() const;

  void ScreenshotJPEG();
  void ScreenshotBMP();
  void DoGif();

 private:
  void Screenshot(int const &is_jpeg = ScreenshotType::SCREENSHOT_JPEG);
  void StartGif();

 private:
  IFacadeModel *facade_model_;
  QWidget *widget_;
  int gif_fps_;
  double start_time_;
  int end_time_;
  int frame_num_ = 0;

  GifCreator *gif_;
  QTimer *timer_gif_;
  bool is_start_timer_;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_IMAGECAPTURE_HPP_
