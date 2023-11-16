#ifndef TESTS_TEST_MODEL_CALCULATOR_INCLUDES_TST_MODEL_CALCULATOR_HPP_
#define TESTS_TEST_MODEL_CALCULATOR_INCLUDES_TST_MODEL_CALCULATOR_HPP_

#include <gtest/gtest.h>

#include <QDebug>

#include "../includes/Model/customtypes.hpp"
#include "../includes/Model/model.hpp"

class ModelViewerTest : public ::testing::Test {
 public:
  ModelViewerTest() : model_(new s21::Model) {
    // initialization code here
  }

  void SetUp() {
    // code here will execute just before the test ensues
  }

  void TearDown() {
    // code here will be called just after the test completes
    // ok to through exceptions from here if need be
  }

  ~ModelViewerTest() {
    // cleanup any pending stuff, but no exceptions allowed
    if (model_) delete model_;
  }

  s21::ErrorType GetError();
  void Parse(std::string const& filename = "../objects_for_test/cow.obj");
  std::vector<s21::Point> const& GetPointsArray();
  std::vector<std::vector<int>> const& GetPolygons();
  void ScaleObj(double const& scale);
  void TurnObj(double const& rotation, int const& axis);
  void MoveObj(s21::Point& move_point);
  double GetMaxSize() const;
  void PolygonsClear();

 private:
  s21::Model* model_;
};

#endif  // TESTS_TEST_MODEL_CALCULATOR_INCLUDES_TST_MODEL_CALCULATOR_HPP_
