#include "../includes/tst_model_calculator.hpp"

#include <gtest/gtest.h>

#include <QHash>
#include <QRegularExpression>
#include <QStack>

QString ModalCalculatorTest::Calculate(QString const &str, QString const &x) {
  model_calculator_->Calculate(str, x);
  return model_calculator_->get_result();
}

// -- -- -- --

QString ModalCalculatorTest::GetResult() const {
  return model_calculator_->get_result();
}

// -- -- -- --

void ModalCalculatorTest::ChangeSign() { model_calculator_->ChangeSign(); }

// -- -- -- --

void ModalCalculatorTest::AddValue(QString const &str) {
  model_calculator_->AddValue(str);
}

// -- -- -- --

QString ModalCalculatorTest::FixTextDisplay() const {
  return model_calculator_->get_fix_text_display();
}

// -- -- -- --

void ModalCalculatorTest::Reset() { model_calculator_->Reset(); }

// -- -- -- --

void ModalCalculatorTest::SetBrackets(QString const &str, bool const is_smart,
                                      bool const &is_checked) {
  model_calculator_->SetBrackets(str, is_smart, is_checked);
}

// -- -- -- --

void ModalCalculatorTest::DelOne() { model_calculator_->DelOne(); }

// ----------------------------------------------------------------------------

TEST_F(ModalCalculatorTest, TestChangeSign) {
  AddValue("2");
  AddValue("*");
  AddValue("2");
  QString res = FixTextDisplay();
  EXPECT_EQ(res, "2 * 2");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2)");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "2 * 2");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2)");
  AddValue("+");
  AddValue("8");
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2) + 8");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(-(2 * 2) + 8)");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2) + 8");

  // -- -- -- --

  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2) + 8");
  AddValue("+");
  AddValue("sin(");
  AddValue("19");
  AddValue(")");
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2) + 8 + sin(19)");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(-(2 * 2) + 8 + sin(19))");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2) + 8 + sin(19)");
  AddValue("+");
  AddValue("cos(");
  AddValue("20");
  AddValue(")");
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2) + 8 + sin(19) + cos(20)");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(-(2 * 2) + 8 + sin(19) + cos(20))");

  // -- -- -- --

  Reset();

  AddValue("0");
  res = FixTextDisplay();
  EXPECT_EQ(res, "0");
  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-0");
  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "0");
  AddValue("+");
  AddValue("8");
  res = FixTextDisplay();
  Calculate();
  res = GetResult();
  EXPECT_EQ(res, "8");
  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-8");
  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "8");
  AddValue("3");
  AddValue("2");
  res = FixTextDisplay();
  EXPECT_EQ(res, "832");
  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-832");
  AddValue("-");
  SetBrackets("(", true, true);
  AddValue("8");
  AddValue("+");
  AddValue("2");
  SetBrackets("(", true, true);
  res = FixTextDisplay();
  EXPECT_EQ(res, "-832 - (8 + 2)");
}

// ----------------------------------------------------------------------------

TEST_F(ModalCalculatorTest, TestDelOne) {
  QString res;

  AddValue("cos(8) + 2");
  res = FixTextDisplay();
  EXPECT_EQ(res, "cos(8) + 2");
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res, "cos(8) + ");
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res, "cos(8) ");
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res, "cos(8");
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res, "cos(");
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res, "0");

  Reset();
  AddValue(
      "cos(8) + tan(2) - sin(1) / acs(3) * asn(1) + atn(4) ^ sqrt(9) % ln(1) - "
      "log(3)");
  res = FixTextDisplay();
  EXPECT_EQ(res,
            "cos(8) + tan(2) - sin(1) / acs(3) * asn(1) + atn(4) ^ sqrt(9) % "
            "ln(1) - log(3)");
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res,
            "cos(8) + tan(2) - sin(1) / acs(3) * asn(1) + atn(4) ^ sqrt(9) % "
            "ln(1) - log(3");
  DelOne();
  DelOne();
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res,
            "cos(8) + tan(2) - sin(1) / acs(3) * asn(1) + atn(4) ^ sqrt(9) % "
            "ln(1) ");
  DelOne();
  DelOne();
  DelOne();
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res,
            "cos(8) + tan(2) - sin(1) / acs(3) * asn(1) + atn(4) ^ sqrt(9) ");
  DelOne();
  DelOne();
  DelOne();
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res, "cos(8) + tan(2) - sin(1) / acs(3) * asn(1) + atn(4) ");

  DelOne();
  DelOne();
  DelOne();
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res, "cos(8) + tan(2) - sin(1) / acs(3) * asn(1) ");

  DelOne();
  DelOne();
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res, "cos(8) + tan(2) - sin(1) / acs(3) *");

  DelOne();
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res, "cos(8) + tan(2) - sin(1) / acs(3");

  DelOne();
  DelOne();
  DelOne();
  DelOne();
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res, "cos(8) + tan(2) - sin(");

  DelOne();
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res, "cos(8) + tan(2) ");

  DelOne();
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res, "cos(8) + tan(");

  DelOne();
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res, "cos(8) ");

  DelOne();
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res, "cos(");

  DelOne();
  DelOne();
  res = FixTextDisplay();
  EXPECT_EQ(res, "0");
}

// ----------------------------------------------------------------------------

TEST_F(ModalCalculatorTest, TestBrackets) {
  QString res;

  res = Calculate("(2 + 2)");
  EXPECT_EQ(res, "4");

  res = Calculate("-(8 + 2)");
  EXPECT_EQ(res, "-10");

  res = Calculate("-(8 + 2) * 2");
  EXPECT_EQ(res, "-20");

  res = Calculate("23 * 2 - (3 + 4) * (2 * 2 * 2 - (2 - 80 ))");
  EXPECT_EQ(res, "-556");
}

// ----------------------------------------------------------------------------

TEST_F(ModalCalculatorTest, TestXCoordinates) {
  QString res;

  res = Calculate("2 + 2 * x", "2");
  EXPECT_EQ(res, "6");

  res = Calculate("x");
  EXPECT_EQ(res, "0");

  // -- -- -- --

  Reset();
  res = Calculate("log(0)");
  EXPECT_EQ(res, "-inf");
  res = Calculate("log(0)");
  EXPECT_EQ(res, "-inf");
}

// ----------------------------------------------------------------------------
