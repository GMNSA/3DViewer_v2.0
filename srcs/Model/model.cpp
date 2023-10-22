#include "../../includes/Model/model.hpp"

#include <fstream>
#include <iostream>
#include <vector>

namespace s21 {

void PrintMatrix(S21Matrix matrix) {
  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetCols(); j++) {
      cout << matrix(i, j) << " ";
    }
    cout << endl;
  }
}

// ----------------------------------------------------------------------------

Model::Model(std::string const& file) : file_(file) {
  if (!file.empty()) Parse();
}

// ----------------------------------------------------------------------------

void Model::Parse(std::string const& filename) {
  error_ = ErrorType::ERROR_OK;
  if (!filename.empty()) file_ = filename;
  // TODO(_who): clear data
  max_size_ = 0;
  polygons_.clear();
  points_array_.clear();
  std::string line;
  std::ifstream in(file_);
  if (in.is_open()) {
    Point add_one;
    points_array_.push_back(add_one);
    while (getline(in, line)) {
      if (line[0] == 'v' && line[1] == ' ') {
        AddPoint(line.data() + 2);
      } else if (line[0] == 'f' && line[1] == ' ') {
        AddPoligon(line.data() + 2);
      }
    }
    in.close();
  } else {
    error_ = ErrorType::ERROR_PARSE;
  }
}

// ----------------------------------------------------------------------------

void Model::AddPoligon(char* line) {
  vector<int> poligon;
  for (int i = 0; line[i]; i++) {
    if (isdigit(line[i])) {
      poligon.push_back(stoi(line + i));
      while (line[i + 1] != ' ' && line[i + 1]) {
        i++;
      }
    }
  }
  polygons_.push_back(poligon);
}

// ----------------------------------------------------------------------------

void Model::AddPoint(char* line) {
  Point point;
  size_t count = 0;
  for (int i = 0; line[i]; i++) {
    if (isdigit(line[i]) || (line[i] == '-' && isdigit(line[i + 1]))) {
      point[count++] = stod(line + i);
      while (isdigit(line[++i]) || line[i] == '.') {
      }
      if (count == 3) break;
    }
  }
  add_max_size(point);
  points_array_.push_back(point);
}

// ----------------------------------------------------------------------------

void Model::ScaleObj(double const& scale) {
  S21Matrix matrix_scale(4, 4);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j)
        matrix_scale(i, j) = scale;
      else
        matrix_scale(i, j) = 0;
    }
  }
  matrix_scale(3, 3) = 1;
  AffineTransformation(matrix_scale);
}

// ----------------------------------------------------------------------------

void Model::TurnObj(double const& rotation, int const& axis) {
  S21Matrix matrix_turn(4, 4);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j)
        matrix_turn(i, j) = 1;
      else
        matrix_turn(i, j) = 0;
    }
  }
  MatrixRotation(matrix_turn, rotation, axis);
  AffineTransformation(matrix_turn);
}

// ----------------------------------------------------------------------------

void Model::MatrixRotation(S21Matrix& matrix_turn, double const& rotation,
                           int const& axis) {
  double gradus = rotation * M_PI / 180;
  if (axis == 1) {
    matrix_turn(1, 1) = cos(gradus);
    matrix_turn(1, 2) = sin(gradus);
    matrix_turn(2, 1) = -sin(gradus);
    matrix_turn(2, 2) = cos(gradus);
  } else if (axis == 2) {
    matrix_turn(0, 0) = cos(gradus);
    matrix_turn(0, 2) = -sin(gradus);
    matrix_turn(2, 0) = sin(gradus);
    matrix_turn(2, 2) = cos(gradus);
  } else if (axis == 3) {
    matrix_turn(0, 0) = cos(gradus);
    matrix_turn(0, 1) = sin(gradus);
    matrix_turn(1, 0) = -sin(gradus);
    matrix_turn(1, 1) = cos(gradus);
  }
}

// ----------------------------------------------------------------------------

void Model::MoveObj(Point& move_point) {
  S21Matrix matrix_move(4, 4);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j)
        matrix_move(i, j) = 1;
      else
        matrix_move(i, j) = 0;
    }
  }
  matrix_move(0, 3) = move_point.x;
  matrix_move(1, 3) = move_point.y;
  matrix_move(2, 3) = move_point.z;
  AffineTransformation(matrix_move);
}

// ----------------------------------------------------------------------------

void Model::AffineTransformation(S21Matrix& matrix_affin) {
  S21Matrix matrix_point(4, 1), matrix_result;
  matrix_point(3, 0) = 1;
  for (unsigned i = 1; i < points_array_.size(); i++) {
    matrix_point(0, 0) = points_array_[i].x;
    matrix_point(1, 0) = points_array_[i].y;
    matrix_point(2, 0) = points_array_[i].z;
    matrix_result = matrix_affin * matrix_point;
    // PrintMatrix(matrix_affin);
    // PrintMatrix(matrix_point);
    // PrintMatrix(matrix_result);
    points_array_[i].x = matrix_result(0, 0);
    points_array_[i].y = matrix_result(1, 0);
    points_array_[i].z = matrix_result(2, 0);
  }
}

// ----------------------------------------------------------------------------

void Model::PrintPoints() {
  for (unsigned i = 0; i < points_array_.size(); i++) {
    cout << points_array_[i].x << " ";
    cout << points_array_[i].y << " ";
    cout << points_array_[i].z << endl;
  }
}

// ----------------------------------------------------------------------------

// int main() {
//   Model s("/home/usup/Desktop/cow.obj");
//   s.TurnObj(180, 1);
//   s.PrintPoints();
//   return 0;
// }

// ----------------------------------------------------------------------------

void Model::add_max_size(Point const& point) {
  if (fabs(point.x) > max_size_) max_size_ = fabs(point.x);
  if (fabs(point.y) > max_size_) max_size_ = fabs(point.y);
  if (fabs(point.z) > max_size_) max_size_ = fabs(point.z);
}

// ----------------------------------------------------------------------------

void Model::set_max_size(double const& size) { max_size_ = size; }

// ----------------------------------------------------------------------------

double Model::get_max_size() { return max_size_; }

// ----------------------------------------------------------------------------

ErrorType Model::get_error() { return error_; }

// ----------------------------------------------------------------------------

void Model::set_error(ErrorType const& error) { error_ = error; }

// ----------------------------------------------------------------------------

std::vector<Point> const& Model::get_points_array() { return points_array_; }

// ----------------------------------------------------------------------------

std::vector<std::vector<int>> const& Model::get_polygons() { return polygons_; }

// ----------------------------------------------------------------------------

void Model::PolygonsClear() { polygons_.clear(); }

}  // namespace s21
