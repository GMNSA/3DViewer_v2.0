#ifndef INCLUDES_VIEW_CUSTOMTYPES_HPP_
#define INCLUDES_VIEW_CUSTOMTYPES_HPP_

namespace s21 {

typedef enum MoveRotationType {
  MOVE_ROTATE_Y = 1,
  MOVE_ROTATE_X,
  MOVE_ROTATE_Z,
  MOVE_ROTATE_END
} MoveRotationType;

// -- -- -- --

typedef enum MoveType { MOVE_X = 0, MOVE_Y, MOVE_Z, MOVE_END } MoveType;

}  // namespace s21

#endif  // INCLUDES_VIEW_CUSTOMTYPES_HPP_
