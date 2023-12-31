#ifndef INCLUDES_CONTROLLER_CONTROLLER_HPP_
#define INCLUDES_CONTROLLER_CONTROLLER_HPP_

#include <QWidget>

#include "../includes/Model/ifacademodel.hpp"
#include "../includes/View/mainwindow.hpp"
#include "./icontrollerinterface.hpp"

class IFacadeModel;

namespace s21 {

class Controller : public QObject, virtual public IControllerInterface {
  Q_OBJECT
  Q_INTERFACES(s21::IControllerInterface)

 public:
  explicit Controller(IFacadeModel *model);
  Controller(Controller const &other) = delete;
  Controller &operator=(Controller const &other) = delete;

  virtual ~Controller();

  void MoveDirectionX(float const &value,
                      MoveType const &direction = MOVE_DIRECTION_X) override;
  void MoveDirectionY(float const &value,
                      MoveType const &direction = MOVE_DIRECTION_Y) override;
  void MoveDirectionZ(float const &value,
                      MoveType const &direction = MOVE_DIRECTION_Z) override;

  void MoveRotationX(float const &value, MoveRotationType const &direction =
                                             MOVE_ROTATE_X) override;
  void MoveRotationY(float const &value, MoveRotationType const &direction =
                                             MOVE_ROTATE_Y) override;
  void MoveRotationZ(float const &value, MoveRotationType const &direction =
                                             MOVE_ROTATE_Z) override;

  void TurnObjectX(double const &rotate) override;
  void TurnObjectY(double const &rotate) override;

  void ChangeBackgroundColor(int const &value) override;
  void ChangePointColor(int const &value) override;
  void ChangeLinesColor(int const &value) override;

  void WriteConfig(QString const &filename = "") override;
  void LoadConfig(QString const &filename = "") override;

  void OpenFile(QString const &value) override;

  void IncremenetScale() override;
  void DecrementScale() override;
  void ChangeScale(int const &value) override;

  void ChangeLineWidth(double const &value) override;
  void ChangePointSize(int const &value) override;
  void ChangeTypePoint(PointType const &type) override;
  void ChangePerspective(int const &value) override;
  void ChangeLineType(LineType const &type) override;

  void ScreenshotJPEG(QWidget *widget) override;
  void ScreenshotBMP(QWidget *widget) override;
  void Gif(QWidget *widget) override;

 private:
  MainWindow *view_;
  IFacadeModel *model_;
};

}  // namespace s21

#endif  // INCLUDES_CONTROLLER_CONTROLLER_HPP_
