#ifndef INCLUDES_MODEL_IMODELVIEWER_HPP_
#define INCLUDES_MODEL_IMODELVIEWER_HPP_

#include <QString>
#include <vector>

namespace s21 {

enum class ErrorType;
struct Point;

typedef enum MoveRotationType {
  MOVE_ROTATE_Y = 1,
  MOVE_ROTATE_X,
  MOVE_ROTATE_Z,
  MOVE_ROTATE_END
} MoveRotationType;

// -- -- -- --

typedef enum MoveType { MOVE_X = 0, MOVE_Y, MOVE_Z, MOVE_END } MoveType;

// ****************************************************************************

class IModelViewer {
 public:
  virtual ~IModelViewer() {}

  virtual void set_rotate_buff_x(int const &rotate_x) = 0;
  virtual void set_rotate_buff_y(int const &rotate_y) = 0;
  virtual void set_rotate_buff_z(int const &rotate_z) = 0;

  virtual int get_rotate_buff_x() const = 0;
  virtual int get_rotate_buff_y() const = 0;
  virtual int get_rotate_buff_z() const = 0;

  // -- -- -- --

  virtual void MoveRotation(MoveRotationType direction, float value) = 0;
  virtual void MoveDirection(MoveType direction, float value) = 0;

  // -- -- -- --

  virtual void PolygonsClear() = 0;
  virtual void Parse(QString const &str) = 0;
  virtual ErrorType Error() = 0;
  virtual double MaxSizePerpective() = 0;
  virtual std::vector<Point> const &PointsArray() = 0;
  virtual std::vector<std::vector<int>> const &Polygons() = 0;

  // -- -- -- --

  virtual void TurnObjectX(double const &rotate) = 0;
  virtual void TurnObjectY(double const &rotate) = 0;
  virtual void TurnObjectZ(double const &rotate) = 0;
};

}  // namespace s21
#endif  // INCLUDES_MODEL_IMODELVIEWER_HPP_
