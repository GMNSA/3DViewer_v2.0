#include "../includes/tst_model_viewer.hpp"

#include <gtest/gtest.h>

#include <QDir>
#include <QHash>
#include <QRegularExpression>
#include <QStack>

#include "customtypes.hpp"

int eq_double(double num1, double num2) { return fabs(num1 - num2) < 1e-5; }

s21::ErrorType ModelViewerTest::GetError() { return model_->get_error(); }

// -- -- -- --

void ModelViewerTest::Parse(std::string const& filename) {
  model_->Parse(filename);
}

// -- -- -- --

std::vector<s21::Point> const& ModelViewerTest::GetPointsArray() {
  return model_->get_points_array();
}

// -- -- -- --

std::vector<std::vector<int>> const& ModelViewerTest::GetPolygons() {
  return model_->get_polygons();
}

// -- -- -- --

void ModelViewerTest::ScaleObj(double const& scale) {
  return model_->ScaleObj(scale);
}

// -- -- -- --

void ModelViewerTest::TurnObj(double const& rotation, int const& axis) {
  return model_->TurnObj(rotation, axis);
}

// -- -- -- --

void ModelViewerTest::MoveObj(s21::Point& move_point) {
  return model_->MoveObj(move_point);
}

// -- -- -- --

void ModelViewerTest::AffineTransformation(S21Matrix& matrix_affin) {
  model_->AffineTransformation(matrix_affin);
}

// -- -- -- --

double ModelViewerTest::GetMaxSize() const { return model_->get_max_size(); }

// -- -- -- --

void ModelViewerTest::PolygonsClear() { model_->PolygonsClear(); }

// ----------------------------------------------------------------------------

TEST_F(ModelViewerTest, TestParse) {
  QString current_path = QDir::currentPath();
  QString current_dir;
  QString first_name = "/tests/objects_for_test/test_obj.obj";
  QString second_name = "/../objects_for_test/test_obj.obj";
  QDir direcotry;

  if (direcotry.exists(current_path + first_name))
    current_dir = current_path + first_name;
  else
    current_dir = current_path + second_name;

  Parse(current_dir.toStdString());

  if (GetError() == s21::ErrorType::ERROR_PARSE) exit(EXIT_FAILURE);

  ASSERT_DOUBLE_EQ(0, GetPointsArray()[2].x);
  ASSERT_DOUBLE_EQ(0, GetPointsArray()[2].y);
  ASSERT_DOUBLE_EQ(1, GetPointsArray()[2].z);
  ASSERT_DOUBLE_EQ(1, GetPointsArray()[6].x);
  ASSERT_DOUBLE_EQ(0, GetPointsArray()[6].y);
  ASSERT_DOUBLE_EQ(1, GetPointsArray()[6].z);
  ASSERT_DOUBLE_EQ(1, GetPolygons()[0][0]);
  ASSERT_DOUBLE_EQ(7, GetPolygons()[0][1]);
  ASSERT_DOUBLE_EQ(5, GetPolygons()[0][2]);
  ASSERT_DOUBLE_EQ(3, GetPolygons()[4][0]);
  ASSERT_DOUBLE_EQ(8, GetPolygons()[4][1]);
  ASSERT_DOUBLE_EQ(7, GetPolygons()[4][2]);

  first_name = "/tests/objects_for_test/test2_obj.obj";
  second_name = "/../objects_for_test/test2_obj.obj";

  if (direcotry.exists(current_path + first_name))
    current_dir = current_path + first_name;
  else
    current_dir = current_path + second_name;

  Parse(current_dir.toStdString());
  ASSERT_DOUBLE_EQ(0, GetPointsArray()[2].x);
  ASSERT_DOUBLE_EQ(0, GetPointsArray()[2].y);
  ASSERT_DOUBLE_EQ(1, GetPointsArray()[2].z);
  ASSERT_DOUBLE_EQ(1, GetPointsArray()[6].x);
  ASSERT_DOUBLE_EQ(0, GetPointsArray()[6].y);
  ASSERT_DOUBLE_EQ(1, GetPointsArray()[6].z);
  ASSERT_DOUBLE_EQ(1, GetPolygons()[0][0]);
  ASSERT_DOUBLE_EQ(7, GetPolygons()[0][1]);
  ASSERT_DOUBLE_EQ(5, GetPolygons()[0][2]);
  ASSERT_DOUBLE_EQ(3, GetPolygons()[4][0]);
  ASSERT_DOUBLE_EQ(8, GetPolygons()[4][1]);
  ASSERT_DOUBLE_EQ(7, GetPolygons()[4][2]);
}

// ----------------------------------------------------------------------------

TEST_F(ModelViewerTest, TestScaleObj) {
  QString current_path = QDir::currentPath();
  QString current_dir;
  QString first_name = "/tests/objects_for_test/cow.obj";
  QString second_name = "/../objects_for_test/cow.obj";
  QDir direcotry;

  if (direcotry.exists(current_path + first_name))
    current_dir = current_path + first_name;
  else
    current_dir = current_path + second_name;

  Parse(current_dir.toStdString());

  if (GetError() == s21::ErrorType::ERROR_PARSE) exit(EXIT_FAILURE);

  Parse(current_dir.toStdString());

  ScaleObj(2);
  ASSERT_DOUBLE_EQ(4.13736, GetPointsArray()[2].x);
  ASSERT_DOUBLE_EQ(0.810272, GetPointsArray()[2].y);
  ASSERT_DOUBLE_EQ(-4.335, GetPointsArray()[2].z);
  ASSERT_DOUBLE_EQ(4.36556, GetPointsArray()[6].x);
  ASSERT_DOUBLE_EQ(0.837012, GetPointsArray()[6].y);
  ASSERT_DOUBLE_EQ(-4.20374, GetPointsArray()[6].z);
}

// ----------------------------------------------------------------------------

TEST_F(ModelViewerTest, TestTurnObj) {
  QString current_path = QDir::currentPath();
  QString current_dir;
  QString first_name = "/tests/objects_for_test/cow.obj";
  QString second_name = "/../objects_for_test/cow.obj";
  QDir direcotry;

  if (direcotry.exists(current_path + first_name))
    current_dir = current_path + first_name;
  else
    current_dir = current_path + second_name;

  Parse(current_dir.toStdString());

  TurnObj(50, 1);
  ASSERT_DOUBLE_EQ(2.06868, GetPointsArray()[2].x);
  ASSERT_EQ(1, eq_double(-1.39998, GetPointsArray()[2].y));

  ASSERT_EQ(1, eq_double(-1.70359, GetPointsArray()[2].z));
  ASSERT_EQ(2.18278, GetPointsArray()[6].x);
  ASSERT_EQ(1, eq_double(-1.34112, GetPointsArray()[6].y));
  ASSERT_EQ(1, eq_double(-1.67165, GetPointsArray()[6].z));

  TurnObj(50, 2);
  ASSERT_EQ(1, eq_double(2.634751, GetPointsArray()[2].x));
  ASSERT_EQ(1, eq_double(-1.399985, GetPointsArray()[2].y));
  ASSERT_EQ(1, eq_double(0.48965187, GetPointsArray()[2].z));
  ASSERT_EQ(1, eq_double(2.683622, GetPointsArray()[6].x));
  ASSERT_EQ(1, eq_double(-1.341115, GetPointsArray()[6].y));
  ASSERT_EQ(1, eq_double(0.597590, GetPointsArray()[6].z));

  TurnObj(50, 3);
  ASSERT_EQ(1, eq_double(0.621135, GetPointsArray()[2].x));
  ASSERT_EQ(1, eq_double(-2.918229, GetPointsArray()[2].y));
  ASSERT_EQ(1, eq_double(0.489651, GetPointsArray()[2].z));
  ASSERT_EQ(1, eq_double(0.697645, GetPointsArray()[6].x));
  ASSERT_EQ(1, eq_double(-2.917826, GetPointsArray()[6].y));
  ASSERT_EQ(1, eq_double(0.597590, GetPointsArray()[6].z));
}

// -- -- -- --

TEST_F(ModelViewerTest, TestMoveOjb) {
  QString current_path = QDir::currentPath();
  QString current_dir;
  QString first_name = "/tests/objects_for_test/cow.obj";
  QString second_name = "/../objects_for_test/cow.obj";
  QDir direcotry;

  if (direcotry.exists(current_path + first_name))
    current_dir = current_path + first_name;
  else
    current_dir = current_path + second_name;

  Parse(current_dir.toStdString());
  s21::Point p{3, 5, -4};
  MoveObj(p);
  ASSERT_EQ(1, eq_double(5.068680, GetPointsArray()[2].x));
  ASSERT_EQ(1, eq_double(5.405136, GetPointsArray()[2].y));
  ASSERT_EQ(1, eq_double(-6.167500, GetPointsArray()[2].z));
  ASSERT_EQ(1, eq_double(5.182780, GetPointsArray()[6].x));
  ASSERT_EQ(1, eq_double(5.418506, GetPointsArray()[6].y));
  ASSERT_EQ(1, eq_double(-6.101870, GetPointsArray()[6].z));
}

// -- -- -- --

TEST_F(ModelViewerTest, TestAffine_transformation) {
  QString current_path = QDir::currentPath();
  QString current_dir;
  QString first_name = "/tests/objects_for_test/cow.obj";
  QString second_name = "/../objects_for_test/cow.obj";
  QDir direcotry;

  if (direcotry.exists(current_path + first_name))
    current_dir = current_path + first_name;
  else
    current_dir = current_path + second_name;

  Parse(current_dir.toStdString());

  S21Matrix matrix_move(4, 4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j)
        matrix_move(i, j) = 1;
      else
        matrix_move(i, j) = 0;
    }
  }
  matrix_move(0, 3) = 3;
  matrix_move(1, 3) = 5;
  matrix_move(2, 3) = -4;
  AffineTransformation(matrix_move);
  ASSERT_DOUBLE_EQ(1, eq_double(5.068680, GetPointsArray()[2].x));
  ASSERT_DOUBLE_EQ(1, eq_double(5.405136, GetPointsArray()[2].y));
  ASSERT_DOUBLE_EQ(1, eq_double(-6.167500, GetPointsArray()[2].z));
  ASSERT_DOUBLE_EQ(1, eq_double(5.182780, GetPointsArray()[6].x));
  ASSERT_DOUBLE_EQ(1, eq_double(5.418506, GetPointsArray()[6].y));
  ASSERT_DOUBLE_EQ(1, eq_double(-6.101870, GetPointsArray()[6].z));
}

// -- -- -- --

TEST_F(ModelViewerTest, TestGetMaxSize) {
  QString current_path = QDir::currentPath();
  QString current_dir;
  QString first_name = "/tests/objects_for_test/cow.obj";
  QString second_name = "/../objects_for_test/cow.obj";
  QDir direcotry;

  if (direcotry.exists(current_path + first_name))
    current_dir = current_path + first_name;
  else
    current_dir = current_path + second_name;

  Parse(current_dir.toStdString());

  ASSERT_EQ(1, eq_double(5.784799, GetMaxSize()));
  ASSERT_DOUBLE_EQ(1, GetPolygons()[0][0]);
  PolygonsClear();
  ASSERT_EQ(0, GetPolygons().size());
}

// ----------------------------------------------------------------------------
