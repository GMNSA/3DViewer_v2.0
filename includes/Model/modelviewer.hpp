#ifndef INCLUDES_MODEL_MODELVIEWER_HPP_
#define INCLUDES_MODEL_MODELVIEWER_HPP_

#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QPoint>
#include <QString>
#include <vector>

#include "./imagecapture.hpp"
#include "./imodelviewer.hpp"
#include "./model.hpp"

namespace s21 {

// ----------------------------------------------------------------------------

class ModelViewer : public IModelViewer {
 public:
  ModelViewer();
  virtual ~ModelViewer();

 public:  // -- OVERRIDE --
  void set_rotate_x(int const &rotate) override;
  void set_rotate_y(int const &rotate) override;
  void set_rotate_z(int const &rotate) override;

  int get_rotate_x() const override;
  int get_rotate_y() const override;
  int get_rotate_z() const override;

  // -- -- -- --

  void set_rotate_buff_x(int const &rotate) override;
  void set_rotate_buff_y(int const &rotate) override;
  void set_rotate_buff_z(int const &rotate) override;

  int get_rotate_buff_x() const override;
  int get_rotate_buff_y() const override;
  int get_rotate_buff_z() const override;

  // -- -- -- --

  void set_background_color(int const value_) override;
  QColor get_background_color() const override;
  void set_point_color(int const &value) override;
  QColor get_point_color() const override;
  void set_lines_color(int const &value) override;
  QColor get_lines_color() const override;

  // -- -- -- --

  void set_perspective(int const &value) override;

  int get_perspective() const override;
  double get_size_perspective() const override;
  QString get_filename_object() const override;

  bool get_is_valid() const override;

  void set_line_type(LineType const &type) override;
  LineType get_line_type() const override;

  void set_point_type(PointType const &type) override;
  PointType get_point_type() const override;
  void set_point_size(double const &size) override;
  double get_point_size() const override;
  double get_point_size_max() const override;
  double get_point_size_min() const override;

  void set_line_width(double const &value) override;
  double get_line_width() const override;

  // -- -- -- --

  void set_scale(int const &value) override;
  void set_max_scale(int const &value) override;
  void set_min_scale(int const &value) override;

  int get_scale() const override;
  int get_max_scale() const override;
  int get_min_scale() const override;

  // -- -- -- --

  void OpenFileObject(QString const &filename) override;

  // -- -- -- --

  void MoveRotation(MoveRotationType direction, float value) override;
  void MoveDirection(MoveType direction, float value) override;

  InfoData const &get_info_file() override;

  void PolygonsClear() override;
  void Parse(QString const &str) override;
  ErrorType Error() override;
  double MaxSizePerpective() override;

  std::vector<Point> const &PointsArray() override;
  std::vector<std::vector<int>> const &Polygons() override;

  // -- -- -- --

  void TurnObjectX(double const &rotate) override;
  void TurnObjectY(double const &rotate) override;
  // void TurnObjectZ(double const &rotate) override;

  void ScaleObject(double const &scale) override;

  // -- -- -- --

  void Attach(IWidgetOpenglObserver *observer) override;
  void Detach(IWidgetOpenglObserver *observer) override;
  void NotifyWidgetOpengl() override;
  void NotifyWidgetOpenglInfo() override;

  // -- -- -- --

  void Attach(IMainWindowObserver *observer) override;
  void Detach(IMainWindowObserver *observer) override;
  void NotifyMainWindow() override;

  void DefaultConfig();
  void DefaultConfigSimple();

  // -- -- -- --

  bool WriteToFileConfig(QString path = "") override;
  bool LoadConfig(QString path = "") override;

  // -- -- -- --

  void ScreenshotJPEG(QWidget *widget) override;
  void ScreenshotBMP(QWidget *widget) override;

  void Gif(QWidget *widget) override;
  QLabel *GetLabelGifTime() const override;

 public:  // -- origin --
  int CountNumber(int number_);
  int UpdateData();

 private:
  void UpdateInfoObject();

 private:
  Model *model_;
  ImageCapture *image_capture_;

  bool is_valid_;

  int rotate_x_;
  int rotate_y_;
  int rotate_z_;

  qint64 rotate_before_x_;
  qint64 rotate_before_y_;
  qint64 rotate_before_z_;

  long double move_before_x_;
  long double move_before_y_;
  long double move_before_z_;

  QColor line_color_;
  QColor point_color_;
  QColor background_color_;

  LineType line_type_;
  int perspective_;
  double line_width_;
  double point_size_;
  double max_point_size_;
  double min_point_size_;
  PointType point_type_;  // 0 - none; 1 - circle; 2 - square

  // long double widht_line_;
  int count_scale_;
  int max_scale_;
  int min_scale_;

  // bool initialized_;
  QPoint m_Pos;
  double size_perspective_;

  QString filename_object_;

  InfoData info_data_;

  QList<IWidgetOpenglObserver *> list_widget_opengl_;
  QList<IMainWindowObserver *> list_main_menu_;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_MODELVIEWER_HPP_
