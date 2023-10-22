#ifndef INCLUDES_MODEL_HPP_
#define INCLUDES_MODEL_HPP_

#include <string>
#include <vector>

#include "../../lib/MatrixLib//includes/matrix.hpp"

namespace s21 {

enum class ErrorType { ERROR_OK = 0, ERROR_PARSE = 1 };

struct Point {
  double x = 0;
  double y = 0;
  double z = 0;

  double& operator[](size_t number) {
    if (number == 0)
      return x;
    else if (number == 1)
      return y;
    else
      return z;
  }
};

// ----------------------------------------------------------------------------

// x = model_->points_array_[model_->polygons_[i][j]].x;

class Model {
 public:
  Model(std::string const& file = "");
  void ScaleObj(double const& scale);
  void TurnObj(double const& rotation, int const& axis);
  void MoveObj(Point& move_point);
  void PrintPoints();
  void Parse(std::string const& filename = "");

  void set_max_size(double const& size);
  double get_max_size();

  ErrorType get_error();
  void set_error(ErrorType const& error);

  std::string get_file();
  void set_file(std::string const& file);

  std::vector<Point> const& get_points_array();
  std::vector<std::vector<int>> const& get_polygons();

  void PolygonsClear();

 private:
  void AddPoint(char* line);
  void AddPoligon(char* line);
  void AffineTransformation(S21Matrix& matrix_affin);
  void MatrixRotation(S21Matrix& matrix_turn, double const& rotation,
                      int const& axis);
  void add_max_size(Point const& t);

  double max_size_ = 0.0;
  ErrorType error_ = ErrorType::ERROR_OK;
  std::string file_;
  std::vector<Point> points_array_;  // !!
  std::vector<std::vector<int>> polygons_;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_HPP_
