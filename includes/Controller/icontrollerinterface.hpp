#ifndef INCLUDES_CONTROLLER_ICONTROLLER_HPP_
#define INCLUDES_CONTROLLER_ICONTROLLER_HPP_

#include <QtPlugin>

#include "../Model/customtypes.hpp"

namespace s21 {

class IControllerInterface {
 public:
  virtual ~IControllerInterface() {}

  virtual void SetRotateBuffY(int const &value) = 0;
  virtual void SetRotateBuffX(int const &value) = 0;
  virtual void SetRotateBuffZ(int const &value) = 0;

  virtual void MoveDirectionX(float value, MoveType direction = MOVE_X) = 0;
  virtual void MoveDirectionY(float value, MoveType direction = MOVE_Y) = 0;
  virtual void MoveDirectionZ(float value, MoveType direction = MOVE_Z) = 0;

  virtual void MoveRotationX(float value, MoveType direction = MOVE_X) = 0;
  virtual void MoveRotationY(float value, MoveType direction = MOVE_Y) = 0;
  virtual void MoveRotationZ(float value, MoveType direction = MOVE_Z) = 0;
};

}  // namespace s21

Q_DECLARE_INTERFACE(s21::IControllerInterface, "s21_IControllerInterface");

#endif  // INCLUDES_CONTROLLER_ICONTROLLER_HPP_
