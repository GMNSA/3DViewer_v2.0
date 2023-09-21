#ifndef TESTS_TEST_MODEL_CALCULATOR_INCLUDES_TST_MODEL_CALCULATOR_HPP_
#define TESTS_TEST_MODEL_CALCULATOR_INCLUDES_TST_MODEL_CALCULATOR_HPP_

#include <gtest/gtest.h>

#include <QDebug>

#include "../includes/Model/modelcalculator.hpp"

class ModalCalculatorTest : public ::testing::Test {
 public:
  ModalCalculatorTest() : model_calculator_(new s21::ModelCalculator) {
    // initialization code here
  }

  void SetUp() {
    // code here will execute just before the test ensues
  }

  void TearDown() {
    // code here will be called just after the test completes
    // ok to through exceptions from here if need be
  }

  ~ModalCalculatorTest() {
    // cleanup any pending stuff, but no exceptions allowed
    if (model_calculator_) delete model_calculator_;
  }

  QString GetResult() const;
  void AddValue(QString const &str);
  QString FixTextDisplay() const;
  QString Calculate(QString const &str = "", QString const &x = "");
  void ChangeSign();
  void Reset();
  void SetBrackets(QString const &str, bool const is_smart,
                   bool const &is_checked);
  void DelOne();
  // put in any custom data members that you need
 private:
  s21::ModelCalculator *model_calculator_;
};

#endif  // TESTS_TEST_MODEL_CALCULATOR_INCLUDES_TST_MODEL_CALCULATOR_HPP_
