#ifndef INCLUDES_CONTROLLER_ICONTROLLERINTERFACE_HPP_
#define INCLUDES_CONTROLLER_ICONTROLLERINTERFACE_HPP_

#include <QtPlugin>

#include "../Model/customtypes.hpp"

namespace s21 {

class IControllerInterface {
 public:
  virtual ~IControllerInterface() {}

  virtual void MoveDirectionX(float const &value,
                              MoveType const &direction = MOVE_DIRECTION_X) = 0;
  virtual void MoveDirectionY(float const &value,
                              MoveType const &direction = MOVE_DIRECTION_Y) = 0;
  virtual void MoveDirectionZ(float const &value,
                              MoveType const &direction = MOVE_DIRECTION_Z) = 0;

  virtual void MoveRotationX(
      float const &value,
      MoveRotationType const &direction = MOVE_ROTATE_X) = 0;
  virtual void MoveRotationY(
      float const &value,
      MoveRotationType const &direction = MOVE_ROTATE_Y) = 0;
  virtual void MoveRotationZ(
      float const &value,
      MoveRotationType const &direction = MOVE_ROTATE_Z) = 0;

  virtual void TurnObjectX(double const &rotate) = 0;
  virtual void TurnObjectY(double const &rotate) = 0;

  virtual void WriteConfig(QString const &filename = "") = 0;
  virtual void LoadConfig(QString const &filename = "") = 0;

  virtual void ChangeBackgroundColor(int const &value) = 0;
  virtual void ChangePointColor(int const &value) = 0;
  virtual void ChangeLinesColor(int const &value) = 0;

  virtual void OpenFile(QString const &value) = 0;

  virtual void IncremenetScale() = 0;
  virtual void DecrementScale() = 0;
  virtual void ChangeScale(int const &value) = 0;

  virtual void ChangeLineWidth(double const &value) = 0;
  virtual void ChangePointSize(int const &value) = 0;
  virtual void ChangeTypePoint(PointType const &type) = 0;
  virtual void ChangePerspective(int const &value) = 0;
  virtual void ChangeLineType(LineType const &type) = 0;

  virtual void ScreenshotJPEG(QWidget *widget) = 0;
  virtual void ScreenshotBMP(QWidget *widget) = 0;

  virtual void Gif(QWidget *widget) = 0;

  // -- -- -- --
};

}  // namespace s21

Q_DECLARE_INTERFACE(s21::IControllerInterface, "s21_IControllerInterface");

#endif  //  INCLUDES_CONTROLLER_ICONTROLLERINTERFACE_HPP_
