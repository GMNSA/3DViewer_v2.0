#ifndef INCLUDES_CONTROLLER_CONTROLLER_HPP_
#define INCLUDES_CONTROLLER_CONTROLLER_HPP_

#include <QWidget>

#include "../includes/Model/modelviewer.hpp"
#include "../includes/View/mainwindow.hpp"
#include "./icontrollerinterface.hpp"

class IModelViewer;

namespace s21 {

class Controller : public QObject, virtual public IControllerInterface {
  Q_OBJECT
  Q_INTERFACES(s21::IControllerInterface)
 public:
  Controller(IModelViewer *model);
  Controller(Controller const &other) = delete;
  Controller &operator=(Controller const &other) = delete;

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

 private:
  MainWindow *view_;
  IModelViewer *model_;
};

}  // namespace s21

#endif  // INCLUDES_CONTROLLER_CONTROLLER_HPP_
