#ifndef INCLUDES_MODEL_MODELVIEWER_HPP_
#define INCLUDES_MODEL_MODELVIEWER_HPP_

#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QPoint>
#include <QString>
#include <vector>

#include "./imagecapture.hpp"
#include "./imodelviewer.hpp"
#include "./model.hpp"

namespace s21 {

// ----------------------------------------------------------------------------

class ModelViewer {
 public:
  ModelViewer();
  virtual ~ModelViewer();

 public:
  void SetRotateX(int const &rotate);
  void SetRotateY(int const &rotate);
  void SetRotateZ(int const &rotate);
  void SetBackgroundColor(int const value_);
  void SetPointColor(int const &value);
  void SetLinesColor(int const &value);
  void SetLineType(LineType const &type);
  void SetPointType(PointType const &type);
  void SetPointSize(double const &size);
  void SetLineWidth(double const &value);
  void SetScale(int const &value);
  void SetMaxScale(int const &value);
  void SetMinScale(int const &value);
  void SetPerspective(int const &value);
  void SetFilename(QString const &path);
  void CopyData(DataViewer const &other);

  DataViewer const &GetDataViewer() const;

  // -- -- -- --

  bool OpenFileObject(QString const &filename);

  // -- -- -- --

  void MoveRotation(MoveRotationType direction, float value);
  void MoveDirection(MoveType direction, float value);

  InfoData const &get_info_file();

  void PolygonsClear();
  ErrorType Error();
  double MaxSizePerpective();

  std::vector<Point> const &PointsArray();
  std::vector<std::vector<int>> const &Polygons();

  // -- -- -- --

  void TurnObjectX(double const &rotate);
  void TurnObjectY(double const &rotate);

  // -- -- -- --

  void ScaleObject(double const &scale);

  // -- -- -- --

  void DefaultConfig();
  void DefaultConfigSimple();

  // -- -- -- --

  bool WriteToFileConfig(QString path = "");
  bool LoadConfig(QString path = "");

 public:  // -- origin --
          // TODO(probiuss): need to think move to update data from public to
          // private.
  bool UpdateData();

 private:
  void UpdateInfoObject();
  int CountNumber(int number_);

 private:
  Model *model_;
  DataViewer *data_viewer_;

  QList<IWidgetOpenglObserver *> list_widget_opengl_;
  QList<IMainWindowObserver *> list_main_menu_;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_MODELVIEWER_HPP_
