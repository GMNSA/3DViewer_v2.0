#include "../includes/tst_polishnotation.hpp"

#include <gtest/gtest.h>

#include <QHash>
#include <QRegularExpression>
#include <QStack>

bool PolishNotationTest::get_error() const {
  return polish_notation_->get_error();
}

QStack<QString> PolishNotationTest::get_stack() const {
  return polish_notation_->get_stack();
}

bool PolishNotationTest::IsNumber(QString const &str) const {
  return polish_notation_->IsNumber(str);
}

qint64 PolishNotationTest::Priority(QChar const &ch) {
  return polish_notation_->Priority(ch);
}

bool PolishNotationTest::IsSign(QChar const &ch) {
  return polish_notation_->IsSign(ch);
}

bool PolishNotationTest::IsMathFunction(QString const &str) {
  return polish_notation_->IsMathFunction(str);
}

bool PolishNotationTest::IsCustomNumber(QString const &str) {
  return polish_notation_->IsCustomNumber(str);
}

qint64 PolishNotationTest::FindStr(QString const &str, QString const &needle,
                                   qint64 i) {
  return polish_notation_->FindStr(str, needle, i);
}

qint64 PolishNotationTest::AddMathFunction(QString const &src, qint64 i_begin) {
  return polish_notation_->AddMathFunction(src, i_begin);
}

QHash<QString, qint64> PolishNotationTest::GetNumberFromString(QString str,
                                                               qint64 i_begin) {
  return polish_notation_->GetNumberFromString(str, i_begin);
}

bool PolishNotationTest::IsFindInStackBrackets(QStack<QString> const &stack) {
  return polish_notation_->IsFindInStackBrackets(stack);
}

QString PolishNotationTest::StrToPostfix(QString const &str) {
  return polish_notation_->StrToPostfix(str);
}

QStack<QString> PolishNotationTest::StringToStack(QString const &str) {
  return polish_notation_->StringToStack(str);
}

double PolishNotationTest::CalculateNumbersMul(double num1, QString const &str,
                                               double num2) {
  polish_notation_->ResetError();
  return polish_notation_->CalculateNumbersMul(num1, str, num2);
}

QString PolishNotationTest::CalculateNotation(QString str) {
  return polish_notation_->CalculateNotation(str);
}

void PolishNotationTest::ZerosRemove(QString *str) {
  polish_notation_->ZerosRemove(str);
}

// ----------------------------------------------------------------------------

TEST_F(PolishNotationTest, TestIsNumber) {
  auto res = IsNumber("4293");
  EXPECT_TRUE(res);

  res = IsNumber("42.93");
  EXPECT_TRUE(res);

  res = IsNumber("42.9g3");
  EXPECT_FALSE(res);
}

// ----------------------------------------------------------------------------

TEST_F(PolishNotationTest, TestRemoveZeros) {
  QString src = "30.0000";

  ZerosRemove(&src);
  EXPECT_EQ(src, "30");

  // -- -- -- --

  src = "30.3000";
  ZerosRemove(&src);
  EXPECT_EQ(src, "30.3");

  // -- -- -- --

  src = "30.3300";
  ZerosRemove(&src);
  EXPECT_EQ(src, "30.33");

  // -- -- -- --

  src = "30.3390";
  ZerosRemove(&src);
  EXPECT_EQ(src, "30.339");

  // -- -- -- --

  src = "30.3390";
  ZerosRemove(&src);
  EXPECT_EQ(src, "30.339");

  // -- -- -- --

  src = "30.3391";
  ZerosRemove(&src);
  EXPECT_EQ(src, "30.3391");

  // -- -- -- --

  src = "0";
  ZerosRemove(&src);
  EXPECT_EQ(src, "0");

  // -- -- -- --

  src = "x";
  ZerosRemove(&src);
  EXPECT_EQ(src, "x");

  // -- -- -- --

  src = "0.0";
  ZerosRemove(&src);
  EXPECT_EQ(src, "0");

  // -- -- -- --

  src = "0.03";
  ZerosRemove(&src);
  EXPECT_EQ(src, "0.03");
}

// ----------------------------------------------------------------------------
TEST_F(PolishNotationTest, TestFirstTest) {
  QString res = StrToPostfix("(-3 + 4) * ((-2.8) / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 ~ 4 + 2.8 ~ 1 5 - 2 ^ / *");
  QString pols = CalculateNotation(res);
  EXPECT_EQ(pols, "-0.175");
}

// ----------------------------------------------------------------------------

TEST_F(PolishNotationTest, TestPriority) {
  // QChar sign = '*';
  // qint64 res = Priority(sign);
  // qDebug() << "res: " << res;
  //
  // QString res = StrToPostfix("0");
  // EXPECT_EQ(res, "0");
  // QString pol = CalculateNotation(res);
  // EXPECT_EQ(pol, "0");
}

// ----------------------------------------------------------------------------

TEST_F(PolishNotationTest, TestIsSign) {
  // Exercises the Xyz feature of Foo.

  EXPECT_TRUE(IsSign('^'));
  EXPECT_TRUE(IsSign('*'));
  EXPECT_TRUE(IsSign('+'));
  EXPECT_TRUE(IsSign('-'));
  EXPECT_TRUE(IsSign('/'));
  EXPECT_TRUE(IsSign('%'));
  EXPECT_FALSE(IsSign('l'));
  EXPECT_FALSE(IsSign('!'));
}

// ----------------------------------------------------------------------------

TEST_F(PolishNotationTest, IsMathFunction) {
  EXPECT_FALSE(IsMathFunction("llog"));
  EXPECT_FALSE(IsMathFunction("og"));
  EXPECT_FALSE(IsMathFunction("coss"));
  EXPECT_FALSE(IsMathFunction("solo"));
  EXPECT_FALSE(IsMathFunction("tang"));

  EXPECT_TRUE(IsMathFunction("cos"));
  EXPECT_TRUE(IsMathFunction("sin"));
  EXPECT_TRUE(IsMathFunction("tan"));
  EXPECT_TRUE(IsMathFunction("acs"));
  EXPECT_TRUE(IsMathFunction("asn"));
  EXPECT_TRUE(IsMathFunction("atn"));
  EXPECT_TRUE(IsMathFunction("sqrt"));
  EXPECT_TRUE(IsMathFunction("ln"));
  EXPECT_TRUE(IsMathFunction("log"));
}

// ----------------------------------------------------------------------------

TEST_F(PolishNotationTest, TestIsCustomNumber) {
  EXPECT_FALSE(IsCustomNumber("39a28"));
  EXPECT_FALSE(IsCustomNumber("39+28"));
  EXPECT_FALSE(IsCustomNumber("+3928"));
  EXPECT_FALSE(IsCustomNumber("0.o"));
  EXPECT_FALSE(IsCustomNumber("k"));

  EXPECT_TRUE(IsCustomNumber("3928"));
  EXPECT_TRUE(IsCustomNumber("-3914"));
  EXPECT_TRUE(IsCustomNumber("-49.424"));
  EXPECT_TRUE(IsCustomNumber("49920.0042"));
}

// ----------------------------------------------------------------------------

TEST_F(PolishNotationTest, TestFindStr) {
  QString str = "there is no spoon.";
  const char *needle = "the";
  qint64 i = 0;
  qint64 n = FindStr(str, needle, i);

  EXPECT_NE(n, 1);
  EXPECT_EQ(n, 2);

  str = "there is no spoon.";
  needle = "there";
  i = 0;

  n = FindStr(str, needle, i);
  EXPECT_EQ(n, 4);

  str = "there is no spoon.";
  needle = "ehere";
  i = 0;

  n = FindStr(str, needle, i);
  EXPECT_EQ(n, -1);

  str = "there is no spoon.";
  needle = "t";
  i = 0;

  n = FindStr(str, needle, i);
  EXPECT_EQ(n, 0);

  // -- -- -- --
  str = "cos(2 * x)";
  needle = "cos";
  i = 0;

  n = FindStr(str, needle, i);
  EXPECT_EQ(n, 2);
}

// ----------------------------------------------------------------------------

TEST_F(PolishNotationTest, TestAddMathFunctions) {
  QStack<QString> dest;
  QString src = "There srcsis nolnmod spooon. cosalog";
  unsigned n_src = src.length();
  QString tmp = "";

  for (qint64 i = 0; i < n_src && i != -1; ++i) {
    i = AddMathFunction(src, i);
  }

  dest = get_stack();

  if (dest.isEmpty())
    tmp = "";
  else
    tmp = dest.pop();
  EXPECT_EQ(tmp, "log");

  if (dest.isEmpty())
    tmp = "";
  else
    tmp = dest.pop();
  EXPECT_EQ(tmp, "cos");

  if (dest.isEmpty())
    tmp = "";
  else
    tmp = dest.pop();
  EXPECT_EQ(tmp, "mod");

  if (dest.isEmpty())
    tmp = "";
  else
    tmp = dest.pop();
  EXPECT_EQ(tmp, "ln");

  if (dest.isEmpty())
    tmp = "";
  else
    tmp = dest.pop();
  EXPECT_EQ(tmp, "");
}

// ----------------------------------------------------------------------------

TEST_F(PolishNotationTest, TestGetNumberFromString) {
  QString str = "t32.42 8th";
  auto res = GetNumberFromString(str, 0);

  EXPECT_EQ(res.begin().key(), "");
  EXPECT_EQ(res.begin().value(), 0);

  res = GetNumberFromString(str, 1);
  EXPECT_EQ(res.begin().key(), "32.42");
  EXPECT_EQ(res.begin().value(), 6);

  res = GetNumberFromString(str, 6);
  EXPECT_EQ(res.begin().key(), "");
  EXPECT_EQ(res.begin().value(), 6);

  res = GetNumberFromString(str, 7);
  EXPECT_EQ(res.begin().key(), "8");
  EXPECT_EQ(res.begin().value(), 8);

  res = GetNumberFromString(str, 8);
  EXPECT_EQ(res.begin().key(), "");
  EXPECT_EQ(res.begin().value(), 8);

  res = GetNumberFromString(str, 9);
  EXPECT_EQ(res.begin().key(), "");
  EXPECT_EQ(res.begin().value(), 9);
}

// ----------------------------------------------------------------------------

TEST_F(PolishNotationTest, TestIsFindInStackBrackets) {
  QStack<QString> s;

  s.push_back("there");
  s.push_back("is");
  s.push_back("no");
  s.push_back("spoon");

  bool res = IsFindInStackBrackets(s);

  EXPECT_EQ(res, 0);

  // -- -- -- --
  s.push_back("(");
  res = IsFindInStackBrackets(s);
  EXPECT_EQ(res, 1);

  // -- -- -- --

  s.clear();
  res = IsFindInStackBrackets(s);
  EXPECT_EQ(res, 0);

  // -- -- -- --

  s.push_back(")");
  res = IsFindInStackBrackets(s);
  EXPECT_EQ(res, 1);
  s.clear();

  // -- -- -- --

  s.push_back(")");
  s.push_back("there");
  res = IsFindInStackBrackets(s);
  EXPECT_EQ(res, 1);
  s.clear();

  // -- -- -- --

  s.push_back(")");
  s.push_back("there");
  res = IsFindInStackBrackets(s);
  EXPECT_EQ(res, 1);
  s.clear();

  // -- -- -- --

  res = IsFindInStackBrackets(s);
  EXPECT_EQ(res, 0);
}

// -- -- -- --

TEST_F(PolishNotationTest, TestStrToPostfix) {
  QString res = StrToPostfix("(8 + 2 * 5) / (1 + 3 * 2 - 4)");
  QString example = "8 2 5 * + 1 3 2 * + 4 - /";

  EXPECT_EQ(res, example);

  res = StrToPostfix("(8 + 2 * 5) / (1 + 3 * 2 - 4)");

  EXPECT_EQ(res, "8 2 5 * + 1 3 2 * + 4 - /");

  // -- -- -- --

  res = StrToPostfix("3 + 4 * 2 / (1 - 5) ^ 2");
  EXPECT_EQ(res, "3 4 2 * 1 5 - 2 ^ / +");

  // -- -- -- --

  res = StrToPostfix("398 + 4487 * 224 / (128 - 548) ^ 20");
  EXPECT_EQ(res, "398 4487 224 * 128 548 - 20 ^ / +");

  // -- -- -- --

  res = StrToPostfix("3.98 + 4 * 2.0 / (1.5 - 5) ^ 2");
  EXPECT_EQ(res, "3.98 4 2.0 * 1.5 5 - 2 ^ / +");

  // -- -- -- --

  res = StrToPostfix("(3 + 4) * (2 / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 4 + 2 1 5 - 2 ^ / *");

  // -- -- -- --

  res = StrToPostfix("(3 + 4) * ((2) / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 4 + 2 1 5 - 2 ^ / *");

  // -- -- -- --

  res = StrToPostfix("(3 + 4) * ((2.8) / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 4 + 2.8 1 5 - 2 ^ / *");

  // -- -- -- --

  res = StrToPostfix("(-3 + 4) * ((2.8) / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 ~ 4 + 2.8 1 5 - 2 ^ / *");

  // -- -- -- --

  res = StrToPostfix("(-3 + 4) * ((-2.8) / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 ~ 4 + 2.8 ~ 1 5 - 2 ^ / *");

  // -- -- -- --

  res = StrToPostfix("(-3 + 4) * ((-2.8) / (-1 - 5) ^ +2)");
  EXPECT_EQ(res, "3 ~ 4 + 2.8 ~ 1 ~ 5 - ^ / 2 + *");

  // -- -- -- --

  res = StrToPostfix("(-3 + 4) * ((-2.8) / (-1 - 5) ^ +(2))");
  EXPECT_EQ(res, "3 ~ 4 + 2.8 ~ 1 ~ 5 - ^ / 2 + *");

  // -- -- -- --

  res = StrToPostfix("(-3 + 4) * ((-2.8) / (-1 - 5) ^ +(2)");
  EXPECT_TRUE(res.isEmpty());

  // -- -- -- --

  res = StrToPostfix("(-3 + 4) * ((-2.8) / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 ~ 4 + 2.8 ~ 1 5 - 2 ^ / *");

  // -- -- -- --

  res = StrToPostfix("-(122.33 + 33)");
  EXPECT_EQ(res, "122.33 33 + ~");

  // -- -- -- --

  res = StrToPostfix("-(122 + 33) + 28 - ((22 - 3) + (33 - 2))");
  EXPECT_EQ(res, "122 33 + ~ 28 + 22 3 - 33 2 - + -");

  // -- -- -- --

  res = StrToPostfix("-(-42)+1");
  EXPECT_EQ(res, "42 ~ ~ 1 +");

  // -- -- -- --

  res = StrToPostfix("2 / (3 - (4 + (5 * 6))) ");
  EXPECT_EQ(res, "2 3 4 5 6 * + - /");

  // -- -- -- --

  res = StrToPostfix("-( -(129.0000000) * 6 )");
  EXPECT_EQ(res, "129.0000000 ~ 6 * ~");

  // -- -- -- --

  res = StrToPostfix("(atn(8)*sqrt(4))+((ln(88.2)*ln(8.3))-3)");
  EXPECT_EQ(res, "8 atn 4 sqrt * 88.2 ln 8.3 ln * 3 - +");

  // -- -- -- --

  res = StrToPostfix("(aton(8)*sqrt(4))+((ln(88.2)*ln(8.3))-3)");
  EXPECT_TRUE(res.isEmpty());

  // -- -- -- --

  res = StrToPostfix("(atn(8)*sqrt(4))+((ln(88.2)*ln(8.3)) - 3)");
  EXPECT_EQ(res, "8 atn 4 sqrt * 88.2 ln 8.3 ln * 3 - +");

  // -- -- -- --

  res = StrToPostfix("(-3 + 6) * -2");
  EXPECT_EQ(res, "3 ~ 6 + 2 ~ *");

  // -- -- -- --

  res = StrToPostfix("(84 + x * (x - 473.938 * x - (x / x)))");
  EXPECT_EQ(res, "84 x x 473.938 x * - x x / - * +");

  // -- -- -- --

  res = StrToPostfix(
      "(84 + x * (x - 473.938 * x - (x / x * atn(x)))) + cos(x) * mod(87.44)");
  EXPECT_EQ(res,
            "84 x x 473.938 x * - x x / x atn * - * + x cos 87.44 mod * +");

  // -- -- -- --

  res = StrToPostfix("(84+x*(x-473.938*x-(x/x*atn(x))))+cos(x)*mod(87.44)");
  EXPECT_EQ(res,
            "84 x x 473.938 x * - x x / x atn * - * + x cos 87.44 mod * +");

  // -- -- -- --

  res = StrToPostfix("((x * x / x + 0.1)) + (x * x * x * x * x)");
  EXPECT_EQ(res, "x x * x / 0.1 + x x * x * x * x * +");

  // -- -- -- --

  res = StrToPostfix("alg(1) * atn(2)");
  EXPECT_EQ(res, "1 alg 2 atn *");

  // -- -- -- --

  res = StrToPostfix("3--3");
  EXPECT_TRUE(res.isEmpty());
}

// ----------------------------------------------------------------------------

TEST_F(PolishNotationTest, TestStringToStack) {
  QString str = "21 22 23 24";
  QString res = "";
  QStack<QString> stack;

  stack = StringToStack(str);

  EXPECT_TRUE(!stack.isEmpty());
  EXPECT_EQ(stack.size(), 4);

  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_EQ(res, "24");

  // -- -- -- --
  stack.clear();

  str = "21 22 23 24  ";
  stack = StringToStack(str);

  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.size(), 4);

  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_EQ(res, "24");

  // -- -- -- --

  str = "21 22 23 24        ";
  stack = StringToStack(str);

  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.size(), 4);

  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_EQ(res, "24");

  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_EQ(res, "23");

  // -- -- -- --

  str = "       21 22 23 24        ";
  stack = StringToStack(str);

  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.size(), 4);

  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_EQ(res, "24");

  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_EQ(res, "23");

  // -- -- -- --

  stack.clear();
  str = "1 ";
  stack = StringToStack(str);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.size(), 1);
  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_EQ(res, "1");

  res.clear();
  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_TRUE(res.isEmpty());

  // -- -- -- --

  str = "  ";
  stack = StringToStack(str);
  EXPECT_TRUE(stack.isEmpty());
  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_TRUE(res.isEmpty());

  // -- -- -- --

  str = " ";
  stack = StringToStack(str);
  EXPECT_TRUE(stack.isEmpty());
  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_TRUE(res.isEmpty());

  // -- -- -- --

  str = "";
  stack = StringToStack(str);
  EXPECT_TRUE(stack.isEmpty());
  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_TRUE(res.isEmpty());
}

// -- -- -- --

TEST_F(PolishNotationTest, TestCalculateNumbersMul) {
  double res = CalculateNumbersMul(33, "*", 2);
  EXPECT_NEAR(res, 66.0, 0.001);
  EXPECT_FALSE(get_error());

  // -- -- -- --

  res = CalculateNumbersMul(33.5, "+", 2);
  EXPECT_NEAR(res, 35.5, 0.001);
  EXPECT_FALSE(get_error());

  // -- -- -- --

  res = CalculateNumbersMul(33.5, "-", 2);
  EXPECT_NEAR(res, 31.5, 0.001);
  EXPECT_FALSE(get_error());

  // -- -- -- --

  res = CalculateNumbersMul(33.5, "/", 2);
  EXPECT_NEAR(res, 16.75, 0.001);
  EXPECT_FALSE(get_error());

  // -- -- -- --

  res = CalculateNumbersMul(1.6, "%", 1.2);
  EXPECT_NEAR(res, 0.4, 0.001);
  EXPECT_FALSE(get_error());

  // -- -- -- --

  res = CalculateNumbersMul(1.6, NULL, 1.2);
  EXPECT_NEAR(res, 0, 0.001);
  EXPECT_TRUE(get_error());

  // -- -- -- --

  res = CalculateNumbersMul(1.6, "", 1.2);
  EXPECT_NEAR(res, 0, 0.001);
  EXPECT_TRUE(get_error());

  // -- -- -- --

  res = CalculateNumbersMul(1.6, "kdgh", 1.2);
  EXPECT_NEAR(res, 0, 0.001);
  EXPECT_TRUE(get_error());
}

// ----------------------------------------------------------------------------

TEST_F(PolishNotationTest, TestCalculateNotation) {
  QString res = CalculateNotation("3 ~ 6 + 2 ~ *");
  EXPECT_EQ(res, "-6");

  res = CalculateNotation("");
  EXPECT_EQ(res, "error");

  // -- -- -- --

  res = StrToPostfix("(8 + 2 * 5) / (1 + 3 * 2 - 4)");
  EXPECT_EQ(res, "8 2 5 * + 1 3 2 * + 4 - /");
  QString pols = CalculateNotation(res);
  EXPECT_EQ(pols, "6");

  // -- -- -- --

  res = StrToPostfix("(-3 + 4) * ((-2.8) / (1 - 5) ^ 2)");

  EXPECT_EQ(res, "3 ~ 4 + 2.8 ~ 1 5 - 2 ^ / *");

  pols = CalculateNotation(res);

  EXPECT_EQ(pols, "-0.175");

  // -- -- -- --

  res = StrToPostfix("35 * (54 - 9)");
  pols.clear();
  EXPECT_EQ(res, "35 54 9 - *");

  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "1575");

  // -- -- -- --

  res = StrToPostfix("4 ^ 2");
  pols.clear();
  EXPECT_EQ(res, "4 2 ^");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "16");

  // -- -- -- --

  res = StrToPostfix("4 ^ 2 + (2* 3.8) - 3");
  pols.clear();
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "20.6");

  // -- -- -- --

  res = StrToPostfix("(76.3 - 7.8 * 44.002) - ((87 / 3.8) + 9.9 - 4)");
  pols.clear();

  EXPECT_EQ(res, "76.3 7.8 44.002 * - 87 3.8 / 9.9 + 4 - -");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "-295.7103368");

  // -- -- -- --

  res = StrToPostfix("acs(1) + ln(44.2) * asn(1)");
  pols = CalculateNotation(res);

  EXPECT_EQ(pols, "5.9513149");
  // -- -- -- --

  res = StrToPostfix("((84.998  * 3.94 * 2.2) - (778.9) ^ 2)");
  pols.clear();
  EXPECT_EQ(res, "84.998 3.94 * 2.2 * 778.9 2 ^ -");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "-605948.4473359");

  // -- -- -- --

  res = StrToPostfix("849.938 * sin(44) + 74.9 * ((40.9 * cos(20.8)) - 57.8)");
  EXPECT_EQ(res, "849.938 44 sin * 74.9 40.9 20.8 cos * 57.8 - * +");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "-5449.4537614");

  // -- -- -- --

  res = StrToPostfix("(-3 + 6) * -2");
  pols.clear();
  EXPECT_EQ(res, "3 ~ 6 + 2 ~ *");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "-6");

  // -- -- -- --

  res = StrToPostfix("(-3 + 4) * ((2.8) / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 ~ 4 + 2.8 1 5 - 2 ^ / *");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "0.175");

  // -- -- -- --

  res = StrToPostfix("(-3 + (4.9483 / 3.9)) * ((sin(2.8)) / (1 - 5) ^ 2)");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "-0.0362458");

  // -- -- -- --

  res = StrToPostfix("atn(sin(49.99)) * 30.8");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "-8.1800322");

  // -- -- -- --

  res = StrToPostfix("atn(log(9.39)) * 30.8 * sin(9)");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "9.7933808");

  // -- -- -- --

  res = StrToPostfix("acs(1) + ln(44.2) * asn(1)");
  pols = CalculateNotation(res);

  EXPECT_EQ(pols, "5.9513149");

  // -- -- -- --

  res = StrToPostfix("tan(3.94) * 392.2 / (2.8 + 4.93992) * 2");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "104.0164484");

  // -- -- -- --

  res = StrToPostfix("atn(sin(49.99)) * 30.8");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "-8.1800322");

  // -- -- -- --

  res = StrToPostfix("sqrt(49.29) * ((((34.2 - 2) - 44.9) * 2.843) / 4.83)");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "-52.4822999");

  // -- -- -- --

  res = StrToPostfix("cos(1)");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "0.5403023");

  // -- -- -- --

  res = StrToPostfix("(-3 + 4) * ((-2.8) / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 ~ 4 + 2.8 ~ 1 5 - 2 ^ / *");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "-0.175");

  // -- -- -- --

  res = StrToPostfix("(-3+ 4)* ((-2.8)/(1-5) ^ 2)");
  EXPECT_EQ(res, "3 ~ 4 + 2.8 ~ 1 5 - 2 ^ / *");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "-0.175");

  // -- -- -- --

  res = StrToPostfix("sin(2)*cos(2)*3+4*(25-5)");
  pols = CalculateNotation(res);
  EXPECT_EQ(res, "2 sin 2 cos * 3 * 4 25 5 - * +");

  // -- -- -- --

  res = StrToPostfix("sin(2)*cos(2)*");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "error");

  // -- -- -- --

  res = StrToPostfix("sin(2)*cos(2)*");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "error");

  // -- -- -- --

  res = StrToPostfix("32 * / 90- 1");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "error");

  // -- -- -- --

  res = StrToPostfix("32 % 3");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "2");

  // -- -- -- --

  res = StrToPostfix("32.939 % 3.329");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "2.978");

  // -- -- -- --

  res = StrToPostfix("3/+");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "error");

  // -- -- -- --

  res = StrToPostfix("cos(3) /cos(8)");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "6.8040705");

  // -- -- -- --

  res = StrToPostfix("asn(0.3) /asn(0.8)");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "0.3285821");

  // -- -- -- --

  res = StrToPostfix("sin(8.3) / sin(0.1)");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "9.036772");

  // -- -- -- --

  res = StrToPostfix("(tan(8.3)*atn(0.1))");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "-0.2084447");

  // -- -- -- --

  res = StrToPostfix("(acs(0.5)*ln(8.8))");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "2.2773946");

  // -- -- -- --

  res = StrToPostfix("(acs(0.5)^ln(8.8))");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "1.1054962");

  // -- -- -- --

  res = StrToPostfix("atn(0.3) + (-10) * sin(-10)");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "-5.1487543");

  // -- -- -- --

  res = StrToPostfix("*2");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "error");

  // -- -- -- --

  res = StrToPostfix("-(-42)+1");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "43");

  // -- -- -- --

  res = StrToPostfix("kk");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "error");

  // -- -- -- --

  res = StrToPostfix("2 + asn");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "error");

  // -- -- -- --

  res = StrToPostfix("kk");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "error");

  // -- -- -- --

  res = StrToPostfix("849.938 * sin(44) + 74.9 * ((40.9 * cos(20.8)) - 57.8)");
  EXPECT_EQ(res, "849.938 44 sin * 74.9 40.9 20.8 cos * 57.8 - * +");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "-5449.4537614");

  // -- -- -- --

  res = StrToPostfix("((2 + 3) * (asn(0.3) + 3))");
  EXPECT_EQ(res, "2 3 + 0.3 asn 3 + *");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "16.5234632");

  // -- -- -- --

  res = StrToPostfix("-(-(12 / 9 * 3) * 6)");
  pols = CalculateNotation(res);
  EXPECT_EQ(pols, "23.9999999");
}

// ----------------------------------------------------------------------------

TEST_F(PolishNotationTest, TestArifmeticOperation) {
  QString res = StrToPostfix("(-3 + 4) * ((2.8) / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 ~ 4 + 2.8 1 5 - 2 ^ / *");
  QString pol = CalculateNotation(res);

  res = StrToPostfix("tan(-10)");
  pol.clear();

  EXPECT_EQ(res, "10 ~ tan");
  pol = CalculateNotation(res);
  EXPECT_EQ(pol, "-0.6483608");

  // -- -- -- --

  res = StrToPostfix("tan(-9)");
  pol.clear();
  EXPECT_EQ(res, "9 ~ tan");

  pol = CalculateNotation(res);
  EXPECT_EQ(pol, "0.4523156");

  // -- -- -- --

  res = StrToPostfix("tan(-8)");
  pol.clear();
  EXPECT_EQ(res, "8 ~ tan");

  pol = CalculateNotation(res);
  EXPECT_EQ(pol, "6.7997114");

  // -- -- -- --

  res = StrToPostfix("tan(-7)");
  pol.clear();
  EXPECT_EQ(res, "7 ~ tan");

  pol = CalculateNotation(res);
  EXPECT_EQ(pol, "-0.8714479");

  // -- -- -- --

  res = StrToPostfix("*2");
  pol = CalculateNotation(res);
  EXPECT_EQ(pol, "error");

  // -- -- -- --

  res = StrToPostfix("**2");
  pol = CalculateNotation(res);
  EXPECT_EQ(pol, "error");

  // -- -- -- --

  res = StrToPostfix("2*");
  pol = CalculateNotation(res);
  EXPECT_EQ(pol, "error");

  res = StrToPostfix("2 + 2");
  pol = CalculateNotation(res);
  EXPECT_EQ(pol, "4");

  res = StrToPostfix("0");
  pol = CalculateNotation(res);
  EXPECT_EQ(pol, "0");

  // -- -- -- --

  res = StrToPostfix("9");
  pol = CalculateNotation(res);
  EXPECT_EQ(pol, "9");

  // -- -- -- --

  res = StrToPostfix("10");
  pol = CalculateNotation(res);
  EXPECT_EQ(pol, "10");
}

// ----------------------------------------------------------------------------

TEST_F(PolishNotationTest, TestXCoordinates) {
  QString res = StrToPostfix("2 * 2");
  EXPECT_EQ(res, "2 2 *");

  QString pol = CalculateNotation(res);
  EXPECT_EQ(pol, "4");

  res = StrToPostfix("2 * 2 + x");
  EXPECT_EQ(res, "2 2 * x +");
}

// ----------------------------------------------------------------------------
