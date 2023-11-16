#ifndef INCLUDES_MODEL_HPP_
#define INCLUDES_MODEL_HPP_

#include <string>
#include <vector>

#include "../../lib/MatrixLib/includes/matrix.hpp"
#include "./customtypes.hpp"

/**
 * @brief Class for tests.
 */
class ModelViewerTest;

namespace s21 {

// ----------------------------------------------------------------------------

// x = model_->points_array_[model_->polygons_[i][j]].x;

class Model {
 public:
  Model(std::string const& file = "");
  void ScaleObj(double const& scale);
  void TurnObj(double const& rotation, int const& axis);
  void MoveObj(Point& move_point);
  void Parse(std::string const& filename = "");

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
  void MatrixRotation(S21Matrix& matrix_turn, double const& rotation,
                      int const& axis);
  void add_max_size(Point const& t);

  double max_size_ = 0.0;
  ErrorType error_ = ErrorType::ERROR_OK;
  std::string file_;
  std::vector<Point> points_array_;  // !!
  std::vector<std::vector<int>> polygons_;

  friend ModelViewerTest;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_HPP_
