#ifndef INCLUDES_MODEL_HPP_
#define INCLUDES_MODEL_HPP_

#include <string>
#include <vector>

#include "../../lib/MatrixLib//includes/matrix.hpp"

namespace s21 {

enum class ERROR_TYPE { ERROR_OK = 0, ERROR_PARSE = 1 };

struct Point {
  double x = 0, y = 0, z = 0;
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

class Model {
 public:
  Model(std::string const& file);
  void ScaleObj(double const& scale);
  void TurnObj(double const& rotation, int const& axis);
  void MoveObj(Point& move_point);
  std::vector<Point> points_array_;  // !!
  std::vector<std::vector<int>> poligons_;
  std::string file_;
  void PrintPoints();
  void Parse(std::string const& filename = "");
  double max_size_ = 0.0;

  ERROR_TYPE error_ = ERROR_TYPE::ERROR_OK;

 private:
  void AddPoint(char* line);
  void AddPoligon(char* line);
  void AffineTransformation(S21Matrix& matrix_affin);
  void MatrixRotation(S21Matrix& matrix_turn, double const& rotation,
                      int const& axis);
  void add_max_size(Point const& t);
};

}  // namespace s21

#endif  // INCLUDES_MODEL_HPP_
