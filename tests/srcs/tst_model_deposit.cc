#include "../includes/tst_model_deposit.hpp"

void ModelDepositTest::SettingOne(QString const &deposit_sum,
                                  QString const &percent_rate,
                                  QString const &placement_period,
                                  QString const &tax_rate) {
  model_deposit_->set_deposit_sum(deposit_sum);
  model_deposit_->set_percent_rate(percent_rate);
  model_deposit_->set_placement_period(placement_period);
  model_deposit_->set_tax_rate(tax_rate);
}

// -- -- -- --
void ModelDepositTest::SettingTwo(s21::PeriodicityPayments const &pp,
                                  s21::Capitalization const &cap) {
  model_deposit_->set_frequency_payments(pp);
  model_deposit_->set_capitalization(cap);
}
// -- -- -- --
void ModelDepositTest::SettingThree(QListWidget *top_up_account,
                                    QListWidget *widthdraw_from_account) {
  model_deposit_->set_top_up_account(top_up_account);
  model_deposit_->set_widthdraw_from_account(widthdraw_from_account);
}
// -- -- -- --
void ModelDepositTest::Calculate() { model_deposit_->Calculate(); }
// -- -- -- --
QString ModelDepositTest::get_total_amount() const {
  return model_deposit_->get_total_amount();
}
// -- -- -- --
QString ModelDepositTest::get_amount_taxes() const {
  return model_deposit_->get_amount_taxes();
}
// -- -- -- --
QString ModelDepositTest::get_total_deposit_amount() const {
  return model_deposit_->get_total_deposit_amount();
}
// -- -- -- --
QString ModelDepositTest::get_accrued_interest() const {
  return model_deposit_->get_accrued_interest();
}
// -- -- -- --
QString ModelDepositTest::get_withdrawal_amount() const {
  return model_deposit_->get_withdrawal_amount();
}

// ----------------------------------------------------------------------------

TEST_F(ModelDepositTest, TestBase) {
  SettingOne("100000", "10", "12", "0");
  SettingTwo();
  SettingThree();

  Calculate();
  EXPECT_EQ(get_total_amount(), "110000.00");
  EXPECT_EQ(get_accrued_interest(), "10000.00");
  EXPECT_EQ(get_amount_taxes(), "0.00");

  SettingOne("100000", "10", "6", "0");

  Calculate();
  EXPECT_EQ(get_total_amount(), "105000.00");
  EXPECT_EQ(get_accrued_interest(), "5000.00");
  EXPECT_EQ(get_amount_taxes(), "0.00");

  SettingOne("1000000", "8", "12", "0");

  Calculate();
  EXPECT_EQ(get_total_amount(), "1080000.00");
  EXPECT_EQ(get_accrued_interest(), "80000.00");
  EXPECT_EQ(get_amount_taxes(), "0.00");

  // -- -- -- --

  // SettingOne("100000", "10", "12", "0");
  // SettingTwo();
  // QListWidget *w = new QListWidget;
  // Q_UNUSED(w);
  // w->addItem("8000");
  // w->addItem("800");
  // SettingThree(w);

  // Calculate();
  // EXPECT_EQ(get_accrued_interest(), "10880.00");
  // EXPECT_EQ(get_amount_taxes(), "0.00");
  // EXPECT_EQ(get_total_amount(), "119680.00");

  // -- -- -- --

  // SettingOne("100000", "10", "6", "0");
  // w->addItem("700");
  // w->addItem("333");
  // SettingThree(nullptr, w);

  // Calculate();
  // EXPECT_EQ(get_accrued_interest(), "4948.35");
  // EXPECT_EQ(get_amount_taxes(), "0.00");
  // EXPECT_EQ(get_total_amount(), "103915.35");

  // if (w) delete w;

  // -- -- -- --

  SettingOne("1000000", "8", "12", "0");

  Calculate();
  EXPECT_EQ(get_total_amount(), "1080000.00");
  EXPECT_EQ(get_accrued_interest(), "80000.00");
  EXPECT_EQ(get_amount_taxes(), "0.00");
}

// -- -- -- --

TEST_F(ModelDepositTest, TestCapitalization) {
  SettingOne("100000", "10", "12", "0");
  SettingTwo(s21::PeriodicityPayments::kOnce, s21::Capitalization::kMontly);
  SettingThree();

  Calculate();
  EXPECT_EQ(get_accrued_interest(), "10000.00");
  EXPECT_EQ(get_amount_taxes(), "0.00");
  EXPECT_EQ(get_total_amount(), "110000.00");

  SettingTwo(s21::PeriodicityPayments::kMontly, s21::Capitalization::kMontly);
  Calculate();
  EXPECT_EQ(get_total_amount(), "110471.31");
  EXPECT_EQ(get_amount_taxes(), "0.00");
  EXPECT_EQ(get_accrued_interest(), "10471.31");

  SettingOne("1000000", "8", "12", "0");

  Calculate();
  EXPECT_EQ(get_total_amount(), "1082999.51");
  EXPECT_EQ(get_accrued_interest(), "82999.51");
  EXPECT_EQ(get_amount_taxes(), "0.00");
}

// -- -- -- --

TEST_F(ModelDepositTest, TestTaxes) {
  SettingOne("100000", "23", "21", "1");
  SettingTwo(s21::PeriodicityPayments::kOnce, s21::Capitalization::kMontly);
  SettingThree();

  Calculate();
  EXPECT_EQ(get_total_amount(), "136317.50");
  EXPECT_EQ(get_accrued_interest(), "40250.00");
  EXPECT_EQ(get_amount_taxes(), "3932.50");
}

// ----------------------------------------------------------------------------
