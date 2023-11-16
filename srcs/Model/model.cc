#include "../../includes/Model/model.hpp"

#include <fstream>
#include <iostream>
#include <vector>

namespace s21 {

Model::Model(std::string const& file) : file_(file) {
  if (!file.empty()) Parse();
}

// ----------------------------------------------------------------------------

void Model::Parse(std::string const& filename) {
  error_ = ErrorType::ERROR_OK;
  if (!filename.empty()) file_ = filename;
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
  std::vector<int> poligon;
  for (int i = 0; line[i]; i++) {
    if (isdigit(line[i])) {
      poligon.push_back(std::stoi(line + i));
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
      point[count++] = std::stod(line + i);
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
  for (size_t i = 1; i < points_array_.size(); ++i) {
    points_array_[i].x *= scale;
    points_array_[i].y *= scale;
    points_array_[i].z *= scale;
  }
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
  size_t size = points_array_.size();
  for (size_t i = 1; i < size; ++i) {
    double x = points_array_[i].x, y = points_array_[i].y,
           z = points_array_[i].z;
    points_array_[i].x = x * matrix_turn(0, 0) + y * matrix_turn(0, 1) +
                         z * matrix_turn(0, 2) + matrix_turn(0, 3);
    points_array_[i].y = x * matrix_turn(1, 0) + y * matrix_turn(1, 1) +
                         z * matrix_turn(1, 2) + matrix_turn(1, 3);
    points_array_[i].z = x * matrix_turn(2, 0) + y * matrix_turn(2, 1) +
                         z * matrix_turn(2, 2) + matrix_turn(0, 3);
  }
}

// ----------------------------------------------------------------------------

void Model::MatrixRotation(S21Matrix& matrix_turn, double const& rotation,
                           int const& axis) {
  double gradus = rotation * M_PI / 180;
  if (axis == MOVE_ROTATE_Y) {
    matrix_turn(1, 1) = cos(gradus);
    matrix_turn(1, 2) = sin(gradus);
    matrix_turn(2, 1) = -sin(gradus);
    matrix_turn(2, 2) = cos(gradus);
  } else if (axis == MOVE_ROTATE_X) {
    matrix_turn(0, 0) = cos(gradus);
    matrix_turn(0, 2) = -sin(gradus);
    matrix_turn(2, 0) = sin(gradus);
    matrix_turn(2, 2) = cos(gradus);
  } else if (axis == MOVE_ROTATE_Z) {
    matrix_turn(0, 0) = cos(gradus);
    matrix_turn(0, 1) = sin(gradus);
    matrix_turn(1, 0) = -sin(gradus);
    matrix_turn(1, 1) = cos(gradus);
  }
}

// ----------------------------------------------------------------------------

void Model::MoveObj(Point& move_point) {
  for (size_t i = 1; i < points_array_.size(); ++i) {
    points_array_[i].x += move_point.x;
    points_array_[i].y += move_point.y;
    points_array_[i].z += move_point.z;
  }
}

// ----------------------------------------------------------------------------

void Model::add_max_size(Point const& point) {
  if (fabs(point.x) > max_size_) max_size_ = fabs(point.x);
  if (fabs(point.y) > max_size_) max_size_ = fabs(point.y);
  if (fabs(point.z) > max_size_) max_size_ = fabs(point.z);
}

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
