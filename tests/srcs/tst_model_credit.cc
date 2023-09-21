#include "../includes/tst_model_credit.hpp"

void ModelCreditTest::CalculatorDifferent() {
  model_credit_->CalculatorDifferent();
}

void ModelCreditTest::Calculate() { model_credit_->Calculate(); }

// -- -- -- --

void ModelCreditTest::CalculatorAnnuit() { model_credit_->CalculatorAnnuit(); }
long double ModelCreditTest::get_mount() const { return model_credit_->mount_; }

// -- -- -- --

QString ModelCreditTest::MonthlyPayment() const {
  return model_credit_->MonthlyPayment();
}

// -- -- -- --

QString ModelCreditTest::AccruedInterest() const {
  return model_credit_->AccruedInterest();
}

// -- -- -- --

QString ModelCreditTest::DebgAndInterest() const {
  return model_credit_->DebgAndInterest();
}

// -- -- -- --

long double ModelCreditTest::get_mount_last() const {
  return model_credit_->mount_last_;
}

// -- -- -- --

long double ModelCreditTest::get_procents() const {
  return model_credit_->procents_;
}

// -- -- -- --

long double ModelCreditTest::get_total() const { return model_credit_->total_; }
void ModelCreditTest::set_sum(QString const &count) {
  model_credit_->set_sum(count);
}
void ModelCreditTest::set_different(bool const &is_dif) {
  model_credit_->set_different(is_dif);
}
void ModelCreditTest::set_is_mount(bool const &is_mount) {
  model_credit_->set_is_mount(is_mount);
}
void ModelCreditTest::set_procent(QString const &count) {
  model_credit_->set_procent(count);
}
void ModelCreditTest::set_time(QString const &count) {
  model_credit_->set_time(count);
}

// ----------------------------------------------------------------------------

TEST_F(ModelCreditTest, TestCreditDifferentYears) {
  set_sum("0");
  set_time("1");
  set_is_mount(true);
  set_procent("0");
  CalculatorDifferent();

  EXPECT_NEAR(get_mount(), 0.0, 0.001);
  EXPECT_NEAR(get_mount_last(), 0.0, 0.001);
  EXPECT_NEAR(get_procents(), 0.0, 0.001);
  EXPECT_NEAR(get_total(), 0.0, 0.001);

  // -- -- -- --

  set_sum("112300");
  set_time("2");
  set_is_mount(true);
  set_procent("9");
  CalculatorDifferent();

  EXPECT_NEAR(get_mount(), 5521.42, 0.001);
  EXPECT_NEAR(get_mount_last(), 4714.26, 0.001);
  EXPECT_NEAR(get_procents(), 10528.13, 0.001);
  EXPECT_NEAR(get_total(), 122828.13, 0.001);

  // -- -- -- --

  set_sum("240000");
  set_time("6");
  set_is_mount(true);
  set_procent("9");
  CalculatorDifferent();

  EXPECT_NEAR(get_mount(), 5133.33, 0.001);
  EXPECT_NEAR(get_mount_last(), 3358.33, 0.001);
  EXPECT_NEAR(get_procents(), 65700.00, 0.001);
  EXPECT_NEAR(get_total(), 305700.00, 0.001);

  // -- -- -- --

  set_sum("112300");
  set_time("2");
  set_is_mount(true);
  set_procent("9");
  CalculatorDifferent();

  EXPECT_NEAR(get_mount(), 5521.42, 0.001);
  EXPECT_NEAR(get_mount_last(), 4714.26, 0.001);
  EXPECT_NEAR(get_procents(), 10528.13, 0.001);
  EXPECT_NEAR(get_total(), 122828.13, 0.001);

  // -- -- -- --

  set_sum("3830000");
  set_time("12");
  set_is_mount(true);
  set_procent("14");
  CalculatorDifferent();

  EXPECT_NEAR(get_mount(), 71280.56, 0.001);
  EXPECT_NEAR(get_mount_last(), 26907.52, 0.001);
  EXPECT_NEAR(get_procents(), 3239541.67, 0.001);
  EXPECT_NEAR(get_total(), 7069541.67, 0.001);
}

// ----------------------------------------------------------------------------

TEST_F(ModelCreditTest, TestCreditDifferentMount) {
  set_sum("240000");
  set_time("6");
  set_is_mount(false);
  set_procent("9");
  CalculatorDifferent();

  EXPECT_NEAR(get_mount(), 41800.00, 0.001);
  EXPECT_NEAR(get_mount_last(), 40300.00, 0.001);
  EXPECT_NEAR(get_procents(), 6300.00, 0.001);
  EXPECT_NEAR(get_total(), 246300.00, 0.001);

  // -- -- -- --

  set_sum("240000");
  set_time("6");
  set_is_mount(true);
  set_procent("9");
  CalculatorDifferent();

  EXPECT_NEAR(get_mount(), 5133.33, 0.001);
  EXPECT_NEAR(get_mount_last(), 3358.33, 0.001);
  EXPECT_NEAR(get_procents(), 65700.00, 0.001);
  EXPECT_NEAR(get_total(), 305700.00, 0.001);

  set_different(true);
  Calculate();

  EXPECT_NEAR(get_mount(), 5133.33, 0.001);
  EXPECT_NEAR(get_mount_last(), 3358.33, 0.001);
  EXPECT_NEAR(get_procents(), 65700.00, 0.001);
  EXPECT_NEAR(get_total(), 305700.00, 0.001);

  set_different(false);
  Calculate();

  EXPECT_NEAR(get_mount(), 4326.13, 0.001);
  EXPECT_NEAR(get_procents(), 71481.36, 0.001);
  EXPECT_NEAR(get_total(), 311481.36, 0.001);

  qDebug() << "month: " << MonthlyPayment();
  qDebug() << "accrued: " << AccruedInterest();
  qDebug() << "Debg: " << DebgAndInterest();

  EXPECT_EQ(MonthlyPayment(), "4 326.13");
  EXPECT_EQ(AccruedInterest(), "71 481.36");
  EXPECT_EQ(DebgAndInterest(), "311 481.36");

  // -- -- -- --

  set_sum("2300");
  set_time("6");
  set_is_mount(false);
  set_procent("9");
  CalculatorDifferent();

  EXPECT_NEAR(get_mount(), 400.58, 0.001);
  EXPECT_NEAR(get_mount_last(), 386.201, 0.01);
  EXPECT_NEAR(get_procents(), 60.38, 0.001);
  EXPECT_NEAR(get_total(), 2360.38, 0.001);

  // -- -- -- --

  set_sum("3830000");
  set_time("78");
  set_is_mount(false);
  set_procent("14");
  CalculatorDifferent();

  EXPECT_NEAR(get_mount(), 93785.90, 0.001);
  EXPECT_NEAR(get_mount_last(), 49675.43, 0.001);
  EXPECT_NEAR(get_procents(), 1764991.67, 0.001);
  EXPECT_NEAR(get_total(), 5594991.67, 0.001);

  // -- -- -- --

  set_sum("93830000");
  set_time("94");
  set_is_mount(false);
  set_procent("23");
  CalculatorDifferent();

  EXPECT_NEAR(get_mount(), 2796599.82, 0.001);
  EXPECT_NEAR(get_mount_last(), 1017323.49, 0.001);
  EXPECT_NEAR(get_procents(), 85424395.83, 0.001);
  EXPECT_NEAR(get_total(), 179254395.83, 0.001);
}

// ----------------------------------------------------------------------------

TEST_F(ModelCreditTest, TestCreditAnnuitMount) {
  set_sum("20000");
  set_time("36");
  set_is_mount(false);
  set_procent("12");
  CalculatorAnnuit();

  EXPECT_NEAR(get_mount(), 664.29, 0.001);
  EXPECT_NEAR(get_procents(), 3914.44, 0.001);
  EXPECT_NEAR(get_total(), 23914.44, 0.001);

  // -- -- -- --

  set_sum("2000");
  set_time("48");
  set_is_mount(false);
  set_procent("48");
  CalculatorAnnuit();

  EXPECT_NEAR(get_mount(), 94.36, 0.001);
  EXPECT_NEAR(get_procents(), 2529.28, 0.001);
  EXPECT_NEAR(get_total(), 4529.28, 0.001);

  // -- -- -- --

  set_sum("30000");
  set_time("6");
  set_is_mount(false);
  set_procent("9");
  CalculatorAnnuit();

  EXPECT_NEAR(get_mount(), 5132.07, 0.001);
  EXPECT_NEAR(get_procents(), 792.42, 0.001);
  EXPECT_NEAR(get_total(), 30792.42, 0.001);
}

// ----------------------------------------------------------------------------

TEST_F(ModelCreditTest, TestCreditAnnuitYears) {
  set_sum("20000");
  set_time("18");
  set_is_mount(true);
  set_procent("12");
  CalculatorAnnuit();

  EXPECT_NEAR(get_mount(), 226.39, 0.001);
  EXPECT_NEAR(get_procents(), 28900.24, 0.001);
  EXPECT_NEAR(get_total(), 48900.24, 0.001);

  // -- -- -- --

  set_sum("2000");
  set_time("4");
  set_is_mount(true);
  set_procent("48");
  CalculatorAnnuit();

  EXPECT_NEAR(get_mount(), 94.36, 0.001);
  EXPECT_NEAR(get_procents(), 2529.28, 0.001);
  EXPECT_NEAR(get_total(), 4529.28, 0.001);

  // -- -- -- --

  set_sum("30000");
  set_time("12");
  set_is_mount(true);
  set_procent("9");
  CalculatorAnnuit();

  EXPECT_NEAR(get_mount(), 341.41, 0.001);
  EXPECT_NEAR(get_procents(), 19163.04, 0.001);
  EXPECT_NEAR(get_total(), 49163.04, 0.001);

  // MonntlyPayment && AccruedInterest &&DebgAndIntereset
}

// ----------------------------------------------------------------------------
