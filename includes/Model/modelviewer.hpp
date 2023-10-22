#ifndef INCLUDES_MODEL_MODELVIEWER_HPP_
#define INCLUDES_MODEL_MODELVIEWER_HPP_

#include <QHBoxLayout>
#include <QLabel>
#include <QPoint>
#include <QString>

#include "./imodelviewer.hpp"
#include "./model.hpp"

namespace s21 {

class ModelViewer : public IModelViewer {
 public:
  ModelViewer();
  virtual ~ModelViewer();

  void set_rotate_buff_x(int const &rotate_x) override;
  void set_rotate_buff_y(int const &rotate_y) override;
  void set_rotate_buff_z(int const &rotate_z) override;

  int get_rotate_buff_x() const override;
  int get_rotate_buff_y() const override;
  int get_rotate_buff_z() const override;

  // -- -- -- --

  void MoveRotation(MoveRotationType direction, float value) override;
  void MoveDirection(MoveType direction, float value) override;

  void PolygonsClear() override;
  void Parse(QString const &str) override;
  ErrorType Error() override;
  double MaxSizePerpective() override;

  std::vector<Point> const &PointsArray() override;
  std::vector<std::vector<int>> const &Polygons() override;

  // -- -- -- --

  void TurnObjectX(double const &rotate) override;
  void TurnObjectY(double const &rotate) override;
  void TurnObjectZ(double const &rotate) override;

 private:
  Model *model_;

  bool is_valid_;

  int rotate_x_;
  int rotate_y_;
  int rotate_z_;

  qint64 rotate_before_x_;
  qint64 rotate_before_y_;
  qint64 rotate_before_z_;

  long double move_before_x_;
  long double move_before_y_;
  long double move_before_z_;

  QString m_fileNameObject;

  int m_lineType;
  int m_perspective;
  double m_lineWidth;
  double m_pointSize;
  double m_maxPointSize;
  double m_minPointSize;
  int m_pointType;  // 0 - none; 1 - circle; 2 - square

  long double m_widthLine;
  int m_countScale;
  int m_maxScale;
  int m_minScale;

  bool m_initialized;
  QPoint m_Pos;
  double m_sizePerspective;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_MODELVIEWER_HPP_
