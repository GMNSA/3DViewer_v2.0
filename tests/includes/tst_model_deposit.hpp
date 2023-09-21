#ifndef TESTS_TEST_MODEL_DEPOSIT_INCLUDES_TST_MODEL_DEPOSIT_HPP_
#define TESTS_TEST_MODEL_DEPOSIT_INCLUDES_TST_MODEL_DEPOSIT_HPP_

#include <gtest/gtest.h>

#include <QDebug>

#include "../includes/Model/modeldeposit.hpp"
#include "../includes/custom_types.hpp"

class ModelDepositTest : public ::testing::Test {
 public:
  ModelDepositTest() : model_deposit_(new s21::ModelDeposit) {
    // initialization code here
  }

  void SetUp() {
    // code here will execute just before the test ensues
  }

  void TearDown() {
    // code here will be called just after the test completes
    // ok to through exceptions from here if need be
  }

  ~ModelDepositTest() {
    // cleanup any pending stuff, but no exceptions allowed
    if (model_deposit_) delete model_deposit_;
  }

  void SettingOne(QString const &deposit_sum, QString const &percent_rate,
                  QString const &placement_period, QString const &tax_rate);

  void SettingTwo(
      s21::PeriodicityPayments const &pp = s21::PeriodicityPayments::kOnce,
      s21::Capitalization const &cap = s21::Capitalization::kNo);
  void SettingThree(QListWidget *top_up_account = nullptr,
                    QListWidget *widthdraw_from_account = nullptr);

  void Calculate();
  QString get_total_amount() const;
  QString get_amount_taxes() const;
  QString get_total_deposit_amount() const;
  QString get_accrued_interest() const;
  QString get_withdrawal_amount() const;
  // put in any custom data members that you need
 private:
  s21::ModelDeposit *model_deposit_;
};

#endif  // TESTS_TEST_MODEL_DEPOSIT_INCLUDES_TST_MODEL_DEPOSIT_HPP_
