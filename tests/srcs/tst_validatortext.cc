#include "../includes/tst_validatortext.hpp"

#include <gtest/gtest.h>

#include <QHash>
#include <QRegularExpression>
#include <QStack>

TEST_F(ValidatorTextTest, TestFixFunc) {
  QString res;

  validator_text_->Reset();
  res = validator_text_->ReplaceDummyFunctions("32 - 3");
  EXPECT_EQ(res, "32 - 3");

  res = validator_text_->ReplaceDummyFunctions("32 - 3 - 3");
  EXPECT_EQ(res, "32 - 3 - 3");
}

TEST_F(ValidatorTextTest, TestConsistently) {
  QString res;
  validator_text_->Reset();
  validator_text_->AddText("32 - 3");
  res = validator_text_->get_text();
  EXPECT_EQ(res, "32 - 3");

  res = validator_text_->ReplaceDummyFunctions(res);
  EXPECT_EQ(res, "32 - 3");

  res = validator_text_->FixedText(res);
  EXPECT_EQ(res, "32 - 3");

  // -- -- -- --

  validator_text_->AddText("-");
  res = validator_text_->get_text();
  EXPECT_EQ(res, "32 - 3-");

  res = validator_text_->ReplaceDummyFunctions(res);
  EXPECT_EQ(res, "32 - 3-");

  res = validator_text_->FixedText(res);
  EXPECT_EQ(res, "32 - 3-");

  // -- -- -- --

  validator_text_->AddText("3");
  res = validator_text_->get_text();
  EXPECT_EQ(res, "32 - 3-3");

  res = validator_text_->ReplaceDummyFunctions(res);
  EXPECT_EQ(res, "32 - 3-3");

  res = validator_text_->FixedText(res);
  EXPECT_EQ(res, "32 - 3 - 3");

  // -- -- -- --

  validator_text_->Reset();

  validator_text_->AddText("32 - 3 - 3");
  res = validator_text_->get_text();
  EXPECT_EQ(res, "32 - 3 - 3");

  res = validator_text_->ReplaceDummyFunctions(res);
  EXPECT_EQ(res, "32 - 3 - 3");

  res = validator_text_->FixedText(res);
  EXPECT_EQ(res, "32 - 3 - 3");
}

TEST_F(ValidatorTextTest, TestSimpleNumbers) {
  QString res;

  validator_text_->Reset();
  validator_text_->AddTextToStr("32");
  validator_text_->AddTextToStr(" + ");
  validator_text_->AddTextToStr("4");
  res = validator_text_->get_text();
  EXPECT_EQ(res, "32 + 4");

  validator_text_->AddTextToStr("*");
  validator_text_->AddTextToStr("8");

  res = validator_text_->get_text();
  EXPECT_EQ(res, "32 + 4 * 8");

  validator_text_->AddTextToStr("/");
  validator_text_->AddTextToStr("8.9384");

  res = validator_text_->get_text();
  EXPECT_EQ(res, "32 + 4 * 8 / 8.9384");

  validator_text_->AddTextToStr(" ");

  res = validator_text_->get_text();
  EXPECT_EQ(res, "32 + 4 * 8 / 8.9384");

  validator_text_->AddTextToStr(" 3.2");
  validator_text_->AddTextToStr("9.2");
  res = validator_text_->get_text();

  validator_text_->Reset();
  validator_text_->AddTextToStr("32");
  validator_text_->AddTextToStr("-");
  validator_text_->AddTextToStr("3");
  res = validator_text_->get_text();
  EXPECT_EQ(res, "32 - 3");

  // validator_text_->AddTextToStr("-");
  // validator_text_->AddTextToStr("3");
  // qDebug() << "res: " << res;
  // EXPECT_EQ(res, "32 - 3 - 3");
}

// ----------------------------------------------------------------------------

TEST_F(ValidatorTextTest, TestSmartBrackets) {
  QString res;

  validator_text_->SetBrackets("(", 1, 1);
  validator_text_->AddTextToStr("3.2");
  validator_text_->AddTextToStr(" + ");
  validator_text_->AddTextToStr("4.8");
  validator_text_->SetBrackets("(", 1, 1);

  res = validator_text_->get_text();
  EXPECT_EQ(res, "(3.2 + 4.8)");

  // -- -- -- --

  validator_text_->AddTextToStr("/ ");
  validator_text_->AddTextToStr("8");
  validator_text_->AddTextToStr(" *");
  validator_text_->SetBrackets("(", 1, 1);
  validator_text_->AddTextToStr("13.2");
  validator_text_->AddTextToStr(" + ");
  validator_text_->AddTextToStr("7.77");
  validator_text_->SetBrackets("(", 1, 1);

  res = validator_text_->get_text();
  EXPECT_EQ(res, "(3.2 + 4.8) / 8 * (13.2 + 7.77)");

  validator_text_->Reset();
  res = validator_text_->get_text();
  EXPECT_EQ(res, "");

  // -- -- -- --

  validator_text_->SetBrackets("    )", 1, 1);
  validator_text_->AddTextToStr("3.2");
  validator_text_->AddTextToStr(" + ");
  validator_text_->AddTextToStr("4.8");
  validator_text_->SetBrackets("(", 1, 1);
  validator_text_->AddTextToStr("/ ");
  validator_text_->AddTextToStr("8");
  validator_text_->AddTextToStr(" *");
  validator_text_->SetBrackets(")", 1, 1);
  validator_text_->AddTextToStr("13.2");
  validator_text_->AddTextToStr(" + ");
  validator_text_->AddTextToStr("7.77");
  validator_text_->SetBrackets(" )", 1, 1);

  res = validator_text_->get_text();
  EXPECT_EQ(res, "(3.2 + 4.8) / 8 * (13.2 + 7.77)");
}

// ----------------------------------------------------------------------------

TEST_F(ValidatorTextTest, TestSimpleBrackets) {
  QString res;

  validator_text_->Reset();
  validator_text_->SetBrackets("(", 0, 0);
  validator_text_->AddTextToStr("3.2");
  validator_text_->AddTextToStr(" + ");
  validator_text_->AddTextToStr("4.8");
  validator_text_->SetBrackets("(", 0, 0);

  res = validator_text_->get_text();
  EXPECT_EQ(res, "(3.2 + 4.8(");
  validator_text_->Reset();

  // -- -- -- --

  validator_text_->SetBrackets("(", 0, 0);
  validator_text_->AddTextToStr("3.2");
  validator_text_->AddTextToStr(" + ");
  validator_text_->AddTextToStr("4.8");
  validator_text_->AddTextToStr("*");
  validator_text_->SetBrackets("(", 0, 0);
  validator_text_->AddTextToStr("33.2");
  validator_text_->AddTextToStr("/");
  validator_text_->AddTextToStr("4");
  validator_text_->SetBrackets(")", 0, 0);
  validator_text_->AddTextToStr("+");
  validator_text_->AddTextToStr("8");
  validator_text_->SetBrackets(")", 0, 0);

  res = validator_text_->get_text();
  EXPECT_EQ(res, "(3.2 + 4.8 * (33.2 / 4) + 8)");
}

// ----------------------------------------------------------------------------

TEST_F(ValidatorTextTest, TestFunction) {
  QString res;

  validator_text_->Reset();
  validator_text_->SetBrackets("(", 1, 1);
  validator_text_->AddTextToStr("atan(");
  validator_text_->AddTextToStr("3.2");
  validator_text_->SetBrackets("(", 1, 1);
  validator_text_->AddTextToStr(" + ");
  validator_text_->AddTextToStr("4.8");
  validator_text_->SetBrackets("(", 1, 1);

  res = validator_text_->get_text();
  EXPECT_EQ(res, "(atn(3.2) + 4.8)");
}

// ----------------------------------------------------------------------------
