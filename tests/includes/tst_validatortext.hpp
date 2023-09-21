#ifndef TESTS_TEST_VALIDATETEXT_INCLUDES_TST_VALIDATORTEXT_HPP_
#define TESTS_TEST_VALIDATETEXT_INCLUDES_TST_VALIDATORTEXT_HPP_

#include <gtest/gtest.h>

#include <QDebug>

#include "../includes/Model/validatetext.hpp"

class ValidatorTextTest : public ::testing::Test {
 public:
  ValidatorTextTest() : validator_text_(new s21::ValidateText()) {
    // initialization code here
  }

  void SetUp() {
    // code here will execute just before the test ensues
  }

  void TearDown() {
    // code here will be called just after the test completes
    // ok to through exceptions from here if need be
  }

  ~ValidatorTextTest() {
    // cleanup any pending stuff, but no exceptions allowed
    if (validator_text_) delete validator_text_;
  }

  // put in any custom data members that you need
 public:
  s21::ValidateText *validator_text_;
};

#endif  // TESTS_TEST_VALIDATETEXT_INCLUDES_TST_VALIDATORTEXT_HPP_
