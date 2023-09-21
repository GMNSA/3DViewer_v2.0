#ifndef TESTS_TEST_POLISHNOTATION_INCLUDES_TST_POLISHNOTATION_HPP_
#define TESTS_TEST_POLISHNOTATION_INCLUDES_TST_POLISHNOTATION_HPP_

#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>

#include <QDebug>

#include "../includes/Model/polishnotation.hpp"

class PolishNotationTest : public ::testing::Test {
 public:
  PolishNotationTest() : polish_notation_(new s21::PolishNotation) {
    // initialization code here
  }

  void SetUp() {
    // code here will execute just before the test ensues
  }

  void TearDown() {
    // code here will be called just after the test completes
    // ok to through exceptions from here if need be
  }

  ~PolishNotationTest() {
    // cleanup any pending stuff, but no exceptions allowed
    if (polish_notation_) delete polish_notation_;
  }

  bool get_error() const;
  QStack<QString> get_stack() const;
  bool IsNumber(QString const &str) const;
  qint64 Priority(QChar const &ch);
  bool IsSign(QChar const &ch);
  bool IsMathFunction(QString const &str);
  bool IsCustomNumber(QString const &str);
  qint64 FindStr(QString const &str, QString const &needle, qint64 i);
  qint64 AddMathFunction(QString const &src, qint64 i_begin);
  QHash<QString, qint64> GetNumberFromString(QString str, qint64 i_begin);
  bool IsFindInStackBrackets(QStack<QString> const &stack);
  QString StrToPostfix(QString const &str);
  QStack<QString> StringToStack(QString const &str);
  double CalculateNumbersMul(double num1, QString const &str, double num2);
  QString CalculateNotation(QString str);
  void ZerosRemove(QString *str);

  // put in any custom data members that you need
 public:
  s21::PolishNotation *polish_notation_;

  friend class PolishNotation;
};

#endif  // TESTS_TEST_POLISHNOTATION_INCLUDES_TST_POLISHNOTATION_HPP_
