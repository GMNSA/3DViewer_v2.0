#ifndef INCLUDES_MODEL_IMODELVIEWER_HPP_
#define INCLUDES_MODEL_IMODELVIEWER_HPP_

namespace s21 {

typedef enum e_moveRotationType {
  MOVE_ROTATE_Y = 1,
  MOVE_ROTATE_X,
  MOVE_ROTATE_Z,
  MOVE_ROTATE_END
} e_moveRotatinoType;

// -- -- -- --

typedef enum e_moveType { MOVE_X = 0, MOVE_Y, MOVE_Z, MOVE_END } e_moveType;

// ****************************************************************************

class IModelViewer {
 public:
  virtual ~IModelViewer() {}

  virtual void set_rotate_buff_x(int const &rotate_x) = 0;
  virtual void set_rotate_buff_y(int const &rotate_y) = 0;
  virtual void set_rotate_buff_z(int const &rotate_z) = 0;

  virtual int get_rotate_buff_x() const = 0;
  virtual int get_rotate_buff_y() const = 0;
  virtual int get_rotate_buff_z() const = 0;

  // -- -- -- --

  virtual void MoveRotation(e_moveRotatinoType direction, float value) = 0;
  virtual void MoveDirection(e_moveType direction, float value) = 0;
};

}  // namespace s21
#endif  // INCLUDES_MODEL_IMODELVIEWER_HPP_
