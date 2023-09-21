#include <gtest/gtest.h>

#include <QDebug>

#include "../includes/tst_model_calculator.hpp"
#include "../includes/tst_model_credit.hpp"
#include "../includes/tst_model_deposit.hpp"
#include "../includes/tst_polishnotation.hpp"
#include "../includes/tst_validatortext.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
