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

  void MoveRotation(e_moveRotatinoType direction, float value) override;
  void MoveDirection(e_moveType direction, float value) override;

 private:
  Model *model_;

  bool m_isValid;

  int m_rotateX;
  int m_rotateY;
  int m_rotateZ;

  qint64 m_rotateBeforeX;
  qint64 m_rotateBeforeY;
  qint64 m_rotateBeforeZ;
  long double m_moveBeforeX;
  long double m_moveBeforeY;
  long double m_moveBeforeZ;

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
