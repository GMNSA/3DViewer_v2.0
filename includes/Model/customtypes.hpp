#ifndef INCLUDES_MODEL_CUSTOMTYPES_HPP_
#define INCLUDES_MODEL_CUSTOMTYPES_HPP_

#include <QColor>
#include <QString>
#include <cstddef>

namespace s21 {

typedef enum PointType {
  POINT_NONE = 0,
  POINT_CIRCLE,
  POINT_SQUARE,
  POINT_END
} PointType;

typedef enum LineType { LINE_SIMPLE = 0, LINE_STIPPLE, LINE_END } LineType;

typedef enum ScreenshotType {
  SCREENSHOT_JPEG = 0,
  SCREENSHOT_BPM,
  SCREENSHOT_END
} ScreenshotType;

typedef enum PerspectiveType {
  PERSPECTIVE_CENTRAL = 0,
  PERSPECTIVE_PARALLEL,
  PERSPECTIVE_END
} PerspectiveType;

// -- -- -- --

typedef enum MoveRotationType {
  MOVE_ROTATE_Y = 1,
  MOVE_ROTATE_X,
  MOVE_ROTATE_Z,
  MOVE_ROTATE_END
} MoveRotationType;

// -- -- -- --

typedef enum MoveType { MOVE_X = 0, MOVE_Y, MOVE_Z, MOVE_END } MoveType;

// -- -- -- --

struct Point {
  double x = 0;
  double y = 0;
  double z = 0;

  double &operator[](size_t number) {
    if (number == 0)
      return x;
    else if (number == 1)
      return y;
    else
      return z;
  }
};

// -- -- -- --

typedef struct InfoData {
  QString label_name;
  QString label_vertex;
  QString label_polygons;

  void ClearInfo() {
    label_name.clear();
    label_vertex.clear();
    label_polygons.clear();
  }
} InfoData;

// -- -- -- --

enum class ErrorType { ERROR_OK = 0, ERROR_PARSE = 1 };

// -- -- -- --

typedef struct DataViewer {
  bool is_valid;

  int rotate_x;
  int rotate_y;
  int rotate_z;

  qint64 rotate_before_x;
  qint64 rotate_before_y;
  qint64 rotate_before_z;

  long double move_before_x;
  long double move_before_y;
  long double move_before_z;

  QColor line_color;
  QColor point_color;
  QColor background_color;

  LineType line_type;
  int perspective;
  double line_width;
  double point_size;
  double max_point_size;
  double min_point_size;
  PointType point_type;

  int count_scale;
  int max_scale;
  int min_scale;

  double size_perspective;
  double max_perspective;

  QString filename_object;

  InfoData info_data;

  void ClearData() {
    info_data.ClearInfo();
    is_valid = 0;

    rotate_x = 0;
    rotate_y = 0;
    rotate_z = 0;

    rotate_before_x = 0;
    rotate_before_y = 0;
    rotate_before_z = 0;

    move_before_x = 0;
    move_before_y = 0;
    move_before_z = 0;

    line_color = {1, 1, 1};
    point_color = {1, 1, 1};
    background_color = {1, 1, 1};

    line_type = LineType::LINE_SIMPLE;
    perspective = 0;
    line_width = 1.0;
    point_size = 1.0;
    max_point_size = 25.0;
    min_point_size = 0.0;
    point_type = PointType::POINT_NONE;
    count_scale = 10;
    max_scale = 60;
    min_scale = -40;
    size_perspective = 0.0;
    max_perspective = 0.0;

    filename_object = "";
  }
} DataViewer;

}  // namespace s21

#endif  // INCLUDES_MODEL_CUSTOMTYPES_HPP_
