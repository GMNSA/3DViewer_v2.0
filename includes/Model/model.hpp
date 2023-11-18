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

/**
 * @brief Class The model class. We implement file parsing.
 *              we divide it into vectors.
 *              We also implement rotations and movement of matrices.
 */
class Model {
 public:
  Model(std::string const& file = "");
  Model(Model const& other) = delete;
  Model& operator=(Model const& other) = delete;

  /**
   * @brief Decrease, increase the object.
   *
   * @param scale - The number by whcih the change will occur.
   */
  void ScaleObj(double const& scale);

  /**
   * @brief Rotate an object around its axis.
   *
   * @param rotation - How much we will rotata.
   * @param axis - The direction directory.
   */
  void TurnObj(double const& rotation, int const& axis);

  /**
   * @brief Object movement.
   *
   * @param move_point - The number by whcih the change will occur.
   */
  void MoveObj(Point& move_point);

  /**
   * @brief Parsing the data from the file. (the file
   *        must be in teh format.obj)
   *
   * @param filename - The name of file.
   */
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
  unsigned degrees_in_circle_;
  size_t row_;
  size_t col_;
  void AddPoint(char* line);
  void AddPoligon(char* line);
  void MatrixRotation(S21Matrix& matrix_turn, double const& rotation,
                      int const& axis);
  void add_max_size(Point const& t);

  double max_size_ = 0.0;
  ErrorType error_ = ErrorType::ERROR_OK;
  std::string file_;
  std::vector<Point> points_array_;
  std::vector<std::vector<int>> polygons_;

  friend ModelViewerTest;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_HPP_
