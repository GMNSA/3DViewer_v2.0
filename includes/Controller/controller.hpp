#ifndef INCLUDES_CONTROLLER_CONTROLLER_HPP_
#define INCLUDES_CONTROLLER_CONTROLLER_HPP_

#include <QWidget>

#include "./icontroller.hpp"

namespace s21 {

class Controller : public IController {
 public:
  Controller();
  virtual ~Controller();

  void SetRotateBuffY(int const &value) override;
  void SetRotateBuffX(int const &value) override;
  void SetRotateBuffZ(int const &value) override;

  void MoveDirectionX(float value, MoveType direction = MOVE_X) override;
  void MoveDirectionY(float value, MoveType direction = MOVE_Y) override;
  void MoveDirectionZ(float value, MoveType direction = MOVE_Z) override;

  void MoveRotationX(float value, MoveType direction = MOVE_X) override;
  void MoveRotationY(float value, MoveType direction = MOVE_Y) override;
  void MoveRotationZ(float value, MoveType direction = MOVE_Z) override;
};

}  // namespace s21

#endif  // INCLUDES_CONTROLLER_CONTROLLER_HPP_
