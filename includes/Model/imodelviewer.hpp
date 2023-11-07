#ifndef INCLUDES_MODEL_IMODELVIEWER_HPP_
#define INCLUDES_MODEL_IMODELVIEWER_HPP_

#include <QLabel>
#include <QString>
#include <vector>

#include "../View/imainmenuobserver.hpp"
#include "../View/iwidgetopenglobserver.hpp"
#include "./customtypes.hpp"

namespace s21 {

// class IWidgetOpenglObserver;
// class IMainWindowObserver;

enum class ErrorType;
struct Point;

// ****************************************************************************

class IModelViewer {
 public:
  virtual ~IModelViewer() {}

  virtual void set_rotate_x(int const &rotate) = 0;
  virtual void set_rotate_y(int const &rotate) = 0;
  virtual void set_rotate_z(int const &rotate) = 0;

  virtual int get_rotate_x() const = 0;
  virtual int get_rotate_y() const = 0;
  virtual int get_rotate_z() const = 0;

  // -- -- -- --

  virtual void set_background_color(int const value_) = 0;
  virtual QColor get_background_color() const = 0;

  virtual void set_point_color(int const &value) = 0;
  virtual QColor get_point_color() const = 0;

  virtual void set_lines_color(int const &value) = 0;
  virtual QColor get_lines_color() const = 0;

  // -- -- -- --

  virtual void set_perspective(int const &value) = 0;

  virtual int get_perspective() const = 0;
  virtual double get_size_perspective() const = 0;
  virtual QString get_filename_object() const = 0;
  virtual bool get_is_valid() const = 0;

  // -- -- -- --

  virtual void set_line_type(LineType const &type) = 0;
  virtual LineType get_line_type() const = 0;

  // -- -- -- --

  virtual void set_point_type(PointType const &type) = 0;
  virtual PointType get_point_type() const = 0;
  virtual void set_point_size(double const &size) = 0;

  virtual double get_point_size() const = 0;
  virtual double get_point_size_max() const = 0;
  virtual double get_point_size_min() const = 0;

  // -- -- -- --

  virtual void set_line_width(double const &value) = 0;
  virtual double get_line_width() const = 0;

  // -- -- -- --

  virtual void set_scale(int const &value) = 0;
  virtual void set_max_scale(int const &value) = 0;
  virtual void set_min_scale(int const &value) = 0;

  virtual int get_scale() const = 0;
  virtual int get_max_scale() const = 0;
  virtual int get_min_scale() const = 0;

  // -- -- -- --

  virtual void OpenFileObject(QString const &filename) = 0;

  // -- -- -- --

  virtual void MoveRotation(MoveRotationType direction, float value) = 0;
  virtual void MoveDirection(MoveType direction, float value) = 0;

  virtual InfoData const &get_info_file() = 0;

  // -- -- -- --

  virtual void PolygonsClear() = 0;
  virtual ErrorType Error() = 0;
  virtual double MaxSizePerpective() = 0;
  virtual std::vector<Point> const &PointsArray() = 0;
  virtual std::vector<std::vector<int>> const &Polygons() = 0;

  // -- -- -- --

  virtual void TurnObjectX(double const &rotate) = 0;
  virtual void TurnObjectY(double const &rotate) = 0;

  // -- -- -- --

  virtual void ScaleObject(double const &scale) = 0;

  // -- -- -- --

  virtual void Attach(IWidgetOpenglObserver *observer) = 0;
  virtual void Detach(IWidgetOpenglObserver *observer) = 0;
  virtual void NotifyWidgetOpengl() = 0;
  virtual void NotifyWidgetOpenglInfo() = 0;

  virtual void Attach(IMainWindowObserver *observer) = 0;
  virtual void Detach(IMainWindowObserver *observer) = 0;
  virtual void NotifyMainWindow() = 0;

  // -- -- -- --

  virtual bool WriteToFileConfig(QString path = "") = 0;
  virtual bool LoadConfig(QString path = "") = 0;

  // -- -- -- --

  virtual void ScreenshotJPEG(QWidget *widget) = 0;
  virtual void ScreenshotBMP(QWidget *widget) = 0;

  virtual void Gif(QWidget *widget) = 0;

  virtual QLabel *GetLabelGifTime() const = 0;
};

}  // namespace s21
#endif  // INCLUDES_MODEL_IMODELVIEWER_HPP_
