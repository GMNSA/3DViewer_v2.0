#ifndef INCLUDES_CONTROLLER_CONTROLLER_HPP_
#define INCLUDES_CONTROLLER_CONTROLLER_HPP_

#include "./icontroller.hpp"

namespace s21 {

class Controller : public IController {
 public:
  Controller();
  virtual ~Controller();

  virtual void rotateX(int value_) = 0;
  virtual void rotateY(int value_) = 0;
  virtual void rotateZ(int value_) = 0;
};

}  // namespace s21

#endif  // INCLUDES_CONTROLLER_CONTROLLER_HPP_
