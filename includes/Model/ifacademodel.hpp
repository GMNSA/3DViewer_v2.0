#ifndef INCLUDES_MDOEL_IFACADEMODEL_HPP_
#define INCLUDES_MDOEL_IFACADEMODEL_HPP_

#include <QLabel>
#include <QString>
#include <vector>

#include "../View/imainmenuobserver.hpp"
#include "../View/iwidgetopenglobserver.hpp"
#include "./customtypes.hpp"

namespace s21 {

enum class ErrorType;
struct Point;

class IFacadeModel {
 public:
  virtual ~IFacadeModel() {}

  virtual void Attach(IWidgetOpenglObserver *observer) = 0;
  virtual void Detach(IWidgetOpenglObserver *observer) = 0;
  virtual void NotifyWidgetOpengl() = 0;
  virtual void NotifyWidgetOpenglInfo() = 0;

  virtual void Attach(IMainWindowObserver *observer) = 0;
  virtual void Detach(IMainWindowObserver *observer) = 0;
  virtual void NotifyMainWindow() = 0;

  // -- -------------------------------------------- --

  virtual void ChangeBackgroundColor(int const &value) = 0;
  virtual void ChangePointColor(int const &value) = 0;
  virtual void ChangeLinesColor(int const &value) = 0;

  virtual void OpenFile(QString const &filename) = 0;

  virtual void IncremenetScale() = 0;
  virtual void DecrementScale() = 0;

  virtual void ChangeLineWidth(double const &value) = 0;
  virtual void ChangePointSize(int const &value) = 0;
  virtual void ChangeTypePoint(PointType const &type) = 0;
  virtual void ChangePerspective(int const &value) = 0;
  virtual void ChangeLineType(LineType const &type) = 0;

  virtual DataViewer const &GetDataViewer() const = 0;

  // -- -- -- --

  // virtual void OpenFileData(QString const &filename) = 0;

  // -- -- -- --

  virtual void MoveRotationSlider(MoveRotationType direction, float value) = 0;
  virtual void MoveDirectionSlider(MoveType direction, float value) = 0;
  virtual void MoveRotationMouse(MoveRotationType direction, float value) = 0;

  virtual void PolygonsClear() = 0;
  virtual ErrorType get_error() = 0;

  virtual std::vector<Point> const &PointsArray() = 0;
  virtual std::vector<std::vector<int>> const &Polygons() = 0;

  // -- -- -- --

  virtual void ResetData() = 0;

  // -- -- -- --

  virtual void ScreenshotJPEG(QWidget *widget) = 0;
  virtual void ScreenshotBMP(QWidget *widget) = 0;

  virtual void Gif(QWidget *widget) = 0;
  virtual QLabel *GetLabelGifTime() const = 0;

  // -- -- -- --

  virtual bool SaveData(QString const &path = "") = 0;
  virtual bool LoadData(QString const &path = "") = 0;

 protected:
};

}  // namespace s21

#endif  // INCLUDES_MDOEL_IFACADEMODEL_HPP_
