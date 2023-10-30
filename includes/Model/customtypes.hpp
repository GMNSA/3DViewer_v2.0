#ifndef INCLUDES_MODEL_CUSTOMTYPES_HPP_
#define INCLUDES_MODEL_CUSTOMTYPES_HPP_

#include <cstddef>

namespace s21 {

typedef enum PointType {
  POINT_NONE = 0,
  POINT_CIRCLE,
  POINT_SQUARE,
  POINT_END
} PointType;

typedef enum LineType { LINE_SIMPLE = 0, LINE_STIPPLE, LINE_END } LineType;

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

  double& operator[](size_t number) {
    if (number == 0)
      return x;
    else if (number == 1)
      return y;
    else
      return z;
  }
};

// -- -- -- --

enum class ErrorType { ERROR_OK = 0, ERROR_PARSE = 1 };

}  // namespace s21

#endif  // INCLUDES_MODEL_CUSTOMTYPES_HPP_
